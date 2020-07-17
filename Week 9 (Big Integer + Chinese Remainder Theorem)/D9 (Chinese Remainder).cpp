#include<bits/stdc++.h>
using namespace std;
#define err1(x) {cerr << '(' << x << ')' << '\n';}
#define err2(x) {cerr << '{' << x << '}' << '\n';}
#define err3(x) {cerr << '[' << x << ']' << '\n';}
#define mp make_pair
#define pb push_back
#define mt make_tuple
#define pmax (1e9+7)
#define forn(i, n) for(int i=0; i<n; i++)
#define long long long

void swapGCD(long &a, long &b, long c, long d) {
    a=c;
    b=d;
}

pair<long, pair<long, long> > gcd(long a, long b) {
    long s=0, ss=1,
           t=1, tt=0,
           r=b, rr=a;
    while (!(r==0)) {
        long q=rr/r;
        swapGCD(rr, r, r, rr-q*r);
        swapGCD(ss, s, s, ss-q*s);
        swapGCD(tt, t, t, tt-q*t);
    }
    return mp(rr, mp(ss, tt));
}

void solve() {
    int N;
    long K;
    string KK;
    cin >> N >> KK;
    K=(KK);
    map<string, string> check;
    vector<long> rest, mod;
    bool impos=false;
    forn(i, N) {
        long x, y;
        string xx, yy;
        cin >> xx >> yy;
        string r=check[xx];
        if (!r.size())
            check[xx]=yy;
        else if (r==yy)
            continue;
        else
            impos=true;
        x=xx, y=yy;
        mod.pb(x);
        rest.pb(y);
    }
    if (impos) {
        cout << "impossible\n";
        return;
    }
    if (N==0) {
        cout << K << endl;
    } else {
        N=mod.size();
        forn(i, N-1) {
            pair<long, long> g=gcd(mod[i], mod[i+1]).second;
            rest[i+1]=((rest[i]*g.second)*mod[i+1])+((rest[i+1]*g.first)*mod[i]);
            mod[i+1]=mod[i]*mod[i+1];
            rest[i+1]=rest[i+1]%mod[i+1];
        }
        long next;
        if (rest[N-1]>K) {
            next=(rest[N-1]-K-1)/mod[N-1]+1;
            rest[N-1]=rest[N-1]-next*mod[N-1];
        } else {
            next=(K-rest[N-1])/mod[N-1];
            rest[N-1]=rest[N-1]+next*mod[N-1];
        }
        while (rest[N-1]>K) rest[N-1]=rest[N-1]-mod[N-1];
        while (rest[N-1]+mod[N-1]<=K) rest[N-1]=rest[N-1]+mod[N-1];
        if (rest[N-1]<0 || rest[N-1]>K)
            cout << "impossible\n";
        else
            cout << rest[N-1] << endl;
    }

}

int main() {
//	freopen("1.in", "r", stdin);
    ios::sync_with_stdio(false);
    int Case;
    cin >> Case;
    for (int i=1; i<=Case; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }
}


