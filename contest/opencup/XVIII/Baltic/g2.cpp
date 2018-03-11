#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
// x^K mod P = A
const int LimitSave = 100000;
LL add( LL a , LL b , LL mod ){
  return (a + b) % mod;
}
LL mul( LL a , LL b , LL mod ){
  if( mod <= (1LL << 31) )
    return (a % mod * (b % mod)) % mod;
  LL ret = 0;
  while( b ){
    if( b & 1 ) ret = (ret + a) % mod;
    a = (a + a) % mod;
    b >>= 1;
  }
  return ret;
}
LL mypow( LL a , LL b , LL mod ){
  LL ret = 1;
  while( b ){
    if( b & 1 ) ret = mul( ret , a , mod );
    a = mul( a , a , mod );
    b >>= 1;
  }
  return ret;
}
// n < 4,759,123,141        3 :  2, 7, 61
// n < 1,122,004,669,633    4 :  2, 13, 23, 1662803
// n < 3,474,749,660,383          6 :  pirmes <= 13
// n < 2^64                       7 :
// 2, 325, 9375, 28178, 450775, 9780504, 1795265022
// Make sure testing integer is in range [2, n−2] if
// you want to use magic.
bool witness(LL a,LL n,LL u,int t){
	LL x=mypow(a,u,n);
	for(int i=0;i<t;i++) {
		LL nx=mul(x,x,n);
		if(nx==1&&x!=1&&x!=n-1) return 1;
		x=nx;
	}
	return x!=1;
}
bool is_p(LL n) {
	// iterate s times of witness on n
	// return 1 if prime, 0 otherwise
	if(n<2) return 0;
	if(!(n&1)) return n == 2;
	LL u=n-1; int t=0;
	// n-1 = u*2^t
	while(!(u&1)) u>>=1, t++;
  for( LL a : {2, 325, 9375, 28178, 450775, 9780504, 1795265022} ){
    if( a > n - 2 ) continue;
		if(witness(a,n,u,t)) return 0;
	}
	return 1;
}
// does not work when n is prime
LL f(LL x, LL mod){
	return add(mul(x,x,mod),1,mod);
}
LL pollard_rho(LL n) {
	if(!(n&1)) return 2;
  while(true){
    LL y=2, x=rand()%(n-1)+1, res=1;
    for(int sz=2; res==1; sz*=2) {
      for(int i=0; i<sz && res<=1; i++) {
        x = f(x, n);
        res = __gcd(abs(x-y), n);
      }
      y = x;
    }
    if (res!=0 && res!=n) return res;
  }
}
LL _mod( LL a , LL mo ){return ( a % mo + mo ) % mo;}
bool ext_gcd(LL A, LL B, LL C, LL &x, LL &y, LL &gn){
	LL t;
	if( A == 0 ){
		gn = B;
		if( _mod(C, B) == 0 )
    { x = 0; y = C / B; return true; }
		return false;
	}
  if( ext_gcd( _mod(B , A) , A , C , y , t , gn ) )
  { x = t - LL(B / A) * y; return true; }
	return false;
}
LL Division( LL A, LL B, LL modular ){
	LL gcdnum, K, Y = 0;
	ext_gcd(modular, B, A, K, Y, gcdnum);
	Y = _mod(Y, modular);
  return Y < 0 ? Y + modular : Y;
}
struct tp{
	LL expo, res;
}data[ LimitSave + 100 ];
bool compareab( const tp &a, const tp &b )
{ return a.res < b.res; }
bool Binary_Search( LL key, LL &pos ){
	LL start, stop;
	start=1; stop=LimitSave;
	while( start <= stop ){
		pos = (start + stop)/2;
		if( data[pos].res == key ) return true;
		if( data[pos].res < key ) start = pos + 1;
		else stop = pos - 1;
	}
	return false;
}
LL get_log( LL root , LL A , LL mod ){
	LL i, j, times, XD, XT, position;
	if( mod - 1 < LimitSave ){
		LL now = 1;
    for( i = 0 ; i < mod ; i ++ ){
			if( now == A ) return i;
			now = _mod( now * root , mod );
		}
	}
	data[1].expo = 0; data[1].res = 1;
  for( i = 1 ; i < LimitSave ; i ++ ){
		data[i+1].expo=i;
		data[i+1].res=_mod(data[i].res*root,mod);
	}
	sort(data+1,data+LimitSave+1,compareab);
	times=mypow(root,LimitSave,mod);
	j=0; XD=1;
	while( 1 ){
		XT = Division(A, XD, mod);
		if( Binary_Search( XT, position ) )
			return j + data[position].expo;
		j = j + LimitSave;
		XD = _mod(XD * times, mod);
	}
}
LL P, K, A;
vector<LL> ans;
vector<int> pri;
LL get_originroot( LL p ){
  LL primes[ 100 ];
	LL tot = 0, tp = P - 1;
	for( LL i = 2 ; i * i <= P - 1 ; i ++ )
		if( _mod( tp , i ) == 0 ){
			primes[ ++ tot ]=i;
			while( _mod(tp,i) == 0 ) tp /= i;
		}
	if( tp != 1 ) primes[ ++ tot] = tp;
	for( LL i = 2 ; ; i ++ ){
		bool ok = true;
    for( LL j = 1 ; j <= tot ; j ++ )
			if( mypow(i, (P-1)/primes[j], P ) == 1 )
      { ok = false; break; }
		if( ok ) return i;
	}
}
bool pp[ (1 << 20) ];
void build(){
  for( int i = 2 ; i < (1 << 20) ; i ++ ) if( !pp[ i ] ){
    pri.push_back( i );
    for( int j = i ; j < (1 << 20) ; j ++ )
      pp[ j ] = true;
  }
}
//x^K mod P = A
LL work_ans() {
  // cin >> P >> K >> A
  A = A % P;
	ans.clear(); // roots in ans
	if( A == 0 ) return 0;
	LL root,logs,delta,deltapower,now,gcdnum,x,y;
  root=get_originroot(P);
	logs=get_log(root,A,P);
  cerr << root << " " << logs << endl;
	if( ext_gcd(K, P-1, logs, x, y, gcdnum) ){
		delta=(P-1) / gcdnum;
		x = _mod(x, delta);
		if(x < 0) x += delta;
		now = mypow(root, x, P);
		deltapower = mypow(root, delta, P);
		while(x < P-1 ){
			//ans.push_back(now);
      return now;
			now=_mod(now * deltapower, P);
			x=x+delta;
		}
	}
  return -1;
}
// x^p = a (mod q)
int main(){
  build();
  int t; cin >> t; while( t -- ){
    //cin >> p >> a >> q;
    cin >> K >> A >> P;
    printf( "%lld\n" , work_ans() );
  }
}
