#include <bits/stdc++.h>
using namespace std;
#define N 10101
typedef long long LL;
int n;
vector< pair<int,int> > v;
bool init(){
  scanf( "%d" , &n );
  if( n == 0 ) return false;
  v.clear();
  for( int i = 0 ; i < n ; i ++ ){
    int ai; scanf( "%d" , &ai );
    v.push_back( { ai , i + 1 } );
  }
  return true;
}
LL dp[ N ];
LL from[ N ];
vector< pair<int,int> > va;
void go( int now ){
  if( now == 0 ) return;
  go( from[ now ] );
  va.push_back( { from[ now ] + 1 , now } );
}
void find_ans(){
  va.clear();
  go( n );
  printf( "%d\n" , (int)va.size() );
  for( auto i : va ){
    printf( "%d " , i.second - i.first + 1 );
    for( int j = i.first ; j <= i.second ; j ++ )
      printf( "%d%c" , v[ j - 1 ].second , " \n"[ j == i.second ] );
  }
}
void solve(){
  sort( v.begin() , v.end() );
  for( int i = 1 ; i <= n ; i ++ ){
    dp[ i ] = 1000000000000000000LL;
    for( int j = 0 ; j < i ; j ++ ){
      LL tdp = dp[ j ] + (LL)( n - j ) * v[ i - 1 ].first;
      if( tdp < dp[ i ] ){
        dp[ i ] = tdp;
        from[ i ] = j;
      }
    }
  }
  printf( "%lld\n" , dp[ n ] );
  find_ans();
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "iq.in" , "r" , stdin );
  freopen( "iq.out" , "w" , stdout );
#endif
  while( init() ) solve();
}
