#include<bits/stdc++.h>
using namespace std;
#define err1(x) {cerr << '(' << x << ')' << '\n';}
#define err2(x) {cerr << '{' << x << '}' << '\n';}
#define err3(x) {cerr << '[' << x << ']' << '\n';}
#define mp make_pair
#define pb push_back
#define mt make_tuple
#define long long long
#define max 1e9+7
#define longmax 1e18+7
#define forn(i, n) for(int i=0; i<n; i++)

void solve() {
    int L, N, D;
    vector<int> pos;
    cin >> L >> N >> D;
    forn(i, N) {
        int x;
        cin >> x;
        pos.pb(x);
    }
    sort(pos.begin(), pos.end());
    int cur=0, ans=0;
    for (double i=0.5; i<=L; i++) {
//        err1(i);
        while (cur!=N && pos[cur]-D<=i) cur++;
        if (cur==0 || cur-1>=N || !(pos[cur-1]-D<=i && i<=pos[cur-1]+D)) {
            cout << "impossible\n";
            return;
        }
        i=-0.5+pos[cur-1]+D;

        ans++;
    }
    cout << ans << endl;
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
