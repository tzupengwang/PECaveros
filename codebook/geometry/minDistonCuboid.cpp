typedef LL T;
T r;
void turn(T i, T j, T x, T y, T z,T x0, T y0, T L, T W, T H) {
	if (z==0) { T R = x*x+y*y; if (R<r) r=R;
	} else {
		if(i>=0 && i< 2) turn(i+1, j, x0+L+z, y, x0+L-x, x0+L, y0, H, W, L);
		if(j>=0 && j< 2) turn(i, j+1, x, y0+W+z, y0+W-y, x0, y0+W, L, H, W);
		if(i<=0 && i>-2) turn(i-1, j, x0-z, y, x-x0, x0-H, y0, H, W, L);
		if(j<=0 && j>-2) turn(i, j-1, x, y0-z, y-y0, x0, y0-H, L, H, W);
}}
T solve(T L, T W, T H, T x1, T y1, T z1, T x2, T y2, T z2){
	if( z1!=0 && z1!=H ){
    if( y1==0 || y1==W )
	    swap(y1,z1), swap(y2,z2), swap(W,H);
  }else
    swap(x1,z1), swap(x2,z2), swap(L,H);
	if (z1==H) z1=0, z2=H-z2;
	r=INF; turn(0,0,x2-x1,y2-y1,z2,-x1,-y1,L,W,H);
  return r;
}
