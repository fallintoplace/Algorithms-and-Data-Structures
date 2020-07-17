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
#define pmax 1e9+7
#define longmax 1e18+7
#define forn(i, n) for(int i=0; i<n; i++)

void solve() {
    int H, N;
    cin >> H >> N;
    vector<tuple<int, int, int> > block;
    block.pb(mt(0, 0, 0));
    forn(i, N) {
        int x, y, z;
        cin >> x >> y >> z;
        block.pb(mt(x, y, z));
        block.pb(mt(x, z, y));
        block.pb(mt(y, x, z));
        block.pb(mt(y, z, x));
        block.pb(mt(z, x, y));
        block.pb(mt(z, y, x));
    }
    sort(block.begin(), block.end());
    vector<int> f(block.size());
    int res=0;
    forn(i, block.size()) {
//        printf("%d %d %d\n", get<0>(block[i]), get<1>(block[i]), get<2>(block[i]));
        forn(j, i) {
            if (get<0>(block[j])<get<0>(block[i]) && get<1>(block[j])<get<1>(block[i])) {
                f[i] = max(f[i], f[j]+get<2>(block[i]));
                res = max(res, f[i]);
            }
        }
    }
//    cout << res << endl;
    if (res>=H) cout << "yes\n";
    else cout << "no\n";
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
