#include <bits/stdc++.h>

using namespace std;

const int K = 30000;

typedef pair<int, int> pii;

int cur;

int P = 3;

int qtms;

bool can(int x) {
  assert( ++ qtms <= 30000 );
#ifndef LOCAL
  char ip[4];
  printf("%d\n", x);
  fflush(stdout);
  scanf("%s", ip);
  return strcmp(ip, "yes") == 0;
#else
  static set<pii> es;
  static set<pii> nes;
  if (es.count({cur, x})) return 1;
  if (nes.count({cur, x})) return 0;
  if (rand() % 100 + 1 <= P) {
    es.insert({cur, x});
    return 1;
  } else {
    nes.insert({cur, x});
    return 0;
  }
#endif
}

set<int> been;

const int MSK = (1<<15)-1;

inline int pick() {
  unsigned int res = 0;
  do {
    res = rand()&MSK | ((rand()&MSK)<<15);
  } while (been.count(res));
  return res;
}

int main() {
  if( can( 1 ) ) return 0;
  for( int i = 2 ; ; i ++ ){
    if( can( i ) ){
      if( can( 1 ) )
        return 0;
    }
  }
  //srand(time(0) ^ 514514);
  //been.insert(0);
  //int cnt = 0;
  //for (int i = 0; i < K; ++i) {
    //int nxt = 0;
    //do {
      //nxt = pick();
    //} while(!can(nxt));
    //printf("%d\n", nxt);
    //been.insert(nxt);
    //if (nxt == 1) break;
    //if (can(1)) break;
    //cur = nxt;
    //cnt = i+1;
  //}
}
