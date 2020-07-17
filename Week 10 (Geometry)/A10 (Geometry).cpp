#include<bits/stdc++.h>
using namespace std;
#define err1(x) {cerr << '(' << x << ')' << '\n';}
#define err2(x) {cerr << '{' << x << '}' << '\n';}
#define err3(x) {cerr << '[' << x << ']' << '\n';}
#define mp make_pair
#define pb push_back
#define mt make_tuple
//#define long long long
#define double long double
#define pmax (1e9+7)
#define longmax (1e18+7)
#define forn(i, n) for(int i=0; i<n; i++)
#define X first
#define Y second

#define node pair<double, double>

node isect(node a, node b, node c, node d) {
    if ((b.X-a.X)*(d.Y-c.Y)==(b.Y-a.Y)*(d.X-c.X)) return mp(pmax, pmax);
    double div=(b.X-a.X)*(d.Y-c.Y)-(b.Y-a.Y)*(d.X-c.X);
    return mp(((b.X-a.X)*(c.X*d.Y-d.X*c.Y)-(d.X-c.X)*(a.X*b.Y-b.X*a.Y))/div,
              ((b.Y-a.Y)*(c.X*d.Y-d.X*c.Y)-(d.Y-c.Y)*(a.X*b.Y-b.X*a.Y))/div);
}

double CCW(node a, node b, node p) {
    return a.X*b.Y+b.X*p.Y+p.X*a.Y-b.X*a.Y-p.X*b.Y-a.X*p.Y;
}

node p0;

bool cmp(node a, node b) {
    return CCW(a, b, p0)>0;
}

void print(node a) {
    cout << a.first << " " << a.second << endl;
}

vector<node> hull(vector<node> p) {
    sort(p.begin(), p.end());
    p0=p[0];
    sort(p.begin()+1, p.end(), cmp);
    vector<node> H;
    int h=1;
    H.pb(p[1]); H.pb(p[2]);
    for (int i=3; i<p.size(); i++) {

        while (CCW(H[h-1], H[h], p[i])>=0) {
            h--;
        }
        H.pb(p[i]); h++;
    }
    return H;
}

bool inside(node a, node b, node p) {
    return (((a.X<=p.X && p.X<=b.X) || (a.X>=p.X && p.X>=b.X)) &&
            ((a.Y<=p.Y && p.Y<=b.Y) || (a.Y>=p.Y && p.Y>=b.Y)));
}

bool cut(node a, node b, node c, node d) {
    node sect=isect(a, b, c, d);
    return (inside(a, b, sect) && inside(c, d, sect));
}

void solve() {
    int N; double X, Y;
    cin >> X >> Y >> N;
    vector<pair<node, node> > poly;
    forn(i, N) {
        double x, y, a, b;
        cin >> x >> y >> a >> b;
        poly.pb(mp(mp(x, y), mp(a, b)));
    }
    node start=mp(X, Y), next=mp(23471, 12567);
    int res=0;
    forn(i, N) {
        node sect=isect(start, next, poly[i].X, poly[i].Y);
        res+=(inside(start, next, sect) && inside(poly[i].X, poly[i].Y, sect));
    }
    if (res%2==1) cout << "jackpot\n";
    else cout << "too bad\n";
//    cout << res << endl;

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
