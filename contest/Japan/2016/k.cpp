#include <bits/stdc++.h>
using namespace std;
#define N 50
typedef long long LL;
int n;
LL sur[ N ];
char c[ N ];
LL bs = (1LL << 50);
inline LL cal(){
  LL ret = 0 , tbs = bs;
  bool flag = false;
  for( int i = 0 ; c[ i ] ; i ++ ){
    if( ( i and c[ i ] != c[ i - 1 ] ) or flag ){
      tbs >>= 1;
      flag = true;
    }
    if( c[ i ] == 'W' )
      ret += tbs;
    else
      ret -= tbs;
  }
  return ret;
}
int ans , len[ N ];
map<LL,int> M;
int main(){
  cin >> n;
  for( int i = 0 ; i < n ; i ++ ){
    cin >> c;
    sur[ i ] = cal();
    len[ i ] = strlen( c );
  }
  if( n < 20 ){
    for( int i = 0 ; i < (1 << n) ; i ++ ){
      int suml = 0;
      LL tmp = 0;
      for( int j = 0 ; j < n ; j ++ )
        if( (i >> j) & 1 ){
          suml += len[ j ];
          tmp += sur[ j ];
        }
      if( tmp == 0 )
        ans = max( ans , suml );
    }
  }else{
    int hf = n / 2 , nhf = n - hf;
    for( int i = 0 ; i < (1 << hf) ; i ++ ){
      int suml = 0;
      LL tmp = 0;
      for( int j = 0 ; j < hf ; j ++ )
        if( (i >> j) & 1 ){
          suml += len[ j ];
          tmp += sur[ j ];
        }
      M[ tmp ] = max( M[ tmp ] , suml );
    }
    for( int i = 0 ; i < (1 << nhf) ; i ++ ){
      int suml = 0;
      LL tmp = 0;
      for( int j = 0 ; j < nhf ; j ++ )
        if( (i >> j) & 1 ){
          suml += len[ hf + j ];
          tmp += sur[ hf + j ];
        }
      auto it = M.find( -tmp );
      if( it == M.end() ) continue;
      ans = max( ans , suml + it->second );
    }
  }
  cout << ans << endl;
}
