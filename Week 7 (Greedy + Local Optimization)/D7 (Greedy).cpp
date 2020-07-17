#include<bits/stdc++.h>
using namespace std;
#define err1(x) {cerr << '(' << x << ')' << '\n';}
#define err2(x) {cerr << '{' << x << '}' << '\n';}
#define err3(x) {cerr << '[' << x << ']' << '\n';}
#define mp make_pair
#define pb push_back
#define mt make_tuple
//#define long long long
#define int long long
#define double long double
#define pmax 1e9+7
#define longmax 1e18+7
#define forn(i, n) for(int i=0; i<n; i++)

vector<int> dura;
int N, M;

int assign() {
    priority_queue<pair<int, int> > f;
    forn(i, M) f.push(mp(0, i));
    forn(i, N) {
        pair<int, int> now=f.top();
        f.pop();
        f.push(mp(now.first-dura[i], now.second));
    }
    forn(i, M-1) f.pop();
    return -f.top().first;
}

void solve() {
    dura.clear();
    cin >> N >> M;
    forn(i, N) {
        int x;
        cin >> x;
        dura.pb(x);
    }
    sort(dura.begin(), dura.end());
    int res=assign();
    sort(dura.begin(), dura.end(), greater<int>());
    res=min(res, assign());
    cout << res << endl;
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
