#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long long LL;

ll c[2005][2005];

vector<ll> v;

ll inf9 = 1e9;
ll inf = 4 * inf9 * inf9;

bool cal( LL now , int m , LL goal ){
  LL cur = 1;
  for( int i = 0 ; i < m ; i ++ ){
    if( cur > inf / (now - i) )
      return true;
    cur *= (now - i);
  }
  //cerr << now << " " << m << " " << goal << " " << cur << endl;
  return cur > goal;
}

LL C( LL k , int m ){
  LL ret = 1;
  for( int i = 0 ; i < m ; i ++ )
    ret *= (k - i);
  for( int i = 0 ; i < m ; i ++ )
    ret /= (m - i);
  return ret;
}

void go(ll n, int m) {
  if (m == 0) return;

  //cerr << n << " " << m << endl;

  ll k , ckm;
  if( m > 5 ){
    k = m - 1;
    while (c[k][m] <= n) k ++ ;
    k --;
    ckm = c[k][m];
  }else{
    if( m == 1 ){
      k = n + 1;
      k --;
      ckm = n;
    }else{
      LL goal = n;
      for( int i = 1 ; i <= m ; i ++ )
        goal *= i;
      LL bl = m , br = 10000000000LL , ba = bl;
      while( bl <= br ){
        LL bmid = (bl + br) >> 1;
        if( cal( bmid , m , goal ) )
          ba = bmid , br = bmid - 1;
        else
          bl = bmid + 1;
      }
      k = ba - 1;
      ckm = C( k , m );
    }
  }

  //cerr << n << " " << m << " " << k << " " << ckm << endl;

  v.push_back(k);
  go(n - ckm, m - 1);
}

int main() {
  ll n;
  int m;
  scanf("%lld%d", &n, &m);

  for (int i = 0; i <= 2000; i ++) c[i][i] = c[i][0] = 1;
  for (int i = 1; i <= 2000; i ++)
    for (int j = 1; j < i; j ++)
      c[i][j] = c[i - 1][j] + c[i - 1][j - 1];

  go(n, m);
  for (int i = 0; i < (int)v.size(); i ++) {
    printf("%lld%c", v[i], " \n"[i + 1 == (int)v.size()]);
  }
}
