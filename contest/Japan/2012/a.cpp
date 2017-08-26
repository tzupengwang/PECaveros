#include <bits/stdc++.h>
using namespace std;
#define int long long
int n , m;
void init(){
  cin >> n >> m;
}
int gcd( int v1 , int v2 ){
  if( v1 == 0 and v2 == 0 ) return 0;
  if( v1 == 0 or v2 == 0 ) return v1 + v2;
  return __gcd( v1 , v2 );
}
bool prime(){
  int mx = n * n + m * m;
  set< pair<int,int> > S;
  for( int i = 0 ; i * i <= mx ; i ++ )
    for( int j = 0 ; i * i + j * j <= mx ; j ++ ){
      if( i == 0 and j == 0 )
        continue;
      for( int di = -1 ; di <= 1 ; di += 2 )
        for( int dj = -1 ; dj <= 1 ; dj += 2 ){
          int ii = i * di;
          int jj = j * dj;
          int vl = ii * ii + jj * jj;
          if( mx % vl ) continue;
          int c1 = ii * n + jj * m;
          int c2 = ii * m - jj * n;
          int dd = gcd( abs( c1 ) , abs( c2 ) );
          if( dd % vl == 0 )
            S.insert( { ii , jj } );
          if( (int)S.size() > 8 )
            return false;
        }
    }
  return true;
}
void solve(){
  puts( prime() ? "P" : "C" );
}
int32_t main(){
  int t; cin >> t; while( t -- ){
    init();
    solve();
  }
}
