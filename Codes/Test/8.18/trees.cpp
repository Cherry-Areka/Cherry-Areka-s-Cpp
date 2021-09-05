// 时间、空间、答案溢出
// 建议快速 mul
#include <bits/stdc++.h>

using namespace std;

#define int long long

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 2e5 + 1, Mod = 1e9 + 7;

int n, K, ans;
int a[maxn], b[maxn], ml[maxn];

inline int Power(int x, int a, int Mod) {
    int ans = 1;
    while(a) {
        if(a & 1)
            ans = (ans * x) % Mod;
        x = (x * x) % Mod;
        a >>= 1;
    }
    return ans;
}

inline int Mul(int n, int m, int p) {
    int res = 0;
    while(m) {
        if(m & 1)
            res = (res + n) % p;
        m >>= 1;
        n = (n + n) % p;
    }
    return res;
}

class Tree_Array {
    private:
        int t[maxn];
        inline int lowbit(int x) {
            return x & (-x);
        }
    public:
        inline void Add(int pos, int v) {
            if(pos <= 0)
                return;
            while(pos <= n) {
                t[pos] = (t[pos] + v) % Mod;
                pos += lowbit(pos);
            }
        }

        inline int Ask(int pos) {
            if(pos <= 0)
                return 0;
            int res = 0;
            while(pos) {
                res = (res + t[pos]) % Mod;
                pos -= lowbit(pos);
            }
            return res % Mod;
        }
};

Tree_Array T;
bool vis[maxn];

inline int C(int n, int m) {
    if(m > n)
        return 0;
    if(m == n)
        return 1;
    if(m == 0 or n == 0)
        return 1;
    int ans1 = ml[n] % Mod;
    int ans2 = Mul(ml[m], ml[n - m], Mod);
    int anss2 = Power(ans2, Mod - 2, Mod);
    return Mul(ans1, anss2, Mod);
}

signed main() {

    #define Areka
    #ifdef Areka
        freopen("trees.in", "r", stdin);
        freopen("trees.out", "w", stdout);
    #endif

    n = read(), K = read();

    if(K > n) {
        puts("0");
        return 0;
    }

    ml[0] = ml[1] = 1;
    for(int i = 2; i <= n; ++i)
        ml[i] = Mul(ml[i - 1], i, Mod);

    for(int i = 1; i <= n; ++i)
        a[i] = read(), b[i] = a[i];

    sort(b + 1, b + n + 1);
    int nn = unique(b + 1, b + n + 1) - b - 1;
    for(int i = 1; i <= n; ++i) {
        a[i] = lower_bound(b + 1, b + nn + 1, a[i]) - b;
        T.Add(a[i], 1);
    }
    
    for(int i = 1; i <= n; ++i) {
        int w = T.Ask(a[i] - 1);
        if(w < K - 1)
            continue;
        else
            ans = (ans + Mul(C(w, K - 1), b[a[i]], Mod)) % Mod;
    }


    for(int i = 1; i <= n; ++i) {
        if(vis[a[i]])
            continue;
        int w = T.Ask(a[i]) - T.Ask(a[i] - 1), w1 = T.Ask(a[i] - 1);
        if(w <= 1 or w + w1 < K)
            continue;
        else {
            if(w1 == 0) {
                if(w < K)
                    continue;
                ans = (ans + Mul(C(w, K), b[a[i]], Mod)) % Mod;
            }
            else {
                int Up = min(w, K);
                for(int j = max(K - w1, 2ll); j <= Up; ++j)
                    ans = (ans + Mul(Mul(C(w, j), C(w1, K - j), Mod), b[a[i]], Mod)) % Mod;
            }
            vis[a[i]] = true;
        }
    }

    printf("%lld\n", ans % Mod);

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
