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
#define N 2020202
char c[ N ] , in[ N ];
void build(){

}
int len;
bool init(){
  gets( in );
  // puts( in );
  if( !strcmp( in , "#" ) ) return false;
  len = 0;
  int tlen = strlen( in );
  for( int i = 0 ; i < tlen ; i ++ )
    if( in[ i ] == 'S' ||
        in[ i ] == '<' ||
        in[ i ] == '>' ||
        isdigit( in[ i ] ) )
      c[ len ++ ] = in[ i ];
  c[ len ] = '\0';
  // puts( c );
  return true;
}
bool is_sft[ N ];
int rgt[ N ];
inline int go( int l , int r ){
  // printf( "%d %d\n" , l , r );
  int pre = -1;
  for( int i = l ; i <= r ; ){
    if( c[ i ] == 'S' ){
      int vl = go( i + 2 , rgt[ i + 1 ] - 1 );
      vl = mul( vl , vl );
      if( pre == -1 ) pre = vl;
      else{
        if( vl > 30 ) pre = 0;
        else pre >>= vl;
      }
      i = rgt[ i + 1 ] + 1;
    }else if( isdigit( c[ i ] ) ){
      int til = i , vl = 0;
      while( til <= r && isdigit( c[ til ] ) ) til ++;
      for( int j = i ; j < til ; j ++ )
        vl = vl * 10 + c[ j ] - '0';
      if( pre == -1 ) pre = vl;
      else{
        if( vl > 30 ) pre = 0;
        else pre >>= vl;
      }
      i = til;
    }else if( is_sft[ i ] && is_sft[ i + 1 ] ) i += 2;
    else assert( false );
  }
  return pre;
}
void solve(){
  for( int i = 0 ; i < len ; i ++ ){
    is_sft[ i ] = false;
    rgt[ i ] = 0;
  }
  for( int i = 0 ; i + 2 < len ; i ++ )
    if( c[ i ] == '>' && c[ i + 1 ] == '>' ){
      if( c[ i + 2 ] == 'S' ||
          isdigit( c[ i + 2 ] ) ){
        is_sft[ i     ] = true;
        is_sft[ i + 1 ] = true;
      }
    }
  // for( int i = 0 ; i < len ; i ++ ){
    // if( is_sft[ i ] ) putchar( '1' );
    // else putchar( '0' );
  // }
  // puts( "" );
  vector< int > vv;
  for( int i = 0 ; i < len ; i ++ )
    if( c[ i ] == '<' ) vv.push_back( i );
    else if( c[ i ] == '>' && !is_sft[ i ] ){
      rgt[ vv.back() ] = i;
      vv.pop_back();
    }
  printf( "%d\n" , go( 0 , len - 1 ) );
}
int main(){
  build();
  //__ = getint();
  while( init() ){
    solve();
  }
}
