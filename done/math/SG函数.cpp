#define MAX 150 //最大的步数
int step[MAX], sg[10500], steps;    //使用前应将sg初始化为-1
//step:所有可能的步数，要求从小到大排序
//steps:step的大小
//sg:存储sg的值
int getsg(int m){
    int hashs[MAX] = {0};
    int i;
    for (i = 0; i < steps; i++){
        if (m - step[i] < 0) {
            break;
        }
        if (sg[m - step[i]] == -1) {
            sg[m - step[i]] = getsg(m - step[i]);
        }
        hashs[sg[m - step[i]]] = 1;
    }
    for (i = 0;; i++) {
        if (hashs[i] == 0) {
            return i;
        }
    }
}

/*
Array(存储可以走的步数，Array[0]表示可以有多少种走法)
Array[]需要从小到大排序
1.可选步数为1-m的连续整数，直接取模即可，SG(x)=x%(m+1);
2.可选步数为任意步，SG(x) = x;
3.可选步数为一系列不连续的数，用GetSG(计算)
*/
//获取sg表
int SG[MAX], hashs[MAX];

void init(int Array[], int n){
    int i, j;
    memset(SG, 0, sizeof(SG));
    for (i = 0; i <= n; i++){
        memset(hashs, 0, sizeof(hashs));
        for (j = 1; j <= Array[0]; j++){
            if (i < Array[j]) {
                break;
            }
            hashs[SG[i - Array[j]]] = 1;
        }
        for (j = 0; j <= n; j++){
            if (hashs[j] == 0){
                SG[i] = j;
                break;
            }
        }
    }
}