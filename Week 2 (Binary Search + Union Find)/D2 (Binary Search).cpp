#include<bits/stdc++.h>
using namespace std;

bool poss(vector<pair<int, int> > *sta, int R, long long mid) {
//    for (i: *sta) {
//        long long begin=i.first, end=i.second;
//        if (begin<=mid) {
//            if (mid<=end) R-=mid-begin+1;
//            else R-=end-begin+1;
//        }
//    }
    for (int i=0; i < (*sta).size(); i++) {
        long long begin = (*sta)[i].first, end = (*sta)[i].second;
        if (begin <= mid) {
            if (mid <= end) R -= mid-begin+1;
            else R-=end-begin+1;
        }
    }
    if (R >= 1) return true;
    return false;
}

void solve() {
    int S, F;
    cin >> S >> F;
    vector<pair<int, int> > stations;
    for (int i=0; i<S; i++) {
        int x, y;
        cin >> x >> y;
        stations.push_back(make_pair(x, y));
    }
    for (int i=0; i<F; i++) {
        int R;
        cin >> R;
        long long low=0, high=INT_MAX;
        while (low+1<high) {
            long long mid=(low+high)/2;
            if (poss(&stations, R, mid)) low=mid;
            else high=mid;
        }
        cout << high << '\n';
    }
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
