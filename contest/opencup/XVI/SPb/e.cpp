#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 101010
LL l , a[ N ] , b[ N ] , n , k;
void init(){
  cin >> l;
  for( int i = 0 ; i < l ; i ++ ){
    cin >> a[ i ] >> b[ i ];
    k += a[ i ];
    n += a[ i ] * b[ i ];
  }
}
vector< pair<LL,LL> > v;
void output(){
  size_t sz = 1;
  for( size_t i = 1 ; i < v.size() ; i ++ )
    if( v[ i ].second == v[ sz - 1 ].second )
      v[ sz - 1 ].first += v[ i ].first;
    else
      v[ sz ++ ] = v[ i ];
  v.resize( sz );
  printf( "%d\n" , (int)v.size() );
  for( auto i : v )
    printf( "%lld %lld\n" , i.first , i.second );
  exit(0);
}
void solve(){
  for( int i = l - 2 ; i >= 0 ; i -- ){
    if( i == l - 2 and b[ i ] - 1 == b[ i + 1 ] )
      continue;
    for( int j = 0 ; j < i ; j ++ ){
      v.push_back( { a[ j ] , b[ j ] } );
      k -= a[ j ];
      n -= a[ j ] * b[ j ];
    }
    if( a[ i ] > 1 ){
      v.push_back( { a[ i ] - 1 , b[ i ] } );
      k -= a[ i ] - 1;
      n -= ( a[ i ] - 1 ) * b[ i ];
    }
    v.push_back( { 1 , b[ i ] - 1 } );
    k --;
    n -= b[ i ] - 1;
    LL bl = 0 , br = k , ba = 0;
    while( bl <= br ){
      LL bmid = (bl + br) >> 1;
      if( bmid <= ( n - ( k - bmid ) ) / ( b[ i ] - 1 ) )
        ba = bmid , bl = bmid + 1; 
      else
        br = bmid - 1;
    }
    if( ba ){
      v.push_back( { ba , b[ i ] - 1 } );
      k -= ba;
      n -= ba * ( b[ i ] - 1 );
    }
    if( k ){
      LL mr = n - k;
      v.push_back( { 1 , 1 + mr } );
      if( k > 1 )
        v.push_back( { k - 1 , 1 } );
    }
    output();
  }
  puts( "-1" );
}
int main(){
  init();
  solve();
}
