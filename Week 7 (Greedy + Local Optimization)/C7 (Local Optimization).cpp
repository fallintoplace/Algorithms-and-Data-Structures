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

#define ite 1000000

int N, globalCnt;
vector<vector<int> > adj;

pair<int, vector<int> > opt() {
    int tot=0;
    vector<int> sub;
    vector<bool> marked(N);
    int cnt=0;
    for(cnt=0; cnt<ite; cnt++) {
        int x;
        do {
            x=rand()%N;
        } while (cnt++<ite && marked[x]);
        if (marked[x]) break;

        int newTot=tot;
        cnt+=adj[x].size();
        forn(i, adj[x].size()) {
            if (marked[adj[x][i]]) newTot--;
            else newTot++;
        }

        if (newTot>tot) {
            tot=newTot;
            sub.pb(x);
            marked[x]=true;
        }

    }
    globalCnt+=cnt;
    return mp(tot, sub);
}

void solve() {
    adj.clear(); globalCnt=0;
    cin >> N;
    adj.resize(N);
    forn(i, N) {
        int x;
        cin >> x;
        while (x--) {
            int a;
            cin >> a;
            adj[i].pb(a-1);
        }
    }
    pair<int, vector<int> > res;
    forn(i, 10) {
        res=max(res, opt());
        if (globalCnt>1e9) break;
    }
//    cout << res.first << endl;
    sort(res.second.begin(), res.second.end());
    forn(i, res.second.size()) cout << res.second[i]+1 << " ";
    cout << endl;

}

int main() {
//	freopen("1.in", "r", stdin);
	ios::sync_with_stdio(false);
	srand(0);
	int Case;
	cin >> Case;
	for (int i=1; i<=Case; i++) {
		cout << "Case #" << i << ":\n";
		solve();
	}
}
