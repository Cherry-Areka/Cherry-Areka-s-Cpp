#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 1e6 + 1;

int Rt = 0, tot = 0;
class Fhq_Treap{
    private :
        class Tree{
            public :
                int ls, rs;
                int dat, val;
                int sz;
        }T[maxn];

        inline void Upd(int p) {
            T[p].sz = T[T[p].ls].sz + T[T[p].rs].sz + 1;
        }

        inline void Split(int p, int k, int& x, int& y) {
            if(p == 0) {
                x = y = 0;
                return;
            }
            
            else {
                if(T[p].val <= k) {
                    x = p;
                    Split(T[p].rs, k, T[p].rs, y);
                }
                else {
                    y = p;
                    Split(T[p].ls, k, x, T[p].ls);
                }
            }
            Upd(p);
            return;
        }

        inline int Marge(int x, int y) {
            if(x == 0 or y == 0) 
                return x + y;

            if(T[x].dat < T[y].dat) {
                T[x].rs = Marge(T[x].rs, y);
                Upd(x);
                return x;
            }
            else {
                T[y].ls = Marge(x, T[y].ls);
                Upd(y);
                return y;
            }
        }

        inline int New_Node(int k) {
            int p = ++tot;
            T[p].sz = 1; T[p].rs = T[p].ls = 0;
            T[p].dat = rand(), T[p].val = k;
            return p;
        }

    public :

        inline bool empty() {
            return T[Rt].sz == 0;
        }

        inline void Insert(int k) {
            int x, y;
            // cout << Rt << endl;
            Split(Rt, k, x, y);
            int New = New_Node(k);
            Rt = Marge(Marge(x, New), y);
            return;
        }

        inline void Remove(int k) {
            int x, y, z;
            Split(Rt, k, x, z);
            Split(x, k - 1, x, y);
            y = Marge(T[y].ls, T[y].rs);
            Rt = Marge(Marge(x, y), z);
        }

        inline int Val(int k) {
            int p = Rt;
            while(true) {
                if(T[T[p].ls].sz + 1 == k)
                    break;
                if(T[T[p].ls].sz + 1 > k) 
                    p = T[p].ls;
                else {
                    k -= (T[T[p].ls].sz + 1);
                    p = T[p].rs;
                }
            }
            return T[p].val;
        }

        inline int Rank(int k) {
            int x, y, ans;
            Split(Rt, k - 1, x, y);
            ans = T[x].sz + 1;
            Rt = Marge(x, y);
            return ans;
        }

        inline int Get_Pre(int k) {
            int x, y, p;
            Split(Rt, k - 1, x, y);
            p = x;
            while(T[p].rs)
                p = T[p].rs;
            int ans = T[p].val;
            Rt = Marge(x, y);
            return ans;
        }

        inline int Get_Nxt(int k) {
            int x, y, p;
            Split(Rt, k, x, y);
            p = y;
            while(T[p].ls)
                p = T[p].ls;
            int ans = T[p].val;
            Rt = Marge(x, y);
            return ans;
        }

        inline bool Find(int k) {
            int x, y, z;
            Split(Rt, k, x, z);
            Split(x, k - 1, x, y);
            bool ans = T[y].sz > 0;
            Rt = Marge(Marge(x, y), z);
            return ans;
        }

        inline int sizes() {
            return T[Rt].sz;
        }
}F;

int n, last, ans, m;

signed main() {
    n = read(), m = read();
    for(int i = 1; i <= m; ++i) {
        int opt = read();
        int x;
        if(opt != 3 and opt != 4 and opt != 5)
            x = read();
        switch(opt) {
            case 1 : {
                x += last;
                F.Insert(x);
                break;
            }
            case 2 : {
                x += last;
                F.Remove(x);
                break;
            }
            case 3 : {
                last = F.empty() ? -1 : F.Val(1);
                ans += last;
                break;
            }
            case 4 : {
                last = F.empty() ? -1 : F.Val(F.sizes());
                ans += last;
                break;
            }
            case 5 : {
                last = F.sizes();
                ans += last;
                break;
            }
            case 6 : {
                x += last;
                last = (int)F.Find(x);
                ans += last;
                break;
            }
            case 7 : {
                x += last;
                last = F.empty() ? -1 : F.Get_Pre(x);
                ans += last;
                break;
            }
            case 8 : {
                x += last;
                last = F.empty() ? -1 : F.Get_Nxt(x);
                ans += last;
                break;
            }
        }
    }


    cout << ans << endl;
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
