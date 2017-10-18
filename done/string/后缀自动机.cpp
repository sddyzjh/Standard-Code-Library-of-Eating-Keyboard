/*
	求多个串的LCS
*/
struct node{
	node *suf, *s[26], *next;
	int val, w[11];
}*r, *l, T[N<<1+1];
node *point[N];
char str[N];
int n, len, k, tot;
inline void add(int w){
	node *p = l, *np = &T[tot++];
	np->val = p->val+1;
	np->next = point[np->val], point[np->val] = np;
	while (p && !p->s[w])
		p->s[w] = np, p = p->suf;
	if (!p)
		np->suf = r;
	else{
		node *q = p->s[w];
		if (p->val+1 == q->val)
			np->suf = q;
		else{
			node *nq = &T[tot++];
			memcpy(nq->s, q->s, sizeof q->s);
			nq->val = p->val+1;
			nq->next = point[p->val+1], point[p->val+1] = nq;
			nq->suf = q->suf;
			q->suf = nq;
			np->suf = nq;
			while (p && p->s[w] == q)
				p->s[w] = nq, p = p->suf;
		}
	}
	l = np;
}
int main(){
	int i, j, now, L, res, ans(0), w;
	node *p;
	r = l = &T[tot++];
	r->next = point[0], point[0] = r;
	scanf("%s", str);
	L = strlen(str);
	for (i = 0;i < L; ++i)
		add(str[i]-'a');
	for (tot = 1;scanf("%s", str) != EOF; ++tot){
		len = strlen(str);
		p = r, now = 0;
		for (j = 0;j < len; ++j){
			w = str[j]-'a';
			if (p->s[w])
				p = p->s[w], p->w[tot] = max(p->w[tot], ++now);
			else{
				while (p && !p->s[w])
					p = p->suf;
				if (!p)
					p = r, now = 0;
				else
					now = p->val+1, p = p->s[w], p->w[tot] = max(p->w[tot], now);
			}
		}
	}
	for (i = L;i >= 0; --i)
		for (node *p = point[i];p;p = p->next){
			res = p->val;
			for (j = 1;j < tot; ++j){
				res = min(p->w[j], res);
				if (p->suf)
					p->suf->w[j] = max(p->suf->w[j], p->w[j]);
			}
			ans = max(ans, res);
		}
	printf("%d\n", ans);
	return 0;
}