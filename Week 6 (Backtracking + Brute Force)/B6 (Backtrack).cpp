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

vector<vector<vector<bool> > > sat;
int M, N;
vector<int> rec;
bool hasAns;

void btrk(int m) {
    if (hasAns) return;
    if (m==M) {
        forn(i, N) {
            bool has=false;
            forn(j, M) {
                if (sat[i][j][rec[j]]) {
                    has=true;
                    break;
                }
            }
            if (!has) return;
        }
        cout << "yes\n";
        hasAns=true;
        return;
    }
    rec[m]=0;
    btrk(m+1);
    rec[m]=1;
    btrk(m+1);
}

void solve() {
    cin >> M >> N;
    rec.resize(M);
    hasAns=false;
    sat=vector<vector<vector<bool> > >(N, vector<vector<bool> >(vector<vector<bool> >(M, vector<bool>(2))));
    forn(i, N) {
        while (true) {
            int x;
            cin >> x;
            if (x==0) break;
            if (x>0) {
                x--;
                sat[i][x][0]=true;
            } else {
                x=-x;
                x--;
                sat[i][x][1]=true;
            }
        }
    }
    btrk(0);
    if (!hasAns) cout << "no\n";
}

int main() {
//	freopen("2.in", "r", stdin);
	ios::sync_with_stdio(false);
	int Case;
	cin >> Case;
	for (int i=1; i<=Case; i++) {
		cout << "Case #" << i << ": ";
		solve();
	}
}
