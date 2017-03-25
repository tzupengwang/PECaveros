#include <bits/stdc++.h>
using namespace std;
#define N 222
char c[ N ][ N ];
char t[ N ][ N ] , tt[ N ][ N ];
int ir , ic , rr , cc;
set< vector<int> > S;
void rotate( int& nr , int& nc ){
  for( int i = 0 ; i < nr ; i ++ )
    for( int j = 0 ; j < nc ; j ++ )
      tt[ i ][ j ] = t[ i ][ j ];
  for( int i = 0 ; i < nr ; i ++ )
    for( int j = 0 ; j < nc ; j ++ )
      t[ j ][ nr - i - 1 ] = tt[ i ][ j ];
  swap( nr , nc );
}
void go( int si , int sj ){
  for( int i = si ; i < si + rr ; i ++ )
    for( int j = sj ; j < sj + cc ; j ++ )
      t[ i - si ][ j - sj ] = c[ i ][ j ];
  int nr = rr , nc = cc;
  vector< vector<int> > vv;
  for( int _ = 0 ; _ < 4 ; _ ++ ){
    if( nr == rr and nc == cc ){
      vector<int> tv;
      for( int i = 0 ; i < nr ; i ++ )
        for( int j = 0 ; j < nc ; j ++ )
          tv.push_back( t[ i ][ j ] == '+' ? 1 : 0 );
      vv.push_back( tv );
    }
    rotate( nr , nc );
  }
  sort( vv.begin() , vv.end() );
  S.insert( vv[ 0 ] );
}
int main(){
  scanf( "%d%d" , &ir , &ic );
  for( int i = 1 ; i <= ir ; i ++ )
    scanf( "%s" , c[ i ] + 1 );
  rr = cc = 1;
  while( c[ 1 + rr + 1 ][ 2 ] != '#' ) rr ++;
  while( c[ 2 ][ 1 + cc + 1 ] != '#' ) cc ++;
  for( int i = 2 ; i < ir ; i += rr + 1 )
    for( int j = 2 ; j < ic ; j += cc + 1 )
      go( i , j );
  printf( "%d\n" , (int)S.size() );
}
