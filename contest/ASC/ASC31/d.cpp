#include <bits/stdc++.h>

using namespace std;
//inline string to_string(const T& x){
	//stringstream ss;
	//return ss<<x,ss.str();
//}
typedef long long LL;
struct bigN:vector<LL>{
	const static int base=1000000000,width=log10(base);
	bool negative;
	bigN(const_iterator a,const_iterator b):vector<LL>(a,b){}
	bigN(string s){
		if(s.empty())return;
		if(s[0]=='-')negative=1,s=s.substr(1);
		else negative=0;
		for(int i=int(s.size())-1;i>=0;i-=width){
			LL t=0;
			for(int j=max(0,i-width+1);j<=i;++j)
				t=t*10+s[j]-'0';
			push_back(t);
		}
		trim();
	}
	template<typename T>
	bigN(const T &x):bigN(to_string(x)){}
	bigN():negative(0){}
	void trim(){
		while(size()&&!back())pop_back();
		if(empty())negative=0;
	}
	void carry(int _base=base){
		for(size_t i=0;i<size();++i){
			if(at(i)>=0&&at(i)<_base)continue;
			if(i+1u==size())push_back(0);
			int r=at(i)%_base;
			if(r<0)r+=_base;
			at(i+1)+=(at(i)-r)/_base;
			at(i)=r;
		}
	}
	int abscmp(const bigN &b)const{
		if(size()>b.size())return 1;
		if(size()<b.size())return -1;
		for(int i=int(size())-1;i>=0;--i){
			if(at(i)>b[i])return 1;
			if(at(i)<b[i])return -1;
		}
		return 0;
	}
	int cmp(const bigN &b)const{
		if(negative!=b.negative)return negative?-1:1;
		return negative?-abscmp(b):abscmp(b);
	}
	bool operator<(const bigN&b)const{return cmp(b)<0;}
	bool operator>(const bigN&b)const{return cmp(b)>0;}
	bool operator<=(const bigN&b)const{return cmp(b)<=0;}
	bool operator>=(const bigN&b)const{return cmp(b)>=0;}
	bool operator==(const bigN&b)const{return !cmp(b);}
	bool operator!=(const bigN&b)const{return cmp(b)!=0;}
	bigN abs()const{
		bigN res=*this;
		return res.negative=0, res;
	}
	bigN operator-()const{
		bigN res=*this;
		return res.negative=!negative, res;
	}
	bigN operator+(const bigN &b)const{
		if(negative)return -(-(*this)+(-b));
		if(b.negative)return *this-(-b);
		bigN res=*this;
		if(b.size()>size())res.resize(b.size());
		for(size_t i=0;i<b.size();++i)res[i]+=b[i];
		return res.carry(),res.trim(),res;
	}
	bigN operator-(const bigN &b)const{
		if(negative)return -(-(*this)-(-b));
		if(b.negative)return *this+(-b);
		if(abscmp(b)<0)return -(b-(*this));
		bigN res=*this;
		if(b.size()>size())res.resize(b.size());
		for(size_t i=0;i<b.size();++i)res[i]-=b[i];
		return res.carry(),res.trim(),res;
	}
	bigN operator*(const bigN &b)const{
		bigN res;
		res.negative=negative!=b.negative;
		res.resize(size()+b.size());
		for(size_t i=0;i<size();++i)
			for(size_t j=0;j<b.size();++j)
				if((res[i+j]+=at(i)*b[j])>=base){
					res[i+j+1]+=res[i+j]/base;
					res[i+j]%=base;
				}//乘法用carry會溢位
		return res.trim(),res;
	}
	/* 用二分搜做除法很慢 
	bigN operator/(const bigN &b)const{
		bigN res;
		if(size()<b.size())return res;
		if(negative||b.negative){
			res=abs()/b.abs();
			res.negative=negative!=b.negative;
			return res.trim(),res;
		}
		res.resize(size()-b.size()+1);
		for(int i=int(res.size())-1;i>=0;--i){
			int l=0,r=base-1,ans=l,mid;
			while(l<=r){
				res[i]=mid=(l+r)/2;
				if((res*b).abscmp(*this)>0)r=mid-1;
				else l=mid+1,ans=mid;
			}
			res[i]=ans;
		}
		return res.carry(),res.trim(),res;
	}
	/*/
	bigN operator/(const bigN &b)const{
		int norm=base/(b.back()+1);
		bigN x=abs()*norm;
		bigN y=b.abs()*norm;
		bigN q,r;
		q.resize(x.size());
		for(int i=int(x.size())-1;i>=0;--i){
			r=r*base+x[i];
			int s1=r.size()<=y.size()?0:r[y.size()];
			int s2=r.size()<y.size()?0:r[y.size()-1];
			int d=(LL(base)*s1+s2)/y.back();
			r=r-y*d;
			while(r.negative)r=r+y,--d;
			q[i]=d;
		}
		q.negative=negative!=b.negative;
		return q.trim(),q;
	}
	//*/
	bigN operator%(const bigN &b)const{
		return *this-(*this/b)*b;
	}
	friend istream& operator>>(istream &ss,bigN &b){
		string s;
		return ss>>s, b=s, ss;
	}
	friend ostream& operator<<(ostream &ss,const bigN &b){
		if(b.negative)ss<<'-';
		ss<<(b.empty()?0:b.back());
		for(int i=int(b.size())-2;i>=0;--i)
		ss<<setw(width)<<setfill('0')<<b[i];
		return ss;
	}
	template<typename T>
	operator T(){
		stringstream ss;
		ss<<*this;
		T res;
		return ss>>res,res;
	}
};

bigN C(bigN n, int k) {
  bigN res(1);
  for (int i = 0; i < k; ++i) {
    res = res * n;
    n = n - 1;
  }
  //for (int i = 0; i < k; ++i) {
    //res = res / (i+1);
  //}
  return res;
}

int main() {
#ifdef ONLINE_JUDGE
  freopen("discuss.in", "r", stdin);
  freopen("discuss.out", "w", stdout);
#endif
  bigN z;
  cin >> z;
  bigN ans = z;
  bigN target = z;
  for (int k = 2; k <= 300; ++k) {
    cout << k << endl;
    target = target * k;
    bigN l(k+k);
    bigN r(ans), mid;
    bigN res(1);
    while (l <= r) {
      mid = (l+r) / 2;
      if (C(mid, k) <= target) {
        res = mid;
        l = mid+1;
      }
      else r = mid-1;
    }
    if (C(res, k) == target) ans = min(ans, res);
  }
  cout << ans << endl;
}
