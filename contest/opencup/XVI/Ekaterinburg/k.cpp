#include <bits/stdc++.h>
using namespace std;
#define N 101010
map<string,int> child[ N ];
bool is_str[ N ];
string ret[ N ];
int root , cnt;
int new_object(){
  return cnt ++;
}
char c[ N ];
int len , ptr;
string parse_key(){
  string tmp = "";
  while( c[ ptr ] != '\"' ) ptr ++;
  ptr ++;
  while( c[ ptr ] != '\"' ){
    tmp += c[ ptr ];
    ptr ++;
  }
  ptr ++;
  return tmp;
}
int parse_object(){
  int now = new_object();
  if( c[ ptr ] == '{' ) ptr ++;
  while( ptr < len and c[ ptr ] != '}' ){
    string key = parse_key();
    while( c[ ptr ] != ':' ) ptr ++;
    ptr ++;
    if( c[ ptr ] == '{' )
      child[ now ][ key ] = parse_object();
    else{
      assert( c[ ptr ] == '\"' ); ptr ++;
      string value = "";
      while( c[ ptr ] != '\"' ){
        value += c[ ptr ];
        ptr ++;
      }
      ptr ++;
      is_str[ cnt ] = true;
      ret[ cnt ] = value;
      child[ now ][ key ] = cnt ++;
    }
    if( c[ ptr ] == ',' ) ptr ++;
  }
  if( c[ ptr ] == '}' ) ptr ++;
  return now;
}
vector<string> vv;
string got;
bool find( int now , size_t iter ){
  if( iter == vv.size() and is_str[ now ] ){
    got = ret[ now ];
    return true; 
  }
  if( iter == vv.size() )
    return false;
  if( is_str[ now ] ) return false;
  if( child[ now ].count( vv[ iter ] ) )
    return find( child[ now ][ vv[ iter ] ] , iter + 1 );
  return false;
}
char buf[ N ];
void init(){
  while( getchar() != '{' );
  c[ len ++ ] = '{';
  int ccnt = 1;
  bool in = false;
  while( ccnt ){
    char ctmp = getchar();
    if( in ){
      c[ len ++ ] = ctmp;
      if( ctmp == '\"' )
        in = false;
      continue;
    }
    if( ctmp == ' ' or ctmp == '\n' ) continue;
    c[ len ++ ] = ctmp;
    if( ctmp == '\"' ) in = true;
    if( ctmp == '{' ) ccnt ++;
    if( ctmp == '}' ) ccnt --;
  }
  root = parse_object();
  fgets( buf , N , stdin );
}
vector< vector<string> > res;
string check( string ss ){
  int tlen = ss.length();
  int l = 0 , r = tlen - 1;
  while( l <= r and ss[ l ] == ' ' ) l ++;
  while( l <= r and ss[ r ] == ' ' ) r --;
  if( l > r ) return ss;
  if( ss.substr( l , 6 ) == "Value:" ){
    vv.clear();
    string tmp = "";
    for( int i = l + 6 ; i <= r ; i ++ )
      if( ss[ i ] == '.' ){
        vv.push_back( tmp );
        tmp = "";
      }else
        tmp += ss[ i ];
    vv.push_back( tmp );
    if( not find( root , 0 ) )
      return ss;
    return got;
  }
  return ss;
}
vector<int> width;
void print_bar(){
  putchar( '+' );
  for( auto i : width ){
    for( int j = 0 ; j < i ; j ++ )
      putchar( '-' );
    putchar( '+' );
  }
  puts( "" );
}
void print( const vector<string>& out ){
  putchar( '|' );
  for( size_t i = 0 ; i < out.size() ; i ++ ){
    cout << out[ i ];
    int rrr = width[ i ] - out[ i ].length();
    for( int j = 0 ; j < rrr ; j ++ )
      putchar( ' ' );
    putchar( '|' );
  }
  puts( "" );
}
void solve(){
  int idx = 0;
  while( fgets( buf , N , stdin ) ){
    idx ++;
    if( idx % 2 ) continue;
    vector<string> tvv;
    int xlen = strlen( buf );
    string tmp;
    for( int i = 0 ; i < xlen ; i ++ )
      if( buf[ i ] == '|' ){
        if( tmp.size() )
          tvv.push_back( check( tmp ) );
        tmp.clear();
      }else
        tmp += buf[ i ];
    res.push_back( tvv );
  }
  width.resize( res[ 0 ].size() );
  for( auto i : res )
    for( size_t j = 0 ; j < i.size() ; j ++ )
      width[ j ] = max( width[ j ] , (int)i[ j ].length() );
  print_bar();
  for( auto i : res ){
    print( i );
    print_bar();
  }
}
int main(){
  init();
  solve();
}
