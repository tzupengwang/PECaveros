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
#define N 5555
void build(){

}
// bool dp[ N ][ N ];
// bool got[ N ][ N ];
char s[ N ] , t[ N ];
int ls , lt , nxt[ N ][ 26 ] , gd[ 26 ];
void init(){
  scanf( "%s" , s + 1 );
  ls = strlen( s + 1 );
  scanf( "%s" , t + 1 );
  lt = strlen( t + 1 );
  for( int i = lt - 1 ; i >= 1 ; i -- ){
    if( t[ i ] != t[ i + 1 ] ) gd[ t[ i ] - 'a' ] = i;
    for( int j = 0 ; j < 26 ; j ++ )
      nxt[ i ][ j ] = gd[ j ];
  }
}
// bool okay( int l1 , int l2 ){
  // if( l1 == 0 && l2 == 0 ) return true;
  // if( l1 == 0 || l2 == 0 || l1 > l2 ) return false;
  // if( got[ l1 ][ l2 ] ) return dp[ l1 ][ l2 ];
  // got[ l1 ][ l2 ] = true;
  // bool good = false;
  // if( s[ l1 ] == t[ l2 ] ) good = good || okay( l1 - 1 , l2 - 1 );
  // if( l2 > 1 && ( t[ l2 ] != t[ l2 - 1 ] ||
                  // t[ l2 ] != s[ l1 ] ) )
    // good = good || okay( l1 , l2 - 1 );
  // return dp[ l1 ][ l2 ] = good;
// }
inline bool okay(){
  if( s[ 1 ] != t[ 1 ] ) return false;
  if( lt == 1 ) return s[ 1 ] == t[ 1 ];
  bool got = false;
  if( t[ 1 ] != t[ 2 ] ) got = true;
  int res = 0;
  for( int i = 2 , pre = 2 ; i <= ls ; i ++ ){
    if( res && s[ i ] == s[ i - 1 ] ){
      res --;
      continue;
    }
    if( !got ){
      if( s[ i ] != t[ pre ] ) return false;
      if( ls == lt ) return true;
      if( t[ pre ] != t[ pre + 1 ] ) got = true , pre ++;
      if( !got ) continue;
    }
    while( pre < lt && !( t[ pre ] == s[ i ] &&
                          t[ pre + 1 ] != s[ i ] ) ){
      if( t[ pre ] == s[ i ] ) res ++;
      else res = 0;
      pre ++;
    }
    if( pre == lt ){
      if( i != ls ){
        while( i < ls && res ){
          if( s[ i + 1 ] == t[ pre ] ){
            i ++; res --;
          }else break;
        }
        if( i != ls )
          return false;
        return true;
      }
      return s[ ls ] == t[ lt ];
    }
    pre = lt + 1;
  }
  return true;
}
void solve(){
  puts( okay() ? "Yes" : "No" );
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
