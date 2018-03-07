#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 3030
char c[ N ];
int len;
vector< pair<pair<int,char>,int> > lcp[ N ];
void predo(){
  for( int i = 0 ; i < len ; i ++ )
    lcp[ i ].clear();
  for( int i = 1 ; i < len ; i ++ ){
    int pg = -1;
    char pc = 0;
    for( int j = 0 ; i + j <= len ; j ++ ){
      if( i + j == len ){
        lcp[ i ].push_back( { { pg , pc } , j } );
        break;
      }
      if( c[ j ] != '*' and c[ i + j ] != '*' ){
        if( c[ j ] != c[ i + j ] ){
          lcp[ i ].push_back( { { pg , pc } , j } );
          break;
        }
        continue;
      }
      if( c[ j ] == '*' and c[ i + j ] != '*' ){
        if( j + j < len ){
          lcp[ i ].push_back( { { pg , pc } , j } );
          pg = j;
          pc = c[ i + j ];
        }
      }
    }
  }
}
//vector< pair<pair<int,char>,int> > lcp[ N ];
vector<int> cand;
char t[ N ];
string ans;
vector<int> which[ N ];
inline int LCP( int id ){
  int ret = 0;
  for( auto k : lcp[ id ] ){
    if( k.first.first == -1 or
        t[ k.first.first ] == k.first.second )
      ret = k.second;
    else
      break;
  }
  ret = min( ret , len / 2 );
  return ret;
}
int nxt[ N ] , pre[ N ] , mx;
int gogo(){
  for( int i = 0 ; i <= len ; i ++ ){
    which[ i ].clear();
    nxt[ i ] = i + 1;
    pre[ i ] = i - 1;
  }

  mx = 1;
  for( int i = 1 ; i < len ; i ++ )
    which[ LCP( i ) ].push_back( i );
  for( int cl = 0 ; cl + 1 < (int)ans.length() ; cl ++ ){
    for( int i : which[ cl ] ){
      mx = max( mx , nxt[ i ] - pre[ i ] );
      pre[ nxt[ i ] ] = pre[ i ];
      nxt[ pre[ i ] ] = nxt[ i ];
    }
    if( mx <= cl + 1 )
      return cl + 1;
  }
  return -1;
}
void go( size_t cur ){
  if( cur == cand.size() ){
    int ret = gogo();
    if( ret <= 0 ) return;
    if( ret >= (int)ans.length() ) return;
    ans = "";
    for( int i = 0 ; i < ret ; i ++ )
      if( c[ i ] == '*' )
        ans += t[ i ];
      else
        ans += c[ i ];
    return;
  }
  t[ cand[ cur ] ] = 'R'; go( cur + 1 );
  t[ cand[ cur ] ] = 'G'; go( cur + 1 );
  t[ cand[ cur ] ] = 'B'; go( cur + 1 );
}
string test( int ii ){
  int lst = len - ii;
  for( int i = 0 ; i < ii ; i ++ )
    if( c[ i ] != '*' and c[ lst + i ] != '*' and
        c[ i ] != c[ lst + i ] )
      return "";
  string ret = "";
  for( int i = 0 ; i < ii ; i ++ )
    if( c[ i ] == '*' and c[ lst + i ] == '*' )
      ret += "R";
    else
      ret += (c[ i ] == '*' ? c[ lst + i ] : c[ i ] );
  return ret;
}
string solve(){
  ans = "";
  for( int i = 0 ; i < len ; i ++ )
    ans += (c[ i ] == '*' ? 'R' : c[ i ]);
  predo();
  cand.clear();
  for( int i = 0 ; i + i < len ; i ++ )
    if( c[ i ] == '*' )
      cand.push_back( i );
  go( 0 );
  if( (int)ans.length() < len ) return ans;
  for( int i = len / 2 + 1 ; i <= len ; i ++ ){
    string can = test( i );
    if( can.length() )
      return can;
  }
  assert( false );
  return "";
}
int main(){
  int _; scanf( "%d" , &_ ); while( _ -- ){
    scanf( "%s" , c );
    len = strlen( c );
    int cnt = 0;
    for( int i = 0 ; i + i < len ; i ++ )
      if( c[ i ] == '*' )
        cnt ++;
    bool rev = cnt >= 10;
    if( rev ) reverse( c , c + len );
    string aa = solve();
    if( rev ) reverse( aa.begin() , aa.end() );
    printf( "%s\n" , aa.c_str() );
  }
}
