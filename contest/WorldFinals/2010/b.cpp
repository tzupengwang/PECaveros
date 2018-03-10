#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 200
int n , a[ N ];
int code[ 1 << 6 ];
vector< pair< pair<int,int> , pair<int,int> > > cand;
bool okay( int l , int r , int L , int R ){
  return L * 210 >= R * 190 and
         L * 105 >= r * 190 and
         l * 210 >= R *  95 and
         l * 105 >= r *  95;
}
void build(){
  for( int i = 0 ; i < (1 << 6) ; i ++ )
    code[ i ] = -1;
  code[  1 ] = 0;
  code[ 17 ] = 1;
  code[  9 ] = 2;
  code[ 24 ] = 3;
  code[  5 ] = 4;
  code[ 20 ] = 5;
  code[ 12 ] = 6;
  code[  3 ] = 7;
  code[ 18 ] = 8;
  code[ 16 ] = 9;
  code[  4 ] = 10;
  code[  6 ] = 11;
  for( int l = 1 ; l <= 200 ; l ++ )
    for( int r = l ; r <= 200 ; r ++ )
      for( int L = r + 1 ; L <= 200 ; L ++ )
        for( int R = L ; R <= 200 ; R ++ )
          if( okay( l , r , L , R ) )
            cand.push_back( { {l, r}, {L, R} } );
  //cerr << cand.size() << endl;
}
void init(){
  for( int i = 0 ; i < n ; i ++ )
    scanf( "%d" , &a[ i ] );
}
bool in( pair<int,int> pp , int x ){
  return pp.first <= x and x <= pp.second;
}
int _cs;
int b[ N ];
bool decoded( pair<int,int> ss , pair<int,int> ll , int tor ){
  for( int i = 0 ; i < n ; i ++ )
    if( in( ss , a[ i ] ) )
      b[ i ] = 0;
    else if( in( ll , a[ i ] ) )
      b[ i ] = 1;
    else
      return false;
  for( int i = 5 ; i < n ; i += 6 )
    if( b[ i ] )
      return false;
  for( int _ = 0 ; _ < 2 ; _ ++ ){
    reverse( b , b + n );
    vector<int> vl;
    bool ok = true;
    for( int i = 0 ; i < n and ok ; i += 6 ){
      int vv = 0;
      for( int j = 0 ; j < 5 ; j ++ )
        vv = (vv << 1) | b[ i + j ];
      if( code[ vv ] == -1 )
        ok = false;
      vl.push_back( code[ vv ] );
    }
    if( not ok ) continue;
    if( vl.size() < 5u ) continue;
    if( vl[ 0 ] != 11 ) continue;
    if( vl.back() != 11 ) continue;
    for( size_t i = 1 ; i + 1 < vl.size() ; i ++ )
      if( vl[ i ] == 11 ){
        ok = false;
        break;
      }
    if( not ok ) continue;
    int candc = 0;
    int candk = 0;
    int nn = vl.size() - 4u;
    for( size_t i = 1 , j = 1 ; i < vl.size() - 3u ; i ++ , j ++ ){
      candc = (candc + ((nn     - j) % 10 + 1) * vl[ i ]) % 11;
      candk = (candk + ((nn + 1 - j) %  9 + 1) * vl[ i ]) % 11;
    }
    candk = (candk + candc) % 11;
    if( candc == vl[ vl.size() - 3 ] and candk == vl[ vl.size() - 2u ] ){
      for( size_t i = 1 ; i + 3 < vl.size() ; i ++ )
        putchar( vl[ i ] < 10 ? vl[ i ] + '0' : '-' );
      puts( "" );
      return true;
    }
    if( candc == vl[ vl.size() - 3 ] and tor == 1 ){
      puts( "bad K" );
      return true;
    }
    if( tor == 2 ){
      puts( "bad C" );
      return true;
    }
  }
  return false;
}
void solve(){
  printf( "Case %d: " , ++ _cs );
  if( (n + 1) % 6 == 0 ){
    for( int j = 0 ; j < 3 ; j ++ )
      for( auto i : cand )
        if( decoded( i.first , i.second , j ) )
          return;
  }
  puts( "bad code" );
}
int main(){
  build();
  while( scanf( "%d" , &n ) == 1 and n ){
    init();
    solve();
  }
}
