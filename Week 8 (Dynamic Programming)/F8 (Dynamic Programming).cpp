#include<bits/stdc++.h>
using namespace std;
#define err1(x) {cerr << '{' << x << '}' << '\n';}
#define err2(x, y) {cerr << '(' << x << " " << y << ')' << '\n';}
#define err3(x) {cerr << '[' << x << ']' << '\n';}
#define err4(x, y, z) {cerr << '(' << x << " " << y << " " << z << ')' << '\n';}
#define err5(x, y, z) {cerr << '[' << x << " " << y << " " << z << ']' << '\n';}

#define mp make_pair
#define pb push_back
#define mt make_tuple
#define long long long
#define double long double
#define pmax (1e9+7)
#define longmax (1e18+7)
#define forn(i, n) for(int i=0; i<n; i++)
#define F first
#define S second

vector<vector<int> > cmp, songs;
vector<int> cf;
int G, N, M;
int F[10010][55][15];


bool f(int time, int fade, int last) {
//    err4(time, fade, last+1);
    if (fade == cf.size()) return true;
//    assert(cf[cf.size()-1]<5100);
    if (time>cf[cf.size()-1]) return false;
    if (F[time][fade][last] != -1) return F[time][fade][last];
    if (time == 0) {
        forn(i, songs.size())
            forn(j, songs[i].size()) {
                int next = songs[i][j];
                for (int k = 5; k <= 10; k++) {
                    if (0<=time+next-k && time<=time+next-k) {
                        int stamp = fade;
                        while (stamp<cf.size() && time+next-k<=cf[stamp] && cf[stamp]<=time+next) stamp++;
                        if (fade==stamp) if (cf[stamp]<time+next-k) continue;
                        if (f(time+next-k, stamp, i) == 1)
                            return F[time][fade][last] = 1;
                    }
                }
            }

    } else {
        forn(i, cmp[last].size()) {
            forn(j, songs[cmp[last][i]].size()) {
                int next = songs[cmp[last][i]][j];
                for (int k = 5; k <= 10; k++) {
                    if (0<=time+next-k && time<=time+next-k) {
                        int stamp = fade;
                        while (stamp<cf.size() && time+next-k<=cf[stamp] && cf[stamp]<=time+next) stamp++;
                        if (fade==stamp) if (cf[stamp]<time+next-k) continue;
                        if (f(time+next-k, stamp, cmp[last][i]) == 1) {
                            return F[time][fade][last] = 1;
                        }
                    }
                }
            }
        }
    }
    return F[time][fade][last] = 0;
}

void print(int x) {
    if (x==0) cout << "no\n";
    else cout << "yes\n";
}

void solve() {
    cmp.clear(); songs.clear(); cf.clear();
    cin >> G >> N >> M;
    cmp.resize(G);
    songs.resize(G);
    forn(i, G) {
        int x, y;
        cin >> x;
        while (x--) {
            cin >> y;
            y--;
            cmp[i].pb(y);
        }
    }
    forn(i, N) {
        int l, g;
        cin >> l >> g;
        g--;
        songs[g].pb(l);
    }
    forn(i, 10000) forn(j, M+2) forn(k, G+2) F[i][j][k]=-1;
    forn(i, M) {
        int x;
        cin >> x;
//        assert(x<=9900);
        cf.pb(x);
    }
    sort(cf.begin(), cf.end());
    print(f(0, 0, 0));

}

main() {

//	freopen("1.in", "r", stdin);
	ios::sync_with_stdio(false);
	int Case;
	cin >> Case;
	for (int i=1; i<=Case; i++) {
		cout << "Case #" << i << ": ";
		solve();
	}
}
