//by tzupengwang™
#include<bits/stdc++.h>
using namespace std;

#define FO(it,c) for (__typeof((c).begin()) it=(c).begin();it!=(c).end();it++)
typedef long long ll;
typedef pair<int,int> ii;

ll t , c1 , c2 , a1 , a2 ;

void init() {
  cin >> t >> c1 >> c2 >> a1 >> a2 ;
}

bool check( ll nw ) {
  ll ct1 = a1 , ct2 = a2 ;
  ll buf = nw ;
  while ( ct1 + ct2 ) {
    buf = min( buf , nw ) ;
    if ( ct2 && buf >= c2 ) {
      buf -= c2 , ct2 -- ;
    } else if ( ct1 && buf >= c1 ) {
      buf -= c1 , ct1 -- ;
    } else {
      return false ;
    }
    buf += t ;
  }
  return true ;
}

void process() {
  if ( a1 == 0 && a2 == 0 ) {
    cout << 0 << endl ;
  } else {
    ll l = 0 , r = ( c1 + c2 ) * ( a1 + a2 ) ;
    while ( l < r ) {
      ll md = ( l + r ) / 2 ;
      //cout << l << " " << md << " " << r << endl ;
      if ( check( md ) ) r = md ;
      else l = md + 1 ;
    }
    cout << l + t * ( a1 + a2 + 1 ) << endl ;
  }
}

int main() {
  freopen( "coffin.in" , "r" , stdin ) ;
  freopen( "coffin.out" , "w" , stdout ) ;
  init() ;
  process() ;
  return 0 ;
}

