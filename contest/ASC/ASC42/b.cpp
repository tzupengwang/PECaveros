#include <bits/stdc++.h>
using namespace std;
int n , s , p , t;
void solve(){
  double ans = 0.0 , np = 1.0 , pp = (double)p / 100.0;
  int now = s;
  while( t -- && now > 0 ){
    int mx = min( now , n - now );
    if( now + mx == n ){
      ans += np * pp;
      now -= mx;
      np *= ( 1.0 - pp );
    }else{
      np *= pp;
      now += mx;
    }
  }
  printf( "%.12f\n" , ans );
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "betting.in" , "r" , stdin );
  freopen( "betting.out" , "w" , stdout );
#endif
  while( scanf( "%d%d%d%d" , &n , &s , &p , &t ) == 4 && n )
    solve();
}
