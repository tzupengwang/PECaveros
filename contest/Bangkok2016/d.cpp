#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
pair<LL,LL> gcd(LL a, LL b){
	if(b == 0) return {1, 0};
  pair<LL,LL> q = gcd(b, a % b);
  return {q.second, q.first - q.second * (a / b)};
}
LL ax , ay , bx , by , k;
int main(){
  int t; scanf( "%d" , &t ); while( t -- ){
    scanf( "%lld%lld%lld%lld%lld" , &ax , &ay , &bx , &by , &k );
    if( ax > bx or ( ax == bx and ay > by ) ){
      swap( ax , bx );
      swap( ay , by );
    }
    if( ax == bx ){
      for( int i = 0 ; i < k ; i ++ )
        printf( "%lld %d\n" , ax + 1 , i );
      continue;
    }
    LL cx = ( by - ay );
    LL cy = ( ax - bx );
    //LL cc = by * ax - bx * ay;
    //LL gg = __gcd( abs( cx ) , abs( cy ) );
    pair<LL,LL> ret = gcd( cx , cy );
    LL dx = ax + ret.first;
    LL dy = ay + ret.second;
    for( int i = 0 ; i < k ; i ++ ){
      printf( "%lld %lld\n" , dx , dy );
      dx += bx - ax;
      dy += by - ay;
    }
    //LL i = bx - 1;
    //while( k -- ){
      //i ++;
      //LL vl = ( i - bx ) * ( by - ay ) / ( bx - ax );
      //if( vl * ( bx - ax ) <= ( i - bx ) * ( by - ay ) ) vl ++;
      //LL xx = i , yy = by + vl;
      //if( __gcd( xx - ax , yy - ay ) > 1 ) continue;
      //if( __gcd( xx - bx , yy - by ) > 1 ) continue;
      //printf( "%lld %lld\n" , xx , yy );
    //}
  }
}
