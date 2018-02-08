#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 202
#define R 0
#define U 1
struct DJS{
  int p[ N * N * 3 ];
  void init( int n ){
    for( int i = 0 ; i <= n ; i ++ )
      p[ i ] = i;
  }
  int f( int x ){
    return x == p[ x ] ? x : p[ x ] = f( p[ x ] );
  }
  void uni( int x , int y ){
    p[ f( x ) ] = f( y );
  }
} djs;
#define X first.first
#define Y first.second
#define D second
typedef pair< pair<int,int> , int > john;
set< john > potential , wall , freee;
int dn[]={1,0,0,-1};
int dm[]={0,1,-1,0};
int cur_goal;
char dc[]="NEWS";
void add_wall( int xi , int yi , int dir ){
  wall.insert( { { xi , yi } , dir } );
  potential.erase( { { xi , yi } , dir } );
}
void Add_wall( int xi , int yi , int dir ){
  if( dir == 0 ) add_wall( xi , yi , U );
  if( dir == 3 ) add_wall( xi - 1 , yi , U );
  if( dir == 1 ) add_wall( xi , yi , R );
  if( dir == 2 ) add_wall( xi , yi - 1 , R );
}
void add_free( int xi , int yi , int dir ){
  freee.insert( { { xi , yi } , dir } );
  potential.erase( { { xi , yi } , dir } );
}
void Add_free( int xi , int yi , int dir ){
  if( dir == 0 ) add_free( xi , yi , U );
  if( dir == 3 ) add_free( xi - 1 , yi , U );
  if( dir == 1 ) add_free( xi , yi , R );
  if( dir == 2 ) add_free( xi , yi - 1 , R );
}
inline int id( int xi , int xj ){
  return xi * (N + 1) + xj;
}
int LU = (N + 1) * (N + 1) + 1;
int RD = (N + 1) * (N + 1) + 2;
bool okay( const john& w ){
  if( w.D == R ){
    int f1 = djs.f( id( w.X , w.Y + 1 ) );
    int f2 = djs.f( id( w.X + 1 , w.Y + 1 ) );
    if( f1 > f2 ) swap( f1 , f2 );
    int ff1 = djs.f( LU );
    int ff2 = djs.f( RD );
    if( ff1 > ff2 ) swap( ff1 , ff2 );
    return f1 != ff1 or f2 != ff2;
  }else{
    int f1 = djs.f( id( w.X + 1 , w.Y ) );
    int f2 = djs.f( id( w.X + 1 , w.Y + 1 ) );
    if( f1 > f2 ) swap( f1 , f2 );
    int ff1 = djs.f( LU );
    int ff2 = djs.f( RD );
    if( ff1 > ff2 ) swap( ff1 , ff2 );
    return f1 != ff1 or f2 != ff2;
  }
}
void build_map( bool can[ N ][ N ][ 2 ] ){
  //fprintf( stderr , "Rebuilding...\n" );
  for( int i = 0 ; i < N ; i ++ )
    for( int j = 0 ; j < N ; j ++ )
      for( int k = 0 ; k < 2 ; k ++ )
        can[ i ][ j ][ k ] = true;
  djs.init( (N + 1) * (N + 1) + 2 );
  for( int i = 0 ; i < N ; i ++ ){
    if( i )
      djs.uni( id( i , 0 ) , LU );
    if( i + 1 < N )
      djs.uni( id( N , i ) , LU );
  }
  for( int i = 0 ; i < N ; i ++ ){
    if( i + 1 < N )
      djs.uni( id( i , N ) , RD );
    if( i )
      djs.uni( id( 0 , i ) , RD );
  }
  //assert( djs.f( LU ) != djs.f( RD ) );
  for( auto w : wall ){
    if( w.D == R )
      djs.uni( id( w.X , w.Y + 1 ) , id( w.X + 1 , w.Y + 1 ) );
    else
      djs.uni( id( w.X + 1 , w.Y ) , id( w.X + 1 , w.Y + 1 ) );
    can[ w.X ][ w.Y ][ w.D ] = false;
  }
  //assert( djs.f( LU ) != djs.f( RD ) );
  vector< john > cand;
  for( auto i : potential )
    if( i.X < cur_goal and
        i.Y < cur_goal )
      cand.push_back( i );
  random_shuffle( cand.begin() , cand.end() );
  //for( auto w : cand ){
    //if( rand() % 3 ) continue;
    //if( not okay( w ) )
      //continue;
    //if( w.X + 4 >= cur_goal or
        //w.Y + 4 >= cur_goal )
      //continue;
    //if( w.D == R )
      //djs.uni( id( w.X , w.Y + 1 ) , id( w.X + 1 , w.Y + 1 ) );
    //else
      //djs.uni( id( w.X + 1 , w.Y ) , id( w.X + 1 , w.Y + 1 ) );
    //can[ w.X ][ w.Y ][ w.D ] = false;
  //}
  //assert( djs.f( LU ) != djs.f( RD ) );
}
bool in( int xn , int xm ){
  return 0 <= xn and xn < N and
         0 <= xm and xm < N;
}
bool block( int sn , int sm , int tn , int tm , bool can[ N ][ N ][ 2 ] ){
  if( tn < sn or (sn == tn and tm < sm) ){
    swap( sn , tn );
    swap( sm , tm );
  }
  if( sn == tn ) return not can[ sn ][ sm ][ R ];
  return not can[ sn ][ sm ][ U ];
}
pair<int,int> Q[ N * N ];
void find_sp( bool can[ N ][ N ][ 2 ] , int sp[ N ][ N ] , int gn , int gm ){
  for( int i = 0 ; i < N ; i ++ )
    for( int j = 0 ; j < N ; j ++ )
      sp[ i ][ j ] = -1;
  //queue< pair<int,int> > Q;
  int qt = 0;
  Q[ qt ++ ] = {gn, gm};
  //Q.push( {gn, gm} );
  sp[ gn ][ gm ] = 0;
  for( int _ = 0 ; _ < qt ; _ ++ ){
  //while( Q.size() ){
    int tn , tm;
    tie( tn , tm ) = Q[ _ ];
    //tie( tn , tm ) = Q.front(); Q.pop();
    for( int dir = 0 ; dir < 4 ; dir ++ ){
      int nxtn = tn + dn[ dir ];
      int nxtm = tm + dm[ dir ];
      if( not in( nxtn , nxtm ) ) continue;
      if( sp[ nxtn ][ nxtm ] != -1 ) continue;
      if( block( tn , tm , nxtn , nxtm , can ) ) continue;
      sp[ nxtn ][ nxtm ] = sp[ tn ][ tm ] + 1;
      //Q.push( { nxtn , nxtm } );
      Q[ qt ++ ] = {nxtn , nxtm};
    }
  }
}
int tag[ N ][ N ] , stmp;
bool gogo( bool can[ N ][ N ][ 2 ] , int sp[ N ][ N ] , int& nowx , int& nowy , int gn , int gm ){
  ++ stmp;
  tag[ nowx ][ nowy ] = stmp;
  if( sp[ nowx ][ nowy ] == -1 ) return true;
  while( true ){
    vector< pair<int,int> > cand;
    for( int dir = 0 ; dir < 4 ; dir ++ ){
      int nxtn = nowx + dn[ dir ];
      int nxtm = nowy + dm[ dir ];
      if( not in( nxtn , nxtm ) ) continue;
      if( sp[ nxtn ][ nxtm ] == -1 ) continue;
      if( tag[ nxtn ][ nxtm ] == stmp ) continue;
      if( block( nowx , nowy , nxtn , nxtm , can ) )
        cand.push_back( { N * N * 2 , dir } );
      else
        cand.push_back( { sp[ nxtn ][ nxtm ] , dir } );
    }
    sort( cand.begin() , cand.end() );
    for( auto i : cand ){
      //fprintf( stderr , "%d %d\n" , i.first , i.second );
      int dir = i.second;
      printf( "%c\n" , dc[ dir ] );
      fflush( stdout );
      char buf[ 8 ];
      scanf( "%s" , buf );
      if( !strcmp( buf , "end" ) ) exit(0);
      if( !strcmp( buf , "ok" ) ){
        Add_free( nowx , nowy , dir );
        nowx += dn[ dir ];
        nowy += dm[ dir ];
        break;
      }
      Add_wall( nowx , nowy , dir );
      return false;
    }
    if( nowx == gn and nowy == gm ){
      puts( "N" );
      fflush( stdout );
      char buf[ 8 ];
      scanf( "%s" , buf );
      if( !strcmp( buf , "end" ) ) exit(0);
      if( !strcmp( buf , "ok" ) ){
        Add_free( nowx , nowy , 0 );
        nowx ++;
        return true;
      }
      Add_wall( nowx , nowy , 0 );
      puts( "E" );
      fflush( stdout );
      scanf( "%s" , buf );
      if( !strcmp( buf , "end" ) ) exit(0);
      if( !strcmp( buf , "ok" ) ){
        Add_free( nowx , nowy , 1 );
        nowy ++;
        return true;
      }
      Add_wall( nowx , nowy , 1 );
      return true;
    }
  }
  return false;
}
bool can[ N ][ N ][ 2 ];
int sp[ N ][ N ];
int main(){
  srand( 514 ^ 50216 ^ 1021 );
  for( int i = 0 ; i < N ; i ++ )
    for( int j = 0 ; j < N ; j ++ ){
      if( j + 1 < N )
        potential.insert( { { i , j } , R } );
      if( i + 1 < N )
        potential.insert( { { i , j } , U } );
    }
  cur_goal = 9;
  build_map( can );
  find_sp( can , sp , cur_goal , cur_goal );
  int nowx = 0 , nowy = 0;
  while( true ){
    if( gogo( can , sp , nowx , nowy , cur_goal , cur_goal ) )
      cur_goal ++;
    cur_goal = min( cur_goal , 200 );
    build_map( can );
    find_sp( can , sp , cur_goal , cur_goal );
  }
}
