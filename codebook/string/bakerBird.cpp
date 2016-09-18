class Node { public:
  Node *fail;
  map<char,Node*> _next;
  int out;
  Node() { fail=NULL; out=-1; }
  ~Node() {
    for(map<char,Node*>::iterator it=_next.begin();it!=_next.end();it++)
      delete it->second;
  }
  Node* build(char ch) {
    if(_next.find(ch)==_next.end()) _next[ch]=new Node;
    return _next[ch];
  }
  Node* next(char ch) {
    if(_next.find(ch)==_next.end()) return NULL;
    return _next[ch];
  }
};
int srn,scn,prn,pcn,mrn,mcn;
char s[MAXN][MAXN],p[MAXN][MAXN];
int rm[MAXN][MAXN]; // rank matrix
int maxrank;
int seq[MAXN]; // index of patterns for radix sort
int rank[MAXN]; // rank of pattern on row r
int cnt[SIGMA+1],tmp[MAXN];
int pre[MAXN]; // pre-matrix for kmp
int ql,qr;
Node* que[MAXN*MAXN];
inline void radix_pass(int j,int *from,int *to) {
  int i;
  for(i=0;i<SIGMA;i++) cnt[i]=0;
  for(i=0;i<prn;i++) cnt[p[from[i]][j]+1]++;
  for(i=0;i<SIGMA;i++) cnt[i+1]+=cnt[i];
  for(i=0;i<prn;i++) to[cnt[p[from[i]][j]]++]=from[i];
}
inline void radix_sort_patterns() {
  int i,j;
  for(i=0;i<prn;i++) ((pcn&1)?tmp[i]:seq[i])=i;
  for(j=pcn-1;j>=0;j--) {
    if(j&1) radix_pass(j,seq,tmp);
    else radix_pass(j,tmp,seq);
  }
  maxrank=0;
  for(i=0;i<prn;i++) {
    if(i&&strcmp(p[seq[i-1]],p[seq[i]])) ++maxrank;
    rank[seq[i]]=maxrank;
  }
}
inline void construct(Node *v,char *p,int ind) {
  while(*p) { v=v->build(*p); p++; }
  v->out=ind;
}
inline void construct_all(Node *ac) {
  for(int i=0;i<prn;i++) construct(ac,p[i],rank[i]);
}
inline void find_fail(Node *ac) {
  Node *v,*u,*f;
  map<char,Node*>::iterator it;
  char ch;
  ql=qr=0; ac->fail=ac;
  for(it=ac->_next.begin();it!=ac->_next.end();it++) {
    u=it->second;
    u->fail=ac;
    que[qr++]=u;
  }
  while(ql<qr) {
    v=que[ql++];
    for(it=v->_next.begin();it!=v->_next.end();it++) {
      ch=it->first; u=it->second;
      f=v->fail;
      while(f!=ac&&f->next(ch)==NULL) f=f->fail;
      if(f->next(ch)) u->fail=f->next(ch);
      else u->fail=ac;
      que[qr++]=u;
    }
  }
}
inline void ac_match(Node *ac,char *s,int *arr) {
  int i;
  Node *v=ac;
  for(i=0;i<scn;i++) {
    while(v!=ac&&v->next(s[i])==NULL) v=v->fail;
    if(v->next(s[i])) v=v->next(s[i]);
    if(i>=pcn-1) arr[i-pcn+1]=v->out;
  }
}
inline void find_rank_matrix() {
  Node ac;
  radix_sort_patterns();
  construct_all(&ac);
  find_fail(&ac);
  mrn=srn; mcn=scn-pcn+1;
  for(int i=0;i<srn;i++) ac_match(&ac,s[i],rm[i]);
}
inline void find_pre(int *p,int plen) {
  int i,x;
  x=pre[0]=-1;
  for(i=1;i<plen;i++) {
    while(x>=0&&p[x+1]!=p[i]) x=pre[x];
    if(p[x+1]==p[i]) x++;
    pre[i]=x;
  }
}
inline int kmp_match(int col,int *p,int plen) {
  int i,x=-1,occ=0;
  for(i=0;i<mrn;i++) {
    while(x>=0&&p[x+1]!=rm[i][col]) x=pre[x];
    if(p[x+1]==rm[i][col]) x++;
    if(x==plen-1) { occ++; x=pre[x]; }
  }
  return occ;
}
inline int baker_bird() {
  int i,occ=0;
  find_rank_matrix();
  find_pre(rank,prn);
  for(i=0;i<mcn;i++) occ+=kmp_match(i,rank,prn);
  return occ;
}
