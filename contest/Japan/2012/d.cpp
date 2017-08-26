#include <bits/stdc++.h>
using namespace std;
#define N 10
int d;
double f[ N ];
struct Comp{
  double c;
  vector<int> d;
  Comp(){
    c = 0;
    d.clear();
  }
};
double cal( const vector<Comp>& ff , double at ){
  double ret = 0;
  for( auto i : ff ){
    double tmp = i.c;
    for( auto j : i.d )
      tmp *= ( at - j );
    ret += tmp;
  }
  return ret;
}
bool okay( const vector< pair<int,double> >& v , bool debug = false ){
  for( size_t bye = 0 ; bye < v.size() ; bye ++ ){
    vector<Comp> wt;
    for( size_t i = 0 ; i < v.size() ; i ++ ){
      if( i == bye ) continue;
      Comp tmp;
      double wwt = v[ i ].second;
      for( size_t j = 0 ; j < v.size() ; j ++ ){
        if( j == bye ) continue;
        if( i == j ) continue;
        tmp.d.push_back( v[ j ].first );
        wwt /= ( v[ i ].first - v[ j ].first );
      }
      tmp.c = wwt;
      wt.push_back( tmp );
    }
    double dlt = fabs( cal( wt , v[ bye ].first ) - v[ bye ].second );
    if( dlt > 1e-2 )
      return false;
  }
  return true;
}
bool init(){
  cin >> d;
  if( d == 0 ) return false;
  for( int i = 0 ; i < d + 3 ; i ++ )
    cin >> f[ i ];
  return true;
}
void solve(){
  for( int i = 0 ; i < d + 3 ; i ++ ){
    vector< pair<int,double> > vv;
    for( int j = 0 ; j < d + 3 ; j ++ ){
      if( i == j ) continue;
      vv.push_back( { j , f[ j ] } );
    }
    if( okay( vv , i == 2 ) ){
      cout << i << "\n";
      return;
    }
  }
  assert( false );
}
int main(){
  while( init() )
    solve();
}
