#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define N 303030
typedef long long LL;
int n , m;
set<int> s[ N ];
void init(){
  scanf( "%d%d" , &n , &m );
  while( m -- ){
    int ui , vi;
    scanf( "%d%d" , &ui , &vi );
    s[ ui ].insert( vi );
    s[ vi ].insert( ui );
  }
}
bool con( int ui , int vi ){
  return s[ ui ].find( vi ) != s[ ui ].end();
}
vector<int> jiou( int ui , int vi ){
  vector<int> ret;
  for( auto x : s[ ui ] )
    if( s[ vi ].find( x ) != s[ vi ].end() )
      ret.push_back( x );
  return ret;
}
LL ax[ N ] , ay[ N ];
bool used[ N ];
void gogo( int ld , int lu , int rd , int ru ){
  used[ ld ] = true;
  used[ lu ] = true;
  used[ rd ] = true;
  used[ ru ] = true;
  {
    bool gt = false;
    for( auto a : s[ ld ] ){
      for( auto b : s[ lu ] ){
        if( a == lu or b == ld ) continue;
        if( con( a , b ) ){
          if( used[ a ] and used[ b ] ) continue;
          //printf( "%d %d %d %d -> %d %d\n" , ld , lu , rd , ru , a , b );
          ax[ a ] = ax[ ld ] - 1;
          ay[ a ] = ay[ ld ];
          ax[ b ] = ax[ lu ] - 1;
          ay[ b ] = ay[ lu ];
          gogo( a , b , ld , lu );
          gt = true;
          break;
        }
      }
      if( gt ) break;
    }
  }
  {
    bool gt = false;
    for( auto a : s[ rd ] ){
      for( auto b : s[ ru ] ){
        if( a == ru or b == rd ) continue;
        if( con( a , b ) ){
          if( used[ a ] and used[ b ] ) continue;
          //printf( "%d %d %d %d -> %d %d\n" , ld , lu , rd , ru , a , b );
          ax[ a ] = ax[ rd ] + 1;
          ay[ a ] = ay[ rd ];
          ax[ b ] = ax[ ru ] + 1;
          ay[ b ] = ay[ ru ];
          gogo( rd , ru , a , b );
          gt = true;
          break;
        }
      }
      if( gt ) break;
    }
  }
  {
    bool gt = false;
    for( auto a : s[ ld ] ){
      for( auto b : s[ rd ] ){
        if( a == rd or b == ld ) continue;
        if( con( a , b ) ){
          if( used[ a ] and used[ b ] ) continue;
          //printf( "%d %d %d %d -> %d %d\n" , ld , lu , rd , ru , a , b );
          ax[ a ] = ax[ ld ];
          ay[ a ] = ay[ ld ] - 1;
          ax[ b ] = ax[ rd ];
          ay[ b ] = ay[ rd ] - 1;
          gogo( a , ld , b , rd );
          gt = true;
          break;
        }
      }
      if( gt ) break;
    }
  }
  {
    bool gt = false;
    for( auto a : s[ lu ] ){
      for( auto b : s[ ru ] ){
        if( a == ru or b == lu ) continue;
        if( con( a , b ) ){
          if( used[ a ] and used[ b ] ) continue;
          //printf( "%d %d %d %d -> %d %d\n" , ld , lu , rd , ru , a , b );
          ax[ a ] = ax[ lu ];
          ay[ a ] = ay[ lu ] + 1;
          ax[ b ] = ax[ ru ];
          ay[ b ] = ay[ ru ] + 1;
          gogo( lu , a , ru , b );
          gt = true;
          break;
        }
      }
      if( gt ) break;
    }
  }
}
void solve(){
  int st = 0;
  for( int i = 1 ; i <= n ; i ++ )
    if( s[ i ].size() == 2u ){
      st = i;
      break;
    }
  assert( st );
  int up = *s[ st ].begin();
  ay[ up ] = 1;
  int rg = *s[ st ].rbegin();
  ax[ rg ] = 1;
  int who = 0;
  vector<int> ret = jiou( up , rg );
  for( int x : ret )
    if( x != st ){
      who = x;
      break;
    }
  assert( who );
  ax[ who ] = 1; ay[ who ] = 1;
  gogo( st , up , rg , who );
  //LL minx = *min_element( ax + 1 , ax + n + 1 );
  //LL miny = *min_element( ay + 1 , ay + n + 1 );
  //for( int i = 1 ; i <= n ; i ++ ){
    //ax[ i ] = ax[ i ] - minx - 100000;
    //ay[ i ] = ay[ i ] - miny - 100000;
  //}
  for( int i = 1 ; i <= n ; i ++ )
    printf( "%lld %lld\n" , ax[ i ] , ay[ i ] );
}
int main(){
  init();
  solve();
}
