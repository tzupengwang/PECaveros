//by tzupengwang™
#include<algorithm>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<vector>
#include<queue>
#include<set>
#include<list>
#include<iostream>
using namespace std;

typedef pair<int,int> ii;

struct Ins {
  int m;
  char k[300005];
  int ac[300005][2];
  void init(int _m) {
    m = _m;
    scanf("%s", k + 1);
    ac[0][0] = ac[0][1] = 0;
    for (int i = 1; i <= m; i ++) {
      ac[i][0] = ac[i - 1][0] + (k[i] == 'A');
      ac[i][1] = ac[i - 1][1] + (k[i] == 'B');
    }
  }
  int numArange(int l, int r) {
    l = min(l, m + 1);
    r = min(r, m);
    return ac[r][0] - ac[l - 1][0];
  }
  int numBrange(int l, int r) {
    l = min(l, m + 1);
    r = min(r, m);
    return ac[r][1] - ac[l - 1][1];
  }
} ins;

int n, m;
int s[300005];
int ans[300005];
int t[300005];
const int BIG = 2000000000;
list<int> pos, neg;

void init() {
  pos.clear(), neg.clear();

  for (int i = 1; i <= n; i ++) {
    scanf("%d", &s[i]);
  }
  for (int i = 2; i <= n; i ++) {
    t[i] = s[i] - s[i - 1];
    if (t[i] > 0) pos.push_back(i);
    else if (t[i] < 0) neg.push_back(i);
  }
  ins.init(m);
}

typedef list<int>::iterator lit;

int leftTotalGrow;
struct Cand {
  int id;
  list<int> lA;
  list<int> lB;
  int tnow, tnxt;
  int negs, poss;
  Cand() {}
  Cand(int idx, lit l1, lit r1, lit l2, lit r2, int ns, int ps) : id(idx), lA(l1, r1), lB(l2, r2), negs(ns), poss(ps) {
    tnow = 1, tnxt = min(-negs, poss) + 1;
  }
};

void reduce(int l, int r, Cand &cand) {
  list<int> &lA = cand.lA;
  list<int> &lB = cand.lB;
  cand.tnow = r;
  int As = ins.numArange(l, r - 1);
  int Bs = ins.numBrange(l, r - 1);

  int aCan;
  {
    int tAs = As;
    while (lA.size()) {
      if (-t[lA.front()] <= tAs) {
        tAs += t[lA.front()];
        cand.negs -= t[lA.front()];
        t[lA.front()] = 0;
        lA.pop_front();
      } else {
        t[lA.front()] += tAs;
        cand.negs += tAs;
        tAs = 0;
        break;
      }
    }
    aCan = As - tAs;
  }
  {
    int tAs = aCan;
    while (lB.size()) {
      if (t[lB.front()] <= tAs) {
        tAs -= t[lB.front()];
        cand.poss -= t[lB.front()];
        t[lB.front()] = 0;
        lB.pop_front();
      } else {
        t[lB.front()] -= tAs;
        cand.poss -= tAs;
        tAs = 0;
        break;
      }
    }
  }
  int bCan;
  {
    int tBs = Bs;
    while (lB.size()) {
      if (t[lB.back()] <= tBs) {
        tBs -= t[lB.back()];
        cand.poss -= t[lB.back()];
        t[lB.back()] = 0;
        lB.pop_back();
      } else {
        t[lB.back()] -= tBs;
        cand.poss -= tBs;
        tBs = 0;
        break;
      }
    }
    bCan = Bs - tBs;
  }
  {
    int tBs = bCan;
    while (lA.size()) {
      if (-t[lA.back()] <= tBs) {
        tBs += t[lA.back()];
        cand.negs -= t[lA.back()];
        t[lA.back()] = 0;
        lA.pop_back();
      } else {
        t[lA.back()] += tBs;
        cand.negs += tBs;
        tBs = 0;
        break;
      }
    }
    leftTotalGrow += tBs;
  }
}

