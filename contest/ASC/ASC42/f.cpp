#include <bits/stdc++.h>
using namespace std;
#define N 10000001
typedef long long LL;
int fac[ N ];
void build(){
  for( int i = 2 ; i < N ; i ++ ) if( fac[ i ] == 0 ){
    fac[ i ] = i;
    for( LL j = (LL)i * i ; j < N ; j += i )
      if( !fac[ j ] )
        fac[ j ] = i;
  }
}
bool win( int w , int h , int who ){
  if( who == 0 ){
    if( w == 1 ) return false;
    return win( w / fac[ w ] , h , 1 - who );
  }else{
    if( h == 1 ) return true;
    return win( w , h / fac[ h ] , 1 - who );
  }
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "funny.in" , "r" , stdin );
  freopen( "funny.out" , "w" , stdout );
#endif
  int w , h;
  build();
  while( scanf( "%d%d" , &w , &h ) == 2 && w ){
    printf( "%d %d - " , w , h );
    puts( win( w , h , 0 ) ? "Vera" : "Harry" );
  }
}
