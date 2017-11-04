#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int t , x , y;
pair<LL,LL> gcd(LL a , LL b){
	if(b == 0) return {1, 0};
  pair<LL,LL> q = gcd(b, a % b);
  return {q.second, q.first - q.second * (a / b)};
}
inline LL cal( const vector< pair<LL,LL> > vv ){
  if( vv.empty() ) return 1e9;
  LL ret = 0;
  for( size_t i = 0 ; i < vv.size() ; i ++ ){
    int nxt = (i + 1) % vv.size();
    ret += vv[ i ].first * vv[ nxt ].second -
           vv[ i ].second * vv[ nxt ].first;
  }
  return abs( ret );
}
int main(){
  cin >> t; while( t -- ){
    cin >> x >> y;
    vector< pair<LL,LL> > ans , ans2;
    {
      pair<LL,LL> ab = gcd( x , y );
      ans.push_back( { 0 , 0 } );
      ans.push_back( { abs( ab.second ) , abs( ab.first ) } );
      ans.push_back( { x , y } );
    }
    {
      LL g = __gcd( x , y );
      if( g > 1 ){
        ans2.push_back( { 0 , 0 } );
        ans2.push_back( { x , y - 1 } );
        ans2.push_back( { x / g , y / g } );
        ans2.push_back( { x - 1 , y } );
      }
    }
    LL area1 = cal( ans );
    LL area2 = cal( ans2 );
    if( area2 < area1 )
      ans = ans2;
    printf( "%d\n" , (int)ans.size() );
    for( auto i : ans )
      printf( "%lld %lld\n" , i.first , i.second );
  }
}
