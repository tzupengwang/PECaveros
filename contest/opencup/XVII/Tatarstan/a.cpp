#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 1010101
//LL n , p[ N ];
//vector<int> v[ N ];
LL k , r;
vector<LL> ans;
vector<LL> cc;
void go( size_t now , int kk , LL vl ){
  if( vl > r ) return;
  if( now == cc.size() ){
    if( kk < k ) return;
    ans.push_back( vl );
    return;
  }
  for( int ii = 0 ; kk + ii <= k ; ii ++ ){
    go( now + 1 , kk + ii , vl );
    if( vl > r / cc[ now ] ) break;
    vl *= cc[ now ];
  }
}
int main(){
  cin >> k >> r;
  for( auto i : { 2 , 3 , 5 , 7 , 11 , 13 } ){
    LL tmp = 1;
    for( int j = 0 ; j < i ; j ++ )
      tmp *= i;
    cc.push_back( tmp );
  }
  go( 0 , 0 , 1 );
  sort( ans.begin() , ans.end() );
  cout << ans.size() << endl;
  for( size_t i = 0 ; i < ans.size() ; i ++ )
    cout << ans[ i ] << " \n"[ i + 1 == ans.size() ];
  //cin >> n;
  //for( int i = 2 ; i <= n ; i ++ ){
    //p[ i ] = 1;
    //for( int j = i ; j <= n ; j += i )
      //if( i % j == 0 ){
        //p[ i ] = p[ j ] * ( i / j ) + j * p[ i / j ];
        //break;
      //}
  //}
  //for( int i = 2 ; i <= n ; i ++ )
    //if( p[ i ] % i == 0 )
      //v[ p[ i ] / i ].push_back( i );
  //for( int i = 0 ; i < N ; i ++ ){
    //if( v[ i ].empty() ) continue;
    //printf( "%d\n" , i );
    //for( auto j : v[ i ] )
      //printf( "%d " , j );
    //puts( "" );
  //}
}
