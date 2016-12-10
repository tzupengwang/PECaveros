#include <bits/stdc++.h>
using namespace std;
const double pi = acos( -1.0 );
double a;
vector< double > line;
#define N 1021
int q;
double qr[ N ] , qt[ N ];
size_t sz;
void init(){
  //scanf( "%lf" , &a );
  cin >> a;
  line.clear();
  int n; cin >> n;
  //scanf( "%d" , &n );
  for( int i = 0 ; i < n ; i ++ ){
    double theta;
    //scanf( "%lf" , &theta );
    cin >> theta;
    line.push_back( theta );
  }
  sort( line.begin() , line.end() );
  sz = line.size();
  for( size_t i = 0 ; i < sz ; i ++ )
    line.push_back( line[ i ] + pi + pi );
  //scanf( "%d" , &q );
  cin >> q;
  for( int i = 0 ; i < q ; i ++ )
    cin >> qr[ i ] >> qt[ i ];
    //scanf( "%lf%lf" , &qr[ i ] , &qt[ i ] );
}
int id;
inline double cube( double x ){
  return max( 0.0 , x * x * x );
}
inline double cal( double t1 , double t2 ){
  return ( cube( t2 ) - cube( t1 ) );
}
void solve(){
  cout << fixed << setprecision( 4 );
  cout << "Spiral " << ++ id << ": ";
  //printf( "Spiral %d: " , ++ id );
  if( line.empty() ){
    if( q )
      cout << "-1" << endl;
      //puts( "-1" );
    else
      cout << 0.0 << " liters" << endl;
      //puts( "0.0000 liters" );
    return;
  }
  double ans = 0.0;
  set< pair<int,int> > S;
  for( int i = 0 ; i < q ; i ++ ){
    int x = 0;
    if( qt[ i ] < line[ 0 ] ) qt[ i ] += pi + pi;
    while( line[ x + 1 ] < qt[ i ] ) x ++;
    int bl = -1 , br = 1e9 , got = -2;
    //int got2 = floor( ( ( qr[ i ] / a ) - qt[ i ] ) / ( pi + pi ) );
    while( bl <= br ){
      int mid = ( bl + br ) >> 1;
      double tt = qt[ i ] + mid * ( pi + pi );
      double rr = a * tt;
      if( rr < qr[ i ] ) got = mid , bl = mid + 1;
      else br = mid - 1;
    }
    //printf( "%d %d\n" , got , got2 );
    if( S.count( { x , got } ) ) continue;
    S.insert( { x , got } );
    double theta1 = line[ x     ] + got * ( pi + pi );
    double theta2 = line[ x + 1 ] + got * ( pi + pi );
    double theta3 = line[ x     ] + ( got + 1 ) * ( pi + pi );
    double theta4 = line[ x + 1 ] + ( got + 1 ) * ( pi + pi );
    ans += cal( theta3 , theta4 );
    ans -= cal( theta1 , theta2 );
  }
  ans *=  a * a / 60.0;
  cout << max( 1e-6 , ans ) << " liters" << endl;
  //printf( "%.4f liters\n" , max( 0.0 , ans ) );
}
int main(){
  int _;
  //scanf( "%d" , &_ );
  cin >> _;
  while( _ -- ){
    init();
    solve();
  }
}
