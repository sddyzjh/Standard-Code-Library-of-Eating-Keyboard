/// 康托展开.
/// 从一个排列映射到排列的rank.
/// power : 阶乘数组.
///////////////////////////////////////////////////////////
int power[21];
/// 康托展开, 排名从0开始.
/// 输入为字符串, 其中的字符根据ascii码比较大小.
/// 可以将该字符串替换成其它线序集合中的元素的排列.
int Cantor(const char* c, int len)
{
    int res = 0;
    for(int i=0; i<len; i++)
    {
        int rank = 0;
        for(int j=i; j<len; j++) if(c[j] < c[i]) rank++;
        res += rank * power[len - i - 1];
    }
    return res;
}
bool cused[21]; // 该数组大小应为字符集的大小.
/// 逆康托展开, 排名从0开始.
/// 输出排名为rank的, 长度为len的排列.
void RevCantor(int rank, char* c, int len)
{
    for(int i=0; i<len; i++) cused[i] = false;
    for(int i=0; i<len; i++)
    {
        int cnt = rank / power[len - i - 1];
        rank %= power[len - i - 1];
        cnt++;
        int num = 0;
        while(true)
        { 
            if(!cused[num]) cnt--;
            if(cnt == 0) break;
            num++;
        }
        cused[num] = true;
        c[i] = num + 'a'; // 输出字符串, 从a开始.
    }
}
/// 阶乘数组初始化.
int main()
{
    power[0] = power[1] = 1;
    for(int i=0; i<20; i++) power[i] = i * power[i-1];
    ...
}