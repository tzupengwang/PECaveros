LL solve(LL x1, LL m1, LL x2, LL m2) {
  pair<LL,LL> p = gcd(m1, m2);
  // m1 * p.first + m2 * p.second = 1
  LL lcm = m1 * m2;
  LL res = p.first * (x2 - x1) * m1 + x1;
  return (res % lcm + lcm) % lcm;
}
