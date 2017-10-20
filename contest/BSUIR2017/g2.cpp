#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 42;
const LL mod = (1LL << N);
LL bs[ N ];
map<LL,string> sv;
inline LL mul( LL a , LL b ){
  if( b == 0 ) return 0;
  LL ret = mul( ( a + a ) % mod , b / 2 );
  if( b & 1 ) ret = ( ret + a ) % mod;
  return ret;
}
void go( int now , LL s , string who ){
  if( now == 21 ){
    sv[ s ] = who;
    s = mul( s , bs[ 21 ] );
    s = ( mod - s ) % mod;
    auto it = sv.find( s );
    if( it == sv.end() ) return;
    cout << who << it->second << endl;
    exit(0);
    return;
  }
  go( now + 1 , ( s * 10 + 1 ) % mod , who + "1" );
  go( now + 1 , ( s * 10 + 2 ) % mod , who + "2" );
}
int main(){
  bs[ 0 ] = 1;
  for( int i = 1 ; i < N ; i ++ )
    bs[ i ] = ( bs[ i - 1 ] * 10 ) % mod;
  go( 0 , 0 , "" );
}
