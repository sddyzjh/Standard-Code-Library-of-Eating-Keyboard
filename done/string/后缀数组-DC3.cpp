//dc3函数:s为输入的字符串,sa为结果数组,slen为s长度,m为字符串中字符的最大值+1
//s及sa数组的大小应为字符串大小的3倍.

#define MAXN 100000  //字符串长度

#define F(x) ((x)/3+((x)%3==1?0:tb))
#define G(x) ((x)<tb?(x)*3+1:((x)-tb)*3+2)

int wa[MAXN], wb[MAXN], wv[MAXN], ws[MAXN];

int c0(int *s, int a, int b)
{
    return s[a] == s[b] && s[a + 1] == s[b + 1] && s[a + 2] == s[b + 2];
}

int c12(int k, int *s, int a, int b)
{   
    if (k == 2) return s[a] < s[b] || s[a] == s[b] && c12(1, s, a + 1, b + 1);
    else return s[a] < s[b] || s[a] == s[b] && wv[a + 1] < wv[b + 1];
}

void sort(int *s, int *a, int *b, int slen, int m)
{
    int i;
    for (i = 0; i < slen; i++) wv[i] = s[a[i]];
    for (i = 0; i < m; i++) ws[i] = 0;
    for (i = 0; i < slen; i++) ws[wv[i]]++;
    for (i = 1; i < m; i++) ws[i] += ws[i - 1];
    for (i = slen - 1; i >= 0; i--) b[--ws[wv[i]]] = a[i];
    return;
}

void dc3(int *s, int *sa, int slen, int m)
{
    int i, j, *rn = s + slen, *san = sa + slen, ta = 0, tb = (slen + 1) / 3, tbc = 0, p;
    s[slen] = s[slen + 1] = 0;
    for (i = 0; i < slen; i++) if (i % 3 != 0) wa[tbc++] = i;
    sort(s + 2, wa, wb, tbc, m);
    sort(s + 1, wb, wa, tbc, m);
    sort(s, wa, wb, tbc, m);
    for (p = 1, rn[F(wb[0])] = 0, i = 1; i < tbc; i++)
        rn[F(wb[i])] = c0(s, wb[i - 1], wb[i]) ? p - 1 : p++;
    if (p < tbc) dc3(rn, san, tbc, p);
    else for (i = 0; i < tbc; i++) san[rn[i]] = i;
    for (i = 0; i < tbc; i++) if (san[i] < tb) wb[ta++] = san[i] * 3;
    if (slen % 3 == 1) wb[ta++] = slen - 1;
    sort(s, wb, wa, ta, m);
    for (i = 0; i < tbc; i++) wv[wb[i] = G(san[i])] = i;
    for (i = 0, j = 0, p = 0; i < ta && j < tbc; p++)
        sa[p] = c12(wb[j] % 3, s, wa[i], wb[j]) ? wa[i++] : wb[j++];
    for (; i < ta; p++) sa[p] = wa[i++];
    for (; j < tbc; p++) sa[p] = wb[j++];
    return;
}