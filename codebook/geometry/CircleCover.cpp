// Find interpoints of two circles.
// identical circle should be handled first
bool CCinter(Circle a, Circle b, Pt &p1, Pt &p2){ 
  // p1, p2 should be the interpoint of a, b
  // if there aren't exactly 2 interpoints, ret false
}
// Area[i] : area covered by at least i circles
struct Tevent {
	Pt p; D ang; int add;
	Tevent() {}
	Tevent(Pt _a, D _b, int _c): p(_a), ang(_b), add(_c) {}
	bool operator<(const Tevent &a)const
	{return ang < a.ang;}
}eve[ N * 2 ];
// strict: c = 0, otherwise c = -1
bool disjuct( Circle& a, Circle &b, int &c)
{ return sign( norm( a.O - b.O ) - a.R - b.R ) > c; }
int E , cnt , C;
Circle c[N];
bool g[N][N], overlap[N][N];
D Area[N];
int cX[N], cY[N], cR[N];
bool contain(int i, int j) {
	return (sign(c[i].R - c[j].R) > 0 ||
          (sign(c[i].R - c[j].R) == 0 && i < j) ) && c[i].contain(c[j], -1);
  /* c[j] is non-strictly in c[i]. */
}
int main() {
	scanf("%d", &C);
	for (int i = 0; i < C; ++i) {
		scanf("%d%d%d", cX+i, cY+i, cR+i);
		c[i].O = Pt(cX[i], cY[i]);
		c[i].R = cR[i];
	}
	for (int i = 0; i <= C; ++i) Area[i] = 0;
	for(int i=0; i<C; ++i) for(int j=0; j<C; ++j)
			overlap[i][j] = contain(i, j);
	for(int i=0; i<C; ++i) for(int j=0; j<C; ++j) 
		g[i][j] = !(overlap[i][j] || overlap[j][i] || disjuct(c[i], c[j], -1));
	for (int i = 0; i < C; ++i) {
		E = 0; cnt = 1;
		for(int j=0;j<C;++j) if(j!=i&&overlap[j][i])cnt++;
		for (int j = 0; j < C; ++j)
			if (i != j && g[i][j]) {
				Pt aa, bb;
				CCinter(c[i], c[j], aa, bb);
				D A = atan2(aa.Y - c[i].O.Y, aa.X - c[i].O.X);
				D B = atan2(bb.Y - c[i].O.Y, bb.X - c[i].O.X);
				eve[E++] = Tevent(bb, B, 1);
				eve[E++] = Tevent(aa, A, -1);
				if (B > A) cnt++;
			}
		if( E == 0 ) Area[cnt] += pi * c[i].R * c[i].R;
		else{
			sort( eve , eve + E );
			eve[E] = eve[0];
			for( int j = 0 ; j < E ; j ++ ){
				cnt += eve[j].add; 
				Area[cnt] += (eve[j].p ^ eve[j + 1].p) * .5;
				D theta = eve[j + 1].ang - eve[j].ang;
				if (theta < 0) theta += 2. * pi;
				Area[cnt] += theta * c[i].R * c[i].R * .5 - sin(theta) * c[i].R * c[i].R * .5;
			}
		}
	}
}
