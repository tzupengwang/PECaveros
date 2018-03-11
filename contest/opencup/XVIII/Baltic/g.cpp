#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define MAGIC 32109
LL add( LL a , LL b , LL mod ){
  return (a + b) % mod;
}
LL mul( LL a , LL b , LL mod ){
  if( mod < (1LL << 31) )
    return (a % mod * (b % mod)) % mod;
  LL ret = 0;
  while( b ){
    if( b & 1LL ) ret = (ret + a) % mod;
    a = (a + a) % mod;
    b >>= 1;
  }
  return ret;
}
LL mypow( LL a , LL b , LL mod ){
  LL ret = 1;
  while( b ){
    if( b & 1LL ) ret = mul( ret , a , mod );
    a = mul( a , a , mod );
    b >>= 1;
  }
  return ret;
}
bool witness(LL a,LL n,LL u,LL t){
	LL x=mypow(a,u,n);
	for(LL i=0;i<t;i++) {
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
	LL u=n-1; LL t=0;
	// n-1 = u*2^t
	while(!(u&1)) u>>=1, t++;
  for( LL a : {2, 325, 9375, 28178, 450775, 9780504, 1795265022} ){
    if( a > n - 2 ) continue;
		if(witness(a,n,u,t)) return 0;
	}
	return 1;
}
LL f(LL x, LL mod){
	return add(mul(x,x,mod),1,mod);
}
LL pollard_rho(LL n) {
	if(!(n&1)) return 2;
  while(true){
    LL y=2, x=rand()%(n-1)+1, res=1;
    for(LL sz=2; res==1; sz*=2) {
      for(LL i=0; i<sz && res<=1; i++) {
        x = f(x, n);
        res = __gcd(abs(x-y), n);
      }
      y = x;
    }
    if (res!=0 && res!=n) return res;
  }
}
pair<LL,LL> gcd(LL a, LL b){
	if(b == 0) return {1, 0};
  pair<LL,LL> q = gcd(b, a % b);
  return {q.second, q.first - q.second * (a / b)};
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
LL get_log( LL root , LL A , LL mod ){
  // root ^ x = A (% mod)
  vector< pair<LL,LL> > wt;
  LL sn = 1;
  while( sn < MAGIC and sn * sn <= mod ) sn ++;
  for( LL i = 0 , v = 1 ; i < sn ; i ++ ){
    wt.push_back( {v, i} );
    v = mul( v , root , mod );
  }
  sort( wt.begin() , wt.end() );
  LL cc = mypow( root , sn , mod );
  for( LL i = 0 , v = 1 ; i < sn ; i ++ ){
    LL need = (gcd( v , mod ).first + mod) % mod;
    need = mul( need , A , mod );
    size_t at = lower_bound( wt.begin() , wt.end() , make_pair(need , -1LL) ) - wt.begin();
    if( at < wt.size() ){
      if( need == wt[ at ].first )
        return i * sn + wt[ at ].second;
    }
    v = mul( v , cc , mod );
  }
  return -1;
}
LL P , K , A;
vector<LL> pri;
LL get_originroot( LL p ){
  vector<LL> cand;
  {
    LL tp = p - 1;
    for( auto i : cand ){
      if( i * i > tp ) break;
      if( tp % i ) continue;
      cand.push_back( i );
      while( tp % i == 0 )
        tp /= i;
    }
    if( tp > 1 ){
      if( is_p( tp ) )
        cand.push_back( tp );
      else{
        LL x = pollard_rho( tp );
        cand.push_back( x );
        cand.push_back( tp / x );
      }
    }
  }
	for( LL i = 2 ; ; i ++ ){
		bool ok = true;
    for( LL j : cand )
			if( mypow(i, (P - 1) / j, P ) == 1 )
      { ok = false; break; }
		if( ok ) return i;
	}
}
LL work_ans() {
  A = A % P;
	if( A == 0 ) return 0;
	LL root,logs,delta,now,gcdnum,x,y;
  root=get_originroot(P);
  if( (P - 1) % K == 0 and (P - 1) / K < 1e7 ){
    LL vv = mypow( root , K , P );
    for( LL r = 0 , i = root , j = vv ;
         r <= (P - 1) / K ;
         i = mul( i , root , P ) ,
         j = mul( j , vv , P ) , r ++ )
      if( j == A )
        return i;
    return -1;
  }
	logs=get_log(root,A,P);
  if( logs == -1 ) return -1;
  //cerr << root << " " << logs << endl;
	if( ext_gcd(K, P-1, logs, x, y, gcdnum) ){
		delta=(P-1) / gcdnum;
		x = _mod(x, delta);
		if(x < 0) x += delta;
		now = mypow(root, x, P);
    return now;
	}
  return -1;
}
bool pp[ (1 << 20) ];
void build(){
  for( int i = 2 ; i < (1 << 20) ; i ++ ) if( !pp[ i ] ){
    pri.push_back( i );
    for( int j = i ; j < (1 << 20) ; j ++ )
      pp[ j ] = true;
  }
}
LL p , a , q;
void solve(){
  pair<LL,LL> ret = gcd( p , q - 1 );
  ret.first = (ret.first % (q - 1) + q - 1) % (q - 1);
  printf( "%lld\n" , mypow( a , ret.first , q ) );
}
int main(){
  build();
  int t; cin >> t; while( t -- ){
    cin >> p >> a >> q;
    if( q > 10 and __gcd( p , q - 1 ) == 1 ) solve();
    else{
      K = p;
      A = a;
      P = q;
      printf( "%lld\n" , work_ans() );
    }
  }
}
