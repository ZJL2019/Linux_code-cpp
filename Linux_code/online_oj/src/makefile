LDFLAGS=-L /home/jaler/work/library/third_part/lib
DEBUGFLAGS=-g
BIN=../bin/oj_server
CC=g++

.PHONY:$(BIN)

$(BIN):oj_server.cpp
	g++ $^ -o $@ $(DEBUGFLAGS) $(LDFLAGS) -lpthread -lctemplate -ljsoncpp

.PHONY:clean

clean:
	rm -f $(BIN)
