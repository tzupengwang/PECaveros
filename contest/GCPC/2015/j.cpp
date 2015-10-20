// eddy1021
#include <bits/stdc++.h>
using namespace std;
typedef double D;
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
#define N 110
void build(){

}
int g , c , n;
int tp[ N ] , pk[ N ] , pr[ N ];
char ch[ N ];
int type( char ctmp ){
  if( ctmp == 'e' ) return 0;
  if( ctmp == 'o' ) return 1;
  if( ctmp == 'r' ) return 2;
  return -1;
}
void init(){
  g = getint();
  c = getint();
  n = getint();
  for( int i = 1 ; i <= n ; i ++ ){
    scanf( "%s" , ch );
    tp[ i ] = type( ch[ 1 ] );
    pk[ i ] = getint();
    pr[ i ] = getint();
  }
}
ll dp[ 2 ][ N ][ N * N + N ];
bool gt[ N ][ N * N + N ];
vector< PII > v[ 2 ];
int maxv[ 2 ];
void solve(){
  int ans = 0;
  v[ 0 ].PB( MP( c , 0 ) );
  maxv[ 0 ] = 0;
  for( int i = 1 ; i <= n ; i ++ ){
    int now = i & 1;
    int pre = 1 - now;
    v[ now ].clear();
    maxv[ now ] = min( N * N + N , maxv[ pre ] + 100 );
    for( int j = 0 ; j <= c ; j ++ )
      for( int k = 0 ; k <= min( N * N + N , maxv[ pre ] + 100 ) ; k ++ )
        gt[ j ][ k ] = false;
    for( int j = 0 ; j < (int)v[ pre ].size() ; j ++ ){
      int coin = v[ pre ][ j ].FI;
      int slv = v[ pre ][ j ].SE;
      int vl = dp[ pre ][ coin ][ slv ];
      if( !gt[ coin ][ slv ] ) v[ now ].PB( MP( coin , slv ) );
      if( !gt[ coin ][ slv ] ||
          vl > dp[ now ][ coin ][ slv ] ){
        gt[ coin ][ slv ] = true;
        dp[ now ][ coin ][ slv ] = vl;
      }
      if( slv >= pr[ i ] ){
        if( !gt[ coin ][ slv - pr[ i ] ] )
          v[ now ].PB( MP( coin , slv - pr[ i ] ) );
        if( !gt[ coin ][ slv - pr[ i ] ] ||
            vl + 1 > dp[ now ][ coin ][ slv - pr[ i ] ] ){
          gt[ coin ][ slv - pr[ i ] ] = true;
          dp[ now ][ coin ][ slv - pr[ i ] ] = vl + 1;
        }
      }
      if( coin > 0 ){
        if( tp[ i ] == 0 && slv < pr[ i ] ){
          int nxtslv = slv + ( ( g - pr[ i ] ) / pk[ i ] +
                             ( ( g - pr[ i ] ) % pk[ i ] != 0 ) ) * pk[ i ];
          if( !gt[ coin - 1 ][ nxtslv ] )
            v[ now ].PB( MP( coin - 1 , nxtslv ) );
          if( !gt[ coin - 1 ][ nxtslv ] ||
              vl + 1 > dp[ now ][ coin - 1 ][ nxtslv ] ){
            gt[ coin - 1 ][ nxtslv ] = true;
            dp[ now ][ coin - 1 ][ nxtslv ] = vl + 1;
          }
        }else if( tp[ i ] ){
          int nxtslv;
          if( tp[ i ] == 1 ){
            int tmp = ( g - pr[ i ] ) / pk[ i ];
            if( ( ( g - pr[ i ] ) % pk[ i ] ) * 2 >= pk[ i ] )
              tmp ++;
            nxtslv = slv + tmp * pk[ i ];
          }
          else 
            nxtslv = slv + ( ( g - pr[ i ] ) / pk[ i ] ) * pk[ i ];
          if( !gt[ coin - 1 ][ nxtslv ] )
            v[ now ].PB( MP( coin - 1 , nxtslv ) );
          if( !gt[ coin - 1 ][ nxtslv ] ||
              vl + 1 > dp[ now ][ coin - 1 ][ nxtslv ] ){
            gt[ coin - 1 ][ nxtslv ] = true;
            dp[ now ][ coin - 1 ][ nxtslv ] = vl + 1;
          }
        }
      }
    }
    for( int j = 0 ; j < (int)v[ now ].size() ; j ++ )
      if( dp[ now ][ v[ now ][ j ].FI ][ v[ now ][ j ].SE ] > ans ){
        ans = dp[ now ][ v[ now ][ j ].FI ][ v[ now ][ j ].SE ]; 
        maxv[ now ] = max( maxv[ now ] , v[ now ][ j ].SE );
      }
  }
  printf( "%d\n" , ans );
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
