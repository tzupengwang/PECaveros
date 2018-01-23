#include <bits/stdc++.h>
using namespace std;
int n , m;
queue< pair<int,int> > Q;
int ln , rn , lm , rm , dn , dm;
void go(){
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j <= m ; j ++ )
      Q.push( { i , j } );
  while( true ){
    pair<int,int> tp;
    while( Q.size() ){
      tp = Q.front(); Q.pop();
      int nn = tp.first , nm = tp.second;
      if( nn + ln < 1 ) continue;
      if( nn + rn > n ) continue;
      if( nm + lm < 1 ) continue;
      if( nm + rm > m ) continue;
      break;
    }
    int nn = tp.first , nm = tp.second;
    printf( "%d %d\n" , nn + dn , nm + dm );
    fflush( stdout );
    char c[ 10 ]; scanf( "%s" , c );
    if( strlen( c ) > 1 ) exit( 0 );
    if( c[ 0 ] == 'U' ){
      dn --;
      ln = min( ln , dn );
    }
    if( c[ 0 ] == 'D' ){
      dn ++;
      rn = max( rn , dn );
    }
    if( c[ 0 ] == 'L' ){
      dm --;
      lm = min( lm , dm );
    }
    if( c[ 0 ] == 'R' ){
      dm ++;
      rm = max( rm , dm );
    }
  }
}
int main(){
  scanf( "%d%d" , &n , &m );
  go();
}
