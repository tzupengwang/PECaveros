#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N (1 << 20)
bool p[ N ];
LL a , n;
vector< pair<LL,LL> > pri;
const LL inf9 = 1e9;
const LL inf = 2LL * inf9 * inf9;
void factor(){
  LL tmp = a;
  for( int i = 2 ; i < N ; i ++ ) if( !p[ i ] ){
    for( int j = i ; j < N ; j += i ) p[ j ] = true;
    if( tmp % i ) continue;
    LL vl = 1;
    while( tmp % i == 0 ){
      tmp /= i;
      vl *= i;
    }
    pri.push_back( { i , vl } );
  }
  if( tmp > 1 ){
    LL bl = 1 , br = inf9 , ba = 1;
    while( bl <= br ){
      LL bmid = (bl + br) >> 1;
      if( bmid * bmid <= tmp )
        ba = bmid , bl = bmid + 1;
      else
        br = bmid - 1;
    }
    if( ba * ba == tmp )
      pri.push_back( { ba , tmp } );
    else
      pri.push_back( { tmp , tmp } );
  }
}
vector<LL> ss;
int main(){
  cin >> a >> n;
  factor();
  ss.resize( pri.size() );
  for( int i = (int)ss.size() - 1 ; i >= 0 ; i -- ){
    ss[ i ] = pri[ i ].first;
    if( i + 1 < (int)ss.size() )
      ss[ i ] *= ss[ i + 1 ];
  }
  LL ans = -1 , pre = 1;
  for( size_t i = 0 ; i < ss.size() ; i ++ ){
    pre *= pri[ i ].second;
    LL tmp = pre;
    if( tmp > inf / pri[ i ].first ) continue;
    tmp *= pri[ i ].first;
    if( i + 1 < ss.size() ){
      if( tmp > inf / ss[ i + 1 ] )
        continue;
      tmp *= ss[ i + 1 ];
    }
    if( tmp > n ) continue;
    ans = tmp;
  }
  printf( "%lld\n" , ans );
}
