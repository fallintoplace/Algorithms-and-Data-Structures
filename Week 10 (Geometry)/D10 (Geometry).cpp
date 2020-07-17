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

int M, N;
vector<int> f;
vector<node> points;
bool hasAns;

node p0;
bool cmp(node a, node b) {
    return CCW(a, b, p0)<0;
}


double dist(node a, node b) {
    return (a.X-b.X)*(a.X-b.X)+(a.Y-b.Y)*(a.Y-b.Y);
}

double area(vector<node> poly) {
    double A=0;
    int N=poly.size();
    forn(i, N) {
        A+=poly[i].X*poly[(i+1)%N].Y-poly[(i+1)%N].X*poly[i].Y;
    }
    return A;
}

vector<node> hull(vector<node> p) {
    sort(p.begin(), p.end());
    p0=p[0];
    sort(p.begin()+1, p.end(), cmp);
    p.pb(p0);
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
    forn(i, h) res.pb(H[i]);
    return res;
}


void btrk(int n, int t, int r) {
    if (hasAns) return;
    if (n==N) {
        if (t!=3 || r!=4) return;
        vector<node> tri, rec, full;
        forn(i, N) {
            if (f[i]==3) {
                tri.pb(points[i]);
                full.pb(points[i]);
            } else if (f[i]==4) {
                rec.pb(points[i]);
                full.pb(points[i]);
            }
        }


        if (tri.size()!=3 || rec.size()!=4) return;
        rec=hull(rec);
        full=hull(full);
//        sort(rec.begin(), rec.end());
//        sort(rec.begin(), rec.end(), cmp);
        if (dist(rec[0], rec[1])!=dist(rec[2], rec[3])) return;
        if (dist(rec[1], rec[2])!=dist(rec[0], rec[3])) return;

        if (dist(rec[0], rec[2])!=
            (dist(rec[0], rec[1])+dist(rec[1], rec[2]))) return;
        if (abs(area(full))==abs(area(tri))) return;
        if (abs(area(full))==abs(area(rec))) return;

        for (int i=0; i<3; i++) for (int j=i+1; j<3; j++)
            for (int k=0; k<4; k++) for (int l=k+1; l<4; l++) {
            if (cut(tri[i], tri[j], rec[k], rec[l])) {
                return;
            }

        }
        cout << "possible\n";
        hasAns=true;
        for (int i=0; i<4; i++) print(rec[i]);
        for (int i=0; i<3; i++) print(tri[i]);

    } else {
        f[n]=0;
        btrk(n+1, t, r);
        if (t<3) {
            f[n]=3;
            btrk(n+1, t+1, r);
        }
        if (r<4) {
            f[n]=4;
            btrk(n+1, t, r+1);
        }

    }
}

void solve() {
    vector<node> points2, total;
    cin >> N;
    f=vector<int>(N);
    points.clear();
    hasAns=0;
    forn(i, N) {
        int x, y;
        cin >> x >> y;
        points.pb(mp(x, y));
    }
    btrk(0, 0, 0);
    if (!hasAns) cout << "impossible\n";

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
