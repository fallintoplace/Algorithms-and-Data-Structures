#include<bits/stdc++.h>
using namespace std;

bool poss(vector<double> *payoff, double b, double prob) {
    double tempProb=prob;
//    for (i: *payoff) {
//        b-=i*tempProb;
//        tempProb*=prob;
//    }
    for (int i=0; i<(*payoff).size(); i++) {
        b -= (*payoff)[i]*tempProb;
        tempProb *= prob;
    }
    return b>0;
}

void solve() {
    int N;
    double B;
    vector<double> A;
    cin >> N >> B;
    for (int i=0; i<N; i++) {
        double a;
        cin >> a;
        A.push_back(a);
    }
    double low=0, high=1;
    while (low+1e-7 < high) {
        double mid = (low+high)/2;
        if (poss(&A, B, mid)) low = mid;
        else high=mid;
    }
    cout << low << '\n';
}

int main() {
//    freopen("1.in", "r", stdin);
    ios::sync_with_stdio(false);
    int Case;
    cin >> Case;
    for (int i=1; i<=Case; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }
}
