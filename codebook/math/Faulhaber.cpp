/* faulhaber’s formula -
 * cal power sum formula of all p=1~k in O(k^2) */
#define MAXK 2500
const int mod = 1000000007;
int b[MAXK];
// bernoulli number
int inv[MAXK+1];
// inverse
int cm[MAXK+1][MAXK+1]; // combinactories
int co[MAXK][MAXK+2];
// coeeficient of x^j when p=i
inline int add(int a,int b) { return a+b<mod?a+b:a+b-mod; }
inline int sub(int a,int b) { return a<b?a-b+mod:a-b; }
inline int getinv(int x) {
  int a=x,b=mod,a0=1,a1=0,b0=0,b1=1;
  while(b) {
    int q,t;
    q=a/b; t=b; b=a-b*q; a=t;
    t=b0; b0=a0-b0*q; a0=t;
    t=b1; b1=a1-b1*q; a1=t;
  }
  return a0<0?a0+mod:a0;
}
inline void pre() {
  /* combinational */
  for(int i=0;i<=MAXK;i++) {
    cm[i][0]=cm[i][i]=1;
    for(int j=1;j<i;j++) cm[i][j]=add(cm[i-1][j-1],cm[i-1][j]);
  }
  /* inverse */
  for(int i=1;i<=MAXK;i++) inv[i]=getinv(i);
  /* bernoulli */
  b[0]=1; b[1]=getinv(2); // with b[1] = 1/2
  for(int i=2;i<MAXK;i++) {
    if(i&1) { b[i]=0; continue; }
    b[i]=1;
    for(int j=0;j<i;j++)
      b[i]=sub(b[i],(long long)cm[i][j]*b[j]%mod*inv[i-j+1]%mod);
  }
  /* faulhaber */
  // sigma_x=1~n {x^p} = 1/(p+1) * sigma_j=0~p { C(p+1,j) * Bj * n^(p-j+1)}
  for(int i=1;i<MAXK;i++) {
    co[i][0]=0;
    for(int j=0;j<=i;j++)
      co[i][i-j+1]=(long long)inv[i+1]%mod*cm[i+1][j]%mod*b[j]%mod;
  }
}
inline int power(int x,int p) {
  int s=1,m=x;
  while(p) {
    if(p&1) s=(long long)s*m%mod;
    p>>=1; m=(long long)m*m%mod;
  }
  return s;
}
/* sample usage: return f(n,p) = sigma_x=1~n (x^p) */
inline int solve(int n,int p) {
  int sol=0,m=n;
  for(int i=1;i<=p+1;i++) {
    sol=add(sol,(long long)co[p][i]*m%mod);
    m=(long long)m*n%mod;
  }
  return sol;
}
