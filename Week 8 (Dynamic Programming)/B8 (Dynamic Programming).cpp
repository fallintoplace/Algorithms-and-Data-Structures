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

string A, B;
int f[1000][1000], len, res;

void cal() {
    forn(k, len) {
        int cur=0;
        forn(i, A.size()+1)
            forn(j, len+1) f[i][j]=0;
        forn(i, A.size()+1) {
            forn(j, len+1) {
                if (i==0) f[i][j]=0;
                else if (j==0) f[i][j]=0;
                else {
                    f[i][j] = max(f[i-1][j], f[i][j-1]);
                    if (A[i-1]==B[k+j-1]) f[i][j] = max(f[i][j], f[i-1][j-1]+1);
                    cur = max(cur, f[i][j]);
//                    if (f[i][j]==4) {
//                        cout << A << " ";
//                        forn(i, len) cout << B[k+i];
//                        cout << endl;
//                    }

                }
            }
        }
        res=max(res, cur);
    }
}

void solve() {
    cin >> A >> B;
    len=B.size();
    B+=B;
    res=0;
    cal();
    reverse(A.begin(), A.end());
    cal();
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
