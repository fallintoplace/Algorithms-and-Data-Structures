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


int M, N, res;
vector<string> human, mice;
int total[4][4], dolph[4][4], domain[5]={-10, -5, 0, 5, 10};
int comp=0;

void btrk(int x, int y, int sum1, int sum2) {
    assert(x<=y);
    if (x==4 && y==4) {
        if (sum1 == 0) res=max(res, sum2);
        return;
    }

    for(int i=-10; i<=10; i+=5) {
        if (y != 3) {
            if (x != y) btrk(x, y+1, sum1+2*i, sum2+i*total[x][y]);
            else if (i >= 0) btrk(x, y+1, sum1+i, sum2+i*total[x][y]);
        } else {
            if (x != y) btrk(x+1, x+1, sum1+2*i, sum2+i*total[x][y]);
            else if (i >= 0) btrk(x+1, x+1, sum1+i, sum2+i*total[x][y]);
        }
    }
}

int convert(char c) {
    if (c == 'A') return 3;
    if (c == 'C') return 2;
    if (c == 'G') return 1;
    return 0;
}

void solve() {
    cin >> M >> N;
    human.clear(), mice.clear(); res=-1;
    forn(i, 4) forn(j, 4) total[i][j]=0;
    int len=0;
    forn(i, M) {
        string x;
        cin >> x;
        human.pb(x);
        len=x.size();
    }
    forn(i, N) {
        string x;
        cin >> x;
        mice.pb(x);
    }
    forn(i, M) forn(j, N) forn(k, len) {
        int x=convert(human[i][k]), y=convert(mice[j][k]);
        if (x>y) swap(x, y);
        total[x][y]++;
    }
    btrk(0, 0, 0, 0);
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
