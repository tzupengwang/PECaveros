#include <bits/stdc++.h>
using namespace std;
const int mod = 10007;
int add( int a , int b ){
  a += b;
  return a >= mod ? a - mod : a;
}
int mul( int a , int b ){
  a *= b;
  return a >= mod ? a % mod : a;
}
int sub( int a , int b ){
  a -= b;
  return a < 0 ? a + mod : a;
}
#define N 500
bool p[ N ];
vector<int> pset;
int at[ N ];
void build(){
  for( int i = 2 ; i < N ; i ++ ) if( !p[ i ] ){
    at[ i ] = pset.size();
    pset.push_back( i );
    for( int j = i ; j < N ; j += i ) p[ j ] = true;
  }
  //cerr << pset.size() << endl;
  //for( int i : pset ){
    //if( i * i > 500 ) break;
    //int cc = 0 , tmp = 1;
    //while( tmp <= 500 ){
      //tmp *= i;
      //cc ++;
    //}
    //printf( "%d %d\n" , i , cc );
  //}
}
// 2 9
// 3 6
// 5 4
// 7 4
// 11 3
// 13 3
// 17 3
// 19 3
inline int highp( int x ){
  int ret = 1;
  for( int i : pset ){
    if( x % i == 0 )
      ret = max( ret , i ); 
  }
  return ret;
}
int n;
vector<int> cc[ N ];
void init(){
  scanf( "%d" , &n );
  for( size_t i = 0 ; i < pset.size() ; i ++ )
    cc[ i ].clear();
  for( int i = 0 , x ; i < n ; i ++ ){
    scanf( "%d" , &x );
    int hp = highp( x );
    if( hp < 20 ) cc[ 0 ].push_back( x );
    else cc[ at[ hp ] ].push_back( x );
  }
}
int mpow( int a , int b ){
  if( !b ) return 1;
  int ret = mpow( a * a , b >> 1 );
  if( b&1 ) ret *= a;
  return ret;
}
int f( int vl , int x ){
  int ret = 0;
  while( vl % x == 0 ){
    ret ++;
    vl /= x;
  }
  return ret;
}
#define FOR(i,k) for( int i = 0 ; i < k ; i ++ )
int ans;
int dp[ 9 ][ 6 ][ 4 ][ 4 ][ 3 ][ 3 ][ 3 ][ 3 ][ 2 ];
void pre_dp(){
  FOR(i2, 9) FOR(i3, 6) FOR(i5, 4) FOR(i7, 4)
    FOR(i11, 3) FOR(i13, 3) FOR(i17, 3) FOR(i19, 3) FOR(bt, 2)
    dp[ i2 ][ i3 ][ i5 ][ i7 ][ i11 ][ i13 ][ i17 ][ i19 ][ bt ] = 0;
  dp[ 0 ][ 0 ][ 0 ][ 0 ][ 0 ][ 0 ][ 0 ][ 0 ][ 0 ] = 1;
  for( auto vl : cc[ 0 ] ){
    FOR(i2, 9) FOR(i3, 6) FOR(i5, 4) FOR(i7, 4)
      FOR(i11, 3) FOR(i13, 3) FOR(i17, 3) FOR(i19, 3){
        dp[ i2 ][ i3 ][ i5 ][ i7 ][ i11 ][ i13 ][ i17 ][ i19 ][ 1 ] = 
          dp[ i2 ][ i3 ][ i5 ][ i7 ][ i11 ][ i13 ][ i17 ][ i19 ][ 0 ];
      }
    FOR(i2, 9) FOR(i3, 6) FOR(i5, 4) FOR(i7, 4)
      FOR(i11, 3) FOR(i13, 3) FOR(i17, 3) FOR(i19, 3){
        if( dp[ i2 ][ i3 ][ i5 ][ i7 ][ i11 ][ i13 ][ i17 ][ i19 ][ 1 ] == 0 )
          continue;
        int ni2 = max( i2 , f( vl , 2 ) );
        int ni3 = max( i3 , f( vl , 3 ) );
        int ni5 = max( i5 , f( vl , 5 ) );
        int ni7 = max( i7 , f( vl , 7 ) );
        int ni11 = max( i11 , f( vl , 11 ) );
        int ni13 = max( i13 , f( vl , 13 ) );
        int ni17 = max( i17 , f( vl , 17 ) );
        int ni19 = max( i19 , f( vl , 19 ) );
        int tms = 1;
        tms = mul( tms , mpow( 2 , ni2 - i2 ) );
        tms = mul( tms , mpow( 3 , ni3 - i3 ) );
        tms = mul( tms , mpow( 5 , ni5 - i5 ) );
        tms = mul( tms , mpow( 7 , ni7 - i7 ) );
        tms = mul( tms , mpow( 11 , ni11 - i11 ) );
        tms = mul( tms , mpow( 13 , ni13 - i13 ) );
        tms = mul( tms , mpow( 17 , ni17 - i17 ) );
        tms = mul( tms , mpow( 19 , ni19 - i19 ) );
        int &who = dp[ ni2 ][ ni3 ][ ni5 ][ ni7 ][ ni11 ][ ni13 ][ ni17 ][ ni19 ][ 0 ];
        who = add( who ,
                  mul( tms , 
                       dp[ i2 ][ i3 ][ i5 ][ i7 ][ i11 ][ i13 ][ i17 ][ i19 ][ 1 ] ) );
      }
  }
  FOR(i2, 9) FOR(i3, 6) FOR(i5, 4) FOR(i7, 4)
    FOR(i11, 3) FOR(i13, 3) FOR(i17, 3) FOR(i19, 3){
      ans = add( ans , 
                 dp[ i2 ][ i3 ][ i5 ][ i7 ][ i11 ][ i13 ][ i17 ][ i19 ][ 0 ] );
      //if( dp[ i2 ][ i3 ][ i5 ][ i7 ][ i11 ][ i13 ][ i17 ][ i19 ][ 0 ] != 0 ){
        //printf( "2: %d, " , i2 );
        //printf( "3: %d, " , i3 );
        //printf( "5: %d, " , i5 );
        //printf( "7: %d, " , i7 );
        //printf( "11: %d, " , i11 );
        //printf( "13: %d, " , i13 );
        //printf( "17: %d, " , i17 );
        //printf( "19: %d : " , i19 );
        //printf( "%d\n" , 
          //dp[ i2 ][ i3 ][ i5 ][ i7 ][ i11 ][ i13 ][ i17 ][ i19 ][ 0 ] );
      //}
    }

}
int dp2[ 9 ][ 6 ][ 4 ][ 4 ][ 3 ][ 3 ][ 3 ][ 3 ][ 2 ][ 2 ];
void DP( const vector<int>& wt , int pr ){
  FOR(i2, 9) FOR(i3, 6) FOR(i5, 4) FOR(i7, 4)
    FOR(i11, 3) FOR(i13, 3) FOR(i17, 3) FOR(i19, 3) FOR(gt, 2) FOR(bt, 2)
      dp2[ i2 ][ i3 ][ i5 ][ i7 ][ i11 ][ i13 ][ i17 ][ i19 ][ gt ][ bt ] = 0;
  FOR(i2, 9) FOR(i3, 6) FOR(i5, 4) FOR(i7, 4)
    FOR(i11, 3) FOR(i13, 3) FOR(i17, 3) FOR(i19, 3)
      dp2[ i2 ][ i3 ][ i5 ][ i7 ][ i11 ][ i13 ][ i17 ][ i19 ][ 0 ][ 0 ] =
        dp[ i2 ][ i3 ][ i5 ][ i7 ][ i11 ][ i13 ][ i17 ][ i19 ][ 0 ];
  for( auto vl : wt ){
    FOR(i2, 9) FOR(i3, 6) FOR(i5, 4) FOR(i7, 4)
      FOR(i11, 3) FOR(i13, 3) FOR(i17, 3) FOR(i19, 3) FOR(gt, 2){
        dp2[ i2 ][ i3 ][ i5 ][ i7 ][ i11 ][ i13 ][ i17 ][ i19 ][ gt ][ 1 ] = 
          dp2[ i2 ][ i3 ][ i5 ][ i7 ][ i11 ][ i13 ][ i17 ][ i19 ][ gt ][ 0 ];
      }
    FOR(i2, 9) FOR(i3, 6) FOR(i5, 4) FOR(i7, 4)
      FOR(i11, 3) FOR(i13, 3) FOR(i17, 3) FOR(i19, 3) FOR(gt, 2){
        if( dp2[ i2 ][ i3 ][ i5 ][ i7 ][ i11 ][ i13 ][ i17 ][ i19 ][ gt ][ 1 ]
            == 0 )
          continue;
        int ni2 = max( i2 , f( vl , 2 ) );
        int ni3 = max( i3 , f( vl , 3 ) );
        int ni5 = max( i5 , f( vl , 5 ) );
        int ni7 = max( i7 , f( vl , 7 ) );
        int ni11 = max( i11 , f( vl , 11 ) );
        int ni13 = max( i13 , f( vl , 13 ) );
        int ni17 = max( i17 , f( vl , 17 ) );
        int ni19 = max( i19 , f( vl , 19 ) );
        int ngt = max( gt , f( vl , pr ) );
        int tms = 1;
        tms = mul( tms , mpow( 2 , ni2 - i2 ) );
        tms = mul( tms , mpow( 3 , ni3 - i3 ) );
        tms = mul( tms , mpow( 5 , ni5 - i5 ) );
        tms = mul( tms , mpow( 7 , ni7 - i7 ) );
        tms = mul( tms , mpow( 11 , ni11 - i11 ) );
        tms = mul( tms , mpow( 13 , ni13 - i13 ) );
        tms = mul( tms , mpow( 17 , ni17 - i17 ) );
        tms = mul( tms , mpow( 19 , ni19 - i19 ) );
        tms = mul( tms , mpow( pr , ngt - gt ) );
        int &who = dp2[ ni2 ][ ni3 ][ ni5 ][ ni7 ][ ni11 ][ ni13 ][ ni17 ][ ni19 ][ ngt ][ 0 ];
        who = add( who ,
                  mul( tms , 
                       dp2[ i2 ][ i3 ][ i5 ][ i7 ][ i11 ][ i13 ][ i17 ][ i19 ][ gt ][ 1 ] ) );
      }
  }
  FOR(i2, 9) FOR(i3, 6) FOR(i5, 4) FOR(i7, 4)
    FOR(i11, 3) FOR(i13, 3) FOR(i17, 3) FOR(i19, 3)
      ans = add( ans , 
                 dp2[ i2 ][ i3 ][ i5 ][ i7 ][ i11 ][ i13 ][ i17 ][ i19 ][ 1 ][ 0 ] );
  FOR(i2, 9) FOR(i3, 6) FOR(i5, 4) FOR(i7, 4)
    FOR(i11, 3) FOR(i13, 3) FOR(i17, 3) FOR(i19, 3)
      dp[ i2 ][ i3 ][ i5 ][ i7 ][ i11 ][ i13 ][ i17 ][ i19 ][ 0 ] =
        add( dp2[ i2 ][ i3 ][ i5 ][ i7 ][ i11 ][ i13 ][ i17 ][ i19 ][ 0 ][ 0 ] ,
             dp2[ i2 ][ i3 ][ i5 ][ i7 ][ i11 ][ i13 ][ i17 ][ i19 ][ 1 ][ 0 ] );
}
int _cs;
void solve(){
  ans = sub( 0 , 1 );
  pre_dp();
  for( size_t i = 1 ; i < pset.size() ; i ++ ){
    if( cc[ i ].empty() ) continue;
    DP( cc[ i ] , pset[ i ] );
  }
  printf( "Case %d: %d\n" , ++ _cs , ans );
}
int main(){
  build();
  int t; scanf( "%d" , &t ); while( t -- ){
    init();
    solve();
  }
}
