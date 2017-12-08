#include <bits/stdc++.h>
using namespace std;
typedef __int128 LLL;
typedef long long LL;
LLL inf = 1000000000000000000LL;
LL x;
ostream& operator<< (ostream& stream, const LLL& tl ) {
  LL f1 = tl / inf;
  LL f2 = tl % inf;
  //stream << f1 << f2;
  printf( "%lld%018lld" , f1 , f2 );
  return stream;
}
void reduce( pair<LLL,LLL>& pp ){
  LLL gg = __gcd( pp.first , pp.second );
  pp.first /= gg;
  pp.second /= gg;
}
pair<LLL,LLL> cal( LLL p1 , LLL q1 , LLL p2 , LLL q2 ){
  if( p1 == 0 ) return { 0 , 1 };
  swap( p1 , q1 ); swap( p2 , q2 );
  LLL u1 = p1 / q1 , u2 = p2 / q2;
  if( u1 != u2 ) return { 1 , max( u1 , u2 ) };
  pair<LLL,LLL> ret = cal( p2 % q2 , q2 , p1 % q1 , q1 );
  ret.first += ret.second * u1;
  swap( ret.first , ret.second );
  reduce( ret );
  return ret;
}
void solve(){
  if( x == 0 ){
    puts( "0 1" );
    return;
  }
  LLL p1 = 0 , q1 = 1;
  LLL p2 = 1 , q2 = 0;
  LLL up = x , dn = inf;
  for( int i = 0 ; dn > 0 ; i ++ ){
    LLL v = up / dn;
    p1 += p2 * v;
    q1 += q2 * v;
    if( q1 > 1000000000 ) break;
    up %= dn;
    swap( p1 , p2 );
    swap( q1 , q2 );
    swap( dn , up );
  }
  //LLL gg1 = __gcd( p1 , q1 );
  //p1 /= gg1; q1 /= gg1;
  //LLL gg2 = __gcd( p2 , q2 );
  //p2 /= gg2; q2 /= gg2;
  //cout << p1 << " " << q1 << " ";
  cout << (LL)p2 << " " << (LL)q2 << "\n";
  return;
  //LLL q1 = (LLL)t9 * t9 * 10 , p1 = (LLL)x * 10 - 5;
  //LLL q2 = (LLL)t9 * t9 * 10 , p2 = (LLL)x * 10 + 5;
  //pair<LLL,LLL> ret = cal( p1 , q1 , p2 , q2 );
  //cout << (LL)ret.first << " " << (LL)ret.second << endl;
}
int main(){
  int t; scanf( "%d\n" , &t ); while( t -- ){
    scanf( "0.%lld\n" , &x );
    solve();
  }
}
