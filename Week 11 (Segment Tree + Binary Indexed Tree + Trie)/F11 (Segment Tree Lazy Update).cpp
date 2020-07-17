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

int seg[50000001];
int lazy[50000001];


void add(int index, int pos, int val, int ll, int rr) {
    if (lazy[index]) {
        lazy[index*2]=1;
        lazy[index*2+1]=1;
        lazy[index]=0;
        seg[index]=0;
    }
    if (pos<ll || pos>rr) {
        return;
    } else if (ll==rr) {
        assert(ll==pos);
        seg[index]=max(seg[index]+val, 0);
    } else {
        int mid=(ll+rr)/2;
        add(index*2, pos, val, ll, mid);
        add(index*2+1, pos, val, mid+1, rr);
        seg[index]=seg[index*2]+seg[index*2+1];
    }
//    printf("%d %d %d %d %d\n", pos, val, ll, rr, seg[index]);
}

int sum(int index, int beg, int end, int ll, int rr) {
    if (lazy[index]) {
        lazy[index*2]=1;
        lazy[index*2+1]=1;
        lazy[index]=0;
        seg[index]=0;
    }
    if (end<ll || rr<beg) {
        return 0;
    } else if (beg<=ll && rr<=end) {
        int x=seg[index];
        return x;
    } else {
        int mid=(ll+rr)/2;
        int total=sum(index*2, beg, end, ll, mid)+sum(index*2+1, beg, end, mid+1, rr);
        seg[index]=seg[index*2]+seg[index*2+1];

        return total;
    }
}

void del(int index, int beg, int end, int ll, int rr) {
    if (lazy[index]) {
        lazy[index*2]=1;
        lazy[index*2+1]=1;
        lazy[index]=0;
        seg[index]=0;
    }
    if (end<ll || rr<beg) {
        return;
    } else if (beg<=ll && rr<=end) {
        seg[index]=0;
        lazy[index]=1;
    } else {
        int mid=(ll+rr)/2;
        del(index*2, beg, end, ll, mid);
        del(index*2+1, beg, end, mid+1, rr);
        seg[index]=seg[index*2]+seg[index*2+1];
    }
}


void solve() {
    int N, Q;
    cin >> N >> Q;
    forn(i, N*22) {
        seg[i]=0;
        lazy[i]=0;
    }
    int ans=0;
    forn(i, Q) {
        char c;
        int p, q;
        cin >> c;
        if (c=='s') {
            cin >> p;
            add(1, p, 1, 1, N);
        } else if (c=='d') {
            cin >> p;
            add(1, p, -1, 1, N);
        } else {
            cin >> p >> q;
//            cout << sum(1, p, q, 1, N) << endl;
            ans+=sum(1, p, q, 1, N);
            del(1, p, q, 1, N);
        }
//        cout << endl;
    }
    cout << ans << endl;
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
