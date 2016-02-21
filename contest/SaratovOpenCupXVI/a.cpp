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
ll mypow( ll _a , ll _x , ll _mod ){
  if( _x == 0 ) return 1ll;
  ll _tmp = mypow( _a , _x / 2 , _mod );
  _tmp = ( _tmp * _tmp ) % _mod;
  if( _x & 1 ) _tmp = ( _tmp * _a ) % _mod;
  return _tmp;
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
inline bool equal( D _x ,  D _y ){
  return _x > _y - eps && _x < _y + eps;
}
int __ = 1 , _cs;
/*********default*********/
#define N 401
int n , t[ N ] , idx[ N ];
void build(){

}
void init(){
  n = getint();
  for( int i = 0 ; i < n ; i ++ ){
    t[ i ] = getint();
    idx[ i ] = i;
  }
}
#define K 200
bool got[ N ][ K ][ K ];
char bk[ N ][ K ][ K ];
char nn[ N ][ K ][ K ];
char g[ 3 ][ N ][ K ][ K ];
#define M 10
vector<int> v[ 3 ];
void find_ans( int now , int ii , int jj ){
  if( now == 0 ) return;
  assert( ii <= jj );
  v[ (int)bk[ now ][ ii ][ jj ] ].PB( idx[ now - 1 ] + 1 );
  int ti = t[ idx[ now - 1 ] ];
  if( nn[ now ][ ii ][ jj ] == 0 )
    find_ans( now - 1 , ii + ti , jj + ti );
  else if( nn[ now ][ ii ][ jj ] == 1 ){
    if( ii < ti )
      find_ans( now - 1 , ti - ii , ti - ii + jj );
    else
      find_ans( now - 1 , ii - ti , jj );
  }else{
    if( jj < ti )
      find_ans( now - 1 , ti - jj , ti - jj + ii );
    else
      find_ans( now - 1 , min( ii , jj - ti ) ,
                          max( ii , jj - ti ) );
  }
}
void solve(){
  srand( 10211021 );
  int aa = INF;
  for( int _ = 0 ; _ < M ; _ ++ ){
    random_shuffle( idx , idx + n );
    memset( got , 0 , sizeof( got ) );
    got[ 0 ][ 0 ][ 0 ] = true;
    for( int i = 0 ; i < 3 ; i ++ )
      g[ i ][ 0 ][ 0 ][ 0 ] = i;
    for( int i = 0 ; i < n ; i ++ )
      for( int j = 0 ; j < K ; j ++ )
        for( int k = 0 ; k < K ; k ++ )
          if( got[ i ][ j ][ k ] ){
            int ti = t[ idx[ i ] ];
            int mn = min( ti , min( j , k ) );
            int mx = max( ti , max( j , k ) );
            int md = ti + j + k - mn - mx;
            for( int l = 0 ; l < 3 ; l ++ )
              g[ l ][ i + 1 ][ md - mn ][ mx - mn ] =
                g[ l ][ i ][ j ][ k ];
            got[ i + 1 ][ md - mn ][ mx - mn ] = true;
            bk[ i + 1 ][ md - mn ][ mx - mn ] = g[ 0 ][ i ][ j ][ k ];
            nn[ i + 1 ][ md - mn ][ mx - mn ] = 0;
            if( md == ti ){
              nn[ i + 1 ][ md - mn ][ mx - mn ] = 1;
              swap( g[ 0 ][ i + 1 ][ md - mn ][ mx - mn ] ,
                    g[ 1 ][ i + 1 ][ md - mn ][ mx - mn ] );
            }else if( mx == ti ){
              nn[ i + 1 ][ md - mn ][ mx - mn ] = 2;
              swap( g[ 0 ][ i + 1 ][ md - mn ][ mx - mn ] ,
                    g[ 2 ][ i + 1 ][ md - mn ][ mx - mn ] );
              swap( g[ 0 ][ i + 1 ][ md - mn ][ mx - mn ] ,
                    g[ 1 ][ i + 1 ][ md - mn ][ mx - mn ] );
            }
            /**************************************************/
            mn = 0;
            mx = max( j + ti , k );
            md = ti + j + k - mn - mx;
            if( mx < K ){
              for( int l = 0 ; l < 3 ; l ++ )
                g[ l ][ i + 1 ][ md - mn ][ mx - mn ] =
                  g[ l ][ i ][ j ][ k ];
              got[ i + 1 ][ md - mn ][ mx - mn ] = true;
              bk[ i + 1 ][ md - mn ][ mx - mn ] = g[ 1 ][ i ][ j ][ k ];
              nn[ i + 1 ][ md - mn ][ mx - mn ] = 1;
              if( mx == j + ti ){
                nn[ i + 1 ][ md - mn ][ mx - mn ] = 2;
                swap( g[ 1 ][ i + 1 ][ md - mn ][ mx - mn ] ,
                      g[ 2 ][ i + 1 ][ md - mn ][ mx - mn ] );
              }
            }
            /**************************************************/
            mn = 0;
            mx = k + ti;
            md = ti + j + k - mn - mx;
            if( mx < K ){
              for( int l = 0 ; l < 3 ; l ++ )
                g[ l ][ i + 1 ][ md - mn ][ mx - mn ] =
                  g[ l ][ i ][ j ][ k ];
              got[ i + 1 ][ md - mn ][ mx - mn ] = true;
              bk[ i + 1 ][ md - mn ][ mx - mn ] = g[ 2 ][ i ][ j ][ k ];
              nn[ i + 1 ][ md - mn ][ mx - mn ] = 2;
            }
          }
    int ans = INF , bsti = 0 , bstj = 0;
    for( int i = 0 ; i < K ; i ++ )
      for( int j = i ; j < K ; j ++ )
        if( got[ n ][ i ][ j ] ){
          if( j < ans ){
            ans = j;
            bsti = i;
            bstj = j;
          }
        }
    if( ans < aa ){
      aa = ans;
      v[ 0 ].clear();
      v[ 1 ].clear();
      v[ 2 ].clear();
      find_ans( n , bsti , bstj );
    }
    if( aa == 0 ) break;
  }
  printf( "%d\n" , aa );
  for( int i = 0 ; i < 3 ; i ++ ){
    if( (int)v[ i ].size() == 0 ){
      puts( "0" );
    }else{
      printf( "%d " , (int)v[ i ].size() );
      for( size_t j = 0 ; j < v[ i ].size() ; j ++ )
        printf( "%d%c" , v[ i ][ j ] , " \n"[ j + 1 == v[ i ].size() ] );
    }
  }
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
