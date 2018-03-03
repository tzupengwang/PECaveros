#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL base = 1440 , per = 1;
#define N 10
LL n;
int _cs , ord[ N ];
bool okay( const vector<pair<LL,LL>>& vv , LL gap ){
  if( vv.empty() ) return true;
  for( int i = 0 ; i < n ; i ++ )
    ord[ i ] = i;
  do{
    bool ok = true;
    LL pre = vv[ ord[ 0 ] ].second;
    for( int _ = 1 ; _ < n and ok ; _ ++ ){
      int i = ord[ _ ];
      LL lb = vv[ i ].second;
      LL rb = vv[ i ].first;
      if( pre + gap > rb )
        ok = false;
      pre = max( lb , pre + gap );
    }
    if( ok )
      return true;
  }while( next_permutation( ord , ord + n ) );
  return false;
}
int main(){
  for( LL i = 2 ; i <= 8 ; i ++ )
    per *= i;
  while( scanf( "%lld" , &n ) and n ){
    vector< pair<LL,LL> > v;
    for( int i = 0 ; i < n ; i ++ ){
      LL ai , bi;
      cin >> ai >> bi;
      ai *= per * 60;
      bi *= per * 60;
      v.push_back( { bi , ai } );
    }
    sort( v.begin() , v.end() );
    LL bl = 0 , br = base * per * 60LL , ba = br;
    while( bl <= br ){
      LL mid = (bl + br) >> 1;
      if( okay( v , mid ) )
        ba = mid , bl = mid + 1;
      else
        br = mid - 1;
    }
    printf( "Case %d: " , ++ _cs );
    ba = (ba + per / 2) / per;
    printf( "%lld:%02lld\n" , ba / 60 , ba % 60 );
  }
}
