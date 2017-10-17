#define MAXM 20001
//返回回文串的最大值
//MAXM至少应为输入字符串长度的两倍+1

int p[MAXM];
char s[MAXM];

int manacher(string str) {
    memset(p, 0, sizeof(p));
    int len = str.size();
    int k;
    for (k = 0; k < len; k++) {
        s[2 * k] = '#';
        s[2 * k + 1] = str[k];
    }
    s[2 * k] = '#';
    s[2 * k + 1] = '\0';
    len = strlen(s);
    int mx = 0;
    int id = 0;
    for (int i = 0; i < len; ++i) {
        if ( i < mx ) {
            p[i] = min(p[2 * id - i], mx - i);
        }
        else {
            p[i] = 1;
        }
        for (; s[i - p[i]] == s[i + p[i]] && s[i - p[i]] != '\0' && s[i + p[i]] != '\0' ; ) {
            p[i]++;
        }
        if ( p[i] + i > mx ) {
            mx = p[i] + i;
            id = i;
        }
    }
    int res = 0;
    for (int i = 0; i < len; ++i) {
        res = max(res, p[i]);
    }
    return res - 1;
}