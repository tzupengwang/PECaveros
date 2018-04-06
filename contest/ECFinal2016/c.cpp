#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<int, int> ii;
#define N 1021
int n , c[ N ];
void init(){
  scanf( "%d" , &n );
  vector<int> li;
  for( int i = 1 ; i <= n ; i ++ ){
    scanf( "%d" , &c[ i ] );
    li.push_back( c[ i ] );
  }
  sort( li.begin() , li.end() );
  li.resize( unique( li.begin() , li.end() ) - li.begin() );
  for( int i = 1 ; i <= n ; i ++ )
    c[ i ] = lower_bound( li.begin() , li.end() , c[ i ] ) - li.begin() + 1;
}
int ans , cnt[ N ] , _cs;
int lp[N];
int ps[N];

void solve(){
  ans = 1;

  { // one segment
    for (int i = 1; i <= n; i ++) cnt[i] = 0;

    for( int lb = 1 , rb = 1 ; rb <= n ; rb ++ ){
      cnt[ c[ rb ] ] ++;
      while( cnt[ c[ rb ] ] > 1 ){
        cnt[ c[ lb ] ] --;
        lb ++;
      }
      ans = max( ans , rb - lb + 1 );
    }
  }

  for (int pl = 1; pl <= n; pl ++) {
    for (int i = 1; i <= n; i ++) cnt[i] = 0;

    int pr = n + 1;
    for (int i = pl; i <= n; i ++) {
      if (cnt[c[i]]) {
        pr = i;
        break;
      }
      cnt[c[i]] = 1;
      lp[c[i]] = i;
    }
    for (int i = 1; i <= n; i ++) if (cnt[i] == 0)
      lp[i] = pr;

    deque<ii> dq;
    multiset<int> cand;
    for (int i = 1; i <= n; i ++) ps[i] = 0;
    int okl = 1;
    for (int lr = 1; lr < pl; lr ++) {
      {
        ii nt(lr, lp[c[lr]] - pl);

        while (dq.size() && dq.back().second >= nt.second) {
          ii tp = dq.back();
          nt.first = tp.first;
          cand.erase(cand.find(tp.second - tp.first));
          dq.pop_back();
        }
        dq.push_back(nt);
        cand.insert(nt.second - nt.first);
      }

      {
        okl = max(okl, ps[c[lr]] + 1);
        ii nt(okl, 0);
        while (dq.size() && dq.front().first <= nt.first) {
          ii tp = dq.front();
          nt.second = tp.second;
          cand.erase(cand.find(tp.second - tp.first));
          dq.pop_front();
        }
        dq.push_front(nt);
        cand.insert(nt.second - nt.first);
      }
      ps[c[lr]] = lr;

      ans = max(ans, *(--cand.end()) + lr + 1);
    }
  }

  printf( "Case #%d: %d\n" , ++ _cs , ans );
}
int main(){
  int t; scanf( "%d" , &t ); while( t -- ){
    init();
    solve();
  }
}
