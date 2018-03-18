#include<bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;

int N, M;
int p[205];

int fd(int x) {
  return (p[x] == x) ? x : (p[x] = fd(p[x]));
}

set<int> odd, even;
vector<int> st[205];
bool par[205];
set<ii> e;

bool dp[205][205][2];

void addedge(int x, int y) {
  if (x > y) swap(x, y);

  int p1 = fd(x);
  int p2 = fd(y);
  if (p1 > p2) swap(p1, p2);

  if (p1 == p2) {
    e.erase(ii(x, y));
  } else {
    for (int x1 : st[p1]) {
      for (int x2 : st[p2]) {
        if (x1 > x2) swap(x1, x2);

        if (ii(x1, x2) == ii(x, y)) continue;
        e.insert(ii(x1, x2));
      }
    }

    int parity = 0;
    if (par[p1]) {
      parity ++;
      odd.erase(p1);
    } else {
      even.erase(p1);
    }

    if (par[p2]) {
      parity ++;
      odd.erase(p2);
    } else {
      even.erase(p2);
    }

    p[p2] = p1;

    for (int x1 : st[p2]) {
      st[p1].push_back(x1);
    }
    st[p2].clear();

    if (parity % 2) {
      par[p1] = true;
      odd.insert(p1);
    } else {
      par[p1] = false;
      even.insert(p1);
    }
  }
}

int main() {
  scanf("%d%d", &N, &M);

  for (int i = 1; i <= N; i ++) {
    p[i] = i;
    par[i] = true;
    odd.insert(i);
    st[ i ].push_back( i );
  }

  for (int i = 0; i < M; i ++) {
    int x, y;
    scanf("%d%d", &x, &y);
    addedge(x, y);
  }

  //int te = N * (N - 1) / 2 - M;
  dp[3][0][0] = false;
  dp[2][1][0] = false;
  dp[1][2][0] = false;
  dp[0][3][0] = false;

  dp[3][0][1] = true;
  dp[2][1][1] = true;
  dp[1][2][1] = true;
  dp[0][3][1] = true;

  if (odd.size() + even.size() == 2) {
    // special case: win in one move
    puts("1");
    fflush(stdout);
    vector<int> v;
    for (int x : odd) v.push_back(x);
    for (int x : even) v.push_back(x);
    printf("%d %d\n", v[0], v[1]);
    fflush(stdout);
    exit(0);
  }

  for (int ij = 4; ij <= N; ij ++) {
    for (int i = 0; i <= ij; i ++) {
      int j = ij - i;
      for (int k = 0; k < 2; k ++) {
        bool win = false;
        if (k) win = win or !dp[i][j][0];
        if (i >= 2)
          win = win or !dp[i - 2][j + 1][k];
        if (j >= 2 || (i && j))
          win = win or !dp[i][j - 1][1 - k];
        dp[i][j][k] = win;
      }
    }
  }
  if( odd.size() + even.size() <= 1u ){
    puts( "1" );
    fflush( stdout );
    exit(0);
  }

  int turn;
  if (dp[odd.size()][even.size()][(int)e.size() & 1]) {
    turn = 0;
    puts("1");
    fflush(stdout);
  } else {
    turn = 1;
    puts("2");
    fflush(stdout);
  }


  while (true) {
    if (turn == 0) { // my turn
      int i = odd.size();
      int j = even.size();

      int fei = e.size();
      int k = e.size() & 1;

      if (odd.size() + even.size() == 2) {
        // special case: win in one move
        vector<int> v;
        for (int x : odd) v.push_back(x);
        for (int x : even) v.push_back(x);
        printf("%d %d\n", v[0], v[1]);
        fflush(stdout);
        exit(0);
      }

      //if (fei && fei % 2 == 0 && !dp[i][j][1]) {
        //ii ed = *e.begin();
        //addedge(ed.first, ed.second);
        //printf("%d %d\n", ed.first, ed.second);
        //fflush(stdout);
      //} else {
        //assert(dp[i][j][k]);

      //if( not e.empty() and k == 0 and !dp[i][j][1] ){
        //ii ed = *e.begin();
        //addedge(ed.first, ed.second);
        //printf("%d %d\n", ed.first, ed.second);
        //fflush(stdout);
      //}else
      if (k && !dp[i][j][0]) {
        ii ed = *e.begin();
        addedge(ed.first, ed.second);
        printf("%d %d\n", ed.first, ed.second);
        fflush(stdout);
      } else if (i >= 2 && !dp[i - 2][j + 1][k]) {
        int x = *odd.begin();
        int y = *odd.rbegin();
        addedge(x, y);
        printf("%d %d\n", x, y);
        fflush(stdout);
      } else if (j >= 2 && !dp[i][j - 1][1 - k]) {
        int x = *even.begin();
        int y = *even.rbegin();
        addedge(x, y);
        printf("%d %d\n", x, y);
        fflush(stdout);
      } else if (i >= 1 && j >= 1 && !dp[i][j - 1][1 - k]) {
        int x = *even.begin();
        int y = *odd.begin();
        addedge(x, y);
        printf("%d %d\n", x, y);
        fflush(stdout);
      } else { 
        printf("%d %d\n", 0, 0);
        fflush(stdout);
      }
      //}
    } else { // input
      int x, y;
      scanf("%d%d", &x, &y);
      if (x == 0 && y == 0) exit(0);
      addedge(x, y);
    }

    turn = 1 - turn;
  }
}
