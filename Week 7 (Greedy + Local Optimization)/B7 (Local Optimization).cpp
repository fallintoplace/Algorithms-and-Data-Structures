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
#define longmax 1e18+7
#define forn(i, n) for(int i=0; i<n; i++)

int N, M;
vector<int> prod;
vector<vector<int> > dev;
vector<int> heu, marked;

void print(vector<int> a) {
    vector<vector<int> > res(N);
    forn(i, a.size()) res[a[i]].pb(i);
    forn(i, N) {
        if (res[i].size()) {
            cout << i+1 << " ";
            forn(j, res[i].size()) cout << res[i][j]+1 << " ";
            cout << endl;
        }
    }
}

void change(int x, int y, int &newTot) {
    assert(marked[heu[x]]>0);
    marked[heu[x]]--;
    if (marked[heu[x]] == 0) newTot -= prod[heu[x]];
    newTot -= dev[heu[x]][x];

    heu[x]=y;
    marked[heu[x]]++;
    if (marked[heu[x]] == 1) newTot += prod[heu[x]];
    newTot += dev[heu[x]][x];
}
int x[400], y[400], old[400];

pair<int, vector<int> > attempt1() {
    heu=vector<int>(M), marked=vector<int>(N);
    forn(i, M) {
        int max=1e9;
        forn(j, N) {
            if (prod[j]+20*dev[j][i] < max) {
                max = prod[j]+20*dev[j][i];
                heu[i] = j;
            }
        }
    }
    int tot=0;
    forn(j, M) {
        tot+=dev[heu[j]][j];
        marked[heu[j]]++;
    }
    forn(i, N) if (marked[i]) tot+=prod[i];

    forn(r, 5000000) {
        int newTot=tot;
        int changeNum = rand()%1+1;
        if (r%1000==0) changeNum = rand()%200+1;
        else if (r%400==0) changeNum = rand()%100+1;
        else if (r%100==0) changeNum = rand()%50+1;
        if (r%50==0) changeNum = rand()%10+1;
        forn(i, changeNum) {
            x[i]=rand()%M, y[i]=rand()%N;
            old[i]=heu[x[i]];
        }
        forn(i, changeNum) {
            change(x[i], y[i], newTot);
        }
        if (newTot<tot) {
            tot=newTot;
            continue;
        }
        forn(i, changeNum) change(x[i], old[i], newTot);
    }
    return mp(tot, heu);
}


void solve() {
    cin >> N >> M;
    dev=vector<vector<int> >(N);
    prod.clear();

    forn(i, N) {
        int x;
        cin >> x;
        prod.pb(x);
    }
    forn(i, N) forn(j, M) {
        int x;
        cin >> x;
        dev[i].pb(x);
    }
    pair<int, vector<int> > res=attempt1();

    cout << res.first << endl;
    print(res.second);
}

int main() {
//	freopen("1.in", "r", stdin);
	ios::sync_with_stdio(false);
	srand(time(0));
	int Case;
	cin >> Case;
	for (int i=1; i<=Case; i++) {
		cout << "Case #" << i << ": ";
		solve();
	}
}
