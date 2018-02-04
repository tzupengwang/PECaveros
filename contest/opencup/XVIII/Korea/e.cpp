#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
const double pi = acos(-1.);
const double eps = 1e-9;
typedef long long LL;
typedef double type;
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
#define ONE 360000
double R , r;
double ans[ ONE ];
Pt o = {0, 0};
double cal( int deg ){
  double adeg = (double)deg / ONE * (pi + pi);
  Pt p1 = {R, 0};
  Pt p2 = {R * cosl(adeg), R * sinl(adeg)};
  double dd = fabs( ((o - p1) ^ (p2 - p1)) / norm(p2 - p1) );
  if(dd > r - eps) return norm(p1 - p2);
  double tang = sqrt( max(0., norm2(o - p1) - r * r) );
  double theta = acosl( min( 1. , max( -1. , r / norm(o - p1) ) ) );
  return tang + tang + (adeg - theta - theta) * r;
}
multiset<int> cand;
set< pair<int,int> > in;
#define N 101010
int n , a[ N ] , inv[ ONE ];
inline pair<int,int> nxt( const pair<int,int>& p ){
  auto it = in.upper_bound( p );
  if( it == in.end() ) it = in.begin();
  return *it;
}
inline pair<int,int> pre( const pair<int,int>& p ){
  auto it = in.lower_bound( p );
  if( it == in.begin() ) it = --in.end();
  else --it;
  return *it;
}
inline int result( const pair<int,int>& p1 ,
                   const pair<int,int>& p2 ){
  if( p1.second == p2.second ) return 0;
  if( inv[ p1.first ] == p2.first ) return 0;
  int dlt = (abs( p1.first - p2.first ) + ONE / 2) % ONE;
  return min( dlt , ONE - dlt );
}
double find_ans(){
  return ans[ *cand.rbegin() ];
}
void rm( pair<int,int> p1 ){
  pair<int,int> pp = pre( p1 );
  pair<int,int> nn = nxt( p1 );
  cand.erase( cand.find( result( pp , p1 ) ) );
  cand.erase( cand.find( result( p1 , nn ) ) );
  cand.insert( result( pp , nn ) );
  in.erase( p1 );
}
void ad( pair<int,int> p1 ){
  pair<int,int> pp = pre( p1 );
  pair<int,int> nn = nxt( p1 );
  cand.erase( cand.find( result( pp , nn ) ) );
  cand.insert( result( pp , p1 ) );
  cand.insert( result( p1 , nn ) );
  in.insert( p1 );
}
int main(){
  cin >> R >> r;
  for( int i = 1 ; i <= ONE / 2 ; i ++ ){
    ans[ i ] = cal( i );
    //if( i % 10000 == 0 )
      //printf( "%d : %.6f\n" , i , ans[ i ] );
  }
  for( int i = 0 ; i < ONE ; i ++ )
    inv[ i ] = (i + ONE / 2) % ONE;
  scanf( "%d" , &n );
  for( int i = 0 ; i < n ; i ++ ){
    scanf( "%d" , &a[ i ] );
    in.insert( { a[ i ] , 1 } );
    in.insert( { inv[ a[ i ] ] , 2 } );
  }
  for( int i = 0 ; i < n ; i ++ ){
    {
      pair<int,int> ret = nxt( { a[ i ] , 1 } );
      cand.insert( result( { a[ i ] , 1 } , ret ) );
    }
    {
      pair<int,int> ret = nxt( { inv[ a[ i ] ] , 2 } );
      cand.insert( result( { inv[ a[ i ] ] , 2 } , ret ) );
    }
  }
  printf( "%.12f\n" , find_ans() );
  int q; scanf( "%d" , &q ); while( q -- ){
    int cmd , x;
    scanf( "%d%d" , &cmd , &x );
    if( cmd == 1 ){
      ad( { x , 1 } );
      ad( { inv[ x ] , 2 } );
    }else{
      rm( { x , 1 } );
      rm( { inv[ x ] , 2 } );
    }
    printf( "%.12f\n" , find_ans() );
  }
}
