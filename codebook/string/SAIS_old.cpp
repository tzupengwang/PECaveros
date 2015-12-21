// Suffix array by Induced-Sorting, O(n)
const int MAXL=200000+1000; // Max Length
// input: S[0..n-1], n; output: SA[0..n-1]
// S[n-1] MUST be an unique smallest item!!!!
// Max alphabet should be < MAXL.
int S[MAXL*2],SA[MAXL*2];
bool _iss[MAXL*2];
int _p[MAXL*2],_pb[MAXL*2],cnt[MAXL],qe[MAXL];
inline void isort(int n,int *s,int *sa,bool *iss,int *p,int pc){
  int a=0,i;
  for(i=0;i<n;i++)a=max(a,s[i]); a++;
  memset(cnt,0,sizeof(int)*a);
  for(i=0;i<n;i++)cnt[s[i]]++;
  qe[0]=cnt[0]; for(i=1;i<a;i++)qe[i]=qe[i-1]+cnt[i];
  memset(sa,-1,sizeof(int)*n);
  for(i=pc-1;i>=0;i--)sa[--qe[s[p[i]]]]=p[i];
  qe[0]=0; for(i=1;i<a;i++)qe[i]=qe[i-1]+cnt[i-1];
  for(i=0;i<n;i++)if(sa[i]>0&&!iss[sa[i]-1])sa[qe[s[sa[i]-1]]++]=sa[i]-1;
  qe[0]=cnt[0]; for(i=1;i<a;i++)qe[i]=qe[i-1]+cnt[i];
  for(i=n-1;i>=0;i--)if(sa[i]>0&&iss[sa[i]-1])sa[--qe[s[sa[i]-1]]]=sa[i]-1;
}
inline bool eq(int *s,bool *iss,int *pp,int *pb,int pc,int x,int p){
  if(pb[p]==pc-1 || pb[x]==pc-1 || pp[pb[p]+1]-p!=pp[pb[x]+1]-x)return 0;
  for(int j=0;j<=pp[pb[p]+1]-p;j++)if(s[j+p]!=s[j+x]||iss[j+p]!=iss[j+x]) return 0;
  return 1;
}
void suffixArray(int n,int a1=0){
  int i;
  int *s=S+a1,*sa=SA+a1,*pp=_p+a1,*pb=_pb+a1;
  bool *iss=_iss+a1;
  iss[n-1]=1;
  for(i=n-2;i>=0;i--)iss[i]=s[i]<s[i+1]||(s[i]==s[i+1]&&iss[i+1]);
  int pc=0;
  for(i=1;i<n;i++)if(iss[i]&&!iss[i-1]){ pp[pc]=i; pb[i]=pc; pc++; }
  isort(n,s,sa,iss,pp,pc);
  int p=-1,c=-1;
  for(i=0;i<n;i++){
    int x=sa[i];
    if(x&&iss[x]&&!iss[x-1]){
      if(p==-1||!eq(s,iss,pp,pb,pc,x,p))c++;
      s[n+pb[x]]=c;
      p=x;
    }
  }
  if(c==pc-1)for(i=0;i<pc;i++)sa[n+s[n+i]]=i;
  else suffixArray(pc,a1+n);
  for(i=0;i<pc;i++)pb[i]=pp[sa[n+i]];
  isort(n,s,sa,iss,pb,pc);
}
int rk[MAXL],DA[MAXL];
void depthArray(int n){
  int i,j;
  for(i=0;i<n;i++) rk[SA[i]]=i;
  for(i=j=0;i<n;i++){
    if(!rk[i]){ j=0; }
    else{
      if(j) j--;
      for(;S[i+j]==S[SA[rk[i]-1]+j];j++);
    }
    DA[rk[i]]=j;
  }
}
