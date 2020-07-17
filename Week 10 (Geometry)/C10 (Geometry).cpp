#include<bits/stdc++.h>
using namespace std;
#define err1(x) {cerr << '(' << x << ')' << '\n';}
#define err2(x) {cerr << '{' << x << '}' << '\n';}
#define err3(x) {cerr << '[' << x << ']' << '\n';}
#define mp make_pair
#define pb push_back
#define mt make_tuple
#define double long double
#define pmax (1e9+7)
#define longmax (1e18+7)
#define forn(i, n) for(int i=0; i<n; i++)
#define X first
#define Y second

#define node pair<double, double>

double dist(node a, node b) {
    return (a.X-b.X)*(a.X-b.X)+(a.Y-b.Y)*(a.Y-b.Y);
}


void solve() {
    int N;
    cin >> N;
    vector<node> p;
    forn(i, N) {
        double x, y;
        cin >> x >> y;
        p.pb(mp(x, y));
    }


    double res=0;
    for (int k=0; k<1; k++) {
        double ab=pmax, bc=pmax;
        for (int i=0; i<N; i++) if (k!=i) ab=min(ab, sqrt(dist(p[k], p[i])));
        for (int i=0; i<N; i++) for (int j=i+1; j<N; j++) if (k!=i && j!=k) bc=min(bc, sqrt(dist(p[i], p[j]))/2);
        double r2=min(bc, ab);
//        cout << r2 << " " << bc << " " << ab << endl;
        res=max(res, max(ab*ab, (ab*ab+r2*r2*N-r2*2*ab)));

    }
    cout << setprecision(10) << res*3.14159265 << endl;
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
