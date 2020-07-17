#include<bits/stdc++.h>
using namespace std;
#define err1(x) {cerr << '(' << x << ')' << '\n';}
#define err2(x) {cerr << '{' << x << '}' << '\n';}
#define err3(x) {cerr << '[' << x << ']' << '\n';}
#define mp make_pair
#define pb push_back
#define mt make_tuple
#define pmax (1e9+7)
#define BigIntmax (1e18+7)
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
    long Y; string YY;
    cin >> N >> YY; Y=long(YY);
    long Z=1;
    forn(i, N) Z=Z*10;
    long X=gcd(Y, Z).second.first;
    if (X<0) X=X+Z;
    cout << X << endl;
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

