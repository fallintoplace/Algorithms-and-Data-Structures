#include<bits/stdc++.h>
using namespace std;
#define err1(x) {cerr << '(' << x << ')' << '\n';}
#define err2(x) {cerr << '{' << x << '}' << '\n';}
#define err3(x) {cerr << '[' << x << ']' << '\n';}
#define mp make_pair
#define pb push_back
#define mt make_tuple
#define long long long
#define double BigInteger double
#define pmax (1e9+7)
#define BigIntegermax (1e18+7)
#define forn(i, n) for(int i=0; i<n; i++)

long Base=1e9;
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
    long operator [](const int &x) const &{
        return digits[x];
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
	    if (digits == x.digits) return false;
		for (int i=digits.size()-1; i>=0; i--) {
		    if (digits[i]>x.digits[i]) return true;
            if (digits[i]<x.digits[i]) return false;
		}
		return true;
	}
	bool operator >=(const BigInteger &x) const {
	    return *this>x || *this==x;
	}
	friend ostream &operator <<(ostream &os, const BigInteger &x) {
	    if (x.digits.size()==0) os << '0';
	    if (x.digits.size()>=1) os << x.digits[x.digits.size()-1];
	    if (x.digits.size()>=2) for (int i=x.digits.size()-2; i>=0; i--) os << setfill('0') << setw(9) << x.digits[i];
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
	BigInteger operator +(BigInteger x) {
	    BigInteger result;
	    result.digits.resize(max(x.digits.size(), digits.size())+1);
	    for (int i=0; i<digits.size(); i++) result.digits[i]+=digits[i];
	    for (int i=0; i<x.digits.size(); i++)  result.digits[i]+=x.digits[i];
	    return result.normalized();
	}
    BigInteger operator -(BigInteger x) {
	    BigInteger result;
	    result.digits=digits;
//	    assert(*this>=x);
	    for (int i=0; i<x.digits.size(); i++) {
	        result.digits[i]-=x.digits[i];
	    }
	    return result.normalized();
	}
	BigInteger operator *(BigInteger x) {
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

            BigInteger d=Divisor;
            int i=0;
            while (rem>=d*B) {
                d=d*B;
                i++;
            }

            long x=rem.digits[rem.size()-1], y=d.digits[d.size()-1];

            if (x<y) {
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

        }
        return result.normalized();
	}
};

void swapGCD(BigInteger &a, BigInteger &b, BigInteger c, BigInteger d) {
    a=c;
    b=d;
}

pair<BigInteger, pair<BigInteger, BigInteger> > gcd(BigInteger a, BigInteger b) {
    BigInteger s=0, ss=1,
        t=1, tt=0,
        r=b, rr=a;
    while (r!=0) {
        BigInteger q=rr/r;
        swapGCD(rr, r, r, rr-q*r);

    }
    return mp(rr, mp(ss, tt));
}

void solve() {
    int N;
    cin >> N;
    vector<BigInteger> candies;
    forn(i, N) {
        BigInteger x; long xx;
        cin >> xx; x=BigInteger(xx);
        candies.pb(x);
    }
    BigInteger res=1;
    forn(bm, (1<<N)) {
        BigInteger now=1;
        forn(i, N) {
            if (bm&(1<<i)) now=now+candies[i];
        }
        res=res/gcd(res, now).first*(now);
    }
    cout << res << endl;
}

int main() {
	freopen("1.in", "r", stdin);
	ios::sync_with_stdio(false);
	int Case;
	cin >> Case;
	for (int i=1; i<=Case; i++) {
		cout << "Case #" << i << ": ";
		solve();
	}
}
