#include<bits/stdc++.h>
using namespace std;

class Oper {
private:
    vector<int> parent, size;
public:
    Oper(int S=0) {
        for (int i=0; i<S; i++) {
            parent.push_back(i);
            size.push_back(1);
        }
    }
    int join(int a, int b) {
        a=find(a), b=find(b);
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
            root = par;
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
    int A, B, C;
    cin >> A >> B >> C;
    vector<int> money;
    vector<bool> invalid(A);
    for (int i=0; i<A-1; i++) {
        int x;
        cin >> x;
        money.push_back(x);
    }
    Oper rels(A);
    for (int i=0; i<B; i++) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        rels.join(x, y);
    }
    for (int i=0; i<C; i++) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        invalid[x]=true, invalid[y]=true;
        rels.join(x, y);
    }
    int ans=-1;
    for (int i=0; i<A-1; i++) {
        if (money[i]>ans && !rels.same(A-1, i) && !invalid[i]) ans=money[i];
    }
    if (ans==-1) cout << "impossible\n";
    else cout << ans << '\n';
}

int main() {
//    freopen("2.in", "r", stdin);
    ios::sync_with_stdio(false);
    int Case;
    cin >> Case;
    for (int i=1; i<=Case; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }
}
