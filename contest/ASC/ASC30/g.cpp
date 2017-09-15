#include <bits/stdc++.h>
using namespace std;
#define N 101010
typedef long long LL;
LL n;
vector< pair<LL,LL> > v;
int main(){
#ifdef ONLINE_JUDGE
  freopen( "pulp.in" , "r" , stdin );
  freopen( "pulp.out" , "w" , stdout );
#endif
  cin >> n;
  v.resize( n );
  for( int i = 0 ; i < n ; i ++ )
    cin >> v[ i ].first >> v[ i ].second;
  sort( v.begin() , v.end() );
  LL ans = 0 , ptr = 0 , cur = 0;
  priority_queue< LL , vector<LL> , greater<LL> > heap;
  while( heap.size() or ptr < n ){
    while( ptr < n and v[ ptr ].first <= cur )
      heap.push( v[ ptr ++ ].second );
    if( heap.size() ){
      LL res = heap.top(); heap.pop();
      if( ptr < n ){
        LL nxt = v[ ptr ].first;
        LL mx = min( res , nxt - cur );
        res -= mx;
        cur += mx;
        if( res == 0 )
          ans += cur;
        else
          heap.push( res );
      }else{
        cur += res;
        ans += cur;
      }
      continue;
    }else{
      cur = v[ ptr ].first;
      heap.push( v[ ptr ++ ].second );
    }
  }
  cout << ans << endl;
}
