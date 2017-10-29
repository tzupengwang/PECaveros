#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define N 101010
typedef long long LL;
LL BIT[ N ];
inline int lb( int x ){
  return x & (-x);
}
void modify( int x , LL v ){
  x ++;
  for( int i = x ; i < N ; i += lb( i ) )
    BIT[ i ] = max( BIT[ i ] , v );
}
LL query( int x ){
  x ++;
  LL ret = 0;
  for( int i = x ; i ; i -= lb( i ) )
    ret = max( ret , BIT[ i ] );
  return ret;
}
int n , c;
int parse(){
  int h , m , d;
  scanf( "%d:%d:%d" , &h , &m , &d );
  return h * 60 * 60 + m * 60 + d;
}
vector< pair< pair<int,int> , int > > vv;
int main(){
  scanf( "%d%d" , &n , &c );
  for( int i = 0 ; i < n ; i ++ ){
    int lt = parse();
    int rt = parse();
    int prob; scanf( "%d" , &prob );
    vv.push_back( { { rt , lt } , prob - c * ( rt - lt ) } );
  }
  sort( vv.begin() , vv.end() );
  LL ans = 0;
  for( auto i : vv ){
    LL cur = query( i.first.second ) + i.second;
    if( cur > ans ) ans = cur;
    modify( i.first.first , cur );
  }
  cout << ans << endl;
}
