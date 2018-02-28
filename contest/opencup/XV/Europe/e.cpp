#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 101010
LL n , ans , a;
vector<LL> pri;
bool p[ N ];
void test( LL h ){
  if( h < 2 ) return;
  LL ca = (n / h) + 1 - h;
  if( ca % 2 ) return;
  if( ca <= 0 ) return;
  ca /= 2;
  if( ans == -1 or h < ans ){
    ans = h;
    a = ca;
  }
}
vector< pair<LL,LL> > fac;
void go( size_t cur , LL vl ){
  if( cur == fac.size() ){
    test( vl );
    return;
  }
  for( int i = 0 ; i <= fac[ cur ].second ; i ++ ){
    go( cur + 1 , vl );
    vl *= fac[ cur ].first;
  }
}
int main(){
  for( int i = 2 ; i < N ; i ++ ) if( !p[ i ] ){
    pri.push_back( i );
    for( int j = i ; j < N ; j += i )
      p[ j ] = true;
  }
  int t; cin >> t; while( t -- ){
    cin >> n;
    n *= 2;
    fac.clear();
    LL nn = n;
    for( LL pp : pri ){
      if( pp * pp > nn ) break;
      if( nn % pp ) continue;
      int cnt = 0;
      while( nn % pp == 0 ){
        cnt ++;
        nn /= pp;
      }
      fac.push_back( { pp , cnt } );
    }
    if( nn > 1 )
      fac.push_back( { nn , 1 } );


    ans = -1;
    go( 0 , 1 );
    //for( LL h = 2 ; h * h <= n ; h ++ ){
      //if( n % h ) continue;
      //test( h );
      //if( h * h < n )
        //test( n / h );
    //}
    if( ans == -1 )
      puts( "IMPOSSIBLE" );
    else{
      n >>= 1;
      printf( "%lld =" , n );
      for( LL i = a ; n > 0 ; i ++ ){
        printf( " %lld" , i );
        n -= i;
        if( n == 0 ) puts( "" );
        else printf( " +" );
        assert( n >= 0 );
      }
    }
  }
}
