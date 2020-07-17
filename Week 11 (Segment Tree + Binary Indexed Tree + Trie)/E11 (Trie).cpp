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
    Trie* next[60];
    int f[4][2][2];
    Trie() {
        forn(i, 4) forn(j, 2) forn(k, 2) f[i][j][k]=-3;
        for (int i=0; i<60; i++)
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

int R, N;
int cnt;
Trie* root;

void print(bool a) {
    if (a) cout << "victory\n";
    else cout << "defeat\n";
}
bool play1(bool side, int round, Trie* cur) {
    if (round==R) {
        return 1;
    }
    if (cur->f[cnt][side][round]!=-3) return cur->f[cnt][side][round];
    bool res=false, has=false;
    for (int i=0; i<60; i++) {
        if (cur->next[i]!=nullptr) {
            has=true;
            if (play1(!side, round, cur->next[i])==0) {
                res=1;
                break;
            }
        }
    }
    if (!has) return cur->f[cnt][side][round]=play1(side, round+1, root);
    return cur->f[cnt][side][round]=res;
}

bool play2(bool side, int round, Trie* cur) {
    if (round==R) {
        return 0;
    }
    if (cur->f[cnt][side][round]!=-3) return cur->f[cnt][side][round];
    bool res=false, has=false;
    for (int i=0; i<60; i++) {
        if (cur->next[i]!=nullptr) {
            has=true;
            if (play2(!side, round, cur->next[i])==0) {
                res=1;
                break;
            }
        }
    }
    if (!has) return cur->f[cnt][side][round]=!play2(!side, round+1, root);
    return cur->f[cnt][side][round]=res;
}
void solve() {
    root=new Trie();
    int Round;
    cin >> Round >> N;
    forn(i, N) {
        string s;
        cin >> s;
        root->insert(s);
    }
    R=1; cnt=0;
    bool res1=play1(0, 0, root);
    R=2; cnt=1;
    bool res2=play1(0, 0, root);
    if (res1==res2) print(res1);
    else {
        if (Round%2==1) print(res1);
        else {
            print(res2);
        }
    }
    R=1; cnt=2;
    bool res3=play2(0, 0, root);
    R=2; cnt=3;
    bool res4=play2(0, 0, root);
    if (res3==res4) print(res3);
    else {
        if (Round%2==1) print(res3);
        else {
            print(res4);
        }
    }
    if (res1==res2) print(!res1);
    else {
        if (Round%2==1) print(!res1);
        else {
            print(!res2);
        }
    }
    if (res3==res4) print(!res3);
    else {
        if (Round%2==1) print(!res3);
        else {
            print(!res4);
        }
    }
}

main() {
//	freopen("1.in", "r", stdin);
	ios::sync_with_stdio(false);
	int Case;
	cin >> Case;
	for (int i=1; i<=Case; i++) {
		cout << "Case #" << i << ":\n";
		solve();
	}
}
