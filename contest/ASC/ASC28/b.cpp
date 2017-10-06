#include <bits/stdc++.h>
using namespace std;
#define N 101010
int n , a[ N ] , b[ N ] , suma , sumb;
int ans , ansa[ N ] , ansb[ N ];
void solve(){
  for( int i = 1 ; i <= n ; i ++ )
    if( a[ i ] + b[ i ] >= max( suma , sumb ) ){
      ans = a[ i ] + b[ i ];
      ansa[ i ] = 0;
      ansb[ i ] = a[ i ];
      int ta = a[ i ] , tb = 0;
      for( int j = 1 ; j <= n ; j ++ )
        if( i != j ){
          ansa[ j ] = ta;
          ansb[ j ] = tb;
          ta += a[ j ];
          tb += b[ j ];
        }
      return;
    }
  ans = max( suma , sumb );
  bool swp = suma > sumb;
  if( swp ){
    for( int i = 1 ; i <= n ; i ++ )
      swap( a[ i ] , b[ i ] );
  }
  int bst = 1;
  for( int i = 1 ; i <= n ; i ++ )
    if( b[ i ] > b[ bst ] )
      bst = i;
  vector< pair<int,int> > vv;
  for( int i = 1 ; i <= n ; i ++ )
    if( i != bst )
      vv.push_back( { a[ i ] - b[ i ] , i } );
  sort( vv.begin() , vv.end() );
  ansa[ bst ] = ans - a[ bst ];
  ansb[ bst ] = 0;
  int ta = 0 , tb = b[ bst ];
  for( auto i : vv ){
    ansa[ i.second ] = ta;
    ansb[ i.second ] = tb;
    ta += a[ i.second ];
    tb += b[ i.second ];
  }
  if( swp ){
    for( int i = 1 ; i <= n ; i ++ )
      swap( ansa[ i ] , ansb[ i ] );
  }
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "carwash.in" , "r" , stdin );
  freopen( "carwash.out" , "w" , stdout );
#endif
  cin >> n;
  for( int i = 1 ; i <= n ; i ++ )
    cin >> a[ i ] >> b[ i ];
  suma = accumulate( a + 1 , a + n + 1 , 0 );
  sumb = accumulate( b + 1 , b + n + 1 , 0 );
  solve();
  printf( "%d\n" , ans );
  for( int i = 1 ; i <= n ; i ++ )
    printf( "%d %d\n" , ansa[ i ] , ansb[ i ] );
}
