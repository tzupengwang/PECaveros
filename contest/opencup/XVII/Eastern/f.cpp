#include <bits/stdc++.h>
using namespace std;
int n;
int main(){
  cin >> n;
  if( n > 8 ){
    puts( "-1" );
    exit(0);
  }
  vector<int> a;
  for( int i = 1 ; i <= n ; i ++ )
    a.push_back( i );
  do{
    bool ok = true;
    for( int i = 1 ; i < n and ok ; i ++ )
      if( a[ i ] % a[ i - 1 ] and a[ i - 1 ] % a[ i ] )
        ok = false;
    if( ok ){
      for( int i = 0 ; i < n ; i ++ )
        cout << a[ i ] << " \n"[ i + 1 == n ];
      exit(0);
    }
  }while( next_permutation( a.begin() , a.end() ) );
  puts( "-1" );
}
