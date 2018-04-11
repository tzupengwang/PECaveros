const double eps = 1e-12;
const double inf = 1e+12;
double a[ 10 ], x[ 10 ];
int n;
int sign( double x ){return (x < -eps)?(-1):(x>eps);}
double f(double a[], int n, double x){
	double tmp=1,sum=0;
	for(int i=0;i<=n;i++)
  { sum=sum+a[i]*tmp; tmp=tmp*x; }
	return sum;
}
double binary(double l,double r,double a[],int n){
	int sl=sign(f(a,n,l)),sr=sign(f(a,n,r));
	if(sl==0) return l; if(sr==0) return r;
	if(sl*sr>0) return inf;
	while(r-l>eps){
		double mid=(l+r)/2;
		int ss=sign(f(a,n,mid));
		if(ss==0) return mid;
		if(ss*sl>0) l=mid; else r=mid;
	}
	return l;
}
void solve(int n,double a[],double x[],int &nx){
	if(n==1){ x[1]=-a[0]/a[1]; nx=1; return; }
	double da[10], dx[10]; int ndx;
	for(int i=n;i>=1;i--) da[i-1]=a[i]*i;
	solve(n-1,da,dx,ndx);
	nx=0;
	if(ndx==0){
		double tmp=binary(-inf,inf,a,n);
		if (tmp<inf) x[++nx]=tmp;
		return;
	}
	double tmp;
	tmp=binary(-inf,dx[1],a,n);
	if(tmp<inf) x[++nx]=tmp;
	for(int i=1;i<=ndx-1;i++){
		tmp=binary(dx[i],dx[i+1],a,n);
		if(tmp<inf) x[++nx]=tmp;
	}
	tmp=binary(dx[ndx],inf,a,n);
	if(tmp<inf) x[++nx]=tmp;
}
int main() {
	scanf("%d",&n);
	for(int i=n;i>=0;i--) scanf("%lf",&a[i]);
	int nx;
	solve(n,a,x,nx);
	for(int i=1;i<=nx;i++) printf("%.6f\n",x[i]);
}
