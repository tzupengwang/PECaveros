#include <bits/stdc++.h>
using namespace std;
#define N 333
int n;
void solve(){
  if( n == 3 ){
    puts( "1" );
    puts( "1 1 1" );
    puts( "1 1 1" );
  }else if( n == 4 ){
    puts( "2" );
    puts( "1 1 2 2" );
    puts( "1 2 1 2" );
  }else if( n == 5 ){
    puts( "2" );
    puts( "1 2 1 1 2" );
    puts( "1 2 1 1 2" );
  }else if( n == 6 ){
    puts( "2" );
    puts( "1 2 1 2 1 2" );
    puts( "1 2 1 2 1 2" );
  }else{
    puts( "3" );
    for( int i = 1 ; i <= n ; i ++ )
      printf( "%d%c" , 1 + i % 2 , " \n"[ i == n ] );
    for( int i = 1 ; i <= n ; i ++ )
      printf( "3%c" , " \n"[ i == n ] );
  }
}
int main(){
  freopen( "jubilee.in" , "r" , stdin );
  freopen( "jubilee.out" , "w" , stdout );
  while( scanf( "%d" , &n ) == 1 && n ) solve();
}
