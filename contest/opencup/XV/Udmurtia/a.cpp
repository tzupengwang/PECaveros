#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
tuple<string,int,int> read(){
  string a , b;
  cin >> a >> b;
  if( b[ 0 ] == '.' )
    return make_tuple( a , b.length() , 0 );
  if( '0' <= b[ 0 ] and b[ 0 ] <= '9' )
    return make_tuple( a , b[ 0 ] - '0' , 1 );
  if( b == "I" ) return make_tuple( a , 1 , 2 );
  if( b == "II" ) return make_tuple( a , 2 , 2 );
  if( b == "III" ) return make_tuple( a , 3 , 2 );
  if( b == "IV" ) return make_tuple( a , 4 , 2 );
  if( b == "V" ) return make_tuple( a , 5 , 2 );
  if( b == "VI" ) return make_tuple( a , 6 , 2 );
  assert( false );
  return make_tuple( "" , 0 , 0 );
}
#define C(X) get<0>(X)
#define N(X) get<1>(X)
#define T(X) get<2>(X)
tuple<string,int,int> a[ 3 ];
vector<string> ans;
int type[ 9 ];
string color[ 9 ];
int cnt[ 3 ];

bool is_p( int x ){
  return x == 2 or x == 3 or x == 5;
}

int main(){
  for( int i = 0 ; i < 3 ; i ++ ){
    a[ i ] = read();
    cnt[ T( a[ i ] ) ] ++;
    type[ N( a[ i ] ) ] = T( a[ i ] );
    color[ N( a[ i ] ) ] = C( a[ i ] );
  }
  if( cnt[ 0 ] == 3 ) ans.push_back( "John" );
  if( cnt[ 2 ] == 0 ) ans.push_back( "David" );
  {
    bool ok = true;
    for( int i = 0 ; i < 3 ; i ++ )
      if( C( a[ i ] ) != "W" )
        ok = false;
    if( ok ) ans.push_back( "Peter" );
  }
  {
    bool ok = true;
    for( int i = 0 ; i < 3 ; i ++ )
      if( C( a[ i ] ) != "B" and C( a[ i] ) != "W" )
        ok = false;
    if( ok ) ans.push_back( "Robert" );
  }
  {
    bool ok = true;
    for( int i = 0 ; i < 3 ; i ++ )
      if( N( a[ i ] ) % 2 ){
        if( C( a[ i ] ) != "W")
          ok = false;
      }else{
        if( C( a[ i ] ) != "B" )
          ok = false;
      }
    if( ok ) ans.push_back( "Mark" );
  }
  {
    bool ok = true;
    for( int i = 0 ; i < 3 ; i ++ )
      if( is_p( N( a[ i ] ) ) != ( T( a[ i ] ) == 1 ) )
        ok = false;
    if( ok ) ans.push_back( "Paul" );
  }
  {
    bool ok = true;
    for( int i = 0 ; i < 3 ; i ++ ){
      if( C( a[ i ] ) == "B" or C( a[ i ] ) == "W" )
        ok = false;
      if( i and C( a[ i ] ) != C( a[ i - 1 ] ) )
        ok = false;
    }
    if( ok ) ans.push_back( "Patrick" );
  }
  {
    bool ok = true;
    for( int i = 0 ; i < 3 ; i ++ )
      if( T( a[ i ] ) == 2 ){
        if( C( a[ i ] ) != "Y" )
          ok = false;
      }
    if( ok ) ans.push_back( "Jack" );
  }
  {
    bool ok = true;
    for( int i = 0 ; i < 3 ; i ++ )
      for( int j = i + 1 ; j < 3 ; j ++ )
        if( C( a[ i ] ) == C( a[ j ] ) )
          ok = false;
    if( ok ) ans.push_back( "Max" );
  }
  {
    bool ok = true;
    for( int i = 0 ; i < 3 ; i ++ )
      for( int j = i + 1 ; j < 3 ; j ++ )
        if( (T( a[ i ] ) == T( a[ j ] )) !=
            (C( a[ i ] ) == C( a[ j ] )) )
          ok = false;
    if( ok ) ans.push_back( "Alex" );
  }
  for( size_t i = 0 ; i < ans.size() ; i ++ )
    printf( "%s%c" , ans[ i ].c_str() , " \n"[ i + 1 == ans.size() ] );
}
