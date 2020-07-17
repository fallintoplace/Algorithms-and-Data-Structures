#include<bits/stdc++.h>
using namespace std;

void solve() {
    int N, M;
    cin >> N >> M;
    vector<vector<pair<int, bool> > > Graph(N);
    for (int i = 0; i < M; i++) {
        char f;
        int x, y;
        cin >> f >> x >> y;
        x--, y--;
        Graph[x].push_back(make_pair(y, f == 'F'));
        Graph[y].push_back(make_pair(x, f == 'F'));
    }

    stack<pair<int, bool> > search; search.push(make_pair(0, true));
    vector<bool> marked(N); marked[0]=true;
    int friends=0;

    while (search.size()) {
        int current = search.top().first; bool grad = search.top().second;
        search.pop();
        if (grad==true) friends++;
//        for (i: Graph[current]) {
//            int next=i.first; bool rel=i.second;
//            if (!marked[next]) {
//                marked[next]=true;
//                search.push(make_pair(next, !(grad xor rel)));
//            }
//        }
        for (int i = 0; i < Graph[current].size(); i++) {
            int next = Graph[current][i].first; bool rel = Graph[current][i].second;
            if (!marked[next]) {
                marked[next] = true;
                search.push(make_pair(next, !(grad xor rel)));
            }
        }
    }
    cout << (friends > N/2? "yes" : "no") << '\n';
}

int main() {
//	freopen("2.in", "r", stdin);
	ios::sync_with_stdio(false);
	int Case;
	cin >> Case;
	for (int i=1; i<=Case; i++) {
		cout << "Case #" << i << ": ";
		solve();
	}
}
