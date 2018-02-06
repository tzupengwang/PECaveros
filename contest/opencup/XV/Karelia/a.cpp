#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int mod = 120586241;
inline int add( int a , int b ){
  a += b;
  return a >= mod ? a - mod : a;
}
inline int mul( LL a , int b ){
  a *= b;
  return a >= mod ? a % mod : a;
}
inline int mpow( int a , int b ){
  int ret = 1;
  while( b ){
    if(b & 1) ret = mul( ret , a );
    a = mul( a , a );
    b >>= 1;
  }
  return ret;
}
inline int inv( int a ){
  return mpow( a , mod - 2 );
}
int t , n , b;
vector<int> p;
//set< vector<int> > S;
//queue< vector<int> > Q;

#define N 101010

int sz[ N ];
int bit[ N ];
int lb( int x ){ return x & (-x); }
inline void modify( int x , int d ){
  for( int i = x ; i <= n ; i += lb( i ) )
    bit[ i ] += d;
}
inline int query( int x ){
  int ret = 0;
  for( int i = x ; i ; i -= lb( i ) )
    ret += bit[ i ];
  return ret;
}

int vl[ N ] , rnk[ N ] , vst[ N ] , stmp;
int score( int li , int ri ){
  int ret = vl[ ri ];
  if( li ) ret = mul( ret , inv( vl[ li - 1 ] ) );
  return ret;
}

int main(){
  scanf( "%d" , &t ); while( t -- ){
    scanf( "%d%d" , &n , &b );
    p.resize( n );
    for( int i = 0 ; i < n ; i ++ )
      scanf( "%d" , &p[ i ] );
    ++ stmp;
    
    for( int i = n - 1 , sc = 0 ; i >= 0 ; i -- , sc ++ )
      vl[ i ] = (sc / b) + 1;

    for( int i = 1 ; i < n ; i ++ )
      vl[ i ] = mul( vl[ i - 1  ] , vl[ i ] );

    for( int i = n - 1 ; i >= 0 ; i -- ){
      if( vst[ i ] == stmp ) break;
      for( int j = i ; j >= 0 ; j -= b ){
        rnk[ j ] = query( p[ j ] );
        modify( p[ j ] , +1 );
      }
      for( int j = i ; j >= 0 ; j -= b ){
        vst[ j ] = stmp;
        modify( p[ j ] , -1 );
      }
    }
    
    int ans = 0;
    for( int i = 0 ; i + b + b < n ; i ++ ){
      //printf( "%d %d\n" , rnk[ i ] , score( i + 1 , n - b - b - 1 ) );
      ans = add( ans , mul( mul( rnk[ i ] , score( i + 1 , n - b - b - 1 ) ) , 2 ) );
    }
    vector<int> v1 , v2;
    for( int i = n - b - b ; i < n ; i ++ )
      v1.push_back( p[ i ] );
    for( int i = n - b ; i < n ; i ++ )
      v2.push_back( p[ i ] );
    for( int i = n - b - b ; i < n - b ; i ++ )
      v2.push_back( p[ i ] );
    if( v2 < v1 )
      ans = add( ans , 1 );
    printf( "%d\n" , add( ans , 1 ) );

    /*
    S.clear();
    S.insert( p );
    Q.push( p );
    while( Q.size() ){
      vector<int> vv = Q.front(); Q.pop();
      for( int i = 0 ; i + b + b <= n ; i ++ ){
        vector<int> tv = vv;
        for( int j = i ; j < i + b ; j ++ )
          tv[ j ] = vv[ j + b ];
        for( int j = i + b ; j < i + b + b ; j ++ )
          tv[ j ] = vv[ j - b ];
        if( S.find( tv ) != S.end() ) continue;
        S.insert( tv );
        Q.push( tv );
      }
    }
    cout << S.size() << endl;
    */
  }
}
