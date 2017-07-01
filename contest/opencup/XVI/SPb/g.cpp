#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define N 111
int a[ 4 ][ 4 ] , b[ 4 ][ 4 ];
void init(){
  for( int i = 0 ; i < 4 ; i ++ )
    for( int j = 0 ; j < 4 ; j ++ )
      cin >> a[ i ][ j ];
}
vector<int> ar;
vector<int> ac;
int cst;
bool vst[ N ];
int cost( const vector<int>& vv ){
  int tmp = 0;
  for( size_t i = 0 ; i < vv.size() ; i ++ )
    vst[ i ] = false;
  for( size_t i = 0 ; i < vv.size() ; i ++ )
    if( not vst[ i ] ){
      int tcc = 0 , now = i;
      while( not vst[ now ] ){
        tcc ++;
        vst[ now ] = true;
        now = vv[ now ];
      }
      tmp += tcc - 1;
    }
  return tmp;
}
int at[ 100 ] , tv[ 100 ];
void fix( vector<int> vv , char bs ){
  int nn = (int)vv.size();
  for( int i = 0 ; i < nn ; i ++ ){
    tv[ i ] = i;
    at[ vv[ i ] ] = i;
  }
  for( int i = 0 ; i < nn ; i ++ )
    while( tv[ i ] != vv[ i ] ){
      printf( "%c-%c\n" , i + bs , at[ tv[ i ] ] + bs );
      swap( tv[ i ] , tv[ at[ tv[ i ] ] ] );
    }
}
void solve(){
  cst = 200;
  vector<int> pr;
  for( int i = 0 ; i < 4 ; i ++ )
    pr.push_back( i );
  do{
    vector<int> pc;
    for( int i = 0 ; i < 4 ; i ++ )
      pc.push_back( i );
    do{
      vector<int> vv;
      for( int i = 0 ; i < 4 ; i ++ )
        for( int j = 0 ; j < 4 ; j ++ )
          vv.push_back( a[ pr[ i ] ][ pc[ j ] ] - 1 );
      int tcst = cost( pr ) + cost( pc ) + cost( vv );
      if( tcst < cst ){
        cst = tcst;
        ar = pr;
        ac = pc;
      }
    }while( next_permutation( pc.begin() , pc.end() ) );
  }while( next_permutation( pr.begin() , pr.end() ) );
  printf( "%d\n" , cst );
  fix( ar , 'a' );
  fix( ac , '1' );
  for( int i = 0 ; i < 4 ; i ++ )
    for( int j = 0 ; j < 4 ; j ++ )
      b[ i ][ j ] = a[ ar[ i ] ][ ac[ j ] ] - 1;
  for( int i = 0 ; i < 4 ; i ++ )
    for( int j = 0 ; j < 4 ; j ++ )
      while( b[ i ][ j ] != i * 4 + j ){
        int toi = b[ i ][ j ] / 4;
        int toj = b[ i ][ j ] % 4;
        printf( "%c%c-%c%c\n" , i + 'a' , j + '1' , toi + 'a' , toj + '1' );
        swap( b[ i ][ j ] , b[ toi ][ toj ] );
      }
}
int main(){
  init();
  solve();
}
