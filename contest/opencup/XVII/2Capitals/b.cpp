#include <bits/stdc++.h>
using namespace std;
#define N 1021
string del;
bool bye;
inline string get_line(){
  string in , ret = "";
  if( !getline( cin , in ) ){
    bye = true;
    return del;
  }
  for( auto c : in ){
    if( c == ' ' ) continue;
    if( c == '\n' ) continue;
    ret += c;
  }
  return ret;
}
typedef vector<string> pages;
pages book;
vector<pages> note;
bool okay( const string& o , const string& n ){
  if( n.length() > o.length() ) return false;
  if( (int)o.length() < n.length() * 0.96 ) return false;
  int it = 0;
  for( auto c : o ){
    if( it >= (int)n.length() ) break;
    if( n[ it ] == '#' or n[ it ] == c ) it ++;
  }
  return it == (int)n.length();
}
int ans[ N ];
bool used[ N ];
int main(){
  for( int i = 0 ; i < 12 ; i ++ )
    del += "---###";
  del += "---";
  while( true ){
    string x = get_line();
    if( x == del ) break;
    book.push_back( x );
  }
  pages pp;
  while( true ){
    string x = get_line();
    if( x == del ){
      if( pp.size() )
        note.push_back( pp );
      pp.clear();
      if( bye ) break;
      continue;
    }
    pp.push_back( x );
  }
  int tot = note.size() , st = 0;
  for( int i = 1 ; i <= tot ; i ++ ){
    bool found = false;
    for( int j = 0 ; j < tot ; j ++ ){
      if( used[ j ] ) continue;
      if( i != tot and note[ j ].size() < 25 )
        continue;
      int gg = 0 , len = note[ j ].size();
      for( int k = 0 ; k < len and gg < 2 ; k ++ )
        if( not okay( book[ st + k ] , note[ j ][ k ] ) )
          gg ++;
      if( gg < 2 ){
        st += (int)note[ j ].size();
        ans[ j ] = i;
        used[ j ] = true;
        found = true;
        break;
      }
    }
    assert( found );
  }
  for( int i = 0 ; i < tot ; i ++ )
    printf( "%d%c" , ans[ i ] , " \n"[ i + 1 == tot ] );
}
