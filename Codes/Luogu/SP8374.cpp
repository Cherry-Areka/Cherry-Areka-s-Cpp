#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

int l, w, r, b;

signed main() {
    r = read(), b = read();
    if(b & 1) 
        l = b * 2 + 1;
    
    else l = b * 2;

    w = (b + r) / l;

    cout << max(l, w) << " " << min(l, w) << endl;
    
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
