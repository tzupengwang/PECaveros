#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef long long type;
typedef pair<type,type> Pt;
typedef pair<Pt,Pt> Line;
typedef pair<Pt,type> Circle;
#define X first
#define Y second
#define O first
#define R second
const double eps = 1e-9;
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
int ori( const Pt& o , const Pt& a , const Pt& b ){
  LL ret = ( a - o ) ^ ( b - o );
  return ret / max( 1ll , abs( ret ) );
}
// p1 == p2 || q1 == q2 need to be handled
bool banana( const Pt& p1 , const Pt& p2 ,
             const Pt& q1 , const Pt& q2 ){
  if( ( ( p2 - p1 ) ^ ( q2 - q1 ) ) == 0 ){ // parallel
    return false;
    if( ori( p1 , p2 , q1 ) ) return false;
    return ( ( p1 - q1 ) * ( p2 - q1 ) ) < 0 ||
           ( ( p1 - q2 ) * ( p2 - q2 ) ) < 0 ||
           ( ( q1 - p1 ) * ( q2 - p1 ) ) < 0 ||
           ( ( q1 - p2 ) * ( q2 - p2 ) ) < 0;
  }
  return (ori( p1, p2, q1 ) * ori( p1, p2, q2 )<0) &&
         (ori( q1, q2, p1 ) * ori( q1, q2, p2 )<0);
}
#define N 111
int n , x[ N ] , y[ N ];
set< pair< pair<int,int> , pair<int,int> > > e;
void add_e( const pair<int,int>& p1 , const pair<int,int>& p2 ){
  e.insert( { p1 , p2 } );
  e.insert( { p2 , p1 } );
}
bool in( const pair<int,int>& p1 , const pair<int,int>& p2 ){
  return e.find( { p1 , p2 } ) != e.end();
}
vector<int> wtx[ N ];
vector< pair<int, pair<int,int>> > bdr;
vector< pair<int,double> > vv[ N * N ];
map< pair<int,int> , int > mid;
int source = 0 , sink = 1 , iter = 2;
int id( pair<int,int> pp ){
  auto it = mid.find( pp );
  if( it != mid.end() ) return it->second;
  //printf( "(%d, %d) => %d\n" , pp.first , pp.second , iter );
  return mid[ pp ] = iter ++;
}
bool vst[ N * N ];
void add_edge( int ui , int vi , double td ){
  vv[ ui ].push_back( { vi , td } );
  vv[ vi ].push_back( { ui , td } );
}
double sqr( double xx ){
  return xx * xx;
}
bool okay( int x1 , int y1 , int x2 , int y2 ){
  if( y1 == y2 ) return true;
  for( int i = 0 ; i < n ; i ++ )
    if( banana( { x1 , y1 } , { x2 , y2 } ,
                { x[ i ] , y[ i ] } ,
                { x[ ( i + 1 ) % n ] , y[ ( i + 1 ) % n ] } ) )
      return false;
  for( auto i : bdr ){
    if( i.first <= y1 or
        i.first >= y2 )
      continue;
    double curx = (double)( i.first - y1 ) * ( x2 - x1 ) / ( y2 - y1 ) + x1;
    if( curx < i.second.first - eps ) return false;
    if( curx > i.second.second + eps ) return false;
  }
  return true;
}
set< tuple<int,int,int,int> > S;
void link( int x1 , int y1 , int x2 , int y2 ){
  if( x1 == x2 and y1 == y2 ) return;
  if( y1 > y2 or ( y1 == y2 and x1 > x2 ) ){
    swap( x1 , x2 );
    swap( y1 , y2 );
  }
  if( S.find( make_tuple( x1 , y1 , x2 , y2 ) ) != S.end() )
    return;
  S.insert( make_tuple( x1 , y1 , x2 , y2 ) );
  if( not okay( x1 , y1 , x2 , y2 ) ) return;
  //printf( "(%d, %d) -> (%d, %d) \n" , x1 , y1 , x2 , y2 );
  add_edge( id( { x1 , y1 } ) , id( { x2 , y2 } ) ,
            sqrt( sqr( x1 - x2 ) + sqr( y1 - y2 ) ) );
}
void solve(){
  vector< pair<int, pair<int,int>> > st , ed;
  {
    int lb , rb , nlb , nrb;
    for( size_t i = 0 ; i < bdr.size() ; i ++ ){
      if( i == 0 ){
        nlb = lb = bdr[ i ].second.first;
        nrb = rb = bdr[ i ].second.second;
      }else{
        nlb = max( lb , bdr[ i ].second.first );
        nrb = min( rb , bdr[ i ].second.second );
      }
      if( i % 2 == 0 )
        st.push_back( { bdr[ i ].first , { lb , rb } } );
      if( i % 2 == 0 and nlb <= nrb )
        st.push_back( { bdr[ i ].first , { nlb , nrb } } );
      if( ( i and bdr[ i ].second.first > bdr[ i - 1 ].second.first ) or
          ( i and bdr[ i ].second.second < bdr[ i - 1 ].second.second ) ){
        int svy = bdr[ i ].first;
        for( ; i < bdr.size() ; i ++ ){
          nlb = max( nlb , bdr[ i ].second.first );
          nrb = min( nrb , bdr[ i ].second.second );
          if( nlb <= nrb )
            st.push_back( { svy , { nlb , nrb } } );
          else break;
        }
        break;
      }
    }
    reverse( bdr.begin() , bdr.end() );
  }
  {
    int lb , rb , nlb , nrb;
    for( size_t i = 0 ; i < bdr.size() ; i ++ ){
      if( i == 0 ){
        nlb = lb = bdr[ i ].second.first;
        nrb = rb = bdr[ i ].second.second;
      }else{
        nlb = max( lb , bdr[ i ].second.first );
        nrb = min( rb , bdr[ i ].second.second );
      }
      if( i % 2 == 0 )
        ed.push_back( { bdr[ i ].first , { lb , rb } } );
      if( i % 2 == 0 and nlb <= nrb )
        ed.push_back( { bdr[ i ].first , { nlb , nrb } } );
      //if( i and bdr[ i ].second.first > bdr[ i - 1 ].second.first ) break;
      //if( i and bdr[ i ].second.second < bdr[ i - 1 ].second.second ) break;
      if( ( i and bdr[ i ].second.first > bdr[ i - 1 ].second.first ) or
          ( i and bdr[ i ].second.second < bdr[ i - 1 ].second.second ) ){
        int svy = bdr[ i ].first;
        for( ; i < bdr.size() ; i ++ ){
          nlb = max( nlb , bdr[ i ].second.first );
          nrb = min( nrb , bdr[ i ].second.second );
          if( nlb <= nrb )
            ed.push_back( { svy , { nlb , nrb } } );
          else break;
        }
        break;
      }
    }
    reverse( bdr.begin() , bdr.end() );
  }
  for( auto i : st ){
    int id1 = id( { i.second.first , i.first } );
    add_edge( source , id1 , 0 );
    int id2 = id( { i.second.second , i.first } );
    add_edge( source , id2 , 0 );
    for( size_t j = 0 ; j < bdr.size() ; j += 2 )
      if( bdr[ j ].first >= i.first ){
        link( i.second.first , i.first , bdr[ j ].second.first , bdr[ j ].first );
        link( i.second.second , i.first , bdr[ j ].second.first , bdr[ j ].first );
        link( i.second.first , i.first , bdr[ j ].second.second , bdr[ j ].first );
        link( i.second.second , i.first , bdr[ j ].second.second , bdr[ j ].first );
      }
    for( auto j : ed ){
      link( i.second.first , i.first , j.second.first , j.first );
      link( i.second.second , i.first , j.second.first , j.first );
      link( i.second.first , i.first , j.second.second , j.first );
      link( i.second.second , i.first , j.second.second , j.first );
    }
  }
  for( auto i : ed ){
    int id1 = id( { i.second.first , i.first } );
    add_edge( id1 , sink , 0 );
    int id2 = id( { i.second.second , i.first } );
    add_edge( id2 , sink , 0 );
    for( size_t j = 0 ; j < bdr.size() ; j += 2 )
      if( bdr[ j ].first <= i.first ){
        link( bdr[ j ].second.first , bdr[ j ].first , i.second.first , i.first );
        link( bdr[ j ].second.second , bdr[ j ].first , i.second.first , i.first );
        link( bdr[ j ].second.first , bdr[ j ].first , i.second.second , i.first );
        link( bdr[ j ].second.second , bdr[ j ].first , i.second.second , i.first );
      }
  }
  for( size_t i = 0 ; i < bdr.size() ; i += 2 )
    for( size_t j = 0 ; j < bdr.size() ; j += 2 ){
      if( bdr[ i ].first <= bdr[ j ].first )
      link( bdr[ i ].second.first , bdr[ i ].first , bdr[ j ].second.first , bdr[ j ].first );
      link( bdr[ i ].second.second , bdr[ i ].first , bdr[ j ].second.first , bdr[ j ].first );
      link( bdr[ i ].second.first , bdr[ i ].first , bdr[ j ].second.second , bdr[ j ].first );
      link( bdr[ i ].second.second , bdr[ i ].first , bdr[ j ].second.second , bdr[ j ].first );
    }
  priority_queue< pair<double,int>,
    vector< pair<double,int> >,
    greater< pair<double,int> > > heap;
  heap.push( { 0 , source } );
  while( heap.size() ){
    int who; double td;
    tie( td , who ) = heap.top(); heap.pop();
    if( vst[ who ] ) continue;
    vst[ who ] = true;
    if( who == sink ){
      printf( "%.12f\n" , td );
      exit(0);
    }
    for( auto i : vv[ who ] )
      if( not vst[ i.first ] )
        heap.push( { td + i.second , i.first } );
  }
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "nightwatch.in" , "r" , stdin );
  freopen( "nightwatch.out" , "w" , stdout );
