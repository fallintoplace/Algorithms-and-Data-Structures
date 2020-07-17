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

#define DIG 8
long Base=1e8;
class BigInteger {
public:
    vector<long> digits;
    BigInteger(long x=0) {
        while (x!=0) {
            digits.pb(x%Base);
            x/=Base;
        }
    }
    int size() {
        return digits.size();
    }
    bool operator ==(const BigInteger &x) const {
		return (digits == x.digits);
	}
	bool operator !=(const BigInteger &x) const {
		return (digits != x.digits);
	}
	bool operator >(const BigInteger &x) const {
	    if (digits.size()>x.digits.size()) return true;
	    if (digits.size()<x.digits.size()) return false;
		for (int i=digits.size()-1; i>=0; i--) {
		    if (digits[i]>x.digits[i]) return true;
            if (digits[i]<x.digits[i]) return false;
		}
		return false;
	}
	bool operator <(const BigInteger &x) const {
	    return !(*this>=x);
	}
	bool operator >=(const BigInteger &x) const {
	    if (digits.size()>x.digits.size()) return true;
	    if (digits.size()<x.digits.size()) return false;
		for (int i=digits.size()-1; i>=0; i--) {
		    if (digits[i]>x.digits[i]) return true;
            if (digits[i]<x.digits[i]) return false;
		}
		return true;
	}
	friend ostream &operator <<(ostream &os, const BigInteger &x) {
	    if (x.digits.size()==0) os << '0';
	    if (x.digits.size()>=1) os << x.digits[x.digits.size()-1];
	    if (x.digits.size()>=2) for (int i=x.digits.size()-2; i>=0; i--) os << setfill('0') << setw(DIG) << x.digits[i];
		return os;
	}
	BigInteger normalized() {
	    for (int i=0; i+1<size(); i++) {
            if (digits[i]>=0) {
                digits[i+1]+=digits[i]/Base;
                digits[i]%=Base;
            } else {
                long rem=(digits[i]+1)/Base-1;
                digits[i+1]+=rem;
                digits[i]-=Base*rem;
            }
	    }
	    for (int i=size()-1; i>=0 && digits[i]==0; i--) {
            digits.erase(digits.begin()+i);
	    }
	    return *this;
	}
	BigInteger operator +(const BigInteger &x) {
	    BigInteger result;
	    result.digits.resize(max(x.digits.size(), digits.size())+1);
	    for (int i=0; i<digits.size(); i++) result.digits[i]+=digits[i];
	    for (int i=0; i<x.digits.size(); i++)  result.digits[i]+=x.digits[i];
	    return result.normalized();
	}
    BigInteger operator -(BigInteger x) {
	    BigInteger result;
	    result.digits=digits;
	    for (int i=0; i<x.digits.size(); i++) {
	        result.digits[i]-=x.digits[i];
	    }
	    return result.normalized();
	}
	BigInteger operator *(const BigInteger &x) {
	    BigInteger result;
	    result.digits.resize(x.digits.size()+digits.size()+1);
	    for (int i=0; i<digits.size(); i++) {
            for (int j=0; j<x.digits.size(); j++) {
                result.digits[i+j]+=digits[i]*x.digits[j];
            }
	    }
	    return result.normalized();
	}
	BigInteger operator /(BigInteger Divisor) {
        BigInteger result, rem;
        result.digits.resize(size());
        rem.digits=digits;
        BigInteger B=BigInteger(Base);
        while (rem>=Divisor) {
            int i=0;
            i=max(rem.size()-Divisor.size()-1, 0);
            BigInteger d; d.digits.resize(Divisor.size()+i);
            for (int j=i; j<Divisor.digits.size()+i; j++) d.digits[j]=Divisor.digits[j-i];
            long x=rem.digits[rem.size()-1], y=d.digits[d.size()-1];
            if (rem.size()>d.size()) {
                x=x*Base+rem.digits[rem.size()-2];
            }
            if (x/(y+1)>1) {
                result.digits[i]+=(x/(y+1));
                rem=rem-d*BigInteger(x/(y+1));
            } else {
                rem=rem-d;
                result.digits[i]+=1;
            }
            rem=rem.normalized();
            result=result.normalized();
        }
        return result.normalized();
	}

};
map<pair<BigInteger, int>, BigInteger > m;
BigInteger Pow(BigInteger B, int n) {
    BigInteger x=m[mp(B, n)];
    if (x!=0) return x;
    if (n==0) return 1;
    if (n==1) return B;
    BigInteger Half=Pow(B, n/2);

    if (n%2==0) return m[mp(B, n)]=Half*Half;
    return m[mp(B, n)]=Half*Half*B;
}

pair<BigInteger, pair<BigInteger, BigInteger> > gcd(BigInteger a, BigInteger b) {
    BigInteger
        r=b, rr=a;
    while (!(r==0)) {
        BigInteger q=rr/r, z=rr-q*r;
        rr=r;
        r=z;
    }
    return mp(rr, mp(0, 0));
}

pair<BigInteger, BigInteger> normalized(BigInteger x, BigInteger y) {
    BigInteger z=gcd(x, y).first;
    if (z==1) return mp(x, y);
    return mp(x/z, y/z);
}

pair<BigInteger, BigInteger> normalized(pair<BigInteger, BigInteger> x) {
    return normalized(x.first, x.second);
}

pair<BigInteger, BigInteger> add(pair<BigInteger, BigInteger> x, pair<BigInteger, BigInteger> y) {
    return mp(x.first*y.second+x.second*y.first, (x.second*y.second));
}

void print(pair<BigInteger, BigInteger> p) {
    cout << p.first << "/" << p.second << endl;
}


void solve() {
    int N, PP, QQ;
    cin >> N >> PP >> QQ;

    BigInteger P(PP), Q(QQ), A=P, B=Q;
    m.clear();
    if (P==Q) {
        cout << N << "/1"  << endl;
        return;
    }
    BigInteger z=gcd(P, Q).first;
    P=P/z;
    Q=Q/z;

    if (P<Q) print(normalized(P*Pow(Q, N)-Pow(P, N+1), Pow(Q, N+1)-P*Pow(Q, N)));
    else print(normalized(Pow(P, N+1)-P*Pow(Q, N), P*Pow(Q, N)-Pow(Q, N+1)));
}

int main() {
	freopen("1.in", "r", stdin);
//	freopen("1.out", "w", stdout);
	ios::sync_with_stdio(false);
	int Case;
	cin >> Case;
	for (int i=1; i<=Case; i++) {
		cout << "Case #" << i << ": ";
		solve();
	}
}
