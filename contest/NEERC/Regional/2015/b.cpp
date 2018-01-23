#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define N 200

vector<string> va;

int vl[ N ][ N ];

void build(){
  vl[ 0 ][ 0 ] = 1;
  for( int i = 1 ; i < N ; i ++ ){
    for( int j = 0 ; j < N ; j ++ )
      vl[ i ][ j ] = vl[ i - 1 ][ j ] * 10;
    for( int j = 0 ; j + 1 < N ; j ++ ){
      vl[ i ][ j + 1 ] += vl[ i ][ j ] / 2;
      vl[ i ][ j ] &= 1;
    }
  }
}

int tv[ N ];

bool ok( const string& ss ){
  for( int i = 0 ; i < N ; i ++ )
    tv[ i ] = 0;

  for( size_t i = 0 ; i < ss.length() ; i ++ ){
    if( ss[ i ] == '0' ) continue;
    int pw = ss.length() - i - 1;
    for( int j = 0 ; j < N ; j ++ )
      tv[ j ] += vl[ pw ][ j ];
  }
  for( int j = 0 ; j + 1 < N ; j ++ ){
    tv[ j + 1 ] += tv[ j ] / 2;
    tv[ j ] &= 1;
  }
  for( size_t i = 0 ; i < ss.length() ; i ++ )
    if( tv[ i ] != ss[ ss.length() - i - 1 ] - '0' )
      return false;
  return true;
}

//void go(ll x, int l) {
  //vector<int> v;
  //while (x) {
    //v.push_back(x % 2);
    //x /= 2;
  //}
  //char buf[100];
  //for (int i = 0; i < l; i ++) buf[i] = ' ';
  //buf[l] = '\0';

  //for (int i = 0; i < (int)v.size(); i ++) {
    //if (l - i - 1 < 0) break;
    //buf[l - i - 1] = v[i] + '0';
  //}
  //puts(buf);
//}

bool cmp( string s1 , string s2 ){
  if( s1.length() != s2.length() )
    return s1.length() < s2.length();
  return s1 < s2;
}

int main(){
  build();
  freopen( "binary.in" , "r" , stdin );
  freopen( "binary.out" , "w" , stdout );
  va.push_back( "0" );
  va.push_back( "1" );
  //ll k = 1;
  //for (int i = 0; i < 25; i ++) {
    //go(k, 50);

    //k *= 10;
  //}
  for( int len = 2 ; ; len ++ ){
    int vsz = (int)va.size();
    for( int _ = 0 ; _ < vsz ; _ ++ ){
      const string& x = va[ _ ];
      string ns = "1";
      int tlen = len - x.length() - 1;
      for( int i = 0 ; i < tlen ; i ++ )
        ns += "0";
      ns += x;
      if( ok( ns ) ){
        va.push_back( ns );
      }
    }
    if( va.size() >= 10001 ) break;
  }
  //cerr << va.size() << endl;
  sort( va.begin() , va.end() , cmp );
  int n; cin >> n;
  cout << va[ n ] << endl;
}
