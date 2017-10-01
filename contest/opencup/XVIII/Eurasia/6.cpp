#include <bits/stdc++.h>
using namespace std;
const double pi = acos( -1. );
double magic = 3;
bool equal( double x , double y ){
  return fabs( x - y ) < 1e-10;
}
int main(){
  double a1 , b1 , c1;
  double a2 , b2 , c2;
  cin >> a1 >> b1 >> c1;
  cin >> a2 >> b2 >> c2;
  double px = ( a1 / ( magic * c1 ) );
  double py = ( b1 / ( magic * c1 ) );
  cout << px << " " << py << endl;
  double qx = ( a2 - a1 ) / ( magic * ( c2 - c1 ) );
  double qy = ( b2 - b1 ) / ( magic * ( c2 - c1 ) );
  cout << qx << " " << qy << endl;
  if( equal( px , qx ) and equal( py , qy ) )
    qy += 1;
  double a = qy - py;
  double b = px - qx;
  double c = px * a + py * b;
  cout << a << " " << b << " " << c << endl;
  double ss = sqrt( a * a + b * b );
  a /= ss;
  b /= ss;
  c /= ss;
  printf( "%.12f %.12f %.12f\n" , a , b , c );
}
