package main

import (
	"database/sql"
	"github.com/gin-gonic/gin"
	_ "github.com/go-sql-driver/mysql"
	"log"
	"net/http"
)

func main() {
	//连金额数据库
	db, err := sql.Open("mysql","root:123456@tcp(127.0.0.1:3306)/commodity_info")
	if err != nil {
		log.Fatalln(err)
	}

	//连接最大数
	db.SetMaxIdleConns(20)
	db.SetMaxOpenConns(20)

	if err := db.Ping(); err !=nil {
		log.Fatalln(err)
	}

	//所有商品信息
	router := gin.Default()
	router.GET("/commoditys", func(c *gin.Context) {
		allcommodity(db,c)
	})

	//所有订单信息
	router.GET("/orders", func(c *gin.Context) {
		allorder(db,c)
	})

	//添加订单
	router.POST("/add_order", func(c *gin.Context) {
		AddOrder(db,c)
	})

	router.Run(":8080")
}

//商品结构体
type Commodity struct {
	ID int `json:"商品编号" form:"商品编号"`
	Name string `json:"商品名称" form:"商品名称"`
	Price int `json:"商品单价" form:"商品单价"`
	Number int `json:"商品数量" form:"商品数量"`
}

//订单结构体
type Order struct {
	Order_ID int `json:"订单编号" form:"订单编号"`
	ID int `json:"商品编号" form:"商品编号"`
	Name string `json:"商品名称" form:"商品名称"`
	Number int `json:"商品数量" form:"商品数量"`
	Price int `json:"商品单价" form:"商品单价"`
	All_Price int `json:"订单价值" form:"订单价值"`
}

//查询所有商品信息
func allcommodity(db *sql.DB,c *gin.Context) {
	//查询所有商品信息
	rows, err := db.Query("select * from commodity")
	if err != nil {
		log.Fatalln(err)
		return
	}
	defer rows.Close()

	//创建分片
	commoditys := make([]Commodity,0)

	//便利遍历查询结果
	for rows.Next(){
		var commodity Commodity
		rows.Scan(&commodity.ID, &commodity.Name, &commodity.Price, &commodity.Number)
		commoditys = append(commoditys, commodity)
	}
	if err = rows.Err(); err != nil {
		log.Fatalln(err)
		return
	}

	//组织响应
	c.JSON(http.StatusOK, gin.H{
		"commoditys":commoditys,
	})
}


//查询所有订单信息
func allorder (db *sql.DB, c *gin.Context) {
	//查询所有订单信息
	rows, err := db.Query("select * from orders")
	if err != nil{
		log.Fatalln(err)
		return
	}
	defer rows.Close()

	//创建分片
	orders := make([]Order,0)

	//遍历查询结果
	for rows.Next(){
		var order Order
		rows.Scan(&order.Order_ID,&order.ID,&order.Name,&order.Number,&order.Price,&order.All_Price)
		orders = append(orders,order)
	}
	if err = rows.Err(); err !=nil {
		log.Fatalln(err)
		return
	}

	//组织响应
	c.JSON(http.StatusOK,gin.H{
		"orders":orders,
	})
}

//POST添加订单绑定
type PostFrom struct {
	ID int `form:"id" json:"id" binding:"required"`
	Number int `form:"number" json:"number" binding:"required"`
}

//添加订单
func AddOrder(db *sql.DB, c *gin.Context){
	//获取body数据
	var postfrom PostFrom
	if c.ShouldBind(&postfrom) ==nil{
		//创建商品结构体存储结果
		var commodity Commodity
		//查询单条数据
		err := db.QueryRow("select * from commodity where 商品编号=?",postfrom.ID).Scan(
			&commodity.ID, &commodity.Name, &commodity.Price, &commodity.Number,
		)
		if err!=nil {
			log.Fatalln(err)
			return
		}

		//判断是否有足够的商品数量
		if commodity.Number==0{
			c.JSON(http.StatusOK,gin.H{
				"err":"commodity's number is empty!",
			})
			return
		} else if  postfrom.Number > commodity.Number{
			postfrom.Number = commodity.Number
		}

		//创建订单结构体存储结果
		var order Order
		//查询订单数，确认当前订单编号
		err = db.QueryRow("select count(订单号) from orders").Scan(&order.Order_ID)
		if err!=nil{
			log.Fatalln(err)
			return
		}
		//组织订单数据
		order.Order_ID += 1
		order.ID = commodity.ID
		order.Name = commodity.Name
		order.Number = postfrom.Number
		order.Price = commodity.Price
		order.All_Price = commodity.Price * order.Number

		//插入订单数据
		_, err = db.Exec("insert into orders(商品编号, 商品名称, 商品数量, 商品单价, 订单总价)values (?,?,?,?,?)",
			order.ID,order.Name,order.Number,order.Price,order.All_Price)
		if err != nil{
			log.Fatalln(err)
			return
		}

		//更新对应的商品数量
		_, err = db.Exec("update commodity set 商品数量=? where 商品编号=?",commodity.Number-order.Number,postfrom.ID)
		if err != nil{
			log.Fatalln(err)
			return
		}

		//查询修改后的商品信息
		err = db.QueryRow("select * from commodity where 商品编号=?",postfrom.ID).Scan(
			&commodity.ID, &commodity.Name, &commodity.Price, &commodity.Number,
		)

		//组织响应
		c.JSON(http.StatusOK, gin.H{
			"order":order,
			"commodity":commodity,
		})
	}
}
