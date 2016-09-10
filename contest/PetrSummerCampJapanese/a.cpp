#include <bits/stdc++.h>
using namespace std;
#define N 1021
int dp[ N ][ N ] , dp2[ N ][ N ] , len;
vector< pair<int,int> > nxt[ N ][ N ];
bool got[ N ][ N ] , got2[ N ][ N ] , wd[ N ] , st[ N ] , isand[ N ] , isc[ N ];
int nxt2[ N ][ N ];
string cc , token;
vector< string > vv;
const string comma = ",";
inline bool isWord( const string& ts ){
  int tlen = ts.length();
  for( int i = 0 ; i < tlen ; i ++ )
    if( ts[ i ] < 'A' || ts[ i ] > 'Z' )
      return false;
  return true;
}
void init(){
  getline( cin , cc );
  stringstream ss( cc );
  vv.clear();
  while( ss >> token ){
    int tlen = token.length();
    if( token[ tlen - 1 ] == ',' ){
      token.resize( tlen - 1 );
      vv.push_back( token );
      vv.push_back( comma );
    }else
      vv.push_back( token );
  }
  len = (int)vv.size();
  for( int i = 0 ; i < len ; i ++ )
    for( int j = i ; j < len ; j ++ ){
      got[ i ][ j ] = false;
      got2[ i ][ j ] = false;
      nxt[ i ][ j ].clear();
    }
  for( int i = 0 ; i < len ; i ++ ){
    wd[ i ] = isWord( vv[ i ] );
    st[ i ] = false;
    if( i + 2 < len ){
      if( vv[ i ] == "a" &&
          vv[ i + 1 ] == "list" &&
          vv[ i + 2 ] == "of" )
        st[ i ] = true;
    }
    isand[ i ] = false;
    if( vv[ i ] == "and" )
      isand[ i ] = true;
    isc[ i ] = false;
    if( vv[ i ] == "," )
      isc[ i ] = true;
  }
}
inline bool okay( int l , int r ){
  if( r - l + 1 < 3 ) return false;
  return st[ l ];
}
void add_link( vector< pair<int,int> >& tv , int lft , int rgt ){
  if( nxt2[ lft ][ rgt ] == -1 )
    tv.push_back( { lft , rgt } );
  else{
    add_link( tv , lft , nxt2[ lft ][ rgt ] - 1 );
    tv.push_back( { nxt2[ lft ][ rgt ] + 1 , rgt } );
  }
}
int DP2( int l , int r );
int DP( int l , int r ){
  if( l > r ) return 0;
  if( got[ l ][ r ] ) return dp[ l ][ r ];
  got[ l ][ r ] = true;
  if( l == r ){
    if( wd[ l ] )
      return dp[ l ][ r ] = 1;
    return dp[ l ][ r ] = 0;
  }
  dp[ l ][ r ] = 0;
  nxt[ l ][ r ].clear();
  if( !okay( l , r ) ) return dp[ l ][ r ];
  int tdp = DP( l + 3 , r );
  if( tdp ){
    dp[ l ][ r ] += tdp;
    nxt[ l ][ r ].push_back( { l + 3 , r } );
    if( dp[ l ][ r ] > 1 ) return dp[ l ][ r ];
  }
  for( int i = l + 3 ; i < r ; i ++ )
    if( isand[ i ] ){
      int rgt = DP( i + 1 , r );
      if( rgt == 0 ) continue;
      int lft = DP2( l + 3 , i - 1 );
      if( lft == 0 ) continue;
      int tms = lft * rgt;
      if( tms > 1 ) return dp[ l ][ r ] = 2;
      dp[ l ][ r ] += tms;
      if( dp[ l ][ r ] > 1 ) return dp[ l ][ r ] = 2;
      add_link( nxt[ l ][ r ] , l + 3 , i - 1 );
      nxt[ l ][ r ].push_back( { i + 1, r } );
    }
  return dp[ l ][ r ];
}
int DP2( int l , int r ){
  if( got2[ l ][ r ] ) return dp2[ l ][ r ];
  int tdp = DP( l , r );
  if( tdp > 1 ) return dp2[ l ][ r ] = 2;
  if( tdp ) nxt2[ l ][ r ] = -1;
  for( int i = l + 1 ; i < r ; i ++ )
    if( isc[ i ] ){
      int lft = DP2( l , i - 1 );
      if( lft == 0 ) continue;
      int rgt = DP( i + 1 , r );
      if( rgt == 0 ) continue;
      int tms = lft * rgt;
      if( tms > 1 ) return dp2[ l ][ r ] = 2;
      tdp += tms;
      if( tdp > 1 ) return dp2[ l ][ r ] = 2;
      nxt2[ l ][ r ] = i;
    }
  return dp2[ l ][ r ] = tdp;
}
void print( int l , int r ){
  if( l == r ){
    printf( "%s" , vv[ l ].c_str() );
    return;
  }
  printf( "(" );
  for( size_t i = 0 ; i < nxt[ l ][ r ].size() ; i ++ ){
    if( i ) printf( " " );
    print( nxt[ l ][ r ][ i ].first ,
           nxt[ l ][ r ][ i ].second );
  }
  printf( ")" );
}
void solve(){
  int num = DP( 0 , len - 1 );
  // for( string ss : vv )
    // cout << "\"" << ss << "\" ";
  // puts( "" );
  if( num > 1 ) puts( "AMBIGUOUS" );
  else{
    print( 0 , len - 1 );
    puts( "" );
  }
}
int main(){
  int _; scanf( "%d" , &_ );
  getline( cin , cc );
  while( _ -- ){
    init();
    solve();
  }
}
