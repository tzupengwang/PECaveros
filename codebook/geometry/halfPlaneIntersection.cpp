#define N 100010
#define EPS 1e-8
#define SIDE 10000000
struct PO{ double x , y ; } p[ N ], o ;
struct LI{
  PO a, b;
  double angle;
  void in( double x1 , double y1 , double x2 , double y2 ){
    a.x = x1 ; a.y = y1 ; b.x = x2 ; b.y = y2;
  }
}li[ N ] , deq[ N ];
int n , m , cnt;
inline int dc( double x ){
  if ( x > EPS ) return 1;
  else if ( x < -EPS ) return -1;
  return 0;
}
inline PO operator-( PO a, PO b ){
  PO c;
  c.x = a.x - b.x ; c.y = a.y - b.y;
  return c;
}
inline double cross( PO a , PO b , PO c ){
  return ( b.x - a.x ) * ( c.y - a.y ) - ( b.y - a.y ) * ( c.x - a.x );
}
inline bool cmp( const LI &a , const LI &b ){
  if( dc( a.angle - b.angle ) == 0 ) return dc( cross( a.a , a.b , b.a ) ) < 0;
  return a.angle > b.angle;
}
inline PO getpoint( LI &a , LI &b ){
  double k1 = cross( a.a , b.b , b.a );
  double k2 = cross( a.b , b.a , b.b );
  PO tmp = a.b - a.a , ans;
  ans.x = a.a.x + tmp.x * k1 / ( k1 + k2 );
  ans.y = a.a.y + tmp.y * k1 / ( k1 + k2 );
  return ans;
}
inline void getcut(){
  sort( li + 1 , li + 1 + n , cmp ); m = 1;
  for( int i = 2 ; i <= n ; i ++ )
    if( dc( li[ i ].angle - li[ m ].angle ) != 0 )
      li[ ++ m ] = li[ i ];
  deq[ 1 ] = li[ 1 ]; deq[ 2 ] = li[ 2 ];
  int bot = 1 , top = 2;
  for( int i = 3 ; i <= m ; i ++ ){
    while( bot < top && dc( cross( li[ i ].a , li[ i ].b , getpoint( deq[ top ] , deq[ top - 1 ] ) ) ) < 0 ) top -- ;
    while( bot < top && dc( cross( li[ i ].a , li[ i ].b , getpoint( deq[ bot ] , deq[ bot + 1 ] ) ) ) < 0 ) bot ++ ;
    deq[ ++ top ] = li[ i ] ;
  }
  while( bot < top && dc( cross( deq[ bot ].a , deq[ bot ].b , getpoint( deq[ top ] , deq[ top - 1 ] ) ) ) < 0 ) top --;
  while( bot < top && dc( cross( deq[ top ].a , deq[ top ].b , getpoint( deq[ bot ] , deq[ bot + 1 ] ) ) ) < 0 ) bot ++;
  cnt = 0;
  if( bot == top ) return;
  for( int i = bot ; i < top ; i ++ ) p[ ++ cnt ] = getpoint( deq[ i ] , deq[ i + 1 ] );
  if( top - 1 > bot ) p[ ++ cnt ] = getpoint( deq[ bot ] , deq[ top ] );
}
double px[ N ] , py[ N ];
void read( int rm ) {
  for( int i = 1 ; i <= n ; i ++ ) px[ i + n ] = px[ i ] , py[ i + n ] = py[ i ];
  for( int i = 1 ; i <= n ; i ++ ){
    // half-plane from li[ i ].a -> li[ i ].b
    li[ i ].a.x = px[ i + rm + 1 ]; li[ i ].a.y = py[ i + rm + 1 ];
    li[ i ].b.x = px[ i ]; li[ i ].b.y = py[ i ];
    li[ i ].angle = atan2( li[ i ].b.y - li[ i ].a.y , li[ i ].b.x - li[ i ].a.x ) ;
  }
}
inline double getarea( int rm ){
  read( rm ); getcut();
  double res = 0.0;
  p[ cnt + 1 ] = p[ 1 ];
  for( int i = 1 ; i <= cnt ; i ++ ) res += cross( o , p[ i ] , p[ i + 1 ] ) ;
  if( res < 0.0 ) res *= -1.0;
  return res;
}
