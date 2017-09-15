vector<Line> go( const Circle& c1 , const Circle& c2 ){
  vector<Line> ret;
  double d_sq = norm2( c1.O - c2.O );
  if( d_sq < eps ) return ret;
  double d = sqrt( d_sq );
  Pt v = ( c2.O - c1.O ) / d;
  for( int sign1 = 1 ; sign1 >= -1 ; sign1 -= 2 ){
    double c = ( c1.R - sign1 * c2.R ) / d;
    if( c * c > 1 ) continue;
    double h = sqrt( max( 0.0 , 1.0 - c * c ) );
    for( int sign2 = 1 ; sign2 >= -1 ; sign2 -= 2 ){
      Pt n;
      n.X = v.X * c - sign2 * h * v.Y;
      n.Y = v.Y * c + sign2 * h * v.X;
      Pt p1 = c1.O + n * c1.R;
      Pt p2 = c2.O + n * ( c2.R * sign1 );
      if( fabs( p1.X - p2.X ) < eps and
          fabs( p1.Y - p2.Y ) < eps )
        p2 = p1 + perp( c2.O - c1.O );
      ret.push_back( { p1 , p2 } );
    }
  }
  return ret;
}
