#include <bits/stdc++.h>
using namespace std;
#define N 2020
#define M 12
int n , m;
double a[ N ][ M ] , sum[ M ];
double pp[ 3 ][ M ];
void init(){
  scanf( "%d%d" , &n , &m );
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < m ; j ++ ){
      scanf( "%lf" , &a[ i ][ j ] );
      sum[ j ] += a[ i ][ j ];
    }
}
int ans[ N ] , dom = 0;
vector< int > les;
double les_sum;
void find_ans(){
  vector< pair< double , int > > vv;
  int cnt = 0;
  for( int now = 0 ; now < n ; now ++ ){
    double rr_sum = 0;
    for( auto i : les )
      rr_sum += a[ now ][ i ];
    if( rr_sum * 4 < les_sum ){
      ++ cnt;
      ans[ now ] = 2;
      continue;
    }
    //vv.push_back( { a[ now ][ dom ] , now } );
    double cst[ 3 ];
    for( int i = 0 ; i < 2 ; i ++ ){
      cst[ i ] = 0;
      for( int j = 0 ; j < m ; j ++ )
        cst[ i ] += fabs( a[ now ][ j ] - pp[ i ][ j ] ) *
                    fabs( a[ now ][ j ] - pp[ i ][ j ] );
    }
    ans[ now ] = 0;
    for( int i = 1 ; i < 2 ; i ++ )
      if( cst[ i ] < cst[ ans[ now ] ] )
        ans[ now ] = i;
  }
  //sort( vv.begin() , vv.end() );
  //reverse( vv.begin() , vv.end() );
  //double pro2 = (double)cnt / (double)n;
  //double pro1 = 0.3;
  //double pro0 = max( 0.4 , 1 - pro1 - pro2 );
  //double ps = pro1 + pro0;
  //pro1 /= ps; pro0 /= ps;
  //for( size_t i = 0 ; i < vv.size() ; i ++ ){
    //if( i >= n * pro1 ) break;
    //ans[ vv[ i ].second ] = 1;
  //}
}
void solve(){
  vector< pair< double , int > > vv;
  for( int i = 0 ; i < m ; i ++ )
    if( sum[ i ] > sum[ dom ] )
      dom = i;
  for( int i = 0 ; i < n ; i ++ )
    vv.push_back( { a[ i ][ dom ] , i } );
  sort( vv.begin() , vv.end() );
  int cnt = 0;
  for( int i = 0 ; i * 10 < 3 * n ; i ++ ){
    ++ cnt;
    for( int j = 0 ; j < m ; j ++ )
      pp[ 0 ][ j ] += a[ vv[ i ].second ][ j ];
  }
  for( int j = 0 ; j < m ; j ++ ){
    pp[ 0 ][ j ] /= (double)cnt;
    pp[ 1 ][ j ] = pp[ 2 ][ j ] = pp[ 0 ][ j ];
  }
  for( int j = 0 ; j < m ; j ++ )
    if( pp[ 0 ][ j ] <= 15.0 ){
      les.push_back( j );
      les_sum += pp[ 0 ][ j ];
    }
  // fraud 1
  pp[ 1 ][ dom ] += 75.0;
  double tsum = 0;
  for( int j = 0 ; j < m ; j ++ )
    tsum += pp[ 1 ][ j ];
  tsum /= 100.0;
  for( int j = 0 ; j < m ; j ++ )
    pp[ 1 ][ j ] /= tsum;
  //for( int i = 0 ; i < 3 ; i ++ , puts( "" ) )
    //for( int j = 0 ; j < m ; j ++ )
      //printf( "%.2f " , pp[ i ][ j ] );
  //exit( 0 );
  find_ans();
  for( int i = 0 ; i < n ; i ++ )
    printf( "%d\n" , ans[ i ] );
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "genome.in" , "r" , stdin );
  freopen( "genome.out" , "w" , stdout );
#endif
  init();
  solve();
}
