// eddy1021
#include <bits/stdc++.h>
using namespace std;
typedef long double D;
typedef long long ll;
typedef pair<int,int> PII;
#define mod9 1000000009ll
#define mod7 1000000007ll
#define INF  1023456789ll
#define INF16 10000000000000000ll
#define FI first
#define SE second
#define PB push_back
#define MP make_pair
#define MT make_tuple
#define eps 1e-9
#define SZ(x) (int)(x).size()
#define ALL(x) (x).begin(), (x).end()
ll getint(){
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
bool equal( D _x ,  D _y ){
    return _x > _y - eps && _x < _y + eps;
}
int __ = 1 , cs;
/*********default*********/
#define N 51
#define SEED 514514
void build(){
  srand( SEED );
}
int n , k;
D v[ N ][ 3 ], bns[ 3 ];
bool got[ N ];
#define K 101
D cal( int tk ){
  D tans = 1e20;
  for( int _ = 0 ; _ < K ; _ ++ ){
    D s[ 3 ];
    s[ 0 ] = s[ 1 ] = s[ 2 ] = 0.0;
    vector<int> idx;
    for( int i = 0 ; i < n ; i ++ ) got[ i ] = false;
    for( int i = tk ; i < n ; i ++ ) idx.PB( i );
    random_shuffle( ALL( idx ) );
    if( tk ) got[ 0 ] = true, s[ 0 ] += v[ 0 ][ 0 ],
                              s[ 1 ] += v[ 0 ][ 1 ],
                              s[ 2 ] += v[ 0 ][ 2 ];
    for( int i = 0 ; i < k - tk ; i ++ ){
      int nidx = idx[ i ];
      got[ nidx ] = true;
      for( int j = 0 ; j < 3 ; j ++ )
        s[ j ] += v[ nidx ][ j ];
    }
    D ttans = s[ 0 ] * s[ 1 ] * s[ 2 ];
    bool better = true;
    while( better ){
      better = false;
      random_shuffle( ALL( idx ) );
      for( int i = 0 ; i < n - tk ; i ++ ){
        int nidx = idx[ i ];
        if( got[ nidx ] ) continue;
        for( int j = tk ; j < n ; j ++ )
          if( got[ j ] ){
            D tmp = 1.0;
            for( int u = 0 ; u < 3 ; u ++ )
              tmp *= ( s[ u ] - v[ j ][ u ] + v[ nidx ][ u ] );
            if( tmp < ttans ){
              ttans = tmp;
              better = true;
              got[ j ] = false;
              got[ nidx ] = true;
              for( int u = 0 ; u < 3 ; u ++ )
                s[ u ] += v[ nidx ][ u ] - v[ j ][ u ];
              break;
            }
          }
      }
    }
    tans = min( tans , ttans );
  }
  return tans;
}
void init(){
  n = getint(); k = getint();
  for( int i = 0 ; i < 3 ; i ++ )
    bns[ i ] = getint();
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < 3 ; j ++ )
      v[ i ][ j ] = getint();
}
void solve(){
  if( n == k ){
    puts( "0.0" );
    return;
  }
  D cst = cal( 0 );
  D ans = bns[ 0 ] + bns[ 1 ] + bns[ 2 ];
  D sv[ 3 ];
  for( int i = 0 ; i < 3 ; i ++ )
    sv[ i ] = v[ 0 ][ i ];
  for( int i = 0 ; i < 3 ; i ++ )
    for( int j = 0 ; j < 8 ; j ++ ){
      if( ( j >> i ) & 1 ) continue;
      for( int u = 0 ; u < 3 ; u ++ )
        if( ( j >> u ) & 1 ) v[ 0 ][ u ] = 0;
        else v[ 0 ][ u ] = sv[ u ];
      D l = 0.0, r = sv[ i ], mid, tcst;
      for( int _ = 0 ; _ < K ; _ ++ ){
        mid = ( l + r ) * 0.5;
        v[ 0 ][ i ] = mid;
        tcst = cal( 1 );
        if( tcst < cst + eps ) l = mid;
        else r = mid;
      }
      if( tcst - eps < cst + eps ){
        D tans = 0.0;
        for( int u = 0 ; u < 3 ; u ++ )
          tans += bns[ u ] * ( ( sv[ u ] - v[ 0 ][ u ] ) / sv[ u ] ); 
        ans = min( ans , tans );
      }
    }
  printf( "%.12f\n" , (double)ans );
}
int main(){
    build();
//    __ = getint();
    while( __ -- ){
        init();
        solve();
    }
}
