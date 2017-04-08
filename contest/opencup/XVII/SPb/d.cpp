#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<LL,LL> frac;
#define P first
#define Q second
#define N 111
int n , k , a[ N ];
void init(){
  scanf( "%d%d" , &n , &k );
  for( int i = 0 ; i < n ; i ++ )
    scanf( "%d" , &a[ i ] );
}
frac operator/( const frac& lhs , const frac& rhs ){
  return { lhs.P * rhs.Q , lhs.Q * rhs.P };
}
bool operator<( const frac& lhs , const frac& rhs ){
  return lhs.P * rhs.Q < lhs.Q * rhs.P;
}
vector< pair<frac,int> > v;
bool cmp( pair<frac,int> lhs , pair<frac,int> rhs ){
  return lhs.first.P * rhs.first.Q <
         rhs.first.P * lhs.first.Q;
}
int cnt[ N ] , got , ans[ N ];
void solve(){
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 1 ; j <= k ; j ++ )
      v.push_back( { { a[ i ] , j } , i } );
  sort( v.begin() , v.end() , cmp );
  size_t al = 0 , ar = v.size();
  frac bst = { 1000000000 , 1 };
  for( size_t bl = 0 , br = 0 ; bl < v.size() ; bl ++ ){
    while( br < v.size() and got < n ){
      int who = v[ br ].second;
      if( cnt[ who ] == 0 ) got ++;
      cnt[ who ] ++;
      br ++;
    }
    if( got < n ) break;
    frac tans = v[ br - 1 ].first / v[ bl ].first;
    if( tans < bst ){
      bst = tans;
      al = bl;
      ar = br;
    }
    int who = v[ bl ].second;
    cnt[ who ] --;
    if( cnt[ who ] == 0 ) got --;
  }
  for( size_t i = al ; i < ar ; i ++ )
    ans[ v[ i ].second ] = v[ i ].first.Q;
  for( int i = 0 ; i < n ; i ++ )
    printf( "%d%c" , ans[ i ] , " \n"[ i + 1 == n ] );
}
int main(){
  init();
  solve();
}
