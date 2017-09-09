#include <bits/stdc++.h>
using namespace std;
#define N 20
char c[ N ][ N ];
int h , w , bomb[ N ][ N ] , ans;
vector< pair<int,int> > b;
bool n[ N ][ N ] , y[ N ][ N ];
void go( int cur , int st );
void go2( int cur , int st , pair<int,int> cst[] , int cstsz , int nowat , int ndsz ){
  if( ndsz == 0 ){
    bool on[ 10 ];
    for( int i = nowat + 1 ; i < cstsz ; i ++ ){
      on[ i ] = n[ cst[ i ].first ][ cst[ i ].second ];
      n[ cst[ i ].first ][ cst[ i ].second ] = true;
    }
    go( cur + 1 , st );
    for( int i = nowat + 1 ; i < cstsz ; i ++ )
      n[ cst[ i ].first ][ cst[ i ].second ] = on[ i ];
    return;
  }
  y[ cst[ nowat ].first ][ cst[ nowat ].second ] = true;
  go2( cur , st + 1 , cst , cstsz , nowat + 1 , ndsz - 1 );
  y[ cst[ nowat ].first ][ cst[ nowat ].second ] = false;
  if( cstsz - nowat - 1 >= ndsz ){
    n[ cst[ nowat ].first ][ cst[ nowat ].second ] = true;
    go2( cur , st , cst , cstsz , nowat + 1 , ndsz );
    n[ cst[ nowat ].first ][ cst[ nowat ].second ] = false;
  }
}
bool got;
void go( int cur , int st ){
  cout << cur << " " << st << endl;
  if( st > ans ) return;
  if( cur == (int)b.size() ){
    got = true;
    //ans = st;
    return;
  }
  int nd = c[ b[ cur ].first ][ b[ cur ].second ] - '0';
  int gt = 0;
  pair<int,int> cst[ 9 ];
  int ctt = 0;
  for( int i = -1 ; i <= 1 ; i ++ )
    for( int j = -1 ; j <= 1 ; j ++ ){
      int ni = b[ cur ].first + i;
      int nj = b[ cur ].second + j;
      if( ni < 0 or ni >= h ) continue;
      if( nj < 0 or nj >= w ) continue;
      if( y[ ni ][ nj ] ) gt ++;
      else if( !n[ ni ][ nj ] )
        cst[ ctt ++ ] = { ni , nj };
    }
  if( gt > nd ) return;
  if( st + nd - gt > ans ) return;
  if( gt + ctt < nd ) return;
  go2( cur , st , cst , ctt , 0 , nd - gt );
}
bool cmp( pair<int,int> p1 , pair<int,int> p2 ){
  return c[ p1.first ][ p1.second ] >
         c[ p2.first ][ p2.second ];
}
int main(){
  while( scanf( "%d%d" , &h , &w ) == 2 and h ){
    b.clear();
    for( int i = 0 ; i < h ; i ++ ){
      scanf( "%s" , c[ i ] );
      for( int j = 0 ; j < w ; j ++ ){
        bomb[ i ][ j ] = 0;
        n[ i ][ j ] = y[ i ][ j ] = false;
      }
    }
    ans = h * w;
    for( int i = 0 ; i < h ; i ++ )
      for( int j = 0 ; j < w ; j ++ )
        if( '0' <= c[ i ][ j ] and c[ i ][ j ] <= '9' )
          b.push_back( { i , j } );
    sort( b.begin() , b.end() , cmp );
    for( int i = 0 ; i < h ; i ++ )
      for( int j = 0 ; j < w ; j ++ )
        if( c[ i ][ j ] == '.' )
          n[ i ][ j ] = true;
    //ans = h * w;
    //go( 0 , 0 );
    ans = 1;
    while( true ){
      got = false;
      go( 0 , 0 );
      if( got ) break;
      ans ++;
    }
    printf( "%d\n" , ans );
  }
}
