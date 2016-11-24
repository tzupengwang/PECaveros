// return day of week on y year m month d day
// 0: Sat, 1: Sun, ...
int zeller(int y,int m,int d) {
	if (m<=2) y--,m+=12; int c=y/100; y%=100;
	int w=((c>>2)-(c<<1)+y+(y>>2)+(13*(m+1)/5)+d-1)%7;
	if (w<0) w+=7; return(w);
}
