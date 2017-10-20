#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int main(){
  int t; cin >> t; while( t -- ){
    LL n; cin >> n;
    n ++;
    for( int i = 1 ; ; i = 1 - i ){
      if( i == 0 ){
        LL hf = n / 2;
        while( hf + hf < n ) hf ++;
        //cerr << "NO " << n << " " << hf << endl;
        if( hf <= 1 ){
          puts( "NO" );
          break;
        }
        n = hf;
      }else{
        LL hf = n / 9;
        while( hf * 9 < n ) hf ++;
        //cerr << "YES " << n << " " << hf << endl;
        if( hf <= 1 ){
          puts( "YES" );
          break;
        }
        n = hf;
      }
    }
  }
}
