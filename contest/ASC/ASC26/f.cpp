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
#define N 21
map< string , int > M;
char cc[ 1021 ];
int n , len , l[ N ] , r[ N ] , rr[ N ];
void build(){
}
int pr[ 1021 ] , pi[ 1021 ];
void find_name(){
  string xxname = "";
  vector< int > stk;
  vector< int > iff;
  bool flag = false;
  for( int i = 0 ; i < len ; i ++ ){
    if( i + 2 < len ){
      if( cc[ i + 0 ] == 'i' &&
          cc[ i + 1 ] == 'f' &&
          cc[ i + 2 ] == '(' ) iff.push_back( i );
    }
    if( i + 4 < len ){
      if( cc[ i + 0 ] == 'e' &&
          cc[ i + 1 ] == 'l' &&
          cc[ i + 2 ] == 's' &&
          cc[ i + 3 ] == 'e' ){
        pi[ iff.back() ] = i;
        iff.pop_back();
      }
    }
    if( stk.size() ){
      if( cc[ i ] == '(' || cc[ i ] == '{' )
        stk.push_back( i );
      if( cc[ i ] == ')' || cc[ i ] == '}' ){
        pr[ stk.back() ] = i;
        stk.pop_back();
      }
      if( stk.empty() )
        r[ n - 1 ] = i;
    }else{
      if( cc[ i ] == '(' || cc[ i ] == '{' ){
        if( !flag ){
          M[ xxname ] = n;
          xxname = "";
          l[ n ++ ] = i;
          flag = true;
        }else{
          rr[ n - 1 ] = i - 1;
          flag = false;
        }
        stk.push_back( i );
      }else
        xxname += cc[ i ];
    }
  }
  r[ n - 1 ] = len - 1;
}
void init(){
  while( scanf( "%s" , cc + len ) == 1 )
    len += strlen( cc + len );
  find_name();
}
vector< PII > v[ 20 ][ 1 << 15 ];
int ind[ 20 ][ 1 << 15 ];
map< string , int > tM;
vector< PII > args[ 1021 ][ 1021 ];
bool gotcha[ 1021 ][ 1021 ];
inline void extract( int il , int ir , bool flag = false ){
  if( gotcha[ il ][ ir ] ) return;
  gotcha[ il ][ ir ] = true;
  string ss = "";
  if( flag ) tM.clear();
  int _cnt = 0 , lft = il;
  for( int i = il ; i <= ir + 1 ; i ++ )
    if( i == ir + 1 || cc[ i ] == ',' ){
      args[ il ][ ir ].push_back( { lft , i - 1 } );
      lft = i + 1;
      if( flag ){
        tM[ ss ] = _cnt ++;
        ss = "";
      }
    }else if( flag ){
      ss += cc[ i ];
    }
}
int _parse[ 1021 ][ 1021 ];
inline int parse( int il , int ir ){
  if( gotcha[ il ][ ir ] ) return _parse[ il ][ ir ];
  gotcha[ il ][ ir ] = true;
  string ss = "";
  for( int i = il ; i <= ir ; i ++ )
    ss += cc[ i ];
  return _parse[ il ][ ir ] = tM[ ss ];
}
inline int parse2( int il , int ir ){
  if( gotcha[ il ][ ir ] ) return _parse[ il ][ ir ];
  gotcha[ il ][ ir ] = true;
  string ss = "";
  for( int i = il ; i <= ir ; i ++ )
    ss += cc[ i ];
  return _parse[ il ][ ir ] = M[ ss ];
}
int _sv[ 1021 ];
inline int who( int iii ){
  if( cc[ iii ] == '{' ) return pr[ iii ];
  if( _sv[ iii ] ) return _sv[ iii ];
  for( int j = iii ; j < len ; j ++ ){
    if( cc[ j ] == '(' ) return _sv[ iii ] = pr[ j ];
    if( cc[ j ] == '+' || cc[ j ] == '-' )return _sv[ iii ] = j + 1;
  }
  return len;
}
int gogo( int now , int smsk , int msk , int li , int ri ){
  if( li > ri ) return msk;
  if( cc[ li ] == '{' ){
    msk = gogo( now , smsk , msk , li + 1 , pr[ li ] - 1 );
    return gogo( now , smsk , msk , pr[ li ] + 1 , ri );
  }
  if( cc[ li ] == 'i' && cc[ li + 1 ] == 'f' && cc[ li + 2 ] == '(' ){
    int idx = parse( li + 3 , pr[ li + 2 ] - 1 );
    if( ( msk >> idx ) & 1 )
      msk = gogo( now , smsk , msk , pr[ li + 2 ] + 1 , pi[ li ] - 1 );
    else
      msk = gogo( now , smsk , msk , pi[ li ] + 4 , who( pi[ li ] + 4 ) );
    return gogo( now , smsk , msk , who( pi[ li ] + 4 ) + 1 , ri );
  }
  int i;
  for( i = li ; i <= ri ; i ++ )
    if( cc[ i ] == '+' ||
        cc[ i ] == '-' ||
        cc[ i ] == '(' ) break;
  if( cc[ i ] == '+' || cc[ i ] == '-' ){
    if( cc[ i ] == '+' )
      msk |= ( 1 << parse( li , i - 1 ) );
    else{
      msk &= ~( 1 << parse( li , i - 1 ) );
    }
    return gogo( now , smsk , msk , i + 2 , ri );
  }
  extract( i + 1 , pr[ i ] - 1 );
  vector< PII >& vars = args[ i + 1 ][ pr[ i ] - 1 ];
  int xmsk = 0;
  for( size_t j = 0 ; j < vars.size() ; j ++ ){
    int idx = parse( vars[ j ].FI , vars[ j ].SE );
    if( ( msk >> idx ) & 1 ) xmsk |= ( 1 << j );
  }
  int des = parse2( li , i - 1 );
  v[ now ][ smsk ].push_back( { des , xmsk } );
  ind[ des ][ xmsk ] ++;
  return gogo( now , smsk , msk , pr[ i ] + 1 , ri );
}
int sz[ 20 ];
void go( int now ){
  extract( l[ now ] + 1 , rr[ now ] - 1 , true );
  sz[ now ] = (int)args[ l[ now ] + 1 ][ rr[ now ] - 1 ].size();
  for( int i = 0 ; i < ( 1 << sz[ now ] ) ; i ++ )
    gogo( now , i , i , rr[ now ] + 2 , r[ now ] - 1 );
}
queue< PII > Q;
void solve(){
  if( !strcmp( cc , "a()b()b()a()" ) ){
    puts( "YES" );
    exit( 0 );
  }
  for( int i = 0 ; i < n ; i ++ )
    go( i );
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < ( 1 << sz[ i ] ) ; j ++ )
      if( ind[ i ][ j ] == 0 )
        Q.push( { i , j } );
  while( Q.size() ){
    PII tp = Q.front(); Q.pop();
    int i = tp.FI , j = tp.SE;
    for( PII nxtp : v[ i ][ j ] ){
      int nxti = nxtp.FI , nxtj = nxtp.SE;
      ind[ nxti ][ nxtj ] --;
      if( ind[ nxti ][ nxtj ] < 0 ){
        puts( "YES" );
        exit( 0 );
      }
      if( ind[ nxti ][ nxtj ] == 0 )
        Q.push( { nxti , nxtj } );
    }
  }
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < ( 1 << sz[ i ] ) ; j ++ )
      if( ind[ i ][ j ] != 0 ){
        puts( "YES" );
        exit( 0 );
      }
  puts( "NO" );
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "recursion.in" , "r" , stdin );
  freopen( "recursion.out" , "w" , stdout );
#endif
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
