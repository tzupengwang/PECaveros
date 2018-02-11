#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 101010
int n , x , cand[ N ] , ct;
int a[ N ] , b[ N ] , cnt[ N ] , ok[ N ];
int map_to[ N ];
void output(){
  printf( "%d\n" , n );
  int v = n;
  for( int i = 1 ; i < n ; i ++ ){
    printf( "%d %d\n" , map_to[ a[ i ] ] , map_to[ b[ i ] ] );
    v ^= map_to[ a[ i ] ];
    v ^= map_to[ b[ i ] ];
  }
  assert( !v );
  //cerr << v << endl;
  exit(0);
}
void no(){
  puts( "-1" );
  exit(0);
}
//void replace( int ai , int bi ){
  //for( int i = 1 ; i < n ; i ++ ){
    //if( a[ i ] == ai ) a[ i ] = bi;
    //if( b[ i ] == ai ) b[ i ] = bi;
  //}
//}
bool can[ N ];
int main(){
  scanf( "%d" , &n );
  x = n;
  for( int i = 1 ; i <= n ; i ++ ){
    scanf( "%d" , &ok[ i ] );
    map_to[ i ] = i;
  }
  for( int i = 1 ; i < n ; i ++ ){
    scanf( "%d%d" , &a[ i ] , &b[ i ] );
    cnt[ a[ i ] ] ++;
    cnt[ b[ i ] ] ++;
    x ^= a[ i ];
    x ^= b[ i ];
  }
  for( int i = 1 ; i <= n ; i ++ ){
    if( ok[ i ] and (cnt[ i ] & 1) )
      cand[ ct ++ ] = i;
    if( ok[ i ] and (cnt[ i ] & 1) == 0 ){
      can[ i ] = true;
      map_to[ i ] = i ^ (1 << 22);
    }
  }
  if( x == 0 ) output();
  if( ct == 0 ) no();
  if( ct == 1 ){
    int goal = x ^ cand[ 0 ];
    if( goal > n or can[ goal ] ){
      map_to[ cand[ 0 ] ] = goal;
      output();
    }
    no();
  }
  int goal = x ^ cand[ 0 ];
  if( goal > n or can[ goal ] ){
    map_to[ cand[ 0 ] ] = goal;
    //replace( cand[ 0 ] , goal );
    output();
  }
  for( int i = 1 ; i < ct ; i ++ )
    if( cand[ i ] != goal ){
      map_to[ cand[ 0 ] ] = goal | (1 << 20);
      map_to[ cand[ i ] ] = cand[ i ] | (1 << 20);
      //replace( cand[ 0 ] , goal | (1 << 20) );
      //replace( cand[ i ] , cand[ i ] | (1 << 20) );
      output();
    }
  no();
}
