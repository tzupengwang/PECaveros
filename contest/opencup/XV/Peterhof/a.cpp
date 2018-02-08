#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 10
int n , k , c[ N ] , w[ N ];
void init(){
  for( int i = 0 ; i < n ; i ++ )
    scanf( "%d" , &c[ i ] );
  for( int i = 0 ; i < k ; i ++ )
    scanf( "%d" , &w[ i ] );
}
int dp[ 1 << N ] , bk[ 1 << N ];
bool ok[ 1 << N ];
int way[ 1 << N ][ N ];
void find_ans(){
  int cur = (1 << k) - 1;
  vector< vector< pair<int,int> > > ans;
  while( cur ){
    int pre = bk[ cur ];
    int now = pre ^ cur;
    cur = pre;
    vector< pair<int,int> > tv;
    int nt = 0 , res = c[ 0 ];
    for( int _ = 0 ; _ < k ; _ ++ ){
      int i = way[ now ][ _ ];
      if( ((now >> i) & 1) == 0 ) continue;
      while( nt < n and w[ i ] > res ){
        nt ++;
        res = c[ nt ];
      }
      if( nt >= n ) break;
      res -= w[ i ];
      tv.push_back( { i + 1 , nt + 1 } );
    }
    ans.push_back( tv );
  }
  printf( "%d\n" , (int)ans.size() );
  for( auto i : ans ){
    printf( "%d" , (int)i.size() );
    for( auto j : i )
      printf( " %d %d" , j.first , j.second );
    puts( "" );
  }
}
void solve(){
  for( int i = 0 ; i < (1 << k) ; i ++ )
    ok[ i ] = false;
  vector<int> ord;
  for( int i = 0 ; i < k ; i ++ )
    ord.push_back( i );
  do{
    int nt = 0 , res = c[ 0 ] , gt = 0;
    for( int _ = 0 ; _ < k ; _ ++ ){
      int i = ord[ _ ];
      while( nt < n and w[ i ] > res ){
        nt ++;
        res = c[ nt ];
      }
      if( nt >= n ) break;
      res -= w[ i ];
      gt |= (1 << i);
      if( ok[ gt ] ) continue;
      ok[ gt ] = true;
      for( int j = 0 ; j < k ; j ++ )
        way[ gt ][ j ] = ord[ j ];
    }
  }while( next_permutation( ord.begin() , ord.end() ) );
  for( int i = 0 ; i < (1 << k) ; i ++ )
    dp[ i ] = 100;
  dp[ 0 ] = 0;
  for( int i = 1 ; i < (1 << k) ; i ++ )
    for( int j = i ; j ; j = (j - 1) & i ){
      if( dp[ i ^ j ] >= 100 or not ok[ j ] ) continue;
      if( dp[ i ^ j ] + 1 < dp[ i ] ){
        dp[ i ] = dp[ i ^ j ] + 1;
        bk[ i ] = i ^ j;
      }
    }
  if( dp[ (1 << k) - 1 ] >= 100 )
    puts( "-1" );
  else
    find_ans();
}
int main(){
  while( scanf( "%d%d" , &n , &k ) == 2 ){
    init();
    solve();
  }
}
