#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 111
int n , ans , ac[ N ];
bool chosen[ N ];
int who[ N ] , ord[ N ];
bitset<75> c[ N ] , goal;
char buf[ N ];
void go( int now ){
  if( now >= ans ) return;
  if( (int)goal.count() == 0 ){
    ans = now;
    for( int i = 0 ; i < now ; i ++ )
      ac[ i ] = who[ i ];
    return;
  }
  if( now + 1 >= ans ) return;
  for( int _ = 0 ; _ < n ; _ ++ ){
    int i = ord[ _ ];
    if( chosen[ i ] ) continue;
  //for( auto _ : vv ){
    //int i = _.second;
    who[ now ] = i;
    bitset<75> sv = goal;
    goal &= ~c[ i ];
    int dlt = sv.count() - goal.count();
    if( dlt == 0 ){
      goal = sv;
      continue;
    }
    int mr = (sv.count() + dlt - 1) / dlt;
    if( now + mr >= ans ){
      goal = sv;
      continue;
    }
    chosen[ i ] = true;
    go( now + 1 );
    goal = sv;
    chosen[ i ] = false;
  }
}
int _cs;
int main(){
  while( cin >> n ){
    for( int i = 0 ; i < n ; i ++ ){
      scanf( "%s" , buf );
      for( int j = 0 ; j < n ; j ++ )
        c[ i ][ j ] = buf[ j ] - '0';
      c[ i ][ i ] = 1;
    }
    ans = n + 1;
    goal.reset();
    for( int i = 0 ; i < n ; i ++ )
      goal[ i ] = 1;
    vector< pair<int,int> > vv;
    for( int i = 0 ; i < n ; i ++ ){
      int mr = (c[ i ] & goal).count();
      vv.push_back( { mr , i } );
    }
    sort( vv.begin() , vv.end() );
    reverse( vv.begin() , vv.end() );
    for( int i = 0 ; i < n ; i ++ )
      ord[ i ] = vv[ i ].second;
    go( 0 );
    printf( "Case %d: %d " , ++ _cs , ans );
    for( int i = 0 ; i < ans ; i ++ )
      printf( "%d%c" , ac[ i ] + 1 , " \n"[ i + 1 == ans ] );
  }
}
