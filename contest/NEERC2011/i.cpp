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
#define N 310
int n , m;
int ac[ N ] , rk[ N ] , solved[ N ][ N ];
// . as 0
// + as 1
char c[ N * N ];
void build(){

}
void find_prob(){
  bool got = false;
  while( scanf( "%s" , c ) == 1 ){
    int len = strlen( c );
    if( len == 1 && c[ 0 ] >= 'A' && c[ 0 ] <= 'Z' ){
      if( !got ){
        if( c[ 0 ] == 'A' ){
          got = true;
          n ++;
        }
      }else n ++;
    }else if( got ) break;
  }
}
bool score(){
  int len = strlen( c );
  if( len == 1 && c[ 0 ] == '.' ) return true;
  if( c[ 0 ] == '+' ) return true;
  int tmp;
  if( c[ 0 ] == '-' && len > 1 ){
    if( sscanf( c + 1 , "%d" , &tmp ) == 1 )
      return true;
  }
  return false;
}
int parse( string ts ){
  int len = ts.length();
  if( len == 1 && ts[ 0 ] == '.' ) return 0;
  if( len == 1 && ts[ 0 ] == '+' ) return 1;
  int tmp = 0;
  sscanf( ts.c_str() + 1 , "%d" , &tmp );
  if( ts[ 0 ] == '+' ) return tmp + 1;
  return -tmp;
}
int parse2( string ts ){
  int tmp;
  sscanf( ts.c_str() , "%d" , &tmp );
  return tmp;
}
vector<string> v;
void find_sc(){
  gets( c ); gets( c );
  while( gets( c ) ){
   // printf( "%s" , c );
    m ++; v.clear();
    int len = strlen( c );
    string ts; bool got = false;
    for( int i = 0 ; i <= len ; i ++ )
      if( i == len || c[ i ] == ' ' ){
        if( got ) v.PB( ts );
        ts.clear();
        got = false;
      }else{
        got = true;
        ts += c[ i ];
      }
    int vn = (int)v.size();
//    for( int i = 0 ; i < vn ; i ++ )
//      cout << v[ i ] << " "; cout << endl;
    for( int i = 0 ; i < n ; i ++ ){
      solved[ m ][ i ] = parse( v[ vn - 3 - ( n - i ) ] );
    }
//    for( int i = 0 ; i < n ; i ++ )
//      printf( "%d " , solved[ m ][ i ] ); puts( "" );
    ac[ m ] = parse2( v[ vn - 3 ] );
    rk[ m ] = parse2( v[ vn - 1 ] );
  }
}
void init(){
  find_prob();
  find_sc();
//  for( int i = 1 ; i <= m ; i ++ )
//    printf( "%d\n" , ac[ i ] );
}
int pac[ N ];
D val , ovr , eve , un;
D in[ N ] , neg;
void solve(){
  for( int i = 1 ; i <= m ; i ++ )
    if( ac[ i ] == 0 ) val += 1.0;
  for( int i = 1 ; i <= m ; i ++ )
    if( ac[ i ] == n ) ovr += 1.0;
  for( int i = 2 ; i <= m ; i ++ )
    if( ac[ i - 1 ] - ac[ i ] > 1 )
      eve += ( ac[ i - 1 ] - ac[ i ] - 1 );
  for( int i = 1 ; i <= m ; i ++ )
    for( int j = 0 ; j < n ; j ++ )
      if( solved[ i ][ j ] > 0 )
        pac[ j ] ++;
  for( int i = 0 ; i < n ; i ++ )
    if( pac[ i ] == 0 )
      un += 1.0;
  for( int i = 0 ; i < n ; i ++ )
    for( int j = m ; j >= 1 ; j -- )
      if( solved[ j ][ i ] > 0 ){
        int nrk = rk[ j ];
        for( int k = j - 1 ; k >= 1 ; k -- )
          if( rk[ k ] < nrk && solved[ k ][ i ] <= 0 )
            in[ i ] ++;
        break;
      }
  val /= (D)m; neg += 1.03 * val;
  ovr /= (D)m; neg += 3.141 * ovr;
  eve /= (D)n; neg += 2.171 * eve;
  un /= (D)n;  neg += 1.414 * un;
  for( int i = 0 ; i < n ; i ++ ){
    in[ i ] /= (D)m;
    neg += in[ i ] / (D)n;
  }
  printf( "Vainness = %.3f\n" , val );
  printf( "Oversimplification = %.3f\n" , ovr );
  printf( "Evenness = %.3f\n" , eve );
  printf( "Unsolvability = %.3f\n" , un );
  for( int i = 0 ; i < n ; i ++ )
    printf( "Instability %d = %.3f\n" , i + 1 , in[ i ] );
  printf( "Negidealness = %.3f\n" , neg );
}
int main(){
  freopen( "ideal.in" , "r" , stdin );
  freopen( "ideal.out" , "w" , stdout );
    build();
//    __ = getint();
    while( __ -- ){
        init();
        solve();
    }
}
