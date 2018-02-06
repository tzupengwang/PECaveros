#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 333
string cmd;
int bl[ N ] , len;
bool better( const string& s1 , const string& s2 ){
  if( s1.length() != s2.length() ) return s1.length() < s2.length();
  return s1 < s2;
}
string parse( int l , int r ){
  if( l > r ) return "";
  vector<string> res;
  vector<string> tmp;
  for( int i = l ; i <= r ; ){
    if( isalpha( cmd[ i ] ) ){
      string _tmp = "";
      _tmp += cmd[ i ];
      tmp.push_back( _tmp );
      i ++;
      continue;
    }
    if( cmd[ i ] == '*' ){
      if( tmp.size() )
        tmp.pop_back();
      string _tmp = "";
      tmp.push_back( _tmp );
      i ++;
      continue;
    }
    if( cmd[ i ] == '|' ){
      string rtmp = "";
      for( auto j : tmp )
        rtmp += j;
      res.push_back( rtmp );
      tmp.clear();
      i ++;
      continue;
    }
    if( cmd[ i ] == '(' ){
      tmp.push_back( parse( i + 1 , bl[ i ] - 1 ) );
      i = bl[ i ] + 1;
      continue;
    }
    if( cmd[ i ] == '$' ){
      string _tmp = "";
      tmp.push_back( _tmp );
      i ++;
      continue;
    }
    assert( false );
  }
  {
    string rtmp = "";
    for( auto i : tmp )
      rtmp += i;
    res.push_back( rtmp );
  }
  string ret = res[ 0 ];
  for( auto i : res )
    if( better( i , ret ) )
      ret = i;
  return ret;
}
int main(){
  int t; cin >> t; while( t -- ){
    cin >> cmd;
    len = cmd.length();
    vector<int> stk;
    for( int i = 0 ; i < len ; i ++ )
      if( cmd[ i ] == '(' )
        stk.push_back( i );
      else if( cmd[ i ] == ')' ){
        bl[ stk.back() ] = i;
        stk.pop_back();
      }
    string ans = parse( 0 , len - 1 );
    if( ans.length() < 1 ) ans = "$";
    cout << ans << endl;
  }
}
