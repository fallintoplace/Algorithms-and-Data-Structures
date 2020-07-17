#include<bits/stdc++.h>
using namespace std;
#define err1(x) {cerr << '(' << x << ')' << '\n';}
#define err2(x) {cerr << '{' << x << '}' << '\n';}
#define err3(x) {cerr << '[' << x << ']' << '\n';}

class Oper {
private:
    vector<int> parent, size;
public:
    Oper (int S=0) {
        for (int i=0; i<S; i++) {
            parent.push_back(i);
            size.push_back(1);
        }
    }
    int join(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return a;
        if (size[a] < size[b]) swap(a, b);
        parent[b]=a;
        size[a] += size[b];
        return a;
    }
    int find(int a) {
        int root=a;
        while (true) {
            int par=parent[root];
            if (par == root) break;
            root=par;
        }
        int current=a;
        while (current != root) {
            int nextElem = parent[current];
            parent[current] = root;
            current = nextElem;
        }
        return root;
    }
    bool same(int a, int b) {
        return find(a) == find(b);
    }
};

void solve() {
    int N;
    cin >> N;
    priority_queue<pair<int, pair<int, int> > > mst;
    for (int i=0; i<N; i++) for (int j=0; j<N; j++) {
        int m;
        cin >> m;
        if (i<j) mst.push(make_pair(-m, make_pair(i, j)));
    }
    Oper nodes(N);
    vector<pair<int, int> > ans;
    while (mst.size()) {
        pair<int, pair<int, int> > top = mst.top(); mst.pop();
        int x = top.second.first, y = top.second.second;
        if (!nodes.same(x, y)) {
            nodes.join(x, y);
            ans.push_back(top.second);
        }
    }
    sort(ans.begin(), ans.end());
    for (int i=0; i<ans.size(); i++) cout << ans[i].first+1 << " " << ans[i].second+1 << '\n';
}

int main() {
//	freopen("2.txt", "r", stdin);
	ios::sync_with_stdio(false);
	int Case;
	cin >> Case;
	for (int i=1; i<=Case; i++) {
		cout << "Case #" << i << ":\n";
		solve();
	}
}
