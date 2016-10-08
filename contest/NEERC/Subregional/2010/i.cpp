#include <bits/stdc++.h>
using namespace std;
#define N 12
int d , h , w;
int bl[ N ][ N ];
char c[ N ][ N ][ N ];
void init(){
  scanf( "%d%d%d" , &d , &h , &w );
  for( int i = 0 ; i < d ; i ++ )
    for( int j = 0 ; j < h ; j ++ ){
      scanf( "%s" , c[ i ][ j ] );
      for( int k = 0 ; k < w ; k ++ )
        if( c[ i ][ j ][ k ] == 'B' )
          bl[ j ][ k ] |= ( 1 << i );
    }
}
inline bool in( int xi , int xj ){
  return 0 <= xi && xi < h &&
         0 <= xj && xj < w;
}
int dp[ N ][ N ][ 1 << 11 ];
int fr[ N ][ N ][ 1 << 11 ];
const int INF = 1023456789;
int di[]={0,1,-1,0};
int dj[]={1,0,0,-1};
char dd[5]= "RDUL";
void DP( int msk ){
  if( msk == ( msk & (-msk) ) ){
    for( int i = 0 ; i < h ; i ++ )
      for( int j = 0 ; j < w ; j ++ )
        dp[ i ][ j ][ msk ] = 1;
    return;
  }
typedef pair< int , pair<int,int> > data;
  priority_queue< data , vector<data> , greater<data> > vv;
  for( int i = 0 ; i < h ; i ++ )
    for( int j = 0 ; j < w ; j ++ ){
      int bb = msk & bl[ i ][ j ];
      int ww = msk ^ bb;
      int tdp = max( dp[ i ][ j ][ ww ] , dp[ i ][ j ][ bb ] );
      if( bb == 0 || ww == 0 ) tdp = INF;
      fr[ i ][ j ][ msk ] = -1;
      dp[ i ][ j ][ msk ] = tdp;
      vv.push( { tdp , { i , j } } );
    }
  while( vv.size() ){
    data td = vv.top(); vv.pop();
    int i = td.second.first;
    int j = td.second.second;
    for( int dir = 0 ; dir < 4 ; dir ++ ){
      int nxti = i + di[ dir ];
      int nxtj = j + dj[ dir ];
      if( !in( nxti , nxtj ) ) continue;
      int tdp = dp[ i ][ j ][ msk ] + 1;
      if( tdp < dp[ nxti ][ nxtj ][ msk ] ){
        dp[ nxti ][ nxtj ][ msk ] = tdp;
        fr[ nxti ][ nxtj ][ msk ] = 3 - dir;
        vv.push( { tdp , { nxti , nxtj } } );
      }
    }
  }
}
void find_ans( int ni , int nj , int msk ){
  if( msk == 0 ) return;
  if( msk == ( msk & (-msk) ) ){
    printf( "%d" , (int)__lg( msk ) );
    return;
  }
  if( fr[ ni ][ nj ][ msk ] >= 0 ){
    putchar( dd[ fr[ ni ][ nj ][ msk ] ] );
    int nxti = ni + di[ fr[ ni ][ nj ][ msk ] ];
    int nxtj = nj + dj[ fr[ ni ][ nj ][ msk ] ];
    find_ans( nxti , nxtj , msk );
  }else{
    int bb = msk & bl[ ni ][ nj ];
    int ww = bb ^ msk;
    putchar( '(' );
    find_ans( ni , nj , ww );
    putchar( ':' );
    find_ans( ni , nj , bb );
    putchar( ')' );
  }
}
void solve(){
  for( int msk = 0 ; msk < ( 1 << d ) ; msk ++ )
    DP( msk );
  find_ans( 0 , 0 , ( 1 << d ) - 1 );
  puts( "" );
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "image.in" , "r" , stdin );
  freopen( "image.out" , "w" , stdout );
#endif
  init();
  solve();
}
