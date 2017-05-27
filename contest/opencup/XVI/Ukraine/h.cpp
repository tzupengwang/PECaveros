#include <bits/stdc++.h>
using namespace std;
#define N 22
#define K 1021
const double eps = 1e-8;
bool equal( double x , double y ){
  return fabs( x - y ) < eps;
}
struct Solver{
  double par[ N ][ N ];
  int n;
  void solve(){
    for( int i = 0 ; i < n ; i ++ ){
      int ni = i;
      for( int j = i ; j < n ; j ++ )
        if( not equal( 0 , par[ j ][ i ] ) ){
          ni = j;
          break;
        }
      for( int j = 0 ; j <= n ; j ++ )
        swap( par[ i ][ j ] , par[ ni ][ j ] );
      double vv = par[ i ][ i ];
      for( int j = 0 ; j <= n ; j ++ )
        par[ i ][ j ] /= vv;
      for( int j = 0 ; j < n ; j ++ ){
        if( i == j ) continue;
        double mul = par[ j ][ i ];
        for( int k = 0 ; k <= n ; k ++ )
          par[ j ][ k ] -= mul * par[ i ][ k ];
      }
    }
  }
} solver;
map< vector<int> , int > M;
int n , mcnt;
vector< pair<int,double> > nxt[ K ];
vector< int > v[ N ];
double p[ N ];
vector<int> topo;
vector< vector<int> > ord;
double sta[ K ];
double C2( double a ){
  return a * ( a - 1 ) / 2;
}
void go( vector<int> vv ){
  sort( vv.begin() , vv.end() );
  if( M.count( vv ) ) return;
  for( auto i : vv )
    sta[ mcnt ] += C2( i );
  sta[ mcnt ] /= C2( n );
  ord.push_back( vv );
  M[ vv ] = mcnt ++;
  for( size_t i = 0 ; i < vv.size() ; i ++ )
    for( size_t j = i + 1 ; j < vv.size() ; j ++ ){
      vector<int> tv = vv;
      tv[ i ] = vv[ i ] + vv[ j ];
      swap( tv[ j ] , tv.back() );
      tv.pop_back();
      double prob = 0.0;
      sort( tv.begin() , tv.end() );
      go( tv );
      prob = (double)vv[ i ] * vv[ j ] / C2( n );
      nxt[ M[ vv ] ].push_back( { M[ tv ] , prob } );
    }
  topo.push_back( M[ vv ] );
}
void init(){
  scanf( "%d" , &n );
  for( int i = 0 ; i < n ; i ++ )
    scanf( "%lf" , &p[ i ] );
  for( int i = 0 ; i < n ; i ++ ){
    int c; scanf( "%d" , &c ); while( c -- ){
      int tnxt; scanf( "%d" , &tnxt );
      v[ i ].push_back( tnxt - 1 );
    }
  }
  vector<int> vv;
  for( int i = 0 ; i < n ; i ++ )
    vv.push_back( 1 );
  go( vv );
}
double dp[ K ][ N ];
void solve(){
  //reverse( topo.begin() , topo.end() );
  for( size_t i = 0 ; i < topo.size() ; i ++ ){
    int id = topo[ i ];
    if( nxt[ id ].empty() ){
      for( int j = 0 ; j < n ; j ++ )
        dp[ id ][ j ] = 0.0;
      continue;
    }
    //sort( nxt[ id ].begin() , nxt[ id ].end() );
    //nxt[ id ].resize( unique( nxt[ id ].begin() , nxt[ id ].end() ) -
                      //nxt[ id ].begin() );
    for( int j = 0 ; j < n ; j ++ )
      for( int k = 0 ; k <= n ; k ++ )
        solver.par[ j ][ k ] = 0.0;
    for( int j = 0 ; j < n ; j ++ ){
      solver.par[ j ][ j ] = 1.0;
      for( int nj : v[ j ] ){
        double prob = ( ( 1. - p[ j ] ) + p[ j ] * sta[ id ] )
          / (int)v[ j ].size();
        solver.par[ j ][ nj ] -= prob;
      }
      for( auto np : nxt[ id ] ){
        double pp = p[ j ] * np.second;
        double exp = 0.0;
        for( int nj : v[ j ] )
          exp += dp[ np.first ][ nj ] / (int)v[ j ].size();
        exp *= pp;
        solver.par[ j ][ n ] += exp;
      }
      solver.par[ j ][ n ] += 1.;
    }
    assert( M[ ord[ id ] ] == id );
    solver.n = n;
    solver.solve();
    for( int j = 0 ; j < n ; j ++ )
      dp[ id ][ j ] = solver.par[ j ][ n ];
  }
  vector<int> start;
  for( int i = 0 ; i < n ; i ++ )
    start.push_back( 1 );
  printf( "%.12f\n" , dp[ M[ start ] ][ 0 ] );
}
int main(){
  init();
  solve();
}
