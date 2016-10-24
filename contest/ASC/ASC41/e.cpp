#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
vector< LL > a;
vector< LL > ans;
inline LL secure( int idx ){
  int eaten = ( idx == 2 ? 1 : 2 );
  vector< LL > tmp;
  for( int i = 0 ; i < 3 ; i ++ )
    if( i != eaten )
      tmp.push_back( a[ i ] );
  if( tmp[ 0 ] == 1 && tmp[ 1 ] == 1 ) return 0;
  LL x = tmp.back();
  tmp.pop_back();
  if( x / 2 <= tmp[ 0 ] ){
    tmp.push_back( 1 );
    tmp.push_back( x - 1 );
  }else{
    tmp.push_back( x / 2 );
    tmp.push_back( x - x / 2 );
  }
  sort( tmp.begin() , tmp.end() );
  return tmp[ 1 ];
}
int _cs;
void solve(){
  ans.clear();
  sort( a.begin() , a.end() );
  while( true ){
    LL bst = -1 , which = -1;
    for( int i = 0 ; i < 3 ; i ++ ){
      LL tmp = secure( i );
      if( tmp > bst ){
        bst = tmp;
        which = i;
      }
    }
    int eaten = which == 2 ? 1 : 2;
    ans.push_back( a[ eaten ] );
    
    vector< LL > tmp;
    for( int i = 0 ; i < 3 ; i ++ )
      if( i != eaten )
        tmp.push_back( a[ i ] );
    if( tmp[ 0 ] == 1 && tmp[ 1 ] == 1 ) break;
    LL x = tmp.back();
    tmp.pop_back();
    if( x / 2 <= tmp[ 0 ] ){
      tmp.push_back( 1 );
      tmp.push_back( x - 1 );
    }else{
      tmp.push_back( x / 2 );
      tmp.push_back( x - x / 2 );
    }
    sort( tmp.begin() , tmp.end() );
    a = tmp;
  }
  printf( "Case #%d:\n" , ++ _cs );
  printf( "%d\n" , (int)ans.size() );
  for( size_t i = 0 ; i < ans.size() ; i ++ )
    printf( "%lld%c" , ans[ i ] , " \n"[ i + 1 == ans.size() ] );
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "eating.in" , "r" , stdin );
  freopen( "eating.out" , "w" , stdout );
#endif
  a.resize( 3 );
  while( scanf( "%lld%lld%lld" , &a[ 0 ] , &a[ 1 ] , &a[ 2 ] ) == 3 && a[ 0 ] )
    solve();
}
