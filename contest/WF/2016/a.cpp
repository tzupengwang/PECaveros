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
#define N 1010101
ll n , k , a[ N ] , suma , b[ N ] , cnt[ N ];
void build(){

}
void init(){
  n = getint();
  k = getint();
  for( int i = 1 ; i <= n ; i ++ ){
    a[ i ] = getint();
    suma += a[ i ];
  }
  for( int i = 1 ; i <= k ; i ++ )
    b[ i ] = getint();
  if( k % suma == 0 ){
    puts( "forever" );
    exit( 0 );
  }
  if( k > suma ){
    int xx = k / suma;
    int res = k % suma;
    for( int i = 1 ; i <= res ; i ++ )
      b[ i ] = b[ i + xx * suma ];
    k = res;
  }
  for( int i = 1 ; i <= k ; i ++ )
    cnt[ b[ i ] ] ++;
}
vector<PLL> cand[ N ];
inline PLL itv( int i , ll tk , int s ){
  ll lb = 1 + ( ( tk - 1 ) * suma ) / a[ i ];
  ll rb = ( tk * suma ) / a[ i ];
  if( ( tk * suma ) % a[ i ] == 0 )
    rb --;
  lb = max( lb , (ll)s + 1 );
  return MP( lb , rb );
}
inline void Add( int i , int s ){
  if( cnt[ i ] < a[ i ] ){
    PLL tp = itv( i , cnt[ i ] + 1 , s );
    if( s == k && tp.FI > tp.SE ){
      puts( "0" );
      exit( 0 );
    }
    cand[ tp.FI ].PB( MP( tp.SE , i ) );
    cnt[ i ] ++;
  }
}
void solve(){
  for( int i = 1 ; i <= n ; i ++ )
    Add( i , k );
  // puts( "====" );
  priority_queue< PLL , vector<PLL> , greater<PLL> > heap;
  for( int i = k + 1 ; i <= suma ; i ++ ){
    for( size_t j = 0 ; j < cand[ i ].size() ; j ++ )
      heap.push( cand[ i ][ j ] );
    if( heap.empty() ){
      printf( "%lld\n" , i - k - 1 );
      exit( 0 );
    }
    PLL tp = heap.top(); heap.pop();
    if( tp.FI < i ){
      bool okay = false;
      if( tp.FI + 1 >= i ){
        okay = true;
        if( heap.size() && heap.top().FI < i )
          okay = false;
      }
      if( !okay ){
        printf( "%lld\n" , i - k - 1 );
        exit( 0 );
      }
    }
    // printf( "%d %lld\n" , i , tp.SE );
    Add( tp.SE , i );
  }
  puts( "forever" );
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
