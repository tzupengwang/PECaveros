#include <bits/stdc++.h>
using namespace std;
#define N 101010
typedef long long LL;
int n;
vector< pair<LL,LL> > v;
LL ps[ N ] , mx[ N ];
bool okay( LL tar ){
  priority_queue<LL, vector<LL>, greater<LL> > heap;
  LL as = 0;
  for( int i = 0 ; i + 1 < tar ; i ++ ){
    heap.push( v[ i ].second );
    as += v[ i ].second;
  }
  for( int i = tar ; i <= n ; i ++ ){
    heap.push( v[ i - 1 ].second );
    as += v[ i - 1 ].second;
    while( (LL)heap.size() > tar ){
      as -= heap.top();
      heap.pop();
    }
    if( as >= mx[ i ] )
      return true;
  }
  return false;
}
int main(){
  cin >> n;
  for( int i = 0 ; i < n ; i ++ ){
    LL ai , bi;
    cin >> ai >> bi;
    v.push_back( { ai + bi , ai } );
  }
  sort( v.begin() , v.end() );
  for( int i = 1 ; i <= n ; i ++ ){
    ps[ i ] = ps[ i - 1 ] + v[ i - 1 ].second;
    mx[ i ] = v[ i - 1 ].first;
  }
  LL bl = 1 , br = n , ba = -1;
  while( bl <= br ){
    LL bmid = (bl + br) >> 1;
    if( okay( bmid ) ) ba = bmid , br = bmid - 1;
    else bl = bmid + 1;
  }
  cout << ba << endl;
}
