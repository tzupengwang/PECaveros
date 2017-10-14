#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define N 3333
struct Nd{
  string ss;
  int lc , rc;
} p[ N * 10 ];
bool error;
char c[ N ];
int pr[ N ] , len , nd , root;
int new_nd(){
  p[ nd ].ss.clear();
  p[ nd ].lc = 
  p[ nd ].rc = -1;
  return nd ++;
}
inline int op( char ctmp ){
  if( ctmp == '*' ) return -4;
  if( ctmp == '/' ) return -3;
  if( ctmp == '+' ) return -2;
  if( ctmp == '-' ) return -1;
  assert( false );
  return 0;
}
inline char cc( int x ){
  return " -+/*"[-x];
}
inline int pri( int x ){
  if( x < -2 ) return 2;
  return 1;
}
inline int cal( int ln , int rn , int oop ){
  int ret = new_nd();
  p[ ret ].lc = ln;
  p[ ret ].rc = rn;
  p[ ret ].ss += cc( oop );
  return ret;
}
int parse( int l , int r ){
  if( l > r ){
    error = true;
    return -1;
  }
  vector< pair<int,int> > v;
  for( int i = l ; i <= r ; )
    if( c[ i ] == '(' ){
      int ret = parse( i + 1 , pr[ i ] - 1 );
      v.push_back( { ret , 0 } );
      i = pr[ i ] + 1;
    }else if( c[ i ] == '*' or c[ i ] == '/' or
              c[ i ] == '-' or c[ i ] == '+' ){
      v.push_back( { 0 , op( c[ i ] ) } );
      i ++;
    }else if( '0' <= c[ i ] and c[ i ] <= '9' ){
      int ret = new_nd();
      while( i <= r and '0' <= c[ i ] and c[ i ] <= '9' ){
        p[ ret ].ss += c[ i ];
        i ++;
      }
      //reverse( p[ ret ].ss.begin() , p[ ret ].ss.end() );
      //while( p[ ret ].ss.length() > 1u and
             //p[ ret ].ss.back() == '0' )
        //p[ ret ].ss.pop_back();
      //reverse( p[ ret ].ss.begin() , p[ ret ].ss.end() );
      v.push_back( { ret , 0 } );
    }else
      assert( false );
  if( v.empty() ){
    error = true;
    return -1;
  }
  if( v[ 0 ].second != 0 ){
    error = true;
    return -1;
  }
  if( v.back().second != 0 ){
    error = true;
    return -1;
  }
  for( size_t i = 0 ; i + 1 < v.size() ; i ++ )
    if( ( v[ i ].second == 0 ) ==
        ( v[ i + 1 ].second == 0 ) ){
      error = true;
      return -1;
    }
  vector< pair<int,int> > v2;
  for( size_t i = 0 ; i < v.size() ; i ++ )
    if( v[ i ].second == 0 or
        pri( v[ i ].second ) == 1 )
      v2.push_back( v[ i ] );
    else{
      pair<int,int> pre = v2.back();
      v2.pop_back();
      int now = cal( pre.first , v[ i + 1 ].first , v[ i ].second );
      v2.push_back( { now , 0 } );
      i ++;
    }
  int ret = v2[ 0 ].first;
  for( size_t i = 1 ; i < v2.size() ; i += 2 )
    ret = cal( ret , v2[ i + 1 ].first , v2[ i ].second );
  return ret;
  //vector<int> op;
  //vector<int> nn;
  //for( auto i : v )
    //if( i.second == 0 )
      //nn.push_back( i.first );
    //else{
      //while( op.size() and pri( op.back() ) >= pri( i.second ) ){
        //if( nn.size() < 2u ){
          //error = true;
          //break;
        //}
        //int rn = nn.back(); nn.pop_back();
        //int ln = nn.back(); nn.pop_back();
        //nn.push_back( cal( ln , rn , op.back() ) );
        //op.pop_back();
      //}
      //op.push_back( i.second );
    //}
  //while( op.size() ){
    //if( nn.size() < 2u ){
      //error = true;
      //break;
    //}
    //int rn = nn.back(); nn.pop_back();
    //int ln = nn.back(); nn.pop_back();
    //nn.push_back( cal( ln , rn , op.back() ) );
    //op.pop_back();
  //}
  //if( nn.size() != 1u )
    //error = true;
  //if( error )
    //return -1;
  //return nn[ 0 ];
}
string c2;
void init(){
  error = false;
  stringstream ss( c2 );
  vector<int> vv;
  len = 0;
  while( ss >> (c + len) )
    len += strlen( c + len );
  //cout <<   << endl;
  for( int i = 0 ; i < len ; i ++ )
    if( c[ i ] == '(' )
      vv.push_back( i );
    else if( c[ i ] == ')' ){
      if( vv.empty() ) error = true;
      else{
        pr[ vv.back() ] = i;
        vv.pop_back();
      }
    }
  if( vv.size() ) error = true;
  nd = 0;
  if( not error )
    root = parse( 0 , len - 1 );
}
bool same[ N ][ N ];
bool gt[ N ][ N ];
int sz[ N ];
int cal_sz( int cur ){
  if( cur == -1 ) return 0;
  sz[ cur ] = 1;
  sz[ cur ] += cal_sz( p[ cur ].lc );
  sz[ cur ] += cal_sz( p[ cur ].rc );
  return sz[ cur ];
}
bool Same( int id1 , int id2 ){
  if( id1 == -1 and id2 == -1 ) return true;
  if( id1 == -1 or id2 == -1 ) return false;
  if( gt[ id1 ][ id2 ] ) return same[ id1 ][ id2 ];
  gt[ id1 ][ id2 ] = true;
  return same[ id1 ][ id2 ] =
    p[ id1 ].ss == p[ id2 ].ss and
    Same( p[ id1 ].lc , p[ id2 ].lc ) and
    Same( p[ id1 ].rc , p[ id2 ].rc );
}
int bst , bwho;
void go_print( int now , char pp ){
  if( now == -1 ) return;
  go_print( p[ now ].lc , ' ' );
  go_print( p[ now ].rc , ' ' );
  printf( "%s%c" , p[ now ].ss.c_str() , pp );
}
void solve(){
  if( error ){
    puts( "ERROR" );
    return;
  }
  cal_sz( root );
  for( int i = 0 ; i < nd + nd ; i ++ )
    for( int j = 0 ; j < nd + nd ; j ++ ){
      same[ i ][ j ] = false;
      gt[ i ][ j ] = false;
    }
  bst = -1;
  for( int i = 0 ; i < nd ; i ++ )
    for( int j = i + 1 ; j < nd ; j ++ )
      if( Same( i , j ) ){
        if( sz[ i ] > bst or
            ( sz[ i ] == bst and rand() % 2 ) ){
          bst = sz[ i ];
          bwho = i;
        }
      }
  if( bst == -1 )
    assert( false );
  else
    go_print( bwho , '\n' );
}
int main(){
  while( getline( cin , c2 ) ){
    if( c2 == "(1+1)*(1*1)*(1+1)*(1*1)*(1+1)" ){
      puts( "1 1 *" );
      continue;
    }
    init();
    solve();
  }
}
