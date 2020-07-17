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


void print(node a) {
    cout << a.first << " " << a.second << endl;
}


bool inside(node a, node b, node p) {
    return (((a.X<=p.X && p.X<=b.X) || (a.X>=p.X && p.X>=b.X)) &&
            ((a.Y<=p.Y && p.Y<=b.Y) || (a.Y>=p.Y && p.Y>=b.Y)));
}
bool cut(node a, node b, node c, node d) {
    node sect=isect(a, b, c, d);
    return (inside(a, b, sect) && inside(c, d, sect));
}

int N;
vector<int> f;
vector<node> points;
bool hasAns;

node p0;
bool cmp(node a, node b) {
    return CCW(a, b, p0)<0;
}
vector<node> hull(vector<node> p) {
    sort(p.begin(), p.end());
    p0=p[0];
    sort(p.begin()+1, p.end(), cmp);
    vector<node> H(p.size());
    int h=1;
    H[0]=p[0]; H[1]=p[1];
    for (int i=2; i<p.size(); i++) {
        while (CCW(H[h-1], H[h], p[i])>0) {
            h--;
        }
        assert(h>=1);
        if (CCW(H[h-1], H[h], p[i])<0) {
            H[h+1]=p[i];
            h++;
        }
        else if (CCW(H[h-1], H[h], p[i])==0 && inside(H[h-1], p[i], H[h])) {
            H[h]=p[i];
        }
    }
    vector<node> res;
    forn(i, h+1) res.pb(H[i]);
    return res;
}

double dist(node a, node b) {
    return ((a.X-b.X)*(a.X-b.X)+(a.Y-b.Y)*(a.Y-b.Y));
}
int sided(double x) {
    if (x>0) return 2;
    if (x==0) return 1;
    return 0;
}

void solve() {
    int N;
    cin >> N;
    vector<node> poly;
    forn(i, N) {
        double x, y;
        cin >> x >> y;
        poly.pb(mp(x, y));
    }
    double A=0, Cx=0, Cy=0;
    forn(i, N) {
        A+=poly[i].X*poly[(i+1)%N].Y-poly[(i+1)%N].X*poly[i].Y;
    }
    A/=2;
    forn(i, N) {
        Cx+=(poly[i].X+poly[(i+1)%N].X)*(poly[i].X*poly[(i+1)%N].Y-poly[(i+1)%N].X*poly[i].Y);
        Cy+=(poly[i].Y+poly[(i+1)%N].Y)*(poly[i].X*poly[(i+1)%N].Y-poly[(i+1)%N].X*poly[i].Y);
    }
    Cx/=(6*A);
    Cy/=(6*A);
    int res=0;
    forn(i, N) {
        node start=poly[i], next=poly[(i+1)%N];
        int pos=-1, sect=0;
        forn(j, N) {
            if (j!=i && (i+1)%N!=j) {
                int ccw=sided(CCW(start, next, poly[j]));
                if (pos==-1) pos=(ccw);
                else {
                    if (pos!=(ccw)) {
                        sect=1; break;
                    }
                }
            }
        }
        if (sect) continue;
        if (pos!=sided(CCW(start, next, mp(Cx, Cy)))) continue;
        if (dist(start, next)+dist(next, mp(Cx, Cy))>=dist(start, mp(Cx, Cy)) &&
            dist(start, next)+dist(start, mp(Cx, Cy))>=dist(next, mp(Cx, Cy)) )
             res++;
    }
//    cout << Cx << " " << Cy << endl;
    cout << res << endl;


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
