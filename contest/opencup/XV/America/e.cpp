#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N (1 << 20)
vector<int> pri;
int n , k , a[ N ];
int to[ N ];
bool okay( int vv ){
  int used = 0 , st = 1;
  while( st <= n and used <= k ){
    int val = a[ st ++ ];
    if( to[ val ] < vv ) return false;
    while( st <= n and to[ __gcd( val , a[ st ] ) ] >= vv )
      val = __gcd( val , a[ st ++ ] );
    used ++;
  }
  return used <= k;
}
bool pp[ N ];
int main(){
  for( int i = 2 ; i < N ; i ++ ) if( !pp[ i ] ){
    pri.push_back( i );
    for( int j = i ; j < N ; j += i ){
      pp[ j ] = true;
      to[ j ] = i;
    }
  }

  scanf( "%d%d" , &n , &k );
  for( int i = 1 ; i <= n ; i ++ )
    scanf( "%d" , &a[ i ] );

  int bl = 0 , br = (int)pri.size() - 1 , ba = 0;
  while( bl <= br ){
    int bmid = (bl + br) >> 1;
    if( okay( pri[ bmid ] ) )
      ba = pri[ bmid ] , bl = bmid + 1;
    else
      br = bmid - 1;
  }
  cout << ba << endl;
}
