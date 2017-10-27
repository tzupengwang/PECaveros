Pt inCenter( Pt &A,  Pt &B,  Pt &C) { // 内心
	double a = norm(B-C), b = norm(C-A), c = norm(A-B);
	return (A * a + B * b + C * c) / (a + b + c);
}
Pt circumCenter( Pt &a,  Pt &b,  Pt &c) { // 外心
	Pt bb = b - a, cc = c - a;
	double db=norm2(bb), dc=norm2(cc), d=2*(bb ^ cc);
	return a-Pt(bb.Y*dc-cc.Y*db, cc.X*db-bb.X*dc) / d;
}
Pt othroCenter( Pt &a,  Pt &b,  Pt &c) { // 垂心
	Pt ba = b - a, ca = c - a, bc = b - c;
	double Y = ba.Y * ca.Y * bc.Y,
	  A = ca.X * ba.Y - ba.X * ca.Y,
	  x0= (Y+ca.X*ba.Y*b.X-ba.X*ca.Y*c.X) / A,
	  y0= -ba.X * (x0 - c.X) / ba.Y + ca.Y;
	return Pt(x0, y0);
}
