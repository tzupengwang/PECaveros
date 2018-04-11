#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double D;

const D eps = 1e-9;

int n;

vector<D> chc;

void cut(int id, D r) {
  chc.push_back(chc[id] * r);
  chc[id] *= (1 - r);
  printf("%d %.12f\n", id, r);
  fflush(stdout);
}

void got(int &id, D &r) {
#ifndef LOCAL
  scanf("%d%lf", &id, &r);
#else
  r = 2.0 / 3;
  id = 2 * (rand() % (chc.size() / 2)) + 1;
  printf("%d %.9f\n", id, r);
#endif
  chc.push_back(chc[id] * r);
  chc[id] *= (1-r);
}

double wst = 1.;

void chk() {
#ifndef LOCAL
  int x;
  scanf("%d", &x);
  assert(x == 1);
#else
  D res = 0;
  for (int j = 1; j < chc.size(); j += 2) res += chc[j];
  printf("%.9f\n", res);
  wst = min( wst , res );
  assert(res > 0.55 - eps);
#endif
}

void main2() {
  chc.clear();
  chc.push_back(1);
  for (int i = 0; i < n/2; ++i) {
    vector< pair<double,int> > vv;
    for (int j = 0; j < chc.size(); j += 2) {
      vv.push_back( {chc[j] , j} );
    }
    sort( vv.begin() , vv.end() );
    reverse( vv.begin() , vv.end() );
    if( vv.size() == 1u ) cut( vv[ 0 ].second , 1.0 / 3 );
    else cut( vv[ 1 ].second , 2.0 / 3 );
    //if (i > 0) cut(id, 2.0 / 3);
    //else cut(id, 1.0 / 3);
    int tid; D r;
    got(tid, r);
  }
  {
    int id = -1;
    for (int j = 0; j < chc.size(); j += 2) {
      if (id == -1 || chc[j] > chc[id]) id = j;
    }
    cut(id, 2.0 / 3);
  }
  chk();
}

int main(){
  srand(514514);
  int tc; scanf("%d%d", &tc, &n);
  while (tc--) main2();
  fprintf( stderr , "Word = %.9f\n" , wst );
}
