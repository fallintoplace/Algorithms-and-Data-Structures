#include<bits/stdc++.h>
using namespace std;
#define err1(x, y) {cerr << '(' << x << " " << y << ')' << '\n';}
#define err2(x) {cerr << '{' << x << '}' << '\n';}
#define err3(x) {cerr << '[' << x << ']' << '\n';}
#define err4(x, y, z) {cerr << '(' << x << " " << y << " " << z << ')' << '\n';}
#define mp make_pair
#define pb push_back
#define mt make_tuple
#define double long double
#define pmax (1e9+7)
#define longmax (1e18+7)
#define forn(i, n) for(int i=0; i<n; i++)
#define F first
#define S second

vector<double> gauss(vector<vector<double> > M, vector<double> A) {
    int N=M.size();
    forn(i, N) for (int j=0; j<=i; j++) {
        double D=M[i][j];
        if (j==i) {
            forn(k, N) M[i][k]/=D;
            A[i]/=D;
        } else {
            forn(k, N) M[i][k]-=D*M[j][k];
            A[i]-=D*A[j];
        }
    }
    forn(i, N) for (int j=i+1; j<N; j++) {
        double D=M[i][j];
        forn(k, N) M[i][k]-=D*M[j][k];
        A[i]-=D*A[j];
    }
//    forn(i, N) {
//        forn(j, N) cout << M[i][j] <<  " ";
//        cout << endl;
//    }
//    forn(i, N) cout << A[i] << " "; cout << endl;
    return A;
}

vector<vector<double> > Cal(vector<vector<double> > I) {
    vector<vector<double> > M;
    forn(i, 3) M.pb(I[i]);
    forn(i, 3) forn(j, i) swap(M[i][j], M[j][i]);
//    forn(i, 4) cout << I[i][0] << " " << I[i][1] << endl;
    vector<double> P;
    P=gauss(M, I[3]);
    forn(i, 3) forn(j, 3) {
        M[i][j]*=P[j];
    }
    return M;
}


void solve() {
    vector<vector<double> > M, I, L, N;
    forn(i, 6) {
        double x, y;
        cin >> x >> y;
        I.pb({x, y, 1});
    }

    swap(I[0], I[1]);
    swap(I[2], I[3]);
    swap(I[1], I[2]);
    forn(i, 3) M.pb(I[i]);
    forn(i, 3) forn(j, i) swap(M[i][j], M[j][i]);
//    forn(i, 4) cout << I[i][0] << " " << I[i][1] << endl;
    vector<double> P;
    P=gauss(M, I[3]);
    forn(i, 3) forn(j, 3) {
        M[i][j]*=P[j];
    }

    L.pb({1, 0, 1});
    L.pb({0, 1, 1});
    L.pb({0, 0, 1});
    L.pb({1, 1, 1});
    N=Cal(L);


//    forn(i, 3) {
//        forn(j, 3) cout << M[i][j] << " ";
//        cout << endl;
//    }
//    forn(i, 3) {
//        forn(j, 3) cout << N[i][j] << " ";
//        cout << endl;
//    }

    vector<double> H=gauss(M, I[4]);
    vector<double> O=gauss(M, I[5]);
//    vector<double> L=gauss(M, I[2]);
//    vector<double> Q=gauss(M, I[3]);


    H[2]=H[0]+H[1]-H[2];
    O[2]=O[0]+O[1]-O[2];
    H[0]=H[0]/H[2];
//    H[1]=H[1]/H[2];
//    H[2]=H[2]/H[2];
//    O[0]=O[0]/O[2];
    O[1]=O[1]/O[2];
//    O[2]=O[2]/O[2];
    cout << setprecision(15) << H[1]/O[1] << endl;
//    forn(i, 3) cout << H[i] << " "; cout << endl;
//    forn(i, 3) cout << O[i] << " "; cout << endl;
//    forn(i, 3) cout << L[i] << " "; cout << endl;
//    forn(i, 3) cout << Q[i] << " "; cout << endl;


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
