#include<bits/stdc++.h>
using namespace std;
#define err1(x) {cerr << '(' << x << ')' << '\n';}
#define err2(x) {cerr << '{' << x << '}' << '\n';}
#define err3(x) {cerr << '[' << x << ']' << '\n';}
#define mp make_pair
#define pb push_back
#define mt make_tuple
#define double long double
#define pmax (1e9+7)
#define longmax (1e18+7)
#define forn(i, n) for(int i=0; i<n; i++)


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
    return ((a*b)*(c*d));
}
double dist(node a, node b) {
    return (a-b).norm();
}
bool eq(double x, double y) {
    return abs(x-y)<1e-8;
}
bool node::between(node a, node c){
    if (eq(dist(a, *this), 0) || eq(dist(*this, c), 0)) return 0;
    return eq(dist(a, *this)+dist(*this, c)-dist(a, c), 0);
}
node node::ortho(node a, node b) {
    return ((*this)*(a-b).perp());
}



void solve() {
    node a, b, c;
    a.read(), b.read(), c.read();
    ((a+b+c)/3).print();
    node res=((a.ortho(b, c))*(b.ortho(a, c)));
    res.dehomo().print();
    res=(((b+c)/2).
         ortho(b, c))
    *(((a+c)/2).ortho(a, c));
    res.dehomo();
    (res).print();
}

main() {
	freopen("1.in", "r", stdin);
	ios::sync_with_stdio(false);
	int Case;
	cin >> Case;
	for (int i=1; i<=Case; i++) {
		cout << "Case #" << i << ": ";
		solve();
	}
}