void process() {
  leftTotalGrow = 0;
  set<ii> heap;
  set<int> active;
  vector<Cand> cand;

  {
    auto ptr1 = neg.begin();
    auto ptr2 = pos.begin();

    while (ptr1 != neg.end()) {
      int ns = 0, ps = 0;
      auto l1 = ptr1;
      while (ptr1 != neg.end() && (ptr2 == pos.end() || *ptr1 < *ptr2)) ns += t[*ptr1], ptr1 ++;
      auto r1 = ptr1;
      auto l2 = ptr2;
      while (ptr2 != pos.end() && (ptr1 == neg.end() || *ptr2 < *ptr1)) ps += t[*ptr2], ptr2 ++;
      auto r2 = ptr2;

      cand.emplace_back(cand.size(), l1, r1, l2, r2, ns, ps);
      heap.insert(ii(cand.back().tnxt, cand.back().id));
      active.insert(cand.size() - 1);
    }
  }

  while (heap.size()) {
    int id = heap.begin()->second;
    heap.erase(heap.begin());
    Cand &now = cand[id];

    auto activePt = active.lower_bound(id);

    reduce(now.tnow, now.tnxt, now);
    if (now.lB.size() == 0) {
      auto nxt = activePt;
      nxt ++;
      if (nxt != active.end()) {
        auto &nxtC = cand[*nxt];

        reduce(nxtC.tnow, now.tnxt, nxtC);
        nxtC.lA.splice(nxtC.lA.begin(), now.lA);
        nxtC.negs += now.negs;
        if (heap.count(ii(nxtC.tnxt, nxtC.id))) {
          heap.erase(heap.lower_bound(ii(nxtC.tnxt, nxtC.id)));
          nxtC.tnxt = min(-nxtC.negs, nxtC.poss) + nxtC.tnow;
          heap.insert(ii(nxtC.tnxt, nxtC.id));
        } else {
          nxtC.tnxt = min(-nxtC.negs, nxtC.poss) + nxtC.tnow;
        }
        active.erase(activePt);
      }
    } else if (now.lA.size() == 0) {
      if (activePt != active.begin()) {
        auto pre = activePt;
        pre --;

        auto &preC = cand[*pre];
        reduce(preC.tnow, now.tnxt, preC);
        preC.lB.splice(preC.lB.end(), now.lB);
        preC.poss += now.poss;

        if (heap.count(ii(preC.tnxt, preC.id))) {
          heap.erase(heap.lower_bound(ii(preC.tnxt, preC.id)));
          preC.tnxt = min(-preC.negs, preC.poss) + preC.tnow;
          heap.insert(ii(preC.tnxt, preC.id));
        } else {
          preC.tnxt = min(-preC.negs, preC.poss) + preC.tnow;
        }
        active.erase(activePt);
      }
    }
  }
  while (active.size()) {
    int id = *active.begin(); active.erase(active.begin());
    if (cand[id].lA.size() == 0 && cand[id].tnow <= m) {
      int Bs = ins.numBrange(cand[id].tnow, m);
      {
        while (cand[id].lB.size()) {
          if (t[cand[id].lB.back()] <= Bs) {
            Bs -= t[cand[id].lB.back()];
            leftTotalGrow += t[cand[id].lB.back()];
            t[cand[id].lB.back()] = 0;
            cand[id].lB.pop_back();
          } else {
            t[cand[id].lB.back()] -= Bs;
            leftTotalGrow += Bs;
            Bs = 0;
            break;
          }
        }
      }
    } else if (cand[id].lB.size() == 0 && cand[id].tnow <= m) {
      int As = ins.numArange(cand[id].tnow, m);
      {
        while (cand[id].lA.size()) {
          if (-t[cand[id].lA.front()] <= As) {
            As += t[cand[id].lA.front()];
            t[cand[id].lA.front()] = 0;
            cand[id].lA.pop_front();
          } else {
            t[cand[id].lA.front()] += As;
            As = 0;
            break;
          }
        }
      }
    }
  }
  ans[1] = s[1] + leftTotalGrow;
  for (int i = 2; i <= n; i ++) ans[i] = ans[i - 1] + t[i];

  for (int i = 1; i <= n; i ++)
    printf("%d%c", ans[i], " \n"[i == n]);
}

int main() {
  while (scanf("%d%d", &n, &m) == 2) {
    init() ;
    process() ;
  }
  return 0 ;
}

