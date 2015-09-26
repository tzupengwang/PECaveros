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
#define N 210
int n , n1 , n2;
vector<PII> l , r;
int dp[ N ][ N ][ 2 ];
int st[ N ][ N ][ 2 ];
bool got[ N ][ N ][ 2 ];
void build(){

}
int DP( int tn1 , int tn2 , int lst ){
  if( tn1 == 0 && tn2 == 0 ) return 0;
  if( got[ tn1 ][ tn2 ][ lst ] ) return dp[ tn1 ][ tn2 ][ lst ];
  got[ tn1 ][ tn2 ][ lst ] = true;
  if( tn1 == 0 ){
    if( lst == 0 ) return dp[ tn1 ][ tn2 ][ lst ] = INF;
    int tdp = DP( tn1 , tn2 - 1 , 1 );
    dp[ tn1 ][ tn2 ][ lst ] = max( r[ tn2 - 1 ].FI +
                                   r[ tn2 - 1 ].SE , tdp + 10 );
  }else if( tn2 == 0 ){
    if( lst == 1 ) return dp[ tn1 ][ tn2 ][ lst ] = INF;
    int tdp = DP( tn1 - 1 , tn2 , 0 );
    dp[ tn1 ][ tn2 ][ lst ] = max( l[ tn1 - 1 ].FI +
                                   l[ tn1 - 1 ].SE , tdp + 10 );
  }else if( lst == 0 ){
    int tdp = DP( tn1 - 1 , tn2 , 0 );
    int tans1 = max( max( l[ tn1 - 1 ].FI , st[ tn1 - 1 ][ tn2 ][ 0 ] ) +
                     l[ tn1 - 1 ].SE , tdp + 10 );
        tdp = DP( tn1 - 1 , tn2 , 1 );
    int tans2 = max( l[ tn1 - 1 ].FI , tdp ) + l[ tn1 - 1 ].SE;
    dp[ tn1 ][ tn2 ][ lst ] = min( tans1 , tans2 );
    printf( "%d %d %d : %d %d\n" , tn1 , tn2 , lst , tans1 , tans2 );
    if( tans2 < tans1 )
      st[ tn1 ][ tn2 ][ lst ] = tdp;
    else st[ tn1 ][ tn2 ][ lst ] = st[ tn1 - 1 ][ tn2 ][ 0 ];
  }else{
    int tdp = DP( tn1 , tn2 - 1 , 1 );
    int tans1 = max( max( r[ tn2 - 1 ].FI , st[ tn1 ][ tn2 - 1 ][ 1 ] ) +
                     r[ tn2 - 1 ].SE , tdp + 10 );
        tdp = DP( tn1 , tn2 - 1 , 0 );
    int tans2 = max( r[ tn2 - 1 ].FI , tdp ) + r[ tn2 - 1 ].SE;
    dp[ tn1 ][ tn2 ][ lst ] = min( tans1 , tans2 );
    if( tans2 < tans1 )
      st[ tn1 ][ tn2 ][ lst ] = tdp;
    else st[ tn1 ][ tn2 ][ lst ] = st[ tn1 ][ tn2 - 1 ][ 1 ];
  }
  printf( "%d %d %d %d (%d)\n" , tn1 , tn2 , lst ,
                        dp[ tn1 ][ tn2 ][ lst ] , st[ tn1 ][ tn2 ][ lst ] );
  return dp[ tn1 ][ tn2 ][ lst ];
}
void init(){
  l.clear();
  r.clear();
  n = getint();
  for( int i = 0 ; i < n ; i ++ ){
    char kd[ 3 ]; int s , d;
    scanf( "%s" , kd );
    s = getint();
    d = getint();
    if( kd[ 0 ] == 'A' ) l.PB( MP( s , d ) );
    if( kd[ 0 ] == 'B' ) r.PB( MP( s , d ) );
  }
  sort( ALL( l ) );
  sort( ALL( r ) );
  n1 = (int)l.size();
  n2 = (int)r.size();
  for( int i = 0 ; i <= n1 ; i ++ )
    for( int j = 0 ; j <= n2 ; j ++ ){
      got[ i ][ j ][ 0 ] =
      got[ i ][ j ][ 1 ] = false;
      st[ i ][ j ][ 0 ] =
      st[ i ][ j ][ 1 ] = 0;
    }
}
void solve(){
  printf( "%d\n" , min( DP( n1 , n2 , 0 ) ,
                        DP( n1 , n2 , 1 ) ) );
}
int main(){
    build();
    __ = getint();
    while( __ -- ){
        init();
        solve();
    }
}
