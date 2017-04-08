#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
set<LL> S;
bool isprime( LL x ){
  for( LL i = 2 ; i * i <= x ; i ++ )
    if( x % i == 0 )
      return false;
  return true;
}
LL rev( LL x ){
  LL y = 0;
  while( x ){
    y = y * 10 + x % 10;
    x /= 10;
  }
  return y;
}
vector<LL> v;
int main(){
  S.insert(2);
  S.insert(3);
  S.insert(5);
  S.insert(7);
  v.push_back( 2 );
  v.push_back( 3 );
  v.push_back( 5 );
  v.push_back( 7 );
  for( size_t i = 0 ; i < v.size() ; i ++ ){
    LL now = v[ i ];
    for( LL b : { 3 , 7 } ){
      LL nxt = now * 10 + b;
      if( isprime( nxt ) and S.count( rev( rev( nxt ) / 10 ) ) ){
        S.insert( nxt );
        v.push_back( nxt );
      }
    }
  }
  int x; cin >> x;
  cout << ( x <= 9 ? v[ x - 1 ] : -1 ) << endl;
}
