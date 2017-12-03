#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef LL type;
typedef pair<type,type> Pt;
typedef pair<Pt,Pt> Line;
typedef pair<Pt,type> Circle;
#define X first
#define Y second
#define O first
#define R second
Pt operator+( const Pt& p1 , const Pt& p2 ){
  return { p1.X + p2.X , p1.Y + p2.Y };
}
Pt operator-( const Pt& p1 , const Pt& p2 ){
  return { p1.X - p2.X , p1.Y - p2.Y };
}
Pt operator*( const Pt& tp , const type& tk ){
  return { tp.X * tk , tp.Y * tk };
}
Pt operator/( const Pt& tp , const type& tk ){
  return { tp.X / tk , tp.Y / tk };
}
type operator*( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.X + p1.Y * p2.Y;
}
type operator^( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.Y - p1.Y * p2.X;
}
type norm2( const Pt& tp ){
  return tp * tp;
}
double norm( const Pt& tp ){
  return sqrt( norm2( tp ) );
}
Pt perp( const Pt& tp ){
  return { tp.Y , -tp.X };
}
void scan( Pt& p ){
  cin >> p.X >> p.Y;
}
#define N 333
int n;
Pt p[ N ];
int reg( const Pt& pp ){
  if( pp.Y == 0 ){
    if( pp.X < 0 ) return 0;
    return 1;
  }
  if( pp.Y < 0 ) return 0;
  return 1;
}
bool cmp( const pair<Pt,int>& pp1 ,
          const pair<Pt,int>& pp2 ){
  Pt p1 = pp1.first , p2 = pp2.first;
  int r1 = reg( p1 ) , r2 = reg( p2 );
  if( r1 != r2 ) return r1 < r2;
  return (p1 ^ p2) > 0;
}
double s[ N ];
LL m[ N ];
int main(){
  cin >> n;
  for( int i = 0 ; i < n ; i ++ )
    scan( p[ i ] );
  for( int c = 0 ; c < n ; c ++ ){
    vector< pair<Pt,int> > vv;
    for( int j = 0 ; j < n ; j ++ ){
      if( c == j ) continue;
      vv.push_back( { p[ j ] - p[ c ] , j } );
    }
    sort( vv.begin() , vv.end() , cmp );
    for( int _ = 0 ; _ < 2 ; _ ++ )
      for( int ii = 0 ; ii < n - 1 ; ii ++ )
        vv.push_back( vv[ ii ] );
    for( int i = 0 ; i < n - 1 ; i ++ ){
      double dd = norm( vv[ i ].first );
      int who = vv[ i ].second;
      int st = i + 1;
      while( st % (n - 1) != i and
             (vv[ i ].first ^ vv[ st ].first) >= 0 )
        st ++;
      if( st % (n - 1) == i ) continue;
      int til = st;
      for( int j = i + 1 ; j < st ; j ++ ){
        if( !(( vv[ i ].first ^ vv[ j ].first ) > 0) )
          continue;
        if( (vv[ i ].first ^ vv[ j ].first) < 0 )
          break;
        while( til % (n - 1) != i and
               (vv[ j ].first ^ vv[ til ].first) > 0 )
          til ++;
        //if( who == 1 and c == 0 ){
          //cerr << c << endl;
          //cerr << i << " " << j << " " << st << " " << til << endl;
          //cerr << "             " << til - st << endl;
          //for( int k = 0 ; k < n - 1 ; k ++ )
            //printf( "%lld %lld %d\n" , vv[ k ].first.first ,
                                       //vv[ k ].first.second ,
                                       //vv[ k ].second );

        //}
        //if( who == 1 and til > st ){
          //cerr << c << endl;
          //cerr << i << " " << j << " " << st << " " << til << endl;
          //cerr << "             " << til - st << endl;
          //for( int k = 0 ; k < n - 1 ; k ++ )
            //printf( "%lld %lld %d\n" , vv[ k ].first.first ,
                                       //vv[ k ].first.second ,
                                       //vv[ k ].second );
        //}
        m[ who ] += til - st;
        s[ who ] += (til - st) * dd;
      }
    }
  }
  for( int i = 0 ; i < n ; i ++ )
    if( m[ i ] == 0 ) puts( "-1" );
    else printf( "%.12f\n" , s[ i ] / m[ i ] );
}
