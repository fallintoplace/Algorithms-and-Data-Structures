#include<bits/stdc++.h>
using namespace std;
#define err1(x, y) {cerr << '(' << x << " " << y << ')' << '\n';}
#define err2(x) {cerr << '{' << x << '}' << '\n';}
#define err3(x) {cerr << '[' << x << ']' << '\n';}
#define mp make_pair
#define pb push_back
#define mt make_tuple
#define double long double
#define pmax (1e9+7)
#define longmax (1e18+7)
#define forn(i, n) for(int i=0; i<n; i++)
#define F first
#define S second

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

vector<pair<node, node> > obj;
int N, X, Y;
bool mark[200][200];

void sim(int X, int Y) {
    if (mark[X][Y]) return;
    mark[X][Y]=true;
//    cout << X << " " << Y << endl;
    if (Y==0) return;
    int i=0;
    node cur=cut(node(X, Y), node(X, 0), obj[0].F, obj[0].S);
    forn(j, obj.size()) {
        node inter=cut(node(X, Y), node(X, 0), obj[j].F, obj[j].S);
//        err1(inter.X, inter.Y);
        if (inter.between(obj[j].F, obj[j].S)) {
            if (inter.Y>cur.Y && inter.Y<Y) {
                cur=inter;
                i=j;
            }
        }
    }
    if (i!=0) {
        node inter=cut(node(X, Y), node(X, 0), obj[i].F, obj[i].S);
        if (inter.between(obj[i].F, obj[i].S)) {
            if (obj[i].F.Y==obj[i].S.Y) {
                sim(obj[i].F.X, obj[i].F.Y);
                sim(obj[i].S.X, obj[i].S.Y);
            } else if (obj[i].F.Y<obj[i].S.Y) {
                sim(obj[i].F.X, obj[i].F.Y);
            } else if (obj[i].F.Y>obj[i].S.Y) {
                sim(obj[i].S.X, obj[i].S.Y);
            }
        }
        if (inter.X==X && obj[i].F.X==X) {
            sim(obj[i].F.X, obj[i].F.Y);
        }
        if (inter.X==X && obj[i].S.X==X) {
            sim(obj[i].S.X, obj[i].S.Y);
        }
    } else {
        sim(X, 0);
    }
}

void solve() {
    cin >> N >> X >> Y;
    obj.clear();
    obj.pb(mp(node(0, 0), node(200, 0)));
    forn(i, N) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        obj.pb(mp(node(a, b), node(c, d)));
    }
    forn(i, 200) forn(j, 200) mark[i][j]=0;
    sim(X, Y);
    forn(i, 200) if (mark[i][0]) cout << i << " ";
    cout << endl;
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
