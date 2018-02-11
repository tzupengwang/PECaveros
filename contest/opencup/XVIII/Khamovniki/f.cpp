#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 1048576
char s[ N + N ] , t[ N + N ];
int to[ N + N ] , fr[ N + N ];
bool vst[ N + N ];
vector< pair<int,int> > cand;
char s2[ N + N ] , t2[ N + N ];
int fail[ N + N ];
void no(){
  puts( "-1" );
  exit(0);
}
void go( int now ){
  int tmp = now , ptr = 0;
  while( !vst[ tmp ] ){
    //printf( "%d " , tmp );
    s2[ ptr ] = s[ tmp ];
    t2[ ptr ] = t[ tmp ];
    vst[ tmp ] = true;
    ptr ++;
    tmp = to[ tmp ];
  }
  //puts( "" );
  int len = ptr;
  for( int i = len ; i < len + len ; i ++ )
    s2[ i ] = s2[ i - len ];
  fail[ 0 ] = -1;
  for( int i = 1 , ff = -1 ; i < len ; i ++ ){
    while( ff >= 0 and t2[ ff + 1 ] != t2[ i ] ) ff = fail[ ff ];
    if( t2[ ff + 1 ] == t2[ i ] ) ff ++;
    fail[ i ] = ff;
  }
  int ss = -1;
  for( int i = 0 , ff = -1 ; i < len + len ; i ++ ){
    while( ff >= 0 and t2[ ff + 1 ] != s2[ i ] ) ff = fail[ ff ];
    if( t2[ ff + 1 ] == s2[ i ] ) ff ++;
    if( ff + 1 == len ){
      ss = i - len + 1;
      break;
    }
  }
  if( ss == -1 ) no();
  fail[ 0 ] = -1;
  int self = 1;
  for( int i = 1 , ff = -1 ; i < len + len ; i ++ ){
    while( ff >= 0 and s2[ ff + 1 ] != s2[ i ] ) ff = fail[ ff ];
    if( s2[ ff + 1 ] == s2[ i ] ) ff ++;
    fail[ i ] = ff;
    if( i >= len and ff == len - 1 ){
      self = i - len + 1;
      break;
    }
  }
  //cout << ss << " " << self << endl;
  cand.push_back( { ss , self } );
}
pair<LL,LL> gcd(LL a, LL b){
	if(b == 0) return {1, 0};
  pair<LL,LL> q = gcd(b, a % b);
  return {q.second, q.first - q.second * (a / b)};
}
LL solve(LL x1, LL m1, LL x2, LL m2) {
  LL g = __gcd(m1, m2);
  m1 /= g; m2 /= g;
  pair<LL,LL> p = gcd(m1, m2);
  LL lcm = m1 * m2 * g;
  if( (x2 - x1) % g ) no();
  //pair<LL,LL> p = gcd(m1, m2);
  //// m1 * p.first + m2 * p.second = 1
  //LL lcm = (m1 / __gcd(m1, m2)) * m2;
  LL res = p.first * (x2 - x1) * m1 + x1;
  return (res % lcm + lcm) % lcm;
}
int main(){
  scanf( "%s" , s + 1 );
  scanf( "%s" , t + 1 );
  int n = strlen( s + 1 );
  if( !strcmp( s + 1 , t + 1 ) ){
    puts( "0" );
    return 0;
  }
  for( int i = 1 ; i <= n ; i += 2 )
    fr[ i ] = i / 2 + 1;
  for( int i = 2 ; i <= n ; i += 2 )
    fr[ i ] = i / 2 + n / 2;
  for( int i = 1 ; i <= n ; i ++ )
    to[ fr[ i ] ] = i;
  for( int i = 1 ; i <= n ; i ++ ){
    if( vst[ i ] ) continue;
    go( i );
  }
  LL x = cand[ 0 ].first , m = cand[ 0 ].second;
  for( size_t i = 1 ; i < cand.size() ; i ++ ){
    LL xx = solve( x , m , cand[ i ].first , cand[ i ].second );
    x = xx;
    m = (m / __gcd( m , (LL)cand[ i ].second )) * cand[ i ].second;
  }
  cout << x << endl;
}
