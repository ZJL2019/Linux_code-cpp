class Solution {
public:
	void replaceSpace(char *str,int length)
    {
        if(str==NULL)
        {
            return;
        }
        int allcounts=0;
        int countblocks=0;
        for(int i=0;i<length;i++)
        {
            ++allcounts;
            if(str[i]==' ')
            {
                ++countblocks;
            }
        }
        int len=allcounts+2*countblocks;
        char* pstr1=str+allcounts;
        char* pstr2=str+len;
        while(pstr1<pstr2)
        {
            if(*pstr1==' ')
            {
                *pstr2--='0';
                *pstr2--='2';
                *pstr2--='%';
            }
            else
            {
                *pstr2--=*pstr1;
            }
            pstr1--;
        }
	}
};