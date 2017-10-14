#include <bits/stdc++.h>
using namespace std;
#define N 1010101
int k , n;
vector< pair<int,int> > v;
int cnt[ N ] , got;
void add( int tp ){
  if( cnt[ tp ] == 0 ) got ++;
  cnt[ tp ] ++;
}
void sub( int tp ){
  cnt[ tp ] --;
  if( cnt[ tp ] == 0 ) got --;
}
void init(){
  for( int i = 1 ; i <= k ; i ++ )
    cnt[ i ] = 0;
  got = 0;
  v.clear();
  for( int i = 0 ; i < n ; i ++ ){
    int d , t;
    scanf( "%d%d" , &d , &t );
    v.push_back( { d , t } );
  }
  sort( v.begin() , v.end() );
}
void solve(){
  int ans = 1000000000 , ac = 2000000000;
  size_t ptr = 0;
  for( size_t l = 0 ; l < v.size() ; l ++ ){
    if( ptr < l ) ptr = l;
    while( got < k and ptr < v.size() )
      add( v[ ptr ++ ].second );
    if( got < k ) break;
    int al = v[ l ].first;
    int ar = v[ ptr - 1 ].first;
    int tans = ( ar - al + 1 ) / 2;
    int tac = al + ( ( ar - al ) - tans );
    //printf( "%d %d\n" , tans , tac );
    if( tans < ans or
        ( ans == tans and tac < ac ) ){
      ans = tans;
      ac = tac;
    }
    sub( v[ l ].second );
  }
  printf( "%d\n" , ac );
}
int main(){
  while( scanf( "%d%d" , &k , &n ) == 2 ){
    init();
    solve();
  }
}
