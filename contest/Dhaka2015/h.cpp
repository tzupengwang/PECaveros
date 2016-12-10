#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL mod = 7340033;
const int NN = 101010;
inline LL add( LL a , LL b ){
  a += b;
  return a >= mod ? a - mod : a;
}
inline LL mul( LL a , LL b ){
  a *= b;
  return a >= mod ? a % mod : a;
}
inline LL mypow( LL a , LL b ){
  if( b == 0 ) return 1;
  LL ret = mypow( mul( a , a ) , b >> 1 );
  if( b & 1 ) ret = mul( ret , a );
  return ret;
}
LL fac[ NN ] , iiv[ NN ];
void build(){
  fac[ 0 ] = iiv[ 0 ] = 1;
  for( LL i = 1 ; i < NN ; i ++ ){
    fac[ i ] = mul( fac[ i - 1 ] , i );
    iiv[ i ] = mypow( fac[ i ] , mod - 2 );
  }
}
inline LL C( LL a , LL b ){
  return mul( fac[ a ] , mul( iiv[ b ] , iiv[ a - b ] ) );
}
const int MAXNUM = 1048576;
//std::vector<LL> ps(MAXNUM * 2), rev(MAXNUM * 2);
LL ps[ MAXNUM * 2 ] , rev[ MAXNUM * 2 ]; 
namespace NTT{
LL P = mod, root=3;
// Remember coefficient are mod P
/* p=a*2^n+1
n		2^n 				p 				 a 		root
5		32 					97 				 3 		5
6		64 					193 			 3 		5
7		128					257				 2 		3
8		256 				257 			 1 		3
9		512 				7681 			 15 	17
10 	1024 				12289 		 12 	11
11 	2048 				12289 		 6 		11
12 	4096 				12289 		 3 		11
13 	8192 				40961 		 5		3
14 	16384				65537 		 4 		3
15 	32768 			65537 		 2 		3
16 	65536 			65537 		 1 		3
17 	131072 			786433 		 6 		10
18 	262144 			786433 		 3 		10 (605028353, 2308, 3)
19 	524288 			5767169 	 11 	3
20 	1048576		 	7340033 	 7 		3
21 	2097152			23068673 	 11 	3
22 	4194304 		104857601  25 	3
23 	8388608		 	167772161  20 	3
24 	16777216 		167772161  10 	3
25 	33554432 		167772161  5 		3 (1107296257, 33, 10)
26 	67108864 		469762049  7 		3
27 	134217728 	2013265921 15 	31 */
LL bigmod(LL a,LL b){
	if(b==0)return 1;
	return (bigmod((a*a)%P,b/2)*(b%2?a:1LL))%P;
}
LL inv(LL a,LL b){
	if(a==1)return 1;
	return (((LL)(a-inv(b%a,a))*b+1)/a)%b;
}
struct poly{
	std::vector<LL> co;
	int n;//polynomial degree = n
	poly(int d){n=d;co.resize(n+1,0);}
	void trans2(int NN){
		int r=0,st,N;
		unsigned int a,b;
		while((1<<r)<(NN>>1))++r;
		for(N=2;N<=NN;N<<=1,--r){
			for(st=0;st<NN;st+=N){
				int i,ss=st+(N>>1);
				for(i=(N>>1)-1;i>=0;--i){
					a=co[st+i]; b=(ps[i<<r]*co[ss+i])%P;
					co[st+i]=a+b; if(co[st+i]>=P)co[st+i]-=P;
					co[ss+i]=a+P-b; if(co[ss+i]>=P)co[ss+i]-=P;
				}
			}
		}
	}
	void trans1(int NN){
		int r=0,st,N;
		unsigned int a,b;
		for(N=NN;N>1;N>>=1,++r){
			for(st=0;st<NN;st+=N){
				int i,ss=st+(N>>1);
				for(i=(N>>1)-1;i>=0;--i){
					a=co[st+i]; b=co[ss+i];
					co[st+i]=a+b; if(co[st+i]>=P)co[st+i]-=P;
					co[ss+i]=((a+P-b)*ps[i<<r])%P;
				}
			}
		}
	}
	poly operator*(const poly& _b)const{
		poly a=*this,b=_b;
    //puts( "done" );
		int k=n+b.n,i,N=1;
		while(N<=k)N*=2;
    //puts( "done" );
		a.co.resize(N,0); b.co.resize(N,0);
    //puts( "done" );
		int r=bigmod(root,(P-1)/N),Ni=inv(N,P);
    //puts( "fuck" );
    //printf( "%d\n" , ps.size() );
		ps[0]=1;
    //puts( "done" );
		for(i=1;i<N;++i)ps[i]=(ps[i-1]*r)%P;
		a.trans1(N);b.trans1(N);
		for(i=0;i<N;++i)a.co[i]=((LL)a.co[i]*b.co[i])%P;
		r=inv(r,P);
		for(i=1;i<N/2;++i)std::swap(ps[i],ps[N-i]);
		a.trans2(N);
		for(i=0;i<N;++i)a.co[i]=((LL)a.co[i]*Ni)%P;
		a.n=n+_b.n; return a;
	}
};
};
int xn , x , y , a , b , c , d;
void init(){
  scanf( "%d" , &xn );
  //xn = 100000;
  a = b = c = d = 0;
  for( int i = 0 ; i < xn ; i ++ ){
  ////while( n -- ){
    scanf( "%d%d" , &x , &y );
    if( x > 0 && y > 0 ) a ++;
    if( x > 0 && y < 0 ) d ++;
    if( x < 0 && y > 0 ) b ++;
    if( x < 0 && y < 0 ) c ++;
  }
  //a = 25000;
  //b = 25000;
  //c = 25000;
  //d = 25000;
}
int va[ NN + NN ] , vb[ NN + NN ];
int id;
void solve(){
  int nn = 1;
  while( nn <= xn ) nn *= 2;
  for( int i = 0 ; i <= nn ; i ++ )
    va[ i ] = vb[ i ] = 0;
  for( int i = 0 ; i <= min( a , c ) ; i ++ )
    va[ i * 2 ] = mul( C( a , i ) , C( c , i ) );
  for( int i = 0 ; i <= min( b , d ) ; i ++ )
    vb[ i * 2 ] = mul( C( b , i ) , C( d , i ) );
  NTT::poly pa( nn ) , pb( nn );
  for( int i = 0 ; i <= 2 * min( a , c ) ; i ++ )
    pa.co[ i ] = va[ i ];
  for( int i = 0 ; i <= 2 * min( b , d ) ; i ++ )
    pb.co[ i ] = vb[ i ];
  //puts( "done" );
  NTT::poly pc = pa * pb;
  //puts( "done" );
  printf( "Case %d:\n" , ++ id );
  //printf( "%d\n" , xn );
  for( int i = 1 ; i <= xn ; i ++ )
    if( i < (int)pc.co.size() )
      printf( "%d%c" , pc.co[ i ] , " \n"[ i == xn ] );
    else
      printf( "%d%c" , 0 , " \n"[ i == xn ] );
}
int main(){
  build();
  int t; scanf( "%d" , &t ); while( t -- ){
    init();
    solve();
  }
}
