//使用getExtend获取extend数组(s[i]...s[n-1]与t的最长公共前缀的长度)
//s,t,slen,tlen,分别为对应字符串及其长度.
//next数组返回t[i]...t[m-1]与t的最长公共前缀长度,调用时需要提前开辟空间
void getNext(char* t, int tlen, int* next){
    next[0] = tlen;
    int a;
    int p;
    for (int i = 1, j = -1; i < tlen; i++, j--){
        if (j < 0 || i + next[i - a] >= p){
            if (j < 0) {
                p = i;
                j = 0;
            }
            while (p < tlen && t[p] == t[j]) {
                p++;
                j++;
            }
            next[i] = j;
            a = i;
        }
        else {
            next[i] = next[i - a];
        }
    }
}
void getExtend(char* s, int slen, char* t, int tlen, int* extend, int* next){
    getNext(t, next);
    int a;
    int p;
    for (int i = 0, j = -1; i < slen; i++, j--){
        if (j < 0 || i + next[i - a] >= p){
            if (j < 0) {
                p = i, j = 0;
            }
            while (p < slen && j < tlen && s[p] == t[j]) {
                p++;
                j++;
            }
            extend[i] = j;
            a = i;
        }
        else {
            extend[i] = next[i - a];
        }
    }
}