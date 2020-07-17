#include<bits/stdc++.h>
using namespace std;

bool poss(double d, long long p, double u, double v, double dist) {
    long long begin = u/dist, end = (d-v)/dist;
    double remBeg = u-dist*begin, remEnd = (d-v)-dist*end, gap = (v-u)+remBeg+remEnd;
    p-=begin+end;
    if (p>2 || (p==2 && gap<dist)) return false;
    return true;
}

void solve() {
    double D, U, V;
    long long P;
    cin >> D >> P >> U >> V;
    double low=0, high=D;
    while (low+1e-10 < high) {
        double mid = (low+high)/2;
        if (poss(D, P, U, V, mid)) low = mid;
        else high = mid;
    }
    cout << setprecision(10) << low << '\n';
}

int main() {
    freopen("2.in", "r", stdin);
    ios::sync_with_stdio(false);
    int Case;
    cin >> Case;
    for (int i=1; i<=Case; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }
}
