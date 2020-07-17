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
#define longmax     (1e18+7)
#define forn(i, n)  for(int i=0; i<n; i++)
#define F   first
#define S   second
# define PI     3.14159265358979323846

class node {
public:
    double X, Y, Z;
    node(double x=0, double y=0, double z=1) {
        X=x, Y=y, Z=z;
    }
    node dehomo() {
        if (Z!=0) {
            X/=Z;
            Y/=Z;
            Z/=Z;
        }
        return *this;
    }
    void read() {
        cin >> X >> Y;
        Z=1;
    }
    void print() {
        if (Z==0) cout << "strange\n";
        else {
            cout << setprecision(14) << X << " " << setprecision(14) << Y << endl;
        }
    }
    double norm() {
        return sqrt(X*X+Y*Y+Z*Z);
    }
    node perp() {
        return node(Y, -X, Z);
    }
    node ortho(node a, node b);
    bool between(node a, node c);

};
node operator + (node a, node b) {
    return node(a.X+b.X, a.Y+b.Y, a.Z+b.Z);
}
node operator - (node a, node b) {
    return node(a.X-b.X, a.Y-b.Y, a.Z-b.Z);
}
node operator * (node a, double b) {
    return node(a.X*b, a.Y*b, a.Z*b);
}
node operator / (node a, double b) {
    return node(a.X/b, a.Y/b, a.Z/b);
}
double dot(node a, node b) {
    return a.X*b.X+a.Y*b.Y+a.Z*b.Z;
}
node operator *(node a, node b) {
    return node(a.Y*b.Z-a.Z*b.Y, a.Z*b.X-a.X*b.Z, a.X*b.Y-a.Y*b.X);
}
node cut(node a, node b, node c, node d) {
    node res=((a*b)*(c*d));
    return res.dehomo();
}
double dist(node a, node b) {
    return (a-b).norm();
}
bool eq(double x, double y) {
    return abs(x-y)<1e-8;
}
bool node::between(node a, node c){
    return eq(dist(a, *this)+dist(*this, c)-dist(a, c), 0);
}
node node::ortho(node a, node b) {
    return ((*this)*(a-b).perp());
}

vector<double> mul(vector<double> b, vector<vector<double> > a) {
    int N=a.size();
    vector<double> c(N);
    forn(i, N) forn(j, N) c[i]+=a[i][j]*b[j];
    return c;
}

vector<vector<double> > mul(vector<vector<double> > b, vector<vector<double> > a) {
    int N=a.size();
    vector<vector<double> > c=b;
    forn(i, N) forn(j, N) c[i][j]=0;
    forn(i, N) forn(j, N) forn(k, N) c[i][k]+=a[i][j]*b[j][k];
    return c;
}


int N, D;
double A;
map<char, string> M;

string btrk(string S, int n) {
    if (n==0) return S;
    string res;
    forn(i, S.size()) {
        if (M.count(S[i])) res+=btrk(M[S[i]], n-1);
        else res+=S[i];
    }
    return res;
}
void print(vector<double> A) {
    cout << setprecision(10) << A[0] << " " << setprecision(10) << A[1] << endl;
}

void print(vector<vector<double> > A) {
    int N=A.size();
    forn(i, N) { forn(j, N) cout << A[i][j] << " "; cout << endl; }
}


void solve() {
    string Starl;
    M.clear();
    cin >> N >> D >> A >> Starl;
    A=A/180*PI;
    forn(i, N) {
        string S, SS;
        cin >> S;
        for (int j=3; j<S.size(); j++) SS=SS+S[j];
        M[S[0]]=SS;
    }
    string res;
//    cout << (res=btrk(Starl, D)) << endl;
    res=btrk(Starl, D);
    vector<double> B=vector<double>({0, 0, 1});
    vector<vector<double> > N={{1, 0, 1}, {0, 1, 0}, {0, 0, 1}};
    double rr=0;

//    vector<vector<double> > M={{cos(rr), -sin(rr), 0}, {sin(rr), cos(rr), 0}, {0, 0, 1}};
////    print(mul(M, N));
//    print(mul(B, mul(N, M)));


    print(B);
    forn(i, res.size()) {
        if (res[i]=='+') {
            rr+=A;
        } else if (res[i]=='-') {
            rr-=A;
        } else {

            vector<vector<double> > M={{cos(rr), -sin(rr), 0}, {sin(rr), cos(rr), 0}, {0, 0, 1}};
            vector<vector<double> > N={{1, 0, 1}, {0, 1, 0}, {0, 0, 1}};
            vector<double> C=vector<double>({0, 0, 1});
            C=mul(C, mul(N, M));
            forn(i, 2) B[i]+=C[i];
            print(B);
        }
    }
}

main() {

//    vector<vector<double> > N={{1, 0, 1}, {0, 1, 0}, {0, 0, 1}};
//    vector<double> B=vector<double>({0, 0, 1});
//    B=mul(B, N);
//    forn(i, 3) cout << B[i] << " "; cout << endl;

//	freopen("1.in", "r", stdin);
	ios::sync_with_stdio(false);
	int Case;
	cin >> Case;
	for (int i=1; i<=Case; i++) {
		cout << "Case #" << i << ": ";
		solve();
	}
}
