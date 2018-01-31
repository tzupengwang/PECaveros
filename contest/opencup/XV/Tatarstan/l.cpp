#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 101010
LL n , p[ N ];
int main(){
  cin >> n;
  for( int i = 0 ; i < n ; i ++ )
    cin >> p[ i ];
  LL mx = *max_element( p , p + n );
  vector<int> cand;
  for( int i = 0 ; i < n ; i ++ )
    if( p[ i ] == mx )
      cand.push_back( i );
  if( mx == 0 )
    cout << 0 << endl;
  else if( cand.size() == 1u ){
    bool found = false;
    int who = cand[ 0 ];
    if( who and mx > p[ who - 1 ] + 2 )
      found = true;
    if( who + 1 < n and mx > p[ who + 1 ] + 2 )
      found = true;
    if( found )
      cout << mx - 1 << endl;
    else
      cout << mx << endl;
  }else{
    bool found = false , found2 = false;
    for( int who : cand ){
      if( who and p[ who - 1 ] )
        found = true;
      if( who + 1 < n and p[ who + 1 ])
        found = true;
    }
    if( found )
      cout << mx + 1 << endl;
    else if(mx == 1)
      cout << (int)cand.size() * mx << endl;
    else 
      cout << ((int)cand.size() - 1) * mx << endl;
  }
}
