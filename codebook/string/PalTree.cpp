/*
 * sfail: compressed fail links with same diff
 * O(lgn): length of sfail link path
 */
const int MAXN = 1e6+10;
struct PalT{
  int tot,lst;
  int nxt[MAXN][26], len[MAXN];
  int fail[MAXN], diff[MAXN], sfail[MAXN];
  char* s;
  int newNode(int l, int _fail) {
    int res = ++tot;
    fill(nxt[res], nxt[res]+26, 0);
    len[res] = l, fail[res] = _fail;
    diff[res] = l - len[_fail];
    if (diff[res] == diff[_fail])
      sfail[res] = sfail[_fail];
    else
      sfail[res] = _fail;
    return res;
  }
  void push(int p) {
    int np = lst;
    int c = s[p]-'a';
    while (p-len[np]-1 < 0 || s[p] != s[p-len[np]-1])
      np = fail[np];
    if ((lst=nxt[np][c])) return;
    int nq_f = 0;
    if (len[np]+2 == 1) nq_f = 2;
    else {
      int tf = fail[np];
      while (p-len[tf]-1 < 0 || s[p] != s[p-len[tf]-1])
        tf = fail[tf];
      nq_f = nxt[tf][c];
    }
    int nq = newNode(len[np]+2, nq_f);
    nxt[np][c] = nq;
    lst=nq;
  }
  void init(char* _s){
    s = _s;
    tot = 0;
    newNode(-1, 1);
    newNode(0, 1);
    diff[2] = 0;
    lst = 2;
  }
} palt;
