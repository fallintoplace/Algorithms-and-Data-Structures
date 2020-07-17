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

double W, H;
vector<pair<pair<int, int> , pair<int, int>  > > obj;
vector<node> res;
double F[5009][5009];
int N;
bool inters[5009][5009];

void print(node a) {
    cout << "(" << a.first << "," << a.second << ") ";
}


inline double dist(node a, node b) {
    return sqrt((a.X-b.X)*(a.X-b.X)+(a.Y-b.Y)*(a.Y-b.Y));
}
inline node isect(node a, node b, node c, node d) {
    if ((b.X-a.X)*(d.Y-c.Y)==(b.Y-a.Y)*(d.X-c.X)) return mp(pmax, pmax);
    double div=(b.X-a.X)*(d.Y-c.Y)-(b.Y-a.Y)*(d.X-c.X);
    return mp(((b.X-a.X)*(c.X*d.Y-d.X*c.Y)-(d.X-c.X)*(a.X*b.Y-b.X*a.Y))/div,
              ((b.Y-a.Y)*(c.X*d.Y-d.X*c.Y)-(d.Y-c.Y)*(a.X*b.Y-b.X*a.Y))/div);

}
inline bool inside(node a, node b, node p) {
    return (((a.X<=p.X && p.X<=b.X) || (a.X>=p.X && p.X>=b.X)) &&
            ((a.Y<=p.Y && p.Y<=b.Y) || (a.Y>=p.Y && p.Y>=b.Y)));
}

inline bool cut(node a, node b, node c, node d) {
    node sect=isect(a, b, c, d);
    return (inside(a, b, sect) && inside(c, d, sect)
            && sect!=a && sect!=b && sect!=c && sect!=d
            );
}


void solve() {
    cin >> W >> H >> N;

    res.clear();
    obj.clear();
    vector<pair<int, int> > V;
    forn(i, N) {
        int x, y, u, v;
        cin >> x >> y >> u >> v;
        obj.pb(mp(mp(x, y), mp(x+u, y+v)));
        obj.pb(mp(mp(x+u, y), mp(x, y+v)));
        V.pb(mp(x, y));
        V.pb(mp(x+u, y));
        V.pb(mp(x, y+v));
        V.pb(mp(x+u, y+v));
        F[x][y]=pmax;
        F[x+u][y]=pmax;
        F[x][y+v]=pmax;
        F[x+u][y+v]=pmax;

    }
    int x, y, u, v;
    cin >> x >> y >> u >> v;
    F[x][y]=pmax;
    F[u][v]=pmax;
    V.pb(mp(x, y));
    V.pb(mp(u, v));
    map<pair<int, int> , pair<int, int> > trace;
    priority_queue<pair<double, int >, vector<pair<double, int > >,
    greater<pair<double, int > > > pq;
    pq.push(mp(0, V.size()-2));
    F[x][y]=0;
    vector<int> adj[5001];
    int cnt=0;
    forn (k, V.size()) {
        for (int i=k+1; i<V.size(); i++) {
            inters[k][i]=false;
            inters[i][k]=false;
            forn(j, obj.size()) {
                cnt++;
                assert(cnt<15000000);
                if (cut(V[k], V[i], obj[j].X, obj[j].Y)) {
                    inters[k][i]=true;
                    inters[i][k]=true;
                    break;
                }
            }
            if (inters[k][i]==false) {
                adj[k].pb(i);
                adj[i].pb(k);
            }
        }
    }
    cnt=0;
    while (pq.size()) {
        pair<double, int> top=pq.top(); pq.pop();
        pair<int, int>  a=V[top.Y];
        double d=top.X;
        forn(j, adj[top.Y].size()) {
            int i=adj[top.Y][j];
            cnt++;
//            assert(cnt<10000000);
            if (
//                !inters[top.Y][i] &&
                d+dist(a, V[i])<F[V[i].X][V[i].Y]) {
                F[V[i].X][V[i].Y]=d+dist(a, V[i]);
                pq.push(mp(F[V[i].X][V[i].Y], i));
                trace[V[i]]=a;
            }
        }
    }

    pair<int, int> last=mp(u, v);
    cnt=0;
    while (1) {
        cnt++;
//        assert(cnt<=V.size());
        res.pb(last);
        if (last==mp(x, y)) break;
        assert(last!=trace[last]);
        last=trace[last];
    }
    reverse(res.begin(), res.end());


    forn(i, res.size()) print(res[i]);

    cout << endl;

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
