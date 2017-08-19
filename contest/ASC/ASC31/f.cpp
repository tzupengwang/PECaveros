#include <bits/stdc++.h>
using namespace std;
typedef string var;
var max( var a , var b ){
  var ret;
  if( a.length() > 3 ) ret = "(" + a + ")";
  else ret = a;
  ret += "|";
  if( b.length() > 3 ) ret += "(" + b + ")";
  else ret += b;
  return ret;
}
var min( var a , var b ){
  var ret;
  if( a.length() > 3 ) ret = "(" + a + ")";
  else ret = a;
  ret += "&";
  if( b.length() > 3 ) ret += "(" + b + ")";
  else ret += b;
  return ret;
}
var ans[ 55 ];
var to_s( int num ){
  var ret = "";
  if( num < 10 ) ret += ('0' + num);
  else{
    ret += ('0' + num / 10);
    ret += ('0' + num % 10);
  }
  return ret;
}
var variable( int which , int num ){
  var ret = which ? "y" : "x";
  ret += to_s( num );
  return ret;
}
void solve( int n , int m ){
  for( int i = 1 ; i <= n + m ; i ++ ){
    string out = "";
    for( int j = 0 ; j <= n ; j ++ ){
      int k = i - j;
      //printf( "%d : %d %d\n" , i , j , k );
      if( k < 0 or k > m ) continue;
      if( j == 0 ){
        if( out.length() == 0 )
          out = variable( 1 , k );
        else
          out = min( out , variable( 1 , k ) );
      }else if( k == 0 ){
        if( out.length() == 0 )
          out = variable( 0 , j );
        else
          out = min( out , variable( 0 , j ) );
      }else{
        if( out.length() == 0 )
          out = max( variable( 0 , j ) , variable( 1 , k ) );
        else
          out = min( out , max( variable( 0 , j ) , variable( 1 , k ) ) );
      }
    }
    cout << out << endl;
  }
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "merge.in" , "r" , stdin );
  freopen( "merge.out" , "w" , stdout );
#endif
  int n , m;
  cin >> n >> m;
  solve( n , m );
}
