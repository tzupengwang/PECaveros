#include <bits/stdc++.h>
using namespace std;
#define N 1021
#define K 100
typedef long long LL;
typedef long double D;
const LL mod = 1000000007;
const D eps = 1e-14;
char c[ N ];
LL a[ K ] , len;
LL prod;
D prodlog;
LL mypow( LL d , LL b ){
  if( b == 0 ) return 1;
  LL ret = mypow( ( d * d ) % mod , b / 2 );
  if( b % 2 ) ret = ( ret * d ) % mod;
  return ret;
}
inline LL inv( LL x ){
  return mypow( x , mod - 2 );
}
void init(){
  scanf( "%s" , c );
  len = strlen( c );
  prod = 1;
  for( LL i = 0 ; i < len ; i += 2 ){
    LL vl = ( c[ i ] - '0' ) * 10 + c[ i + 1 ] - '0';
    a[ vl ] ++;
    prod = ( prod * vl ) % mod;
    prodlog += log( vl );
  }
}
vector< pair< LL , LL > > v1 , v2;
vector< pair< D , LL > > d1 , d2;
void go( const vector< pair<LL,LL> >& vv ,
         vector< pair<D,LL> >& dd ,
         LL now , LL tmul , D tlog ){
  if( now == (LL)vv.size() ){
    dd.push_back( { tlog , tmul } );
    return;
  }
  D tvl = log( vv[ now ].first );
  for( LL i = 0 ; i <= vv[ now ].second ; i ++ ){
    go( vv , dd , now + 1 , tmul , tlog );
    tmul = ( tmul * vv[ now ].first ) % mod;
    tlog += tvl;
  }
}
void solve(){
  LL all = 1;
  for( LL i = 0 ; i < K ; i ++ ){
    if( a[ i ] == 0 ) continue;
    all *= (LL)( a[ i ] + 1 );
    if( all <= 100000 ) v1.push_back( { i , a[ i ] } );
    else v2.push_back( { i , a[ i ] } );
  }
  go( v1 , d1 , 0 , 1 , 0.0 );
  go( v2 , d2 , 0 , 1 , 0.0 );
  sort( d1.begin() , d1.end() );
  sort( d2.begin() , d2.end() );
  reverse( d2.begin() , d2.end() );
  D target = prodlog * 0.5 + eps;
  D bst = -1e100;
  LL pp = 1;
  size_t ptr = 0;
  for( size_t i = 0 ; i < d1.size() ; i ++ ){
    while( ptr < d2.size() && d1[ i ].first + d2[ ptr ].first > target )
      ptr ++;
    if( ptr == d2.size() ) break;
    D sum = d1[ i ].first + d2[ ptr ].first;
    if( sum > bst ){
      bst = sum;
      pp = ( (LL)d1[ i ].second * (LL)d2[ ptr ].second ) % mod;
    }
  }
  printf( "%lld\n" , ( pp + prod * inv( pp ) % mod ) % mod );
}
int main(){
  init();
  solve();
}
