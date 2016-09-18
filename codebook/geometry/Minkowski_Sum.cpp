/* convex hull Minkowski Sum*/
#define INF 100000000000000LL
int pos( const Pt& tp ){
  if( tp.Y == 0 ) return tp.X > 0 ? 0 : 1;
  return tp.Y > 0 ? 0 : 1;
}
#define N 300030
Pt pt[ N ], qt[ N ], rt[ N ];
LL Lx,Rx;
int dn,un;
inline bool cmp( Pt a, Pt b ){
	int pa=pos( a ),pb=pos( b );
	if(pa==pb) return (a^b)>0;
	return pa<pb;
}
int minkowskiSum(int n,int m){
	int i,j,r,p,q,fi,fj;
	for(i=1,p=0;i<n;i++){
		if( pt[i].Y<pt[p].Y ||
        (pt[i].Y==pt[p].Y && pt[i].X<pt[p].X) ) p=i; }
	for(i=1,q=0;i<m;i++){
		if( qt[i].Y<qt[q].Y ||
        (qt[i].Y==qt[q].Y && qt[i].X<qt[q].X) ) q=i; }
	rt[0]=pt[p]+qt[q];
	r=1; i=p; j=q; fi=fj=0;
	while(1){
		if((fj&&j==q) ||
       ( (!fi||i!=p) &&
         cmp(pt[(p+1)%n]-pt[p],qt[(q+1)%m]-qt[q]) ) ){
			rt[r]=rt[r-1]+pt[(p+1)%n]-pt[p];
			p=(p+1)%n;
			fi=1;
		}else{
			rt[r]=rt[r-1]+qt[(q+1)%m]-qt[q];
			q=(q+1)%m;
			fj=1;
		}
		if(r<=1 || ((rt[r]-rt[r-1])^(rt[r-1]-rt[r-2]))!=0) r++;
		else rt[r-1]=rt[r];
		if(i==p && j==q) break;
	}
	return r-1;
}
void initInConvex(int n){
	int i,p,q;
	LL Ly,Ry;
	Lx=INF; Rx=-INF;
	for(i=0;i<n;i++){
		if(pt[i].X<Lx) Lx=pt[i].X;
		if(pt[i].X>Rx) Rx=pt[i].X;
	}
	Ly=Ry=INF;
	for(i=0;i<n;i++){
		if(pt[i].X==Lx && pt[i].Y<Ly){ Ly=pt[i].Y; p=i; }
		if(pt[i].X==Rx && pt[i].Y<Ry){ Ry=pt[i].Y; q=i; }
	}
	for(dn=0,i=p;i!=q;i=(i+1)%n){ qt[dn++]=pt[i]; }
	qt[dn]=pt[q]; Ly=Ry=-INF;
	for(i=0;i<n;i++){
		if(pt[i].X==Lx && pt[i].Y>Ly){ Ly=pt[i].Y; p=i; }
		if(pt[i].X==Rx && pt[i].Y>Ry){ Ry=pt[i].Y; q=i; }
	}
	for(un=0,i=p;i!=q;i=(i+n-1)%n){ rt[un++]=pt[i]; }
	rt[un]=pt[q];
}
inline int inConvex(Pt p){
	int L,R,M;
	if(p.X<Lx || p.X>Rx) return 0;
	L=0;R=dn;
	while(L<R-1){ M=(L+R)/2;
		if(p.X<qt[M].X) R=M; else L=M; }
		if(tri(qt[L],qt[R],p)<0) return 0;
		L=0;R=un;
		while(L<R-1){ M=(L+R)/2;
			if(p.X<rt[M].X) R=M; else L=M; }
			if(tri(rt[L],rt[R],p)>0) return 0;
			return 1;
}
int main(){
	int n,m,i;
	Pt p;
	scanf("%d",&n);
	for(i=0;i<n;i++) scanf("%lld%lld",&pt[i].X,&pt[i].Y);
	scanf("%d",&m);
	for(i=0;i<m;i++) scanf("%lld%lld",&qt[i].X,&qt[i].Y);
	n=minkowskiSum(n,m);
	for(i=0;i<n;i++) pt[i]=rt[i];
	scanf("%d",&m);
	for(i=0;i<m;i++) scanf("%lld%lld",&qt[i].X,&qt[i].Y);
	n=minkowskiSum(n,m);
	for(i=0;i<n;i++) pt[i]=rt[i];
	initInConvex(n);
	scanf("%d",&m);
	for(i=0;i<m;i++){
		scanf("%lld %lld",&p.X,&p.Y);
		p.X*=3; p.Y*=3;
		puts(inConvex(p)?"YES":"NO");
	}
}
