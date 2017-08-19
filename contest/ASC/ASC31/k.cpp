#include <bits/stdc++.h>
using namespace std;
#define N 514
char c[ N ];
string ret;
int rnk( char ctmp ){
  if( ctmp == '*' or ctmp == '/' ) return 2;
  if( ctmp == '+' or ctmp == '-' ) return 1;
  if( ctmp == '(' ) return 0;
  assert( false );
  return -1;
}
struct Node{
  int hi , wi;
  char who;
  int lc , rc;
  Node(){
    lc = rc = 0;
    hi = wi = 1;
    who = 0;
  }
} pl[ N + N ];
int nid , rc[ N ] , len;
int to_i( char ctmp ){
  if( ctmp == '+' ) return -1;
  if( ctmp == '-' ) return -2;
  if( ctmp == '*' ) return -3;
  if( ctmp == '/' ) return -4;
  if( ctmp == '^' ) return -5;
  return -6;
}
char to_c( int ii ){
  return " +-*/^"[ -ii ];
}
int parse( int l , int r ){
  vector< int > vv;
  for( int i = l ; i <= r ; )
    if( c[ i ] == '(' ){
      vv.push_back( parse( i + 1 , rc[ i ] - 1 ) );
      i = rc[ i ] + 1;
    }else if( to_i( c[ i ] ) >= -5 ){
      vv.push_back( to_i( c[ i ] ) );
      i ++;
    }else{
      ++ nid;
      pl[ nid ].hi = pl[ nid ].wi = 1;
      pl[ nid ].who = c[ i ];
      vv.push_back( nid );
      i ++;
    }
  { // deal with ^
    reverse( vv.begin() , vv.end() );
    vector<int> vvv;
    for( size_t i = 0 ; i < vv.size() ; i ++ ){
      if( to_c( vv[ i ] ) != '^' ){
        vvv.push_back( vv[ i ] );
        continue;
      }
      int rop = vvv.back(); vvv.pop_back();
      int lop = vv[ i + 1 ]; i ++;
      ++ nid;
      pl[ nid ].lc = lop;
      pl[ nid ].rc = rop;
      pl[ nid ].who = '^';
      pl[ nid ].hi = max( pl[ lop ].hi , pl[ rop ].hi ) + 2;
      pl[ nid ].wi = pl[ lop ].wi + pl[ rop ].wi + 5;
      vvv.push_back( nid );
    }
    vv = vvv;
  }
  {
    reverse( vv.begin() , vv.end() );
    vector<int> var;
    vector<int> op;
    for( auto i : vv ){
      if( i > 0 ){
        var.push_back( i );
        continue;
      }
      while( op.size() and rnk( to_c( op.back() ) ) >=
                           rnk( to_c( i ) ) ){
        int oop = op.back(); op.pop_back();
        int rop = var.back(); var.pop_back();
        int lop = var.back(); var.pop_back();
        ++ nid;
        pl[ nid ].lc = lop;
        pl[ nid ].rc = rop;
        pl[ nid ].who = to_c( oop );
        pl[ nid ].hi = max( pl[ lop ].hi , pl[ rop ].hi ) + 2;
        pl[ nid ].wi = pl[ lop ].wi + pl[ rop ].wi + 5;
        var.push_back( nid );
      }
      op.push_back( i );
    }
    while( op.size() ){
      int oop = op.back(); op.pop_back();
      int rop = var.back(); var.pop_back();
      int lop = var.back(); var.pop_back();
      ++ nid;
      pl[ nid ].lc = lop;
      pl[ nid ].rc = rop;
      pl[ nid ].who = to_c( oop );
      pl[ nid ].hi = max( pl[ lop ].hi , pl[ rop ].hi ) + 2;
      pl[ nid ].wi = pl[ lop ].wi + pl[ rop ].wi + 5;
      var.push_back( nid );
    }
    assert( var.size() == 1u );
    return var[ 0 ];
  }
}
#define O 4096
char out[ O ][ O ];
int til[ O ];
int mxr;
int print( int row , int col , int who ){
  if( pl[ who ].lc ){
    int lcol = print( row + 2 , col , pl[ who ].lc );
    int lwidth = pl[ pl[ who ].lc ].wi;
    int rcol = print( row + 2 , col + lwidth + 5 , pl[ who ].rc );
    out[ row + 1 ][ lcol ] = out[ row + 1 ][ rcol ] = '|';
    til[ row + 1 ] = max( til[ row + 1 ] , rcol );
    for( int i = lcol ; i <= rcol ; i ++ )
      out[ row ][ i ] = '-';
    out[ row ][ lcol ] = out[ row ][ rcol ] = '.';
    out[ row ][ col + lwidth + 1 ] = '[';
    out[ row ][ col + lwidth + 2 ] = pl[ who ].who;
    out[ row ][ col + lwidth + 3 ] = ']';
    til[ row ] = max( til[ row ] , rcol );
    return col + lwidth + 2;
  }
  //printf( "%d : %d %d %d %d\n" , who , row , col , pl[ who ].wi , pl[ who ].hi );
  mxr = max( mxr , row );
  til[ row ] = max( til[ row ] , col );
  out[ row ][ col ] = pl[ who ].who;
  return col;
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "tree.in" , "r" , stdin );
  freopen( "tree.out" , "w" , stdout );
#endif
  scanf( "%s" , c );
  len = strlen( c );
  vector<int> vv;
  for( int i = 0 ; i < len ; i ++ )
    if( c[ i ] == '(' )
      vv.push_back( i );
    else if( c[ i ] == ')' ){
      rc[ vv.back() ] = i;
      vv.pop_back();
    }
  int root = parse( 0 , len - 1 );
  for( int i = 0 ; i < O ; i ++ )
    for( int j = 0 ; j < O ; j ++ )
      out[ i ][ j ] = ' ';
  print( 0 , 0 , root );
  //printf( "%d\n" , pl[ root ].wi );
  //cout << *max_element( til , til + 10 ) << endl;
  for( int i = 0 ; i <= mxr ; i ++ , puts( "" ) )
    for( int j = 0 ; j <= til[ i ] ; j ++ )
      putchar( out[ i ][ j ] );
}
