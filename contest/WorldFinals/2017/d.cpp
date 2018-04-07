#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 505050
int n , m;
#define D first
#define P second
vector< pair<LL,LL> > v;
deque< pair<LL,LL> > dq1 , dq2;
void pre_solve1(){
  for( int i = 0 ; i < n ; i ++ ){
    if( dq1.size() and dq1.back().P <= v[ i ].P )
      continue;
    dq1.push_back( v[ i ] );
  }
}
void pre_solve2(){
  for( int i = m - 1 ; i >= 0 ; i -- ){
    if( dq2.size() and dq2.front().P >= v[ i ].P )
      continue;
    dq2.push_front( v[ i ] );
  }
}
void init(){
  scanf( "%d%d" , &n , &m );
  v.resize( n );
  for( int i = 0 ; i < n ; i ++ )
    scanf( "%lld%lld" , &v[ i ].P , &v[ i ].D );
  sort( v.begin() , v.end() );
  pre_solve1();
  v.resize( m );
  for( int i = 0 ; i < m ; i ++ )
    scanf( "%lld%lld" , &v[ i ].P , &v[ i ].D );
  sort( v.begin() , v.end() );
  pre_solve2();
  LL mx = -1;
  int ptr = (int)dq2.size() - 1;
  deque< pair<LL,LL> > tmp;
  for( int i = (int)dq1.size() - 1 ; i >= 0 ; i -- ){
    while( ptr >= 0 and dq2[ ptr ].D > dq1[ i ].D ){
      mx = max( mx , dq2[ ptr ].P );
      ptr --;
    }
    if( mx > dq1[ i ].P )
      tmp.push_front( dq1[ i ] );
  }
  dq1.swap( tmp );
}
LL ans;
void go( int ln , int rn , int lm , int rm ){
  if( ln > rn ) return;
  int mid = (ln + rn) >> 1;
  LL bst = 0; int who = rm;
  for( int i = lm ; i <= rm ; i ++ ){
    if( dq2[ i ].P < dq1[ mid ].P or
        dq2[ i ].D < dq1[ mid ].D )
      continue;
    LL tans = (dq2[ i ].P - dq1[ mid ].P) *
              (dq2[ i ].D - dq1[ mid ].D);
    tans = max( tans , 0LL );
    if( tans >= bst )
      bst = tans , who = i;
  }
  ans = max( ans , bst );
  go( ln , mid - 1 , lm , who );
  go( mid + 1 , rn , who , rm );
}
void solve(){
  go( 0 , (int)dq1.size() - 1 , 
      0 , (int)dq2.size() - 1 );
  printf( "%lld\n" , ans );
}
int main(){
  init();
  solve();
}
