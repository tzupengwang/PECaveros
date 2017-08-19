#include <bits/stdc++.h>
using namespace std;
#define N 4010
string s;
int len;
void init(){
  cin >> s;
  //for( int i = 0 ; i < 4000 ; i ++ )
    //s += 'a' + ( i % 26 );
  len = s.length();
}
vector<string> vv;
int ans , at , alen;
int lcp[ N ];
void solve(){
  for( int st = 0 ; st < len ; st ++ ){
    map<char,char> M;
    string tmp = "";
    char nxt = 'a';
    for( int i = st ; i < len ; i ++ ){
      if( M.find( s[ i ] ) == M.end() )
        M[ s[ i ] ] = nxt ++;
      tmp += M[ s[ i ] ];
    }
    vv.push_back( tmp );
  }
  sort( vv.begin() , vv.end() );
  for( int i = 0 ; i + 1 < len ; i ++ ){
    while( lcp[ i ] < (int)vv[ i ].length() and
           lcp[ i ] < (int)vv[ i + 1 ].length() ){
      if( vv[ i ][ lcp[ i ] ] == vv[ i + 1 ][ lcp[ i ] ] )
        lcp[ i ] ++;
      else
        break;
    }
  }
  for( int i = 1 ; i <= len ; i ++ ){
    for( size_t l = 0 , r ; l < vv.size() ;  ){
      if( (int)vv[ l ].length() < i ){
        l ++;
        continue;
      }
      r = l;
      while( r < vv.size() and lcp[ r ] >= i ) r ++;
      int tot = r - l + 1;
      int tans = i * tot;
      if( tans > ans ){
        ans = tans;
        at = l;
        alen = i;
      }
      l = r + 1;
    }
  }
  cout << vv[ at ].substr( 0 , alen ) << endl;
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "pattern.in" , "r" , stdin );
  freopen( "pattern.out" , "w" , stdout );
#endif
  init();
  solve();
}
