#include<bits/stdc++.h>
using namespace std;

const int N = 404040;
struct SA{
#define REP(i, n) for(int i=0; i<(int)n; i++)
#define REP1(i,a,b) for(int i=(a); i<=int(b); i++)
  bool _t[N*2];
  int _s[N*2], _sa[N*2], _c[N*2], x[N], _p[N], _q[N*2], hei[N], r[N];
  void build(int *s, int n, int m){
    memcpy(_s, s, sizeof(int) * n);
    sais(_s, _sa, _p, _q, _t, _c, n, m);
    mkhei(n);
  }
  void mkhei(int n){
    REP(i, n) r[_sa[i]]=i;
    hei[0]=0;
    REP(i,n) if(r[i]){
      int ans=i>0?max(hei[r[i-1]]-1, 0) : 0;
      while(_s[i+ans] == _s[_sa[r[i]-1]+ans]) ans++;
      hei[r[i]]=ans;
    }
  }
  void sais(int *s, int *sa, int *p, int *q, bool*t, int *c, int n, int z){
    bool uniq=t[n-1]=true, neq;
    int nn=0, nmxz=-1, *nsa=sa+n, *ns=s+n, lst=-1;
#define MS0(x,n) memset((x),0,n*sizeof(*(x)))
#define MAGIC(XD) MS0(sa, n); \
    memcpy(x, c, sizeof(int) * z);\
    XD; \
    memcpy(x+1, c, sizeof(int) * (z-1)); \
    REP(i,n) if(sa[i] and !t[sa[i]-1]) sa[x[s[sa[i]-1]]++]=sa[i]-1; \
    memcpy(x, c, sizeof(int)*z);\
    for(int i=n-1; i>=0; i--) if(sa[i] and t[sa[i]-1]) sa[--x[s[sa[i]-1]]]=sa[i]-1;
    MS0(c, z);
    REP(i, n) uniq &= ++ c[s[i]] < 2;
    REP(i, z-1) c[i+1] += c[i];
    if(uniq){ REP(i, n) sa[--c[s[i]]] =i; return; }
    for(int i=n-2; i>=0; i--) t[i]=(s[i] == s[i+1] ? t[i+1] : s[i]<s[i+1]);
    MAGIC(REP1(i,1,n-1) if(t[i] and !t[i-1]) sa[--x[s[i]]]=p[q[i]=nn++]=i);
    REP(i, n) if(sa[i] and t[sa[i]] and !t[sa[i]-1]){
      neq=lst<0||memcmp(s+sa[i], s+lst, (p[q[sa[i]]+1]-sa[i])*sizeof(int));
      ns[q[lst=sa[i]]]=nmxz+=neq;
    }
    sais(ns, nsa, p+nn, q+n, t+n, c+z, nn, nmxz+1);
    MAGIC(for(int i=nn-1; i>=0; i--) sa[--x[s[p[nsa[i]]]]] = p[nsa[i]]);
  }
} sa;
int H[N], SA[N];

void Suffix(int *ip, int len){
  ip[len++]=0;
  sa.build(ip, len, 128);
  for(int i=0; i<len; i++){
    H[i]=sa.hei[i+1];
    SA[i]=sa._sa[i+1];
  }
}


typedef pair<int, int> ii;
typedef pair<int, int> pii;
typedef long long LL;
int n, m;

vector<ii> in;
vector<string> qr;
char s[100005];

void init() {
    scanf("%d%d", &n, &m);

    in.clear();

    for (int i = 0; i < n; i ++) {
      int x, y;
      scanf("%d%d", &x, &y);
      in.push_back(ii(x, y));
    }

    scanf("%s", s);
    qr.clear();
    for (int i = 0; i < m; i ++) {
      string str;
      cin >> str;
      qr.push_back(str);
    }
}

vector<string> og;

int v[N], vlen;

inline ii getlr(string& P) {
  int cl = 0, cr = vlen - 1;
  for (int i = 0; i < (int)P.size(); ++i) {
    int cc = P[i] - 'A' + 2;
    if (cl == -1 || cr == -1) return ii(-1, -1);
    int tcl = -1, tcr = -1;
    int L = cl, R = cr;
    while (L <= R) {
      int mid = (L + R) >> 1;
      if (SA[mid] + i < vlen && v[SA[mid] + i] >= cc) {
        tcl = mid;
        R = mid - 1;
      } else L = mid + 1;
    }
    L = cl, R = cr;
    while (L <= R) {
      int mid = (L + R) >> 1;
      if (SA[mid] + i >= vlen || v[SA[mid] + i] <= cc) {
        tcr = mid;
        L = mid + 1;
      } else R = mid - 1;
    }

    cl = tcl;
    cr = tcr;
  }
    if (cl == -1 || cr == -1) return ii(-1, -1);
  return ii(cl, cr);
}

vector<ii> qlr;

void gogo(){
  vlen=0;
  for(auto ss: og){
    int slen=ss.length();
    for(int i=0; i<slen; i++)
      v[vlen ++]=(ss[i] == '@' ? 1 : ss[i] - 'A' + 2);
  }
  Suffix(v, vlen);

  qlr.clear();
  for (auto& ss:qr) {
    pii tp = getlr(ss);
    if (tp.first != -1) qlr.push_back(tp);
    //cerr<<tp.first<<" "<<tp.second<<endl;
  }

  //
}

void ibwt() {
  int len = strlen(s);
  vector<int> vv[27];

  int cnt = 0;
  for (int i = 0; i < len; i ++) {
    if (s[i] == '@') cnt ++, vv[0].push_back(i);
    else vv[s[i] - 'A' + 1].push_back(i);
  }
  vector<int> v1, v2;
  for (int i = 0; i <= 26; i ++) {
    for (int j: vv[i]) {
      v1.push_back(i);
      v2.push_back(j);
    }
  }
  for (int i = 0; i < cnt; i ++) {
    int ps = i;
    string ts;

    do {
      ps = v2[ps];
      if (v1[ps] == 0) ts.push_back('@');
      else ts.push_back('A' + v1[ps] - 1);
    } while (ps != i);

    og.push_back(ts);
    //cout << ts << endl;
  }
}
void solve() {
  ibwt();
  //puts("donw");
  gogo();
  //puts("donw");

  vector<int> vl, vr;
  LL ans = 0;
  for (ii xx: in) {
    vr.push_back(xx.second);
    vl.push_back(xx.first);
  }
  sort(vl.begin(), vl.end());
  sort(vr.begin(), vr.end());

  for (ii pr : qlr) {
    int tans = n;
    tans -= (lower_bound(vr.begin(), vr.end(), pr.first) - vr.begin());
    tans -= (vl.end() - upper_bound(vl.begin(), vl.end(), pr.second));
    ans += tans;
  }
  printf("%lld\n", ans);
}

int main() {
  int t; scanf("%d", &t); while (t --) {
    init();
    solve();
  }
}
