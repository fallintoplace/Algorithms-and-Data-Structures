#include<bits/stdc++.h>
using namespace std;
#define err1(x) {cerr << '{' << x << '}' << '\n';}
#define err2(x, y) {cerr << '(' << x << " " << y << ')' << '\n';}
#define err3(x, y, z) {cerr << '(' << x << " " << y << " " << z << ')' << '\n';}
#define err11(x) {cerr << '[' << x << ']' << '\n';}
#define err33(x, y, z) {cerr << '[' << x << " " << y << " " << z << ']' << '\n';}
#define mp make_pair
#define pb push_back
#define mt make_tuple
#define double long double
#define pmax (1e9+7)
#define longmax (1e18+7)
#define forn(i, n) for(int i=0; i<n; i++)
#define F first
#define S second

vector<string> vec;
bool found=false;

double eval(double x, double y) {
    stack<double> st;
    forn(i, vec.size()) {
        string now=vec[i];
        if (now[0]=='+') {
            double a=st.top();
            st.pop();
            double b=st.top();
            st.pop();
            st.push(a+b);
        }
        else if (now.size()==1 && now[0]=='-') {
            double a=st.top();
            st.pop();
            double b=st.top();
            st.pop();
            st.push(b-a);
        }
        else if (now[0]=='*') {
            double a=st.top();
            st.pop();
            double b=st.top();
            st.pop();
            st.push(a*b);
        }
        else if (now[0]=='N') {
            double a=st.top();
            st.pop();
            st.push(-a);
        }
        else if (now[0]=='S') {
            double a=st.top();
            st.pop();
            st.push(sin(a));
        }
        else if (now[0]=='C') {
            double a=st.top();
            st.pop();
            st.push(cos(a));
        }
        else if (now[0]=='x') {
            st.push(x);
        }
        else if (now[0]=='y') {
            st.push(y);
        }
        else {
            stringstream ss(now);
            double a; ss >> a;

            st.push(a);
        }
    }
    return st.top();
}

void f(double x, double y, double rate) {
    if (found) return;
//    err3(x, y, rate);
    double cur = eval(x, y);
    if (eval(x+rate, y) > cur) f(x+rate, y, rate);
    if (eval(x, y+rate) > cur) f(x, y+rate, rate);
    if (eval(x-rate, y) > cur) f(x-rate, y, rate);
    if (eval(x, y-rate) > cur) f(x, y-rate, rate);
    if (!found) {
        if (rate < 0.000001) {
            found = true;
//            assert(cur > 0);
            assert(cur >= eval(x+rate, y));
            assert(cur >= eval(x-rate, y));
            assert(cur >= eval(x, y+rate));
            assert(cur >= eval(x, y-rate));
            cout << setprecision(10) << x << " " << setprecision(10) << y << endl;
        } else f(x, y, rate/1.1111);
    }
}

void solve() {
    found=false;
    vec.clear();
    int N;
    cin >> N;
    forn(i, N) {
        string x;
        cin >> x;
        vec.pb(x);
    }
//    assert(eval(0, 0)>=0);
    f(0, 0, 0.5);
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
