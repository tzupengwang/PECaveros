#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
inline pair<LL,LL> hsh( const vector<int>& cnt ){
  LL ret1 = 0 , ret2 = 0;
  for( int i = 0 ; i < 13 ; i ++ )
    ret1 = ret1 * 10 + cnt[ i ];
  for( int i = 0 ; i < 13 ; i ++ )
    ret2 = ret2 * 10 + cnt[ 13 + i ];
  return { ret1 , ret2 };
}
#define N 202020
int n , m;
string cand[ N ];
vector<string> v;
bool cmp( string s1 , string s2 ){
  return s1.length() < s2.length();
}
map< pair<LL,LL> , int > bst;
map<string, int> id;
int dp[ N ] , pre[ N ];
int main(){
  cin >> n;
  for( int i = 0 ; i < n ; i ++ )
    cin >> cand[ i ];
  cin >> m;
  for( int i = 0 ; i < m ; i ++ ){
    string tmp; cin >> tmp;
    v.push_back( tmp );
  }
  v.push_back( "" );
  sort( v.begin() , v.end() , cmp );
  for( size_t i = 0 ; i < v.size() ; i ++ )
    id[ v[ i ] ] = i;
  bst[ { 0 , 0 } ] = 0;
  for( size_t i = 1 ; i < v.size() ; i ++ ){
    dp[ i ] = v[ i ].length();
    pre[ i ] = i;
    vector<int> cnt;
    cnt.resize( 26 );
    for( int j = 0 ; j < 26 ; j ++ )
      cnt[ j ] = 0;
    for( auto c : v[ i ] )
      cnt[ c - 'a' ] ++;
    for( size_t j = 0 ; j < v[ i ].length() ; j ++ ){
      cnt[ v[ i ][ j ] - 'a' ] --;
      pair<LL,LL> hsvl = hsh( cnt );
      {
        auto it = bst.find( hsvl );
        if( it != bst.end() ){
          int who = it->second;
          if( dp[ who ] < dp[ i ] ){
            dp[ i ] = dp[ who ];
            pre[ i ] = who;
          }
        }
      }
      cnt[ v[ i ][ j ] - 'a' ] ++;
    }
    pair<LL,LL> hsvl = hsh( cnt );
    auto it = bst.find( hsvl );
    if( it != bst.end() ){
      if( dp[ i ] < dp[ it->second ] )
        bst[ hsvl ] = i;
    }else
      bst[ hsvl ] = i;
  }
  for( int i = 0 ; i < n ; i ++ ){
    int now = id[ cand[ i ] ];
    vector<string> vv;
    while( true ){
      if( now == 0 )
        vv.push_back( "." );
      else
        vv.push_back( v[ now ] );
      if( now == pre[ now ] ) break;
      now = pre[ now ];
    }
    cout << vv.size() << "\n";
    for( size_t j = 0 ; j < vv.size() ; j ++ ){
      if( j ) cout << " -> ";
      cout << vv[ j ];
    }
    cout << "\n";
  }
}
