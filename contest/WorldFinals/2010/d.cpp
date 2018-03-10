#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 111
int n , a[ N ] , m[ N ] , g[ N ];
vector<int> v[ N ];
int _cs;
bool cmp( pair<int,int> p1 , pair<int,int> p2 ){
  return p1.first - p1.second > 
         p2.first - p2.second;
}
pair<int,int> go( int now , int prt ){
  vector< pair<int,int> > wt;
  wt.push_back( { a[ now ] , m[ now ] + g[ now ] } );
  for( int son : v[ now ] ){
    if( son == prt ) continue;
    pair<int,int> tp = go( son , now );
    wt.push_back( tp );
  }
  sort( wt.begin() + 1 , wt.begin() + wt.size() , cmp );
  int ret = 0 , died = 0;
  for( auto p : wt ){
    ret = max( ret , p.first + died );
    died += p.second;
  }
  return {ret, died};
}
int main(){
  while( scanf( "%d" , &n ) == 1 and n ){
    for( int i = 1 ; i <= n ; i ++ ){
      v[ i ].clear();
      scanf( "%d%d%d" , &a[ i ] , &m[ i ] , &g[ i ] );
      a[ i ] = max( a[ i ] , m[ i ] + g[ i ] );
    }
    for( int i = 1 ; i < n ; i ++ ){
      int ui , vi;
      scanf( "%d%d" , &ui , &vi );
      v[ ui ].push_back( vi );
      v[ vi ].push_back( ui );
    }
    int ans = accumulate( a , a + n + 1 , 0 );
    for( int i = 1 ; i <= n ; i ++ )
      ans = min( ans , go( i , i ).first );
    printf( "Case %d: %d\n" , ++ _cs , ans );
  }
}
