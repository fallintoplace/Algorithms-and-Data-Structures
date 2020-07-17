#include<bits/stdc++.h>
using namespace std;
#define err1(x) {cerr << '(' << x << ')' << '\n';}
#define err2(x) {cerr << '{' << x << '}' << '\n';}
#define err3(x) {cerr << '[' << x << ']' << '\n';}
#define mp make_pair
#define pb push_back
#define mt make_tuple
#define long long long
#define double long double
#define pmax (1e9+7)
#define longmax (1e18+7)
#define forn(i, n) for(int i=0; i<n; i++)


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

long solveCons(vector<pair<long, long> > data) {
    map<int, int> check;
    vector<long> rest, mod;
    bool impos=false;
    int N=data.size();
    forn(i, N) {
        long x=data[i].first, y=data[i].second;
        mod.pb(x);
        rest.pb(y);
    }
    N=mod.size();
    forn(i, N-1) {
        pair<long, long> g=gcd(mod[i], mod[i+1]).second;
        rest[i+1]=((rest[i]*g.second)*mod[i+1])+((rest[i+1]*g.first)*mod[i]);
        mod[i+1]=mod[i]*mod[i+1];
        rest[i+1]=rest[i+1]%mod[i+1];
    }
    if (rest[N-1]<0) rest[N-1]+=mod[N-1];
    return rest[N-1];


}


long modExp(long b, long e, long mod) {
    long r=1;
    while (e>0) {
        if ((e&1)==1)
            r=(r*b)%mod;
        b=(b*b)%mod;
        e>>=1;
    }
    return r;
}

long factExp(long n, long p) {
    long e=0, u=p, t=n;
    while (u<=t) {
        e+=t/u;
        u*=p;
    }
    return e;
}

vector<long> getBaseDigits(long n, long b) {
    vector<long> d;
    while (n>0) {
        d.pb(n%b);
        n/=b;
    }
    return d;
}

pair<long, long> egcd(long a, long b) {
    long x=0, y=1, u=1, v=0;
    while (a!=0) {
        long q=b/a, r=b%a, m=x-u*q, n=y-v*q;
        b=a; a=r; x=u, y=v; u=m, v=n;
    }
    return mp(x, y);
}

long crt(vector<pair<long, long> > cons) {
    long m=1;
    forn(i, cons.size()) {
        m*=cons[i].second;
    }
    long res=0;
    forn(i, cons.size()) {
        long s=egcd(m/cons[i].second, cons[i].second).first;
        res+=(cons[i].first*s*m/cons[i].second);
    }
    return res%m;
}

long fermat(long n, long k, long p) {
    long numDeg=factExp(n, p)-factExp(n-k, p),
        denDeg=factExp(k, p);
    if (numDeg>denDeg) return 0;
    if (k>n) return 0;
    long num=1;
    for(int i=n; i>=n-k+1; i--) {
        long cur=i;
        while (cur%p==0) cur/=p;
        num=(num*cur)%p;
    }
    long denom=1;
    for(int i=1; i<=k; i++) {
        long cur=i;
        while (cur%p==0) cur/=p;
        denom=(denom*cur)%p;
    }
    return (num*modExp(denom, p-2, p))%p;
}

long lucas(long n, long k, long p) {
    vector<long> np=getBaseDigits(n, p);
    vector<long> kp=getBaseDigits(k, p);
    long binom=1;
    for (int i=np.size()-1; i>=0; i--) {
        long ni=np[i],
        ki=0;
        if (i<kp.size()) ki=kp[i];
        binom=(binom*fermat(ni, ki, p))%p;
    }
    return binom;
}

long binom(long n, long k, vector<long> mod) {
    vector<pair<long, long> > cons;
    forn(i, mod.size()) {
        cons.pb(mp(mod[i], lucas(n, k, mod[i])));
    }

    return solveCons(cons);
}



void solve() {
    int N, M;
    cin >> N >> M;
    vector<long> mods={
        2,
    3, 5, 7, 11
    , 13, 17, 19, 23
    };
//    BigInteger res=1;
//    for (int i=N-M+1; i<=N; i++) res=res*i;
//    for (int i=1; i<=M; i++) res=res/i;
//    res=res-res/223092870*223092870;
//    cout << res << endl;
    cout << binom(N, M, mods) << endl;

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
