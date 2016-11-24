Pt ORI , info[ N ];
D r; int n;
// Divides into multiple triangle, and sum up
// oriented area
D area2(Pt pa, Pt pb){
	if( norm(pa) < norm(pb) ) swap(pa, pb);
	if( norm(pb) < eps ) return 0;
	D S, h, theta;
	D a = norm( pb ), b = norm( pa ), c = norm(pb - pa);
  D cosB = (pb * (pb - pa)) / a / c, B = acos(cosB);
	D cosC = (pa * pb) / a / b, C = acos(cosC);
	if(a > r){
		S = (C/2)*r*r;
		h = a*b*sin(C)/c;
		if (h < r && B < PI/2) S -= (acos(h/r)*r*r - h*sqrt(r*r-h*h));
	}else if(b > r){
		theta = PI - B - asin(sin(B)/r*a);
		S = .5*a*r*sin(theta) + (C-theta)/2*r*r;
	}else S = .5*sin(C)*a*b;
	return S;
}
D area() {
	D S = 0;
	for(int i = 0; i < n; ++i)
		S += abs( area2(info[i], info[i + 1]) * sign( det(info[i], info[i + 1]));
	return fabs(S);
}
