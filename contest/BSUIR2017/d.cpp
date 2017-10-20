#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
typedef pair<int, int> PII;

const int N = 1e5+10;
const int MOD = 1e9+7;

inline int add(int a, int b) {
  a += b;
  if (a >= MOD) a -= MOD;
  return a;
}

inline int sub(int a, int b) {
  a -= b;
  if (a < 0) a += MOD;
  return a;
}

inline int mul(LL a, LL b) {
  a *= b;
  if (a >= MOD) a %= MOD;
  return a;
}

struct DISC {
  vector<int> vec;
  void init(int *a, int n) {
    vec = vector<int>(a+1, a+1+n);
    sort(vec.begin(), vec.end());
    vec.resize(unique(vec.begin(), vec.end()) - vec.begin());
  }
  int qry(int x) {
    return 1 + lower_bound(vec.begin(), vec.end(), x) - vec.begin();
  }
  int size() {
    return vec.size();
  }
};

struct BIT {
  int sz, dat[N];
  vector<PII> log;
  void init(int n) {
    sz = n;
    fill(dat, dat+1+n, 0);
    log.clear();
  }
  void upd(int id, int x) {
    log.push_back({id, x});
    for (int i = id; i <= sz; i+=i&-i)
      dat[i] = add(dat[i], x);
  }
  int qry(int id=-1) {
    if (id == -1) id = sz;
    int res = 0;
    for (int i = id; i > 0; i -= i&-i)
      res = add(res, dat[i]);
    return res;
  }
  void reset() {
    for (PII p: log) {
      upd(p.first, sub(0, p.second));
    }
    log.clear();
  }
};

DISC dS, dR;

vector<int> pos[N];
int n, S[N], R[N];

void input() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d%d", S+i, R+i);
  }
  dS.init(S, n);
  dR.init(R, n);
  for (int i = 1; i <= n; ++i) {
    S[i] = dS.qry(S[i]);
    R[i] = dR.qry(R[i]);
  }
  for (int i = 1; i <= n; ++i)
    pos[S[i]].push_back(i);
}

BIT bit1, bit2;

/*
 * 0: \i
 * 1: /i
 * 2: i\
 * 3: i/
 */
int C[4][N], *A, *B;

void make_C() {
  bit1.init(dR.size());
  bit2.init(dR.size());
  for (int s = 1; s <= dS.size(); ++s) {
    for (int i: pos[s]) {
      C[0][i] = add(1, bit1.qry((1 + dR.size() - R[i]) - 1));
      C[1][i] = add(1, bit2.qry(R[i] - 1));
    }
    for (int i: pos[s]) {
      bit1.upd((1 + dR.size() - R[i]), C[1][i]);
      bit2.upd(R[i], C[0][i]);
    }
  }

  bit1.init(dR.size());
  bit2.init(dR.size());
  int mnR = N, mxR = -1;
  for (int s = dS.size(); s > 0; --s) {
    for (int i: pos[s]) {
      if (mnR >= R[i]) C[2][i] = 1;
      else C[2][i] = bit1.qry(R[i] - 1);
      if (mxR <= R[i]) C[3][i] = 1;
      else C[3][i] = bit2.qry((1 + dR.size() - R[i]) - 1);
    }
    for (int i: pos[s]) {
      mnR = min(mnR, R[i]);
      mxR = max(mxR, R[i]);
      bit1.upd(R[i], C[3][i]);
      bit2.upd((1 + dR.size() - R[i]), C[2][i]);
    }
  }
}

int ans[N];
int ord1[N], ord2[N];

bool cmpR(int a, int b) {
  return R[a] < R[b];
}

void calc(int l, int mid, int r) {
  int n1 = 0, n2 = 0;
  for (int s = l; s <= mid; ++s)
    for (int i: pos[s])
      ord1[++n1] = i;
  for (int s = mid+1; s <= r; ++s)
    for (int i: pos[s])
      ord2[++n2] = i;

  sort(ord1+1, ord1+1+n1, cmpR);
  sort(ord2+1, ord2+1+n2, cmpR);

  BIT &bitA = bit1;
  BIT &bitB = bit2;

  int l_top_i = n1;
  int l_dn_i = 1;

  int sumB = 0;
  int topR = R[ord2[n2]];

  while (l_dn_i <= n1 and
         R[ord1[l_dn_i]] < topR) {
    bitA.upd(S[ord1[l_dn_i]], A[ord1[l_dn_i]]);
    l_dn_i++;
  }
  l_dn_i--;

  int cur_ans = 0;

  while (l_top_i > 0 and
         R[ord1[l_top_i]] > topR) {
    int id = ord1[l_top_i];
    bitB.upd(S[id], B[id]);
    cur_ans = add(cur_ans, mul(B[id], bitA.qry(S[id] - 1)));
    l_top_i--;
  }

  auto dn_del = [&](int id) {
    bitA.upd(S[id], sub(0, A[id]));
    int rBs = sub(bitB.qry(), bitB.qry(S[id]));
    cur_ans = sub(cur_ans, mul(A[id], rBs));
  };

  auto up_add = [&](int id) {
    bitB.upd(S[id], B[id]);
    cur_ans = add(cur_ans, mul(B[id], bitA.qry(S[id] - 1)));
  };

  int tid = n2;

  for (int _ = n2; _ > 0; --_) {
    int i = ord2[_];
    while (tid > _) {
      int id = ord2[tid];
      if (R[id] > R[i]) {
        sumB = add(sumB, B[id]);
      } else break;
      tid--;
    }
    while (l_dn_i > 0) {
      int id = ord1[l_dn_i];
      if (R[id] >= R[i]) {
        dn_del(id);
        l_dn_i--;
      } else break;
    }
    while (l_top_i > 0) {
      int id = ord1[l_top_i];
      if (R[id] > R[i]){
        up_add(id);
        l_top_i--;
      } else break;
    }
    ans[i] = add(ans[i], cur_ans);
    ans[i] = add(ans[i], mul(sumB, bitA.qry()));
  }

}

void dq(int l, int r) {
  if (l >= r) return;
  int mid = (l+r) / 2;
  dq(l, mid);
  dq(mid+1, r);
  calc(l, mid, r);
  bit1.reset();
  bit2.reset();
}

void hao() {
  make_C();
  A = C[0];
  B = C[2];
  bit1.init(dR.size());
  bit2.init(dR.size());
  dq(1, dS.size());
}

void solve() {
  hao();
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j < 4; ++j) printf("%d ", C[j][i]);
    puts("");
  }
  for (int i = 1; i <= n; ++i) {
    R[i] = 1+dR.vec.size() - R[i];
  }
  hao();
  int ac = 0;
  for (int i = 1; i <= n; ++i) ac = add(ac, ans[i]);
  printf("%d\n", ac);
}

int main() {
  input();
  solve();
}
