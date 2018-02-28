#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 333
int n , a[ N ] , b[ N ] , d[ N ];
void init(){
  cin >> n;
  for( int i = 0 ; i < n ; i ++ )
    cin >> a[ i ] >> b[ i ] >> d[ i ];
}
bool died[ N ];
void solve(){
  for( int i = 0 ; i < n ; i ++ )
    died[ i ] = false;
  vector< pair<int, pair<int,int> > > eve;
  for( int i = 0 ; i < n ; i ++ ){
    eve.push_back( { a[ i ] , { 0 , i } } );
    eve.push_back( { b[ i ] , { 1 , i } } );
  }
  sort( eve.begin() , eve.end() );
  vector<int> who;
  int ans = 0;
  for( auto e : eve ){
    if( e.second.first == 0 ){
      who.push_back( e.second.second );
      continue;
    }
    if( died[ e.second.second ] )
      continue;
    int far = 0;
    for( auto i : who ){
      far = max( far , d[ i ] );
      died[ i ] = true;
    }
    ans += far;
    who.clear();
  }
  printf( "%d\n" , ans );
}
int main(){
  int _; cin >> _; while( _ -- ){
    init();
    solve();
  }
}
