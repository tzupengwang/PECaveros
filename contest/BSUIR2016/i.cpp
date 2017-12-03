#include <bits/stdc++.h>
using namespace std;
#define N 101010
string s;
int n , cand[ N ];
int main(){
  cin >> s;
  cin >> n;
  for( int i = 0 ; i < n ; i ++ )
    cin >> cand[ i ];
  int len = s.length();
  bool same = false;
  for( int i = 0 ; i < len ; i ++ ){
    bool ok = false;
    for( int j = 0 ; j < n ; j ++ ){
      if( i + cand[ j ] < len and
          s[ i + cand[ j ] ] < s[ i ] ){
        ok = true;
        break;
      }
      if( i + cand[ j ] < len and
          s[ i + cand[ j ] ] == s[ i ] )
        same = true;
    }
    if( not ok ) continue;
    vector<string> ss;
    for( int j = 0 ; j < n ; j ++ )
      if( i + cand[ j ] < len and
          s[ i + cand[ j ] ] < s[ i ] ){
        swap( s[ i ] , s[ i + cand[ j ] ] );
        ss.push_back( s );
        swap( s[ i ] , s[ i + cand[ j ] ] );
      }
    sort( ss.begin() , ss.end() );
    cout << ss[ 0 ] << endl;
    exit(0);
  }
  if( same ){
    cout << s << endl;
    exit(0);
  }
  for( int i = len - 1 ; i >= 0 ; i -- ){
    bool ok = false;
    for( int j = 0 ; j < n ; j ++ )
      if( i + cand[ j ] < len ){
        ok = true;
        break;
      }
    if( not ok ) continue;
    vector<string> ss;
    for( int j = 0 ; j < n ; j ++ )
      if( i + cand[ j ] < len ){
        swap( s[ i ] , s[ i + cand[ j ] ] );
        ss.push_back( s );
        swap( s[ i ] , s[ i + cand[ j ] ] );
      }
    sort( ss.begin() , ss.end() );
    cout << ss[ 0 ] << endl;
    exit(0);
  }
}
