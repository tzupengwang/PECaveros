#include <bits/stdc++.h>
using namespace std;
#define N 100010
#define M 1202010
#define MXQ M
//#define int long long
typedef long long LL;
inline LL getint(){
  LL _x=0,_tmp=1; char _tc=getchar();    
  while( (_tc<'0'||_tc>'9')&&_tc!='-' ) _tc=getchar();
  if( _tc == '-' ) _tc=getchar() , _tmp = -1;
  while(_tc>='0'&&_tc<='9') _x*=10,_x+=(_tc-'0'),_tc=getchar();
  return _x*_tmp;
}

/* Dynamic MST O( Q lg^2 Q )
 (qx[i], qy[i])->chg weight of edge No.qx[i] to qy[i]
 delete an edge: (i, \infty)
 add an edge: change from \infty to specific value
 */
const int SZ=M+3*MXQ;
int a[N],*tz;
int find(int xx){
	int root=xx; while(a[root]) root=a[root];
	int next; while((next=a[xx])){a[xx]=root; xx=next; }
	return root;
}
bool cmp(int aa,int bb){ return tz[aa]<tz[bb]; }
int kx[N],ky[N],kt, vd[N],id[M], app[M];
bool extra[M];

bitset<M> useful;
vector<LL> tmp_ans;
int itt;

void solve(int *qx,int *qy,int Q,int n,int *x,int *y,int *z,int m1,long long ans){
	if(Q==1){
		for(int i=1;i<=n;i++) a[i]=0;
		z[ qx[0] ]=qy[0]; tz = z;
		for(int i=0;i<m1;i++) id[i]=i;
		sort(id,id+m1,cmp); int ri,rj;
		for(int i=0;i<m1;i++){
			ri=find(x[id[i]]); rj=find(y[id[i]]);
			if(ri!=rj){ ans+=z[id[i]]; a[ri]=rj; }
		}
    if( useful[ itt ] )
      tmp_ans.push_back( ans );
    itt ++;
		return;
	}
	int ri,rj;
	//contract
	kt=0;
	for(int i=1;i<=n;i++) a[i]=0;
	for(int i=0;i<Q;i++){
		ri=find(x[qx[i]]); rj=find(y[qx[i]]); if(ri!=rj) a[ri]=rj;
	}
	int tm=0;
	for(int i=0;i<m1;i++) extra[i]=true;
	for(int i=0;i<Q;i++) extra[ qx[i] ]=false;
	for(int i=0;i<m1;i++) if(extra[i]) id[tm++]=i;
	tz=z; sort(id,id+tm,cmp);
	for(int i=0;i<tm;i++){
		ri=find(x[id[i]]); rj=find(y[id[i]]);
		if(ri!=rj){
			a[ri]=rj; ans += z[id[i]];
			kx[kt]=x[id[i]]; ky[kt]=y[id[i]]; kt++;
		}
	}
	for(int i=1;i<=n;i++) a[i]=0;
	for(int i=0;i<kt;i++) a[ find(kx[i]) ]=find(ky[i]);
	int n2=0;
	for(int i=1;i<=n;i++) if(a[i]==0)
	vd[i]=++n2;
	for(int i=1;i<=n;i++) if(a[i])
	vd[i]=vd[find(i)];
	int m2=0, *Nx=x+m1, *Ny=y+m1, *Nz=z+m1;
	for(int i=0;i<m1;i++) app[i]=-1;
	for(int i=0;i<Q;i++) if(app[qx[i]]==-1){
		Nx[m2]=vd[ x[ qx[i] ] ]; Ny[m2]=vd[ y[ qx[i] ] ]; Nz[m2]=z[ qx[i] ];
		app[qx[i]]=m2; m2++;
	}
	for(int i=0;i<Q;i++){ z[ qx[i] ]=qy[i]; qx[i]=app[qx[i]]; }
	for(int i=1;i<=n2;i++) a[i]=0;
	for(int i=0;i<tm;i++){
		ri=find(vd[ x[id[i]] ]);  rj=find(vd[ y[id[i]] ]);
		if(ri!=rj){
			a[ri]=rj; Nx[m2]=vd[ x[id[i]] ];
			Ny[m2]=vd[ y[id[i]] ]; Nz[m2]=z[id[i]]; m2++;
		}
	}
	int mid=Q/2;
	solve(qx,qy,mid,n2,Nx,Ny,Nz,m2,ans);
	solve(qx+mid,qy+mid,Q-mid,n2,Nx,Ny,Nz,m2,ans);
}
//int x[SZ],y[SZ],z[SZ],qx[MXQ],qy[MXQ],n,m,Q;
//void init(){
	//scanf("%d%d",&n,&m);
	//for(int i=0;i<m;i++) scanf("%d%d%d",x+i,y+i,z+i);
	//scanf("%d",&Q);
	//for(int i=0;i<Q;i++){ scanf("%d%d",qx+i,qy+i); qx[i]--; }
//}
//void work(){ if(Q) solve(qx,qy,Q,n,x,y,z,m,0); }
//int main(){init(); work(); }
#define MXQ M
int x[MXQ],y[MXQ],z[MXQ],qx[MXQ],qy[MXQ],n,m,Q;
vector<int> v[ N ];
LL sum[ N ];
void init(){
	//scanf("%d%d",&n,&m);
  n = getint();
  m = getint();
	for(int i=0;i<m;i++){
    //scanf("%d%d%d",x+i,y+i,z+i);
    x[ i ] = getint();
    y[ i ] = getint();
    z[ i ] = getint();
    v[ x[ i ] ].push_back( i );
    v[ y[ i ] ].push_back( i );
    sum[ x[ i ] ] += z[ i ];
    sum[ y[ i ] ] += z[ i ];
  }
  for( int i = 1 ; i <= n ; i ++ ){
 //(qx[i], qy[i])->chg weight of edge No.qx[i] to qy[i]
    for( int eid : v[ i ] ){
      qx[ Q ] = eid;
      qy[ Q ++ ] = 0;
    }
    useful[ Q - 1 ] = 1;
    for( int eid : v[ i ] ){
      qx[ Q ] = eid;
      qy[ Q ++ ] = z[ eid ];
    }
  }
}
void work(){
  solve(qx,qy,Q,n,x,y,z,m,0);
  for( int i = 1 ; i <= n ; i ++ )
    printf( "%lld\n" , sum[ i ] + tmp_ans[ i - 1 ] );
}
int32_t main(){
  init();
  work();
}
