#include <bits/stdc++.h>
using namespace std;
vector<string> words( string s ){
  vector<string> ret;
  string word = "";
  for( auto c : s ){
    if( isalpha( c ) )
      word += tolower( c );
    else{
      if( word.length() > 0 )
        ret.push_back( word );
      word = "";
    }
  }
  if( word.length() > 0 )
    ret.push_back( word );
  return ret;
}
bool okay_dot( const string& s , int l , int r ){
  for( int i = l + 1 ; i <= r ; i ++ ){
    if( s[ i ] == ' ' )
      continue;
    if( islower( s[ i ] ) )
      return false;
    return true;
  }
  return true;
}
vector<string> sentences( string s ){
  int l = 0 , r = (int)s.length() - 1;
  while( s[ l ] == ' ' ) l ++;
  while( s[ r ] == ' ' ) r --;
  if( l > r ) return {};
  vector<string> ret;
  while( l <= r ){
    while( l <= r and s[ l ] == ' ' ) l ++;
    string sen = "";
    while( l <= r ){
      sen += s[ l ];
      if( s[ l ] == '?' or s[ l ] == '!' ){
        l ++;
        break;
      }
      if( s[ l ] == '.' and okay_dot( s , l , r ) ){
        l ++;
        break;
      }
      l ++;
    }
    ret.push_back( sen );
  }
  return ret;
}
string s;
int n;
vector<string> ss;
set<string> ww[ 1021 ];
void init(){
  getline( cin , s );
  ss = sentences( s );
  for( size_t i = 0 ; i < ss.size() ; i ++ ){
    vector<string> ws = words( ss[ i ] );
    for( auto w : ws )
      ww[ i ].insert( w );
  }
}
string buf;
void solve(){
  cin >> n;
  getline( cin , buf );
  while( n -- ){
    getline( cin , buf );
    vector<string> ws = words( buf );
    cout << "Search results for \"" << buf << "\":\n";
    for( size_t i = 0 ; i < ss.size() ; i ++ ){
      bool ok = true;
      for( auto w : ws )
        if( ww[ i ].find( w ) == ww[ i ].end() ){
          ok = false;
          break;
        }
      if( ok )
        cout << "- \"" << ss[ i ] << "\"\n";
    }
  }
}
int main(){
  init();
  solve();
}
