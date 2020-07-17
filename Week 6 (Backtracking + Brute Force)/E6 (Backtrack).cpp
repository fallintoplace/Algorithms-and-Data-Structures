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
#define max 1e9+7
#define longmax 1e18+7
#define forn(i, n) for(int i=0; i<n; i++)

vector<int> amount, tot, cur;
vector<vector<int> > center;
vector<tuple<int, int, int, int> > dep;
int N, M, T, ans;

void btrk(int t) {
    if (t==T) {
        forn(i, M) {
            int c=get<0>(dep[i]), p=get<1>(dep[i]), d=get<2>(dep[i]), q=get<3>(dep[i]);
            if (center[c][p] >= center[d][q]) return;
        }
        ans++;
        return;
    }
    forn(i, N) {
        if (tot[i]<amount[i] && (t==0 || cur[t-1]!=i)) {
            center[i][tot[i]]=t;
            tot[i]++;
            cur[t]=i;
            btrk(t+1);
            tot[i]--;
        }
    }
}

void solve() {
    cin >> N >> M;
    ans=0; T=0;
    amount.clear();
    dep.clear();
    cur.clear();
    tot.clear(); tot.resize(N);
    center=vector<vector<int> >(N);
    forn(i, N) {
        int x;
        cin >> x;
        amount.pb(x);
        center[i].resize(x);
        T+=x;
    }
    cur.resize(T);

    forn(i, M) {
        int c, p, d, q;
        cin >> c >> p >> d >> q;
        c--; p--; d--; q--;
        dep.pb(mt(c, p, d, q));
    }
    btrk(0);
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
