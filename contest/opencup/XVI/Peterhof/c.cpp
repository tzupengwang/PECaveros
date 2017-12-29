#include <bits/stdc++.h>
using namespace std;
string cand = "0101010101";
unordered_map<string,string> trans[ 11 ];
#define N 5050
map<string,int> mid;
vector<int> v[ N ];
string go( string ss ){
  string rr = "";
  for( char c : ss ){
    rr += c;
    int len = rr.length();
    if( len > 1 and rr[ len - 1 ] == '0' and
                    rr[ len - 2 ] == '0' ){
      rr.pop_back();
      rr.pop_back();
    }
    if( len > 2 and rr[ len - 1 ] == '1' and
                    rr[ len - 2 ] == '1' and
                    rr[ len - 3 ] == '1' ){
      rr.pop_back();
      rr.pop_back();
      rr.pop_back();
    }
  }
  for( int i = 10 ; i > 5 ; i -- ){
    string tmp = "";
    for( char c : rr ){
      tmp += c;
      int len = tmp.length();
      while( len >= i ){
        string ttmp = "";
        for( int j = i ; j ; j -- )
          ttmp += tmp[ len - j ];
        auto it = trans[ i ].find( ttmp );
        if( it == trans[ i ].end() ) break;
        for( int j = 0 ; j < i ; j ++ )
          tmp.pop_back();
        tmp += it->second;
        len = tmp.length();
      }
    }
    rr = tmp;
  }
  return rr;
}
int main(){
  for( int i = 0 ; i < 10 ; i ++ )
    for( int j = i ; j < 10 ; j ++ ){
      string lft = "" , rgt = "";
      for( int k = 0 ; k < i ; k ++ )
        if( cand[ k ] == '0' )
          lft += "0";
        else
          lft += "11";
      for( int k = 9 ; k > j ; k -- )
        if( cand[ k ] == '0' )
          rgt = "0" + rgt;
        else
          rgt = "11" + rgt;
      lft += rgt;
      string cur = cand.substr( i , j - i + 1 );
      if( lft.length() <= cur.length() )
          //( lft.length() == cur.length() and lft < cur ) )
        trans[ cur.length() ][ cur ] = lft;
    }
  for( int i = 1 ; i <= 10 ; i ++ )
    for( auto x : trans[ i ] )
      cerr << x.first << " " << x.second << endl;
  int n; cin >> n;
  for( int i = 0 ; i < n ; i ++ ){
    string x; cin >> x;
    cout << go( x ) << endl;
  }

}
