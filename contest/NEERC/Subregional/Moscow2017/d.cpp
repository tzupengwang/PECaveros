#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
#define N 10101
vector<LL> v , a;
void parse(){
  ULL tmp = 0;
  for( size_t j = 0 ; j + 1 < v.size() ; j ++ )
    tmp += (1ULL << (j * 7)) * ( v[j] - 128 );
  tmp += (1ULL << ((int(v.size()) - 1) * 7) ) * v.back();
  if( tmp % 2 == 0 ) a.push_back( tmp / 2 );
  else a.push_back( -(tmp / 2) - 1 );
  v.clear();
}
int main(){
  LL n , x; cin >> n;
  for( int i = 0 ; i < n ; i ++ ){
    cin >> x;
    v.push_back( x );
    if( x < 128 ) parse();
  }
  for( auto i : a )
    cout << i << endl;
}
