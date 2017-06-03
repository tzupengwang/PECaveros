#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define X 32
LL n;
LL a[ X + X ] , b[ X + X ];
typedef unsigned int uint;
uint hsh( uint v ){
  v = v + (v << 10);
  v = v ^ (v >> 6);
  v = v + (v << 3);
  v = v ^ (v >> 11);
  v = v + (v << 16);
  return v;
}
void Xor( int sft ){
  for( int i = 0 ; i < X ; i ++ )
    b[ i ] = a[ i ];
  for( int i = X - sft - 1 ; i >= 0 ; i -- )
    a[ i ] = a[ i + sft ] ^ b[ i ];
}
void Add( int sft ){
  for( int i = 0 ; i < X ; i ++ )
    b[ i ] = a[ i ];
  // a32 .... a3 a2 a1 a0
  // a32 .... a0
  for( int i = sft ; i < X ; i ++ ){
    a[ i ] = b[ i ] - a[ i - sft ];
    while( a[ i ] < 0 ){
      a[ i ] += 2;
      b[ i + 1 ] --;
    }
  }
}
LL solve(){
  for( int i = 0 ; i < X ; i ++ ){
    a[ i ] = n & 1LL;
    n >>= 1;
  }
  Add( 16 );
  Xor( 11 );
  Add( 3 );
  Xor( 6 );
  Add( 10 );
  LL ret = 0;
  for( int i = X - 1 ; i >= 0 ; i -- )
    ret = (ret << 1) | a[ i ];
  return ret;
}
int main(){
  //for( int i = 0 ; i < 1000000 ; i ++ ){
    //n = hsh( i );
    //if( i != solve() ){
      //cout << i << endl;
      //cout << hsh( i ) << endl;
      //cout << solve() << endl;
    //}
    //n = hsh( i );
    //assert( i == solve() );
  //}
  freopen( "input.txt" , "r" , stdin );
  freopen( "output.txt" , "w" , stdout );
  int q; cin >> q; while( q -- ){
    cin >> n;
    cout << solve() << endl;
  }
}
