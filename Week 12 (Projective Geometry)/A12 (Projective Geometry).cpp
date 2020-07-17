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
//    if (eq(dist(a, *this), 0) || eq(dist(*this, c), 0)) return 0;
    return eq(dist(a, *this)+dist(*this, c)-dist(a, c), 0);
}
node node::ortho(node a, node b) {
    return ((*this)*(a-b).perp());
}



void solve() {
    node a1, a2, a3, b1, b2, b3;
    a1.read();
    a2.read();
    a3.read();
    b1.read();
    b2.read();
    b3.read();

    node res=(a3*(a1-a2).perp())*(b3*(b1-b2).perp());
    if (res.Z==0) {
        cout << "strange\n";
    } else {
        res.dehomo();
        node ac=cut(a1, a2, a3, res);
        node bc=cut(b1, b2, b3, res);
        ac.dehomo();
        bc.dehomo();
        if (ac.between(a3, res) && bc.between(b3, res))
            res.print();
        else
        cout << "strange\n";

    }

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
