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
#define point pair<int, pair<double, double> >


node isect(node a, node b, node c, node d) {
    if ((b.X-a.X)*(d.Y-c.Y)==(b.Y-a.Y)*(d.X-c.X)) return mp(pmax, pmax);
    double div=(b.X-a.X)*(d.Y-c.Y)-(b.Y-a.Y)*(d.X-c.X);
    return mp(((b.X-a.X)*(c.X*d.Y-d.X*c.Y)-(d.X-c.X)*(a.X*b.Y-b.X*a.Y))/div,
              ((b.Y-a.Y)*(c.X*d.Y-d.X*c.Y)-(d.Y-c.Y)*(a.X*b.Y-b.X*a.Y))/div);
}

double CCW(node a, node b, node p) {
    return a.X*b.Y+b.X*p.Y+p.X*a.Y-b.X*a.Y-p.X*b.Y-a.X*p.Y;
}

point p0;

bool cmp(point a, point b) {
    return CCW(a.Y, b.Y, p0.Y)<0;
}

bool sec(point a, point b) {
    return a.Y<b.Y;
}

void print(node a) {
    cout << a.first << " " << a.second << endl;
}

bool inside(node a, node b, node p) {
    return (((a.X<=p.X && p.X<=b.X) || (a.X>=p.X && p.X>=b.X)) &&
            ((a.Y<=p.Y && p.Y<=b.Y) || (a.Y>=p.Y && p.Y>=b.Y)));
}

vector<point> hull(vector<point> p) {
    sort(p.begin(), p.end(), sec);
    p0=p[0];
    sort(p.begin()+1, p.end(), cmp);
//    forn(i, p.size()) cout << p[i].X << " ", print(p[i].Y);
    vector<point> H(p.size());
    int h=1;
    H[0]=p[0]; H[1]=p[1];
    for (int i=2; i<p.size(); i++) {
        while (CCW(H[h-1].Y, H[h].Y, p[i].Y)>0) {
            h--;
        }

        assert(h>=1);
        if (CCW(H[h-1].Y, H[h].Y, p[i].Y)<0) {
            H[h+1]=p[i];
            h++;
        }
        else if (CCW(H[h-1].Y, H[h].Y, p[i].Y)==0 && inside(H[h-1].Y, p[i].Y, H[h].Y)) {
            H[h]=p[i];
        }
    }
    vector<point> res;
    forn(i, h+1) res.pb(H[i]);
    return res;
}



void solve() {
    int N;
    cin >> N;
    vector<point> garden;
    forn(i, N) {
        double x, y;
        cin >> x >> y;
        garden.pb(mp(i+1, (mp(x, y))));
    }
    vector<point> res=hull(garden);
    sort(res.begin(), res.end());
    forn(i, res.size()) cout << (res[i].first) << " "; cout << endl;
}

int main() {
//	freopen("custom3.in", "r", stdin);
	ios::sync_with_stdio(false);
	int Case;
	cin >> Case;
	for (int i=1; i<=Case; i++) {
		cout << "Case #" << i << ": ";
		solve();
	}
}
