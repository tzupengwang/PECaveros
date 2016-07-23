// eddy1021
#include <bits/stdc++.h>
using namespace std;
typedef double D;
typedef long double LD;
typedef long long ll;
typedef long long LL;
typedef pair<int,int> PII;
typedef pair<LL,LL> PLL;
typedef pair<LD,LD> Pt;
typedef tuple<int,int,int> tiii;
typedef tuple<LL,LL,LL> tlll;
#define mod9 1000000009ll
#define mod7 1000000007ll
#define INF  1023456789ll
#define INF16 10000000000000000ll
#define FI first
#define SE second
#define X FI
#define Y SE
#define PB push_back
#define MP make_pair
#define MT make_tuple
#define eps 1e-9
#define SZ(x) (int)(x).size()
#define ALL(x) (x).begin(), (x).end()
#ifndef ONLINE_JUDGE
#define debug(...) printf(__VA_ARGS__)
#else 
#define debug(...)
#endif
inline ll getint(){
  ll _x=0,_tmp=1; char _tc=getchar();    
  while( (_tc<'0'||_tc>'9')&&_tc!='-' ) _tc=getchar();
  if( _tc == '-' ) _tc=getchar() , _tmp = -1;
  while(_tc>='0'&&_tc<='9') _x*=10,_x+=(_tc-'0'),_tc=getchar();
  return _x*_tmp;
}
inline ll add( ll _x , ll _y , ll _mod = mod7 ){
  ll _ = _x + _y;
  if( _ >= _mod ) _ -= _mod;
  return _;
}
inline ll sub( ll _x , ll _y , ll _mod = mod7 ){
  ll _ = _x - _y;
  if( _ < 0 ) _ += _mod;
  return _;
}
inline ll mul( ll _x , ll _y , ll _mod = mod7 ){
  ll _ = _x * _y;
  if( _ >= _mod ) _ %= _mod;
  return _;
}
ll mypow( ll _a , ll _x , ll _mod ){
  if( _x == 0 ) return 1ll;
  ll _tmp = mypow( _a , _x / 2 , _mod );
  _tmp = mul( _tmp , _tmp , _mod );
  if( _x & 1 ) _tmp = mul( _tmp , _a , _mod );
  return _tmp;
}
ll mymul( ll _a , ll _x , ll _mod ){
  if( _x == 0 ) return 0ll;
  ll _tmp = mymul( _a , _x / 2 , _mod );
  _tmp = add( _tmp , _tmp , _mod );
  if( _x & 1 ) _tmp = add( _tmp , _a , _mod );
  return _tmp;
}
inline bool equal( D _x ,  D _y ){
  return _x > _y - eps && _x < _y + eps;
}
int __ = 1 , _cs;
/*********default*********/
#define N 5050
void build(){

}
int n;
int a[ N ] , b[ N ] , c[ N ] , d[ N ];
int suma[ N ] , sumb[ N ];
int sumc[ N ] , sumd[ N ];
D sum1 , sum2;
void init(){
  n = getint();
  for( int i = 1 ; i <= n ; i ++ ){
    a[ i ] = getint();
    b[ i ] = getint();
    c[ i ] = getint();
    d[ i ] = getint();
    suma[ i ] = suma[ i - 1 ] + a[ i ];
    sumb[ i ] = sumb[ i - 1 ] + b[ i ];
    sumc[ i ] = sumc[ i - 1 ] + c[ i ];
    sumd[ i ] = sumd[ i - 1 ] + d[ i ];
    sum1 += a[ i ] + b[ i ];
    sum2 += c[ i ] + d[ i ];
  }
}
inline pair<D,D> cal( D fst ){
  D time1 = 0.0 , time2 = 0.0;
  for( int i = 1 ; i <= n ; i ++ ){
    time1 += (D)a[ i ] * fst + (D)b[ i ];
    time2 += (D)c[ i ] * ( 1.0 - fst ) + (D)d[ i ];
  }
  return { time1 , time2 };
}
inline D cal1(){
  D l = 0.0 , r = 1.0 , mid , ans;
  for( int i = 0 ; i < 100 ; i ++ ){
    mid = ( l + r ) * 0.5;
    pair<D,D> tp = cal( mid );
    if( tp.FI < tp.SE ) ans = tp.SE , l = mid;
    else ans = tp.FI , r = mid;
  }
  return min( ans , min( sum1 , sum2 ) );
}
inline D cal2(){
  D ans = 0.0;
  for( int i = 1 ; i <= n ; i ++ ){
    D l = 0.0 , r = 1.0 , mid , tans = 1e20;
    for( int j = 0 ; j < 100 ; j ++ ){
      mid = ( l + r ) * 0.5;
      D time1 = (D)a[ i ] * mid + (D)b[ i ];
      D time2 = (D)c[ i ] * ( 1.0 - mid ) + (D)d[ i ];
      if( time1 < time2 ){
        tans = time2;
        l = mid;
      }else{
        tans = time1;
        r = mid;
      }
    }
    ans += min( tans , (D)min( a[ i ] + b[ i ] , c[ i ] + d[ i ] ) );
  }
  return ans;
}
D dpmn[ N ] , dpmx[ N ];
void solve(){
  D ans1 = cal1();
  D ans2 = cal2();
  for( int i = 1 ; i <= n ; i ++ ){
    dpmn[ i ] = +1e20;
    dpmx[ i ] = -1e20;
    for( int j = 1 ; j <= i ; j ++ ){
      int sa = suma[ i ] - suma[ j - 1 ];
      int sb = sumb[ i ] - sumb[ j - 1 ];
      int sc = sumc[ i ] - sumc[ j - 1 ];
      int sd = sumd[ i ] - sumd[ j - 1 ];
      D tmp = min( sa + sb , sc + sd );
      if( sa + sc != 0 ){
        D tk = (D)( sc + sd - sb ) / (D)( sa + sc );
        if( -eps < tk && tk < 1.0 + eps )
          tmp = min( tmp , sa * tk + sb );
      }
      dpmn[ i ] = min( dpmn[ i ] , dpmn[ j - 1 ] + tmp );
      dpmx[ i ] = max( dpmx[ i ] , dpmx[ j - 1 ] + tmp );
    }
    // printf( "%d : %.12f %.12f\n" , i , dpmn[ i ] , dpmx[ i ] );
  }
  printf( "%.12f\n%.12f\n%.12f\n%.12f\n" , ans1 , ans2 , dpmn[ n ] , dpmx[ n ] );
}
int main(){
  freopen( "braess.in" , "r" , stdin );
  freopen( "braess.out" , "w" , stdout );
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
