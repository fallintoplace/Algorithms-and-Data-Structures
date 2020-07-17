#include<bits/stdc++.h>
using namespace std;
#define err1(x) {cerr << '(' << x << ')' << '\n';}
#define err2(x) {cerr << '{' << x << '}' << '\n';}
#define err3(x) {cerr << '[' << x << ']' << '\n';}
#define mp make_pair
#define pb push_back
#define mt make_tuple
#define long long long
#define double long double
#define pmax (1e9+7)
#define longmax (1e18+7)
#define forn(i, n) for(int i=0; i<n; i++)

class Trie {
public:
    Trie* next[26];
    int f[4][2][2];
    ~Trie();
    Trie() {
        forn(i, 4) forn(j, 2) forn(k, 2) f[i][j][k]=-3;
        for (int i=0; i<26; i++)
            this->next[i]=nullptr;
    }
    void insert(string key) {
        Trie* cur=this;
        for (int i=0; i<key.length(); i++) {
            if (cur->next[key[i]-'a']==nullptr)
                cur->next[key[i]-'a']=new Trie();
            cur=cur->next[key[i]-'a'];
        }
    }
};

void solve() {
    Trie *root=new Trie();
    int N;
    cin >> N;
    vector<string> dict;
    forn(i, N) {
        string S;
        cin >> S;
        dict.pb(S);
        root->insert(S);
    }
    int ans=0;
    forn(i, N) {
        ans+=root->search(dict[i]);
    }
    cout << ans << endl;
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
