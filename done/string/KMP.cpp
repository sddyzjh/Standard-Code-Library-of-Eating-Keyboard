//KMP算法
//查找成功则返回所在位置(int),否则返回-1.

#define MAXM 100000000  //字符串最大长度

void getNext(char *p, char *next)
{
    int j = 0;
    int k = -1;
    next[0] = -1;
    while (j < n)
    {
        if (k == -1 || p[j] == p[k])
        {
            j++;
            k++;
            next[j] = k;
        }
        else
            k = next[k];
    }
}

int KMP(char *s, char *p,int m,int n)   //查找成功则返回所在位置(int),否则返回-1.
{                           //s为文本串,p为模式串;m为文本串长度,n为模式串长度.
    char next[MAXM];
    int i = 0;
    int j = 0;
    getNext(p, next);
    while (i < m)
    {
        if (j == -1 || s[i] == p[j])
        {
            i++;
            j++;
        }
        else
            j = next[j];
        if (j == n)
            return i - n + 1;
    }
    return -1;
}
