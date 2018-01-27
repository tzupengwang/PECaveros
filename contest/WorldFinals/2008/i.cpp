#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Node{
  int cnt,dp,msk;
  Node *go[26], *fail;
  Node (){
    cnt = 0; dp = -1; fail = 0;
    msk = 0;
    memset(go,0,sizeof(go));
  }
};

struct ACautomata{
  Node *root;
  Node pool[65536];
  int nMem;
  Node* new_Node(){
    pool[nMem] = Node();
    return &pool[nMem++];
  }
  void init()
  { nMem = 0; root = new_Node(); }
  void add(const string &str, int id)
  { insert(root,str,0, id); }
  void insert(Node *cur, const string &str, int pos, int id){
    if (pos >= (int)str.size())
    { cur->cnt++; cur->msk |= (1<<id); return; }
    int c = str[pos]-'a';
    if (cur->go[c] == 0)
      cur->go[c] = new_Node();
    insert(cur->go[c],str,pos+1, id);
  }
  void make_fail(){
    queue<Node*> que;
    que.push(root);
    while (!que.empty()){
      Node* fr=que.front();
      que.pop();
      for (int i=0; i<26; i++){
        if (fr->go[i]){
          Node *ptr = fr->fail;
          while (ptr && !ptr->go[i]) ptr = ptr->fail;
          if (!ptr) fr->go[i]->fail = root;
          else fr->go[i]->fail = ptr->go[i];
          que.push(fr->go[i]);
        }
      }
    }
  }
} ac;

inline void go(int nd, int c, int &nxt, int &X) {
  nxt = X = 0;
  Node *np = &ac.pool[nd];
  while (np != ac.root and !np->go[c]) {
    np = np->fail;
  }
  if (np->go[c]) np = np->go[c];
  else np = ac.root;
  nxt = np - ac.pool;
  Node *nq = np;
  while (nq != ac.root and nq) {
    X |= nq->msk;
    nq = nq->fail;
  }
}

const int N = 30;
const int M = 11;
const int V = 200;
const ll INF = 1e16;

int n, m, __cs;
string ip[M];

ll dp[N][(1<<M)][V];
bool vis[N][(1<<M)][V];

inline void upd(ll &a, ll b) {
  a += b;
  if (a > INF) a = INF;
}

vector<string> anss;
string s;

void dfs(int tl, int S, int nd) {
  if (tl == n) {
    anss.push_back(s);
    return;
  }
  for (int c = 0; c < 26; ++c) {
    int nxt, X;
    go(nd, c, nxt, X);
    if (vis[tl+1][S|X][nxt]) {
      s.push_back('a' + c);
      dfs(tl+1, (S|X), nxt);
      s.pop_back();
    }
  }
}

void main2() {
  ac.init();
  for (int i = 0; i < m; ++i) {
    cin >> ip[i];
    //cout << ip[i] << endl;
    ac.add(ip[i], i);
  }
  ac.make_fail();
  //for (int nd = 0; nd < ac.nMem; nd++) {
    //printf("nd fail %d\n", ac.pool[nd].fail - ac.pool);
    //for (int c = 0; c < 26; ++c) if (ac.pool[nd].go[c]) {
      //printf("  %d %d\n", c, ac.pool[nd].go[c] - ac.pool);
    //}
  //}
  //printf("ac nMem %d\n", ac.nMem);
  //return;
  memset(dp, 0, sizeof(dp));
  dp[0][0][0] = 1;
  for (int tl = 0; tl < n; ++tl) {
    for (int nd = 0; nd < ac.nMem; nd++)
      for (int c = 0; c < 26; ++c) {
        int nxt, X;
        go(nd, c, nxt, X);
        for (int S = 0; S < (1<<m); S++) {
          upd(dp[tl+1][S | X][nxt], dp[tl][S][nd]);
        }
      }
  }
  ll ans = 0;
  for (int nd = 0; nd < ac.nMem; nd++) ans += dp[n][(1<<m)-1][nd];
  printf("%lld suspects\n", ans);
  if (ans > 42) return;
  memset(vis, 0, sizeof(vis));
  for (int nd = 0; nd < ac.nMem; ++nd) if (dp[n][(1<<m)-1][nd] > 0)
    vis[n][(1<<m)-1][nd] = 1;
  for (int tl = n-1; tl >= 0; --tl)
    for (int nd = 0; nd < ac.nMem; ++nd)
      for (int c = 0; c < 26; ++c) {
        int nxt, X;
        go(nd, c, nxt, X);
        for (int S = 0; S < (1<<m); S++) if (vis[tl+1][S|X][nxt]) {
          vis[tl][S][nd] = dp[tl][S][nd] > 0;
        }
      }
  anss.clear();
  dfs(0, 0, 0);
  sort(anss.begin(), anss.end());
  for (auto ss: anss)
    cout << ss << endl;
}

int main(){
  while (scanf("%d%d", &n, &m) != EOF) {
    if (!n) break;
    printf("Case %d: ", ++__cs);
    main2();
  }
}
