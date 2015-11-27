/* pollard rho */
// does not work when n is prime
}
/* faulhaber */
// sigma_x=1~n {x^p} = 1/(p+1) * sigma_j=0~p { C(p+1,j) *
Bj * n^(p-j+1)}
for(int i=1;i<MAXK;i++) {
  co[i][0]=0;
  for(int j=0;j<=i;j++)
    co[i][i-j+1]=(long long)inv[i+1]%mod*cm[i+1][j]%mod
      *b[j]%mod;
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
5.3 MillerRabbin
/* miller rabin */
inline long long power(long long x,long long p,long long mod
    ) {
  long long s=1,m=x;
  while(p) {
    if(p&1) s=mult(s,m,mod);
    p>>=1;
    m=mult(m,m,mod);
  }
  return s;
}
inline bool witness(long long a,long long n,long long u,int
    t) {
  long long x=power(a,u,n);
  for(int i=0;i<t;i++) {
    long long nx=mult(x,x,n);
    if(nx==1&&x!=1&&x!=n-1) return 1;
    x=nx;
  }
  return x!=1;
}
inline long long gcd(long long a,long long b) {
  while(b) {
    long long t=b;
    b=a%b;
    a=t;
  }
  return a;
}
inline long long modit(long long x,long long mod) {
  if(x>=mod) x-=mod;
  //if(x<0) x+=mod;
  return x;
}
inline long long mult(long long x,long long y,long long mod)
{
  long long s=0,m=x%mod;
  while(y) {
    if(y&1) s=modit(s+m,mod);
    y>>=1;
    m=modit(m+m,mod);
  }
  return s;
}
inline long long f(long long x,long long mod) {
  return modit(mult(x,x,mod)+1,mod);
}
inline long long randll() {
  return ((long long)rand()<<32)+rand();
}
inline long long pollard_rho(long long n) {
  long long x,x2;
  if(!(n&1)) return 2;
  //x=x2=randll()%n;
  x=x2=2;
  while(1) {
    x=f(x,n); x2=f(f(x2,n),n);
    long long d=gcd(abs(x-x2),n);
    if(d!=1&&d!=n) return d;
  }
}
