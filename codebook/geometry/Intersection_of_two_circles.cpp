vector<pdd> interCircle( pdd o1, D r1 , pdd o2 , D r2 ){
  D d2 = (o1 - o2) % (o1 - o2); // dot
  D d = sqrt(d2);
	if (d > r1+r2) return {};
  pdd u = 0.5*(o1+o2) + ((r2*r2-r1*r1)/(2*d2))*(o1-o2);
  D A = sqrt((r1+r2+d) * (r1-r2+d) * (r1+r2-d) * (-r1+r2+d));
  pdd v = A / (2*d2) * pdd(o1.Y-o2.Y, -o1.X+o2.X);
  return {u+v, u-v};
}
