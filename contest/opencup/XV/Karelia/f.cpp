#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int mod = 7340033;
inline int add( int a , int b ){
  a += b;
  return a >= mod ? a - mod : a;
}
inline int mul( LL a , LL b ){
  a *= b;
  return a >= mod ? a % mod : a;
}
#define DIM 150
struct Mat{
  int n , a[ DIM ][ DIM ];
  Mat( int _n = 0 ){
    n = _n;
    for( int i = 0 ; i < n ; i ++ )
      for( int j = 0 ; j < n ; j ++ )
        a[ i ][ j ] = 0;
  }
  Mat operator*( const Mat& he ) const{
    Mat ret( n );
    for( int i = 0 ; i < n ; i ++ )
      for( int j = 0 ; j < n ; j ++ )
        for( int k = 0 ; k < n ; k ++ )
          ret.a[ i ][ j ] = add( ret.a[ i ][ j ] ,
                                 mul( a[ i ][ k ] , he.a[ k ][ j ] ) );
    return ret;
  }
  Mat operator^( LL tk ) const{
    Mat I( n ) , A( n );
    for( int i = 0 ; i < n ; i ++ ){
      for( int j = 0 ; j < n ; j ++ )
        A.a[ i ][ j ] = a[ i ][ j ];
      I.a[ i ][ i ] = 1;
    }
    while( tk ){
      if( tk & 1 ) I = I * A;
      A = A * A;
      tk >>= 1;
    }
    return I;
  }
};
string to_s( int x ){
  char buf[ 32 ] = {};
  sprintf( buf , "%d" , x );
  string ret = "";
  int len = strlen( buf );
  for( int i = 0 ; i < len ; i ++ )
    ret += buf[ i ];
  return ret;
}
map<string, int> S_id;
int s_id;
queue<string> Q;
string gen_s( const string& ori ){  
  string now = "";
  int len = ori.length();
  for( int bl = 0 , br = 0 ; bl < len ; bl = br ){
    while( br < len and ori[ bl ] == ori[ br ] ) br ++;
    now += to_s( br - bl );
    now += ori[ bl ];
  }
  return now;
}
vector<string> split( const string& ss ){
  vector<int> mid;
  mid.push_back( 0 );
  for( int i = 0 ; i < (int)ss.length() ; i ++ ){
    if( ss.substr( i , 4 ) == "1231" )
      mid.push_back( i + 2 );
  }
  mid.push_back( ss.length() );
  vector<string> ret;
  for( size_t i = 0 ; i + 1 < mid.size() ; i ++ )
    ret.push_back( ss.substr( mid[ i ] , mid[ i + 1 ] - mid[ i ] ) );
  return ret;
}
Mat A;
int main(){
  A = Mat( DIM );
  S_id[ "2" ] = s_id ++;
  Q.push( "2" );

  while( Q.size() ){
    string cur = Q.front(); Q.pop();
    string nxt = gen_s( cur );
    vector<string> res = split( nxt );
    for( auto i : res ){
      if( S_id.find( i ) == S_id.end() ){
        S_id[ i ] = s_id ++;
        Q.push( i );
      }
      A.a[ S_id[ cur ] ][ S_id[ i ] ] ++;
    }
  }

  LL t; cin >> t;
  A = A ^ t;
  LL ans = 0;
  for( auto i : S_id ){
    int len = i.first.length();
    ans = add( ans , mul( len , A.a[ 0 ][ i.second ] ) );
  }
  printf( "%lld\n" , ans );
}