#endif
  cin >> n;
  vector<int> xx , yy;
  for( int i = 0 ; i < n ; i ++ ){
    cin >> x[ i ] >> y[ i ];
    x[ i ] *= 2;
    y[ i ] *= 2;
    xx.push_back( x[ i ] );
    yy.push_back( y[ i ] );
  }
  for( int i = 0 ; i < n ; i ++ )
    add_e( { x[ i ] , y[ i ] } ,
           { x[ ( i + 1 ) % n ] , y[ ( i + 1 ) % n ] } );
  sort( xx.begin() , xx.end() );
  xx.resize( unique( xx.begin() , xx.end() ) - xx.begin() );
  sort( yy.begin() , yy.end() );
  yy.resize( unique( yy.begin() , yy.end() ) - yy.begin() );
  {
    int ysz = (int)yy.size();
    for( int i = 1 ; i < ysz ; i ++ )
      yy.push_back( ( yy[ i - 1 ] + yy[ i ] ) / 2 );
    sort( yy.begin() , yy.end() );
    yy.resize( unique( yy.begin() , yy.end() ) - yy.begin() );
  }
  for( int i = 0 ; i < n ; i ++ ){
    pair<int,int> s = { y[ i ] , x[ i ] };
    pair<int,int> t = { y[ ( i + 1 ) % n ] , x[ ( i + 1 ) % n ] };
    if( s > t ) swap( s , t );
    int sy = lower_bound( yy.begin() , yy.end() , s.first ) - yy.begin();
    int ty = upper_bound( yy.begin() , yy.end() , t.first ) - yy.begin();
    for( int j = sy ; j < ty ; j ++ ){
      wtx[ j ].push_back( s.second );
      wtx[ j ].push_back( t.second );
    }
  }
  for( size_t i = 0 ; i < yy.size() ; i ++ ){
    sort( wtx[ i ].begin() , wtx[ i ].end() );
    wtx[ i ].resize( unique( wtx[ i ].begin() , wtx[ i ].end() ) - wtx[ i ].begin() );
    if( wtx[ i ].size() == 2u )
      bdr.push_back( { yy[ i ] , { wtx[ i ][ 0 ] , wtx[ i ][ 1 ] } } );
    else if( wtx[ i ].size() == 3u and
             in( { wtx[ i ][ 0 ] , yy[ i ] } , { wtx[ i ][ 1 ] , yy[ i ] } ) )
      bdr.push_back( { yy[ i ] , { wtx[ i ][ 1 ] , wtx[ i ][ 2 ] } } );
    else if( wtx[ i ].size() == 3u and
             in( { wtx[ i ][ 1 ] , yy[ i ] } , { wtx[ i ][ 2 ] , yy[ i ] } ) )
      bdr.push_back( { yy[ i ] , { wtx[ i ][ 0 ] , wtx[ i ][ 1 ] } } );
    else if( wtx[ i ].size() == 4u ){
      assert( in( { wtx[ i ][ 0 ] , yy[ i ] } , { wtx[ i ][ 1 ] , yy[ i ] } ) );
      assert( in( { wtx[ i ][ 2 ] , yy[ i ] } , { wtx[ i ][ 3 ] , yy[ i ] } ) );
      bdr.push_back( { yy[ i ] , { wtx[ i ][ 1 ] , wtx[ i ][ 2 ] } } );
    }else
      assert( false );
  }
  solve();
}
