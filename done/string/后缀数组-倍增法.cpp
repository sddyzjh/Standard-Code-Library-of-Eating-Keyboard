#define MAXN 100000     //字符串长度

//da函数:s为输入的字符串,sa为结果数组,slen为s长度,m为字符串中字符的最大值+1
//调用前应将s[slen]设为0,因此调用时slen为s长度+1

//calHeight函数:返回sa中排名相邻的两个后缀的最长公共前缀

int cmp(int *s, int a, int b, int l) {
    return (s[a] == s[b]) && (s[a + l] == s[b + l]);
}

int wa[MAXN], wb[MAXN], ws[MAXN], wv[MAXN];
void da(int *s, int *sa, int slen, int m) {
    int i, j, p, *x = wa, *y = wb, *t;
    for (i = 0; i < m; i++) ws[i] = 0;
    for (i = 0; i < slen; i++) ws[x[i] = s[i]]++;
    for (i = 1; i < m; i++) ws[i] += ws[i - 1];
    for (i = slen - 1; i >= 0; i--) sa[--ws[x[i]]] = i;
    for (j = 1, p = 1; p < slen; j *= 2, m = p)
    {
        for (p = 0, i = slen - j; i < slen; i++) y[p++] = i;
        for (i = 0; i < slen; i++) if (sa[i] >= j) y[p++] = sa[i] - j;
        for (i = 0; i < slen; i++) wv[i] = x[y[i]];
        for (i = 0; i < m; i++) ws[i] = 0;
        for (i = 0; i < slen; i++) ws[wv[i]]++;
        for (i = 1; i < m; i++) ws[i] += ws[i - 1];
        for (i = slen - 1; i >= 0; i--) sa[--ws[wv[i]]] = y[i];
        for (t = x, x = y, y = t, p = 1, x[sa[0]] = 0, i = 1; i < slen; i++)
            x[sa[i]] = cmp(y, sa[i - 1], sa[i], j) ? p - 1 : p++;
    }
}

//---------------------------------------------------------
int rank[MAXN], height[MAXN];
void calHeight(int *s, int *sa, int slen) {
    int i, j, k = 0;
    for (i = 1; i <= slen; i++) rank[sa[i]] = i;
    for (i = 0; i < slen; height[rank[i++]] = k )
        for (k ? k-- : 0, j = sa[rank[i] - 1]; s[i + k] == s[j + k]; k++);
}
//---------------------------------------------------------
