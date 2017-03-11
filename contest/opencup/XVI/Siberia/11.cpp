#include <bits/stdc++.h>
using namespace std;
#define N 101010
int n , k , m;
vector<int> rv[ N ];
int bad[ N ];
void init(){
  scanf( "%d%d%d" , &n , &k , &m );
  while( k -- ){
    int id; scanf( "%d" , &id );
    bad[ id ] = true;
  }
}
int ans;
void Bad( int now ){
  if( bad[ now ] ) return;
  bad[ now ] = true;
  ans ++;
  for( auto i : rv[ now ] )
    Bad( i );
}
void solve(){
  ans = accumulate( bad + 1 , bad + n + 1 , 0 );
  while( m -- ){
    int a , b;
    scanf( "%d%d" , &a , &b );
    rv[ b ].push_back( a );
    if( bad[ b ] ) Bad( a );
    printf( "%d\n" , ans );
  }
}
int main(){
  freopen( "input.txt" , "r" , stdin );
  freopen( "output.txt" , "w" , stdout );
  init();
  solve();
}
