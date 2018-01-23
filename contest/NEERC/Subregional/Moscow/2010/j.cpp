#include <bits/stdc++.h>
using namespace std;
#define SZ(X) ((X).size())
#ifndef SUN_MOON_BIG_INT
#define SUN_MOON_BIG_INT
#define SM_BASE 1000000000
#define SM_BASE_DIGITS 9
/*SM_BASE 0 的個數為SM_BASE_DIGITS*/
#include<vector>
#include<iostream>
#include<iomanip>
#include<string>
#include<utility>/*for pair*/
class bigN{
	private:
	std::vector<int>s;
	char sign;
	inline void trim(){
		while(!s.empty()&&!s.back())s.pop_back();
		if(s.empty())sign=1;
	}
	inline char cmp(const bigN &v,bool is=1)const{
		if(is){
			if(sign>v.sign)return 1;
			if(sign<v.sign)return -1;
		}
		char d=sign>0||!is?1:-1;
		if(s.size()>v.s.size())return d;
		if(s.size()<v.s.size())return -d;
		for(int i=s.size()-1;i>=0;i--){
			if(s[i]>v.s[i])return d;
			if(s[i]<v.s[i])return -d;
		}
		return 0;
	}
	public:
	/*初始化*/
	bigN():sign(1){}
	bigN(const long long &v){
		*this=v;
	}
	bigN(const std::string &v){
		*this=v;
	}
	/*等於運算子重載*/
	inline void operator=(const bigN &v){
		sign=v.sign;
		s=v.s;
	}
	inline void operator=(long long v){
		sign=1;s.clear();
		if (v < 0)sign=-1,v=-v;
		for(;v;v/=SM_BASE)s.push_back(v%SM_BASE);
	}
	inline void operator=(const std::string &v){
		sign=1;s.clear();
		int len=0;
		for(;len<(int)v.size()&&(v[len]=='-'||v[len]=='+');len++)
		if(v[len]=='-')sign=-1;
		for(int i=v.size()-1;i>=len;i-=SM_BASE_DIGITS){
			int x=0;
			for(int j=std::max(len,i-SM_BASE_DIGITS+1);j<=i;j++)
			x=x*10+v[j]-'0';
			s.push_back(x);
		}
		trim();
	}
	/*加減運算子重載*/
	inline bigN operator+(const bigN &v)const{
		if(sign==v.sign){
			bigN ans=v;
			int len=std::max(s.size(),v.s.size());
			for(int i=0,is=0;i<len||is;i++){
				if(i==(int)ans.s.size())ans.s.push_back(0);
				ans.s[i]+=is+(i<(int)s.size()?s[i]:0);
				is=ans.s[i]>=SM_BASE;
				if(is)ans.s[i]-=SM_BASE;
			}
			return ans;
		}else return *this-(-v);
	}
	inline bigN operator-(const bigN &v)const{
		if(sign==v.sign){
			if(~cmp(v,0)){
				bigN ans=*this;
				for(int i=0,is=0;i<(int)v.s.size()||is;i++){
					ans.s[i]-=is+(i<(int)v.s.size()?v.s[i]:0);
					is=ans.s[i]<0;
					if(is)ans.s[i]+=SM_BASE;
				}
				ans.trim();
				return ans;
			}else return -(v-*this);
		}else return *this+(-v);
	}
	/*乘法運算子重載*/
	inline bigN operator*(const bigN &v)const{
		std::vector<long long>num;
		num.resize(s.size()+v.s.size());
		for(int i=0;i<(int)s.size();i++){
			for(int j=0;j<(int)v.s.size();j++){
				num[i+j]+=(long long)s[i]*v.s[j];
				if(num[i+j]>=SM_BASE){
					num[i+j+1]+=num[i+j]/SM_BASE;
					num[i+j]%=SM_BASE;
				}
			}
		}
		bigN ans;
		ans.sign=sign*v.sign;
		ans.s.resize(num.size());
		for(int i=0;i<(int)num.size();i++)ans.s[i]=(int)num[i];
		ans.trim();
		return ans;
	}
	/*對整數的乘除做支援運算*/
	inline void operator*=(int v){
		if(v<0)sign=-sign,v=-v;
		for(int i=0,is=0;i<(int)s.size()||is;i++){
			if(i==(int)s.size())s.push_back(0);
			long long a=s[i]*(long long)v+is;
			is=(int)(a/SM_BASE);
			s[i]=(int)(a%SM_BASE);
		}
		trim();
	}
	inline bigN operator*(int v){
		bigN ans=*this;
		ans*=v;
		return ans;
	}
	inline void operator/=(int v){
		if(v<0)sign=-sign,v=-v;
		for(int i=s.size()-1,rem=0;i>=0;i--){
			long long a=s[i]+rem*(long long)SM_BASE;
			s[i]=(int)(a/v);
			rem=a%v;
		}
		trim();
	}
	inline bigN operator/(int v){
		bigN ans=*this;
		ans/=v;
		return ans;
	}
	inline int operator%(int v){
		if(v<0)v=-v;
		int m=0;
		for(int i=s.size()-1;i>=0;i--)
		m=(s[i]+m*(long long)SM_BASE)%v;
		return m*sign;
	}
	/*除法，商為first，餘為second*/
	inline friend std::pair<bigN,bigN>divmod(const bigN &a,const bigN &b){
		int norm=SM_BASE/(b.s.back()+1);
		bigN x=a.abs()*norm;
		bigN y=b.abs()*norm;
		bigN q,r;
		q.s.resize(x.s.size());
		for(int i=x.s.size()-1;i>=0;i--){
			r*=SM_BASE;
			r+=x.s[i];
			int s1=r.s.size()<=y.s.size()?0:r.s[y.s.size()];
			int s2=r.s.size()<=y.s.size()-1?0:r.s[y.s.size()-1];
			int d=((long long)SM_BASE*s1+s2)/y.s.back();
			r-=y*d;
			while(r.cmp(0,1)==-1)r+=y,--d;
			q.s[i]=d;
		}
		q.sign=a.sign*b.sign;
		r.sign=a.sign;
		q.trim();
		r.trim();
		return std::make_pair(q,r/norm);
	}
	inline bigN operator/(const bigN &v)const{
		return divmod(*this,v).first;
	}
	inline bigN operator%(const bigN &v)const{
		return divmod(*this,v).second;
	}
	/*數學指派運算子重載*/
	inline void operator+=(const bigN &v){
		*this=*this+v;
	}
	inline void operator-=(const bigN &v){
		*this=*this-v;
	}
	inline void operator*=(const bigN &v){
		*this=*this*v;
	}
	inline void operator/=(const bigN &v){
		*this=*this/v;
	}
	inline void operator%=(const bigN &v){
		*this=*this%v;
	}
	/*比較運算子重載*/
	inline bool operator<(const bigN &v)const{
		return cmp(v)<0;
	}
	inline bool operator>(const bigN &v)const{
		return cmp(v)>0;
	}
	inline bool operator<=(const bigN &v)const{
		return cmp(v)<=0;
	}
	inline bool operator>=(const bigN &v)const{
		return cmp(v)>=0;
	}
	inline bool operator==(const bigN &v)const{
		return !cmp(v);
	}
	inline bool operator!=(const bigN &v)const{
		return cmp(v)!=0;
	}
	/*數學運算子重載*/
	inline bigN abs()const{
		bigN ans=*this;
		ans.sign*=ans.sign;
		return ans;
	}
	inline bigN operator-()const{
		bigN ans=*this;
		ans.sign=-sign;
		return ans;
	}
	/* >>、<<運算子重載 */
	friend std::istream& operator>>(std::istream &stream,bigN &v) {
		std::string s;
		stream>>s;
		v=s;
		return stream;
	}
	friend std::ostream& operator<<(std::ostream &stream,const bigN &v) {
		if(v.sign==-1)stream<<'-';
		stream<<(v.s.empty()?0:v.s.back());
		for(int i=(int)v.s.size()-2;i>=0;i--)
		stream<<std::setw(SM_BASE_DIGITS)<<std::setfill('0')<<v.s[i];
		return stream;
	}
	/*是否為0*/
	inline bool iszero(){
		return !s.size()||(s.size()==1&&!s[0]);
	}
	/*形態重載*/
	inline operator std::string(){
		std::string ans,x;
		if(s.empty())return "0";
		if(sign==-1)ans+='-';
		int o=s[s.size()-1];
		while(o)x+=o%10+'0',o/=10;
		for(int i=x.size()-1;i>=0;i--)ans+=x[i];
		for(int i=s.size()-2;i>=0;i--){
			std::string t;
			int p=s[i];
			for(int j=0;j<SM_BASE_DIGITS;j++){
				t+=p%10+'0';p/=10;
			}
			for(int j=SM_BASE_DIGITS-1;j>=0;j--)ans+=t[j];
		}
		return ans;
	}
};
#endif
#undef SM_BASE
#undef SM_BASE_DIGITS
string a , b , aa , bb;
int lena , lenb;
void solve(){
  int cnta = 0 , cntb = 0;
  lena = a.length();
  lenb = b.length();
  for( int i = 0 ; i < lena ; i ++ )
    if( a[ i ] == '.' ){
      cnta = lena - i - 1;
      break;
    }
  for( int i = 0 ; i < lenb ; i ++ )
    if( b[ i ] == '.' ){
      cntb = lenb - i - 1;
      break;
    }
  int nda = max( cnta , cntb ) - cnta;
  int ndb = max( cnta , cntb ) - cntb;
  for( int i = 0 ; i < lena ; i ++ ){
    if( a[ i ] == '.' ) continue;
    aa += a[ i ];
  }
  for( int i = 0 ; i < lenb ; i ++ ){
    if( b[ i ] == '.' ) continue;
    bb += b[ i ];
  }
  while( nda -- ) aa += "0";
  while( ndb -- ) bb += "0";
  bigN ai( aa ) , bi( bb );
  bigN ci = ai / bi;
  string ans = ci;
  cout << ans << endl;
}
int main(){
  cin >> a >> b;
  solve();
}
