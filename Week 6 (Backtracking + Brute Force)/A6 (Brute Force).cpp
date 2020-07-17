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
#define max 1e9+7
#define longmax 1e18+7
#define forn(i, n) for(int i=0; i<n; i++)

int hexa[10]={0x7E, 0x30, 0x6D, 0x79, 0x33, 0x5B, 0x5F, 0x70, 0x7F, 0x7B};

vector<vector<int> > trans, rev;
int all;

bool valid(int x, int y) {
    return x>=0 && y>=0 && x<24 && y<60;
}

pair<int, int> inc(pair<int, int> p) {
    int x=p.first, y=p.second;
    return mp((x+(y+1)/60)%24, (y+1)%60);
}

vector<pair<int, int> > gen(pair<int, int> p) {
    int xp=p.first, yp=p.second;
    int a=xp/10, b=xp%10, c=yp/10, d=yp%10;
    vector<pair<int, int> > poss;
    forn(j, trans[a].size())
    forn(k, trans[b].size())
    forn(l, trans[c].size())
    forn(m, trans[d].size()) {
        int x=trans[a][j];
        int y=trans[b][k];
        int u=trans[c][l];
        int v=trans[d][m];
        int r=x*10+y;
        int s=u*10+v;
        if (valid(r, s)) poss.pb(mp(r, s));
    }
    return poss;
}

void print(pair<int, int> p) {
    cout << setfill('0') << setw(2) << p.first << ":" << setfill('0') << setw(2) << p.second << endl;
}

bool check(tuple<int, int, int, int> bitmask, pair<int, int> now, pair<int, int> seen) {
    int a=now.first/10, b=now.first%10, c=now.second/10, d=now.second%10;
    int x=seen.first/10, y=seen.first%10, u=seen.second/10, v=seen.second%10;
    if ((get<0>(bitmask)&hexa[a]) != hexa[x]) return false;
    if ((get<1>(bitmask)&hexa[b]) != hexa[y]) return false;
    if ((get<2>(bitmask)&hexa[c]) != hexa[u]) return false;
    if ((get<3>(bitmask)&hexa[d]) != hexa[v]) return false;
    return true;
}

void solve() {
    forn(i, 10) all=all|hexa[i];
    int N;
    cin >> N;
    vector<pair<int, int> > clock, poss, result;
    vector<vector<pair<int, int> > > all;
    forn(i, N) {
        string s;
        cin >> s;
        int a=s[0]-'0', b=s[1]-'0', c=s[3]-'0', d=s[4]-'0';
        int x=a*10+b;
        int y=c*10+d;
        clock.pb(mp(x, y));
    }
    poss=gen(clock[0]);
    forn(i, poss.size()) {
        bool found=false;
        pair<int, int> now=poss[i]; pair<int, int> cur=clock[0];
        int a=now.first/10, b=now.first%10, c=now.second/10, d=now.second%10;
        int x=cur.first/10, y=cur.first%10, u=cur.second/10, v=cur.second%10;
        forn(bm0, 1<<7) {
            if (found) break;
            if ((bm0&hexa[a]) != hexa[x]) continue;
            forn(bm1, 1<<7) {
                if (found) break;
                if ((bm1&hexa[b]) != hexa[y]) continue;
                forn(bm2, 1<<7) {
                    if (found) break;
                    if ((bm2&hexa[c]) != hexa[u]) continue;
                    forn(bm3, 1<<7) {
                        if (found) break;
                        if ((bm3&hexa[d]) != hexa[v]) continue;
                        tuple<int, int, int, int> bm=mt(bm0, bm1, bm2, bm3);
                        int cnt=0;
                        pair<int, int> tmp=poss[i];
                        forn(j, N) {
                            if (check(bm, tmp, clock[j])) cnt++;
                            else break;
                            tmp=inc(tmp);
                        }
                        if (cnt==N) {
                            found=true;
                            result.pb(poss[i]);
                        }
                    }
                }
            }
        }
    }
    if (!result.size()) {
        cout << "none\n";
        return;
    }
    sort(result.begin(), result.end());
    forn(i, result.size()) print(result[i]);
}

int main() {
//	freopen("1.in", "r", stdin);
	ios::sync_with_stdio(false);
	int Case;
	cin >> Case;
	trans.resize(10); rev.resize(10);
	forn(i, 10) forn(j, 10) if ((hexa[i]&hexa[j])==hexa[i]) rev[i].pb(j);
    trans[0].pb(0), trans[0].pb(8);
    trans[1].pb(0), trans[1].pb(1), trans[1].pb(3), trans[1].pb(4),
                    trans[1].pb(7), trans[1].pb(8), trans[1].pb(9);
    trans[2].pb(2), trans[2].pb(8);
    trans[3].pb(3), trans[3].pb(8), trans[3].pb(9);
    trans[4].pb(4), trans[4].pb(8), trans[4].pb(9);
    trans[5].pb(5), trans[5].pb(6), trans[5].pb(8), trans[5].pb(9);
    trans[6].pb(6), trans[6].pb(8);
    trans[7].pb(0), trans[7].pb(3), trans[7].pb(7), trans[7].pb(8), trans[7].pb(9);
    trans[8].pb(8);
    trans[9].pb(8), trans[9].pb(9);

    forn(i, 10) {
        assert(rev[i].size()==trans[i].size());
        forn(j, trans[i].size()) assert(rev[i][j]==trans[i][j]);
    }
	for (int i=1; i<=Case; i++) {
		cout << "Case #" << i << ": \n";
		solve();
	}
}
