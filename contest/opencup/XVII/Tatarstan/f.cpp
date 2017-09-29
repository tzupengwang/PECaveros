#include <bits/stdc++.h>
using namespace std;
#define N 111
inline int mcp(string s){
  int n = s.length();
  s += s;
  int i=0, j=1;
  while (i<n && j<n){
    int k = 0;
    while (k < n && s[i+k] == s[j+k]) k++;
    if (s[i+k] >= s[j+k]) j += k+1;
    else i += k+1;
    if (i == j) j++;
  }
  int ans = i < n ? i : j;
  return ans;
  //return s.substr(ans, n);
}
int n , m;
char c[ N ][ N ];
int main(){
  scanf( "%d%d" , &n , &m );
  for( int i = 1 ; i <= n ; i ++ )
    scanf( "%s" , c[ i ] + 1 );
  string ans;
  bool gt = false;
  {
    vector<string> vv;
    for( int i = 1 ; i <= n ; i ++ ){
      string ss;
      for( int j = 1 ; j <= m ; j ++ )
        ss += c[ i ][ j ];
      vv.push_back( ss );
    }
    sort( vv.begin() , vv.end() , greater<string>() );
    for( size_t i = 0 ; i < vv.size() ; i ++ ){
      string mid = "";
      for( size_t j = 0 ; j < vv.size() ; j ++ )
        if( i != j )
          mid += vv[ j ];
      for( int id = 0 ; id < m ; id ++ ){
        string tans = vv[ i ].substr( id , m - id );
        tans += mid;
        if( id )
          tans += vv[ i ].substr( 0 , id );
        if( not gt or tans > ans ){
          ans = tans;
          gt = true;
        }
      }
    }
  }
  {
    vector<string> vv;
    for( int j = 1 ; j <= m ; j ++ ){
      string ss;
      for( int i = 1 ; i <= n ; i ++ )
        ss += c[ i ][ j ];
      vv.push_back( ss );
    }
    sort( vv.begin() , vv.end() , greater<string>() );
    for( size_t i = 0 ; i < vv.size() ; i ++ ){
      string mid = "";
      for( size_t j = 0 ; j < vv.size() ; j ++ )
        if( i != j )
          mid += vv[ j ];
      for( int id = 0 ; id < n ; id ++ ){
        string tans = vv[ i ].substr( id , n - id );
        tans += mid;
        if( id )
          tans += vv[ i ].substr( 0 , id );
        if( not gt or tans > ans ){
          ans = tans;
          gt = true;
        }
      }
    }
  }
  int len = ans.length() , ptr = 0;
  while( ptr < len and ans[ ptr ] == '0' ) ptr ++;
  if( ptr == len ) puts( "0" );
  else cout << ans.substr( ptr , len ) << endl;
}
