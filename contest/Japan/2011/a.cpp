#include <bits/stdc++.h>
using namespace std;
#define N 1021
typedef long long LL;
int dy[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
int n , mm[ N ] , d[ N ] , h[ N ] , m[ N ] , e[ N ] , id[ N ];
long long ans;
char cc[ 9 ];
LL cal( int cur ){
  if( cur == 0 ) return 0;
  LL ret = 0;
  if( mm[ cur ] != mm[ cur - 1 ] or
      d[ cur ] != d[ cur - 1 ] ){
    ret += 60 - m[ cur - 1 ];
    m[ cur - 1 ] = 0;
    h[ cur - 1 ] ++;
    ret += ( 24 - h[ cur - 1 ] ) * 60;
    h[ cur - 1 ] = 0;
    d[ cur - 1 ] ++;
    if( d[ cur - 1 ] > dy[ mm[ cur - 1 ] ] ){
      d[ cur - 1 ] = 1;
      mm[ cur - 1 ] ++;
      if( mm[ cur - 1 ] > 12 )
        mm[ cur - 1 ] = 1;
    }
  }else{
    while( h[ cur ] != h[ cur - 1 ] or
           m[ cur ] != m[ cur - 1 ] ){
      ret ++;
      m[ cur - 1 ] ++;
      if( m[ cur - 1 ] == 60 ){
        m[ cur - 1 ] = 0;
        h[ cur - 1 ] ++;
        if( h[ cur - 1 ] >= 24 )
          h[ cur - 1 ] = 0;
      }
    }
    return ret;
  }
  while( mm[ cur - 1 ] != mm[ cur ] ){
    ret += ( dy[ mm[ cur - 1 ] ] - d[ cur - 1 ] + 1 ) * 24 * 60;
    d[ cur - 1 ] = 1;
    mm[ cur - 1 ] ++;
    if( mm[ cur - 1 ] > 12 )
      mm[ cur - 1 ] = 1;
  }
  while( d[ cur - 1 ] != d[ cur ] ){
    ret += 24 * 60;
    d[ cur - 1 ] ++;
  }
  ret += h[ cur ] * 60 + m[ cur ];
  return ret;
}
bool in[ N ];
LL cnt[ N ];
void solve(){
  for( int i = 0 ; i < n ; i ++ ){
    scanf( "%d/%d %d:%d %s %d" , &mm[ i ] , &d[ i ] , &h[ i ] , &m[ i ] ,
           cc , &id[ i ] );
    e[ i ] = ( cc[ 0 ] == 'I' ? 1 : -1 );
  }
  for( int i = 0 ; i < N ; i ++ ){
    in[ i ] = false;
    cnt[ i ] = 0;
  }
  for( int i = 0 ; i < n ; i ++ ){
    long long dlt = 0;
    dlt = cal( i );
    //fprintf( stderr , "%d : %lld\n" , i , dlt );
    if( in[ 0 ] ){
      for( int j = 1 ; j < N ; j ++ )
        if( in[ j ] ){
          cnt[ j ] += dlt;
        }
    }
    if( e[ i ] == 1 and !in[ id[ i ] ] )
      in[ id[ i ] ] = true;
    if( e[ i ] == -1 and in[ id[ i ] ] )
      in[ id[ i ] ] = false;
  }
  ans = 0;
  for( int j = 1 ; j < N ; j ++ ){
    //if( cnt[ j ] )
      //printf( "%d %lld\n" , j , cnt[ j ] );
    ans = max( ans , cnt[ j ] );
  }
  printf( "%lld\n" , ans );
}
int main(){
  while( scanf( "%d" , &n ) == 1 && n ){
    solve();
  }
}
