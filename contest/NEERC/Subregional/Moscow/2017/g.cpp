#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 514
int n , m , u[ N ][ N ] , l[ N ][ N ];
bool vst[ N ][ N ];
LL a[ N ][ N ];
int di[]={0,0,1,-1};
int dj[]={1,-1,0,0};
bool gg;
LL check( int i , int j , int dir ){
  if( dir == 0 ) return l[ i ][ (j + 1) % m ] + a[ i ][ j ];
  if( dir == 1 ) return a[ i ][ j ] - l[ i ][ j ];
  if( dir == 2 ) return a[ i ][ j ] - u[ (i + 1) % n ][ j ];
  if( dir == 3 ) return u[ i ][ j ] + a[ i ][ j ];
  assert( false );
  return 0;
}
void go( int i , int j , LL v ){
  a[ i ][ j ] = v;
  vst[ i ][ j ] = true;
  for( int dir = 0 ; dir < 4 ; dir ++ ){
    int ni = ( i + di[ dir ] + n ) % n;
    int nj = ( j + dj[ dir ] + m ) % m;
    LL exp = check( i , j , dir );
    if( vst[ ni ][ nj ] ){
      if( exp != a[ ni ][ nj ] ){
        gg = true;
        return;
      }
    }else
      go( ni , nj , exp );
  }
}
int main(){
  scanf( "%d%d" , &n , &m );
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < m ; j ++ ){
      scanf( "%d" , &u[ i ][ j ] );
      scanf( "%d" , &l[ i ][ j ] );
    }
  go( 0 , 0 , 0 );
  //for( int i = 0 ; i < n ; i ++ )
    //for( int j = 0 ; j < m ; j ++ )
      //fprintf( stderr , "%3lld%c" , a[ i ][ j ] , " \n"[ j + 1 == m ] );
  puts( gg ? "No" : "Yes" );
}
