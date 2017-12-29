#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
inline int mul( int a , int b , int mod ){
  a *= b;
  return a >= mod ? a % mod : a;
}
inline int mpow( int a , int b , int mod ){
  if( !b ) return 1 % mod;
  int ret = mpow( mul( a , a , mod ) , b >> 1 , mod );
  if( b & 1 ) ret = mul( ret , a , mod );
  return ret;
}
inline int phi( int x ){
  int ret = x;
  for( int p : { 2 , 3 , 5 , 7 } )
    if( x % p == 0 )
      ret = (ret / p) * (p - 1);
  return ret;
}
const int inf = 1000000;
inline int magic( int a , int b ){
  if( a == 1 ) return 1;
  int ret = 1;
  for( int i = 0 ; i < b and ret < inf ; i ++ )
    ret = ret * a;
  return min( ret , inf );
}
pair<int,int> cal( int a , int b , int mod ){
  if( a == b ) return { a % mod , a };
  pair<int,int> pp = cal( a + 1 , b , phi( mod ) );
  int ret = 0;
  if( pp.second >= phi( mod ) )
    ret = mpow( a , pp.first + phi( mod ) , mod );
  else
    ret = mpow( a , pp.first , mod );
  int sec = magic( a , pp.second );
  return { ret , sec };
}
int main(){
  int a , b;
  cin >> a >> b;
  cout << cal( a , b , 10 ).first << endl;
}
