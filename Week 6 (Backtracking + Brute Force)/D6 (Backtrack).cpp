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

int N;
vector<vector<bool> > board;
vector<bool> row, col, diag1, diag2;
bool hasAns;

void btrk(int i) {
    if (hasAns) return;
    if (i==N) {
        forn(i, N) {
            forn(j, N)
                if (board[i][j])
                    cout << 'x';
                else cout << '.';
            cout << endl;
        }
        hasAns=true;
        return;
    }
    if (row[i]) btrk(i+1);
    else {
        forn(j, N) if (!board[i][j] && !row[i] && !col[j] && !diag1[i+j] && !diag2[N-i+j]) {
            board[i][j]=row[i]=col[j]=diag1[i+j]=diag2[N-i+j]=true;
            btrk(i+1);
            board[i][j]=row[i]=col[j]=diag1[i+j]=diag2[N-i+j]=false;
        }
    }
}

void solve() {
    cin >> N;
    hasAns=false;
    board=vector<vector<bool> >(N, vector<bool>(N, false));
    row=col=diag1=diag2=vector<bool>(N, false);
    diag1=diag2=vector<bool>(N+N);
    bool inva=false;
    forn(i, N) {
        string s;
        cin >> s;
        forn(j, s.size()) {
            if (s[j]=='x') {
                if ((row[i]|col[j]|diag1[i+j]|diag2[N-i+j]) == true) {
                    inva=true;
                }
                board[i][j]=row[i]=col[j]=diag1[i+j]=diag2[N-i+j]=true;
            }
        }
    }
    if (inva) {
        cout << "impossible\n"; return;
    }
    btrk(0);
    if (!hasAns) cout << "impossible\n";
}

int main() {
//	freopen("1.in", "r", stdin);
	ios::sync_with_stdio(false);
	int Case;
	cin >> Case;
	for (int i=1; i<=Case; i++) {
		cout << "Case #" << i << ":\n";
		solve();
	}
}
