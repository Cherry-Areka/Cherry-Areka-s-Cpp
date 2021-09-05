#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 1e5 + 1;

#define rint register int

int a[maxn], c[maxn], n;
int sz[maxn], son[maxn];
long long nans, mc, Son, ans[maxn];

int head[maxn], tot;
class Edge {
	public:
		int to, nxt;
}E[maxn << 1];

inline void Add_edge(int u, int v) {
	E[++tot].to = v, E[tot].nxt = head[u];
	head[u] = tot;
	return;
}

inline void Dfs1(int x, int fa) {
	sz[x] = 1, son[x] = 0;
	for(rint i = head[x]; i; i = E[i].nxt) {
		int y = E[i].to;
		if(y == fa)
			continue;
		Dfs1(y, x);
		sz[x] += sz[y];
		if(sz[son[x]] < sz[y])
			son[x] = y;
	}
}

inline void Add(int x, int fa, int k) {
//	cout << nans << endl;
	c[a[x]] += k;
	if(c[a[x]] > mc)
		mc = c[a[x]], nans = a[x];
	else if(c[a[x]] == mc)
		nans += a[x];
	for(rint i = head[x]; i; i = E[i].nxt) {
		int y = E[i].to;
		if(y == fa or y == Son)
			continue;
		Add(y, x, k);
	}
	return;
}

inline void Dfs2(int x, int fa, int opt) {
	for(rint i = head[x]; i; i = E[i].nxt) {
		int y = E[i].to;
		if(y == fa or y == son[x])
			continue;
		Dfs2(y, x, 0);
	}
	if(son[x])
		Dfs2(son[x], x, 1), Son = son[x];
	Add(x, fa, 1);
	Son = 0, ans[x] = nans;
	if(opt == 0)
		Add(x, fa, -1), nans = 0, mc = 0;
	return;
}

signed main() {
//	#define Areka
	#ifdef Areka
		freopen("", "r", stdin);
		freopen("", "w", stdout);
	#endif
	
	n = read();
	
	for(rint i = 1; i <= n; ++i)
		a[i] = read();
		
	for(rint i = 1; i < n; ++i) {
		int x = read(), y = read();
		Add_edge(x, y), Add_edge(y, x);
	}
	
	Dfs1(1, 0);
	Dfs2(1, 0, 1);
	for(rint i = 1; i <= n; ++i)
		printf("%lld ", ans[i]);
	return 0;
}
