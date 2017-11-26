#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define X 2048576
bool p[ X ];
vector<LL> pri;
void build(){
  for( LL i = 2 ; i < X ; i ++ ) if( !p[ i ] ){
    pri.push_back( i );
    for( LL j = i ; j < X ; j += i )
      p[ j ] = true;
  }
  //cerr << "# of prime " << pri.size() << endl;
}
LL n;
vector< int > fac;
void factor(){
  fac.clear();
  LL tn = n;
  for( auto pr : pri ){
    if( pr * pr > tn ) break;
    if( tn % pr == 0 ){
      int cc = 0;
      while( tn % pr == 0 ){
        cc ++;
        tn /= pr;
      }
      fac.push_back( cc );
    }
  }
  if( tn > 1 )
    fac.push_back( 1 );
}
LL ans;
void go( size_t cur , int tmp ){
  if( cur == fac.size() ){
    ans += tmp;
    return;
  }
  for( int i = 0 ; i <= fac[ cur ] ; i ++ )
    go( cur + 1 , tmp + (i > 0) );
}
int main(){
  build();
  int t; scanf( "%d" , &t ); while( t -- ){
    scanf( "%lld" , &n );
    factor();
    ans = 0;
    go( 0 , 0 );
    printf( "%lld\n" , ans );
  }
}
