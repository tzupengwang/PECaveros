#include <bits/stdc++.h>
using namespace std;
inline int who( const string& ss ){
  if( ss == "Russia" ) return 0;
  if( ss == "Sweden" ) return 1;
  if( ss == "Finland" ) return 2;
  if( ss == "NA" ) return 3;
  assert( false );
  return -1;
}
inline vector< string > tokens(){
  vector< string > tok;
  string in , tmp; getline( cin , in );
  stringstream ss( in );
  while( ss >> tmp )
    tok.push_back( tmp );
  return tok;
} 
#define N 50
bool beat[ N ][ N ] , play[ N ][ N ];
int pt[ N ] , win[ N ] , pwin[ N ] , dif[ N ] , sc[ N ];
void init(){
  for( int i = 0 ; i < 5 ; i ++ ){
    vector< string > tok = tokens();
    int id1 = who( tok[ 0 ] );
    int id2 = who( tok[ 1 ] );
    int sc1 = atoi( tok[ 2 ].c_str() );
    int sc2 = atoi( tok[ 3 ].c_str() );
    if( sc1 < sc2 ) swap( id1 , id2 ) , swap( sc1 , sc2 );
    beat[ id1 ][ id2 ] = true;
    play[ id1 ][ id2 ] = true;
    play[ id2 ][ id1 ] = true;
    if( (int)tok.size() > 4 )
      pt[ id2 ] ++;
    else pwin[ id1 ] ++;
    win[ id1 ] ++;
    pt[ id1 ] += 2;
    dif[ id1 ] += sc1 - sc2;
    dif[ id2 ] += sc2 - sc1;
    sc[ id1 ] += sc1;
    sc[ id2 ] += sc2;
  }
  //for( int i = 0 ; i < 4 ; i ++ )
    //printf( "win : %d, pwin : %d, pt : %d, dif : %d, sc : %d\n" , win[ i ] , pwin[ i ] , pt[ i ] , dif[ i ] , sc[ i ] );
}
bool tbeat[ N ][ N ];
int tpt[ N ] , twin[ N ] , tpwin[ N ] , tdif[ N ] , tsc[ N ];
int cnt , ya;
typedef pair<int,tuple<int,int,int,int>> CC;
pair< CC , int > vv[ 4 ];
void go( int id1 , int id2 , int sc1 , int sc2 , int ot ){
  for( int i = 0 ; i < 4 ; i ++ ){
    tpt[ i ] = pt[ i ];
    twin[ i ] = win[ i ];
    tpwin[ i ] = pwin[ i ];
    tdif[ i ] = dif[ i ];
    tsc[ i ] = sc[ i ];
    for( int j = 0 ; j < 4 ; j ++ )
      tbeat[ i ][ j ] = beat[ i ][ j ];
  }
  if( sc1 < sc2 ) swap( id1 , id2 ) , swap( sc1 , sc2 );
  tbeat[ id1 ][ id2 ] = true;
  if( ot ) tpt[ id2 ] ++;
  else tpwin[ id1 ] ++;
  twin[ id1 ] ++;
  tpt[ id1 ] += 2;
  tdif[ id1 ] += sc1 - sc2;
  tdif[ id2 ] += sc2 - sc1;
  tsc[ id1 ] += sc1;
  tsc[ id2 ] += sc2;
  for( int i = 0 ; i < 4 ; i ++ )
    vv[ i ] = { { tpt[ i ] , make_tuple( twin[ i ] , tpwin[ i ] ,
                                tdif[ i ] , tsc[ i ] ) } , i };
  sort( vv , vv + 4 );
  reverse( vv , vv + 4 );
  for( int l = 0 , r = 0 ; l < 4 ; l = r ){
    while( r < 4 && vv[ l ].first.first == vv[ r ].first.first ) r ++;
    if( r - l == 2 ){
      if( tbeat[ vv[ l + 1 ].second ][ vv[ l ].second ] )
        swap( vv[ l ] , vv[ l + 1 ] );
      continue;
    }
    if( r - l == 1 ) continue;
    for( int il = l , ir = l ; il < r ; il = ir ){
      while( ir < 4 && get<0>( vv[ il ].first.second ) == get<0>( vv[ ir ].first.second ) ) ir ++;
      if( ir - il == 2 ){
        if( tbeat[ vv[ il + 1 ].second ][ vv[ il ].second ] )
            swap( vv[ il ] , vv[ il + 1 ] );
          continue;
      }
      if( ir - il == 1 ) continue;
      for( int iil = il , iir = il ; iil < ir ; iil = iir ){
        while( iir < 4 && get<1>( vv[ iil ].first.second ) == get<1>( vv[ iir ].first.second ) ) iir ++;
        if( iir - iil == 2 ){
          if( tbeat[ vv[ iil + 1 ].second ][ vv[ iil ].second ] )
              swap( vv[ iil ] , vv[ iil + 1 ] );
            continue;
        }
        if( iir - iil == 1 ) continue;
        for( int iiil = iil , iiir = iil ; iiil < iir ; iiil = iiir ){
          while( iiir < 4 && get<2>( vv[ iiil ].first.second ) == get<2>( vv[ iiir ].first.second ) ) iiir ++;
          if( iiir - iiil == 2 ){
            if( tbeat[ vv[ iiil + 1 ].second ][ vv[ iiil ].second ] )
                swap( vv[ iiil ] , vv[ iiil + 1 ] );
              continue;
          }
          if( iiir - iiil == 1 ) continue;
          for( int iiiil = iiil , iiiir = iiil ; iiiil < iiir ; iiiil = iiiir ){
            while( iiiir < 4 && get<3>( vv[ iiiil ].first.second ) == get<3>( vv[ iiiir ].first.second ) ) iiiir ++;
            if( iiiir - iiiil == 2 ){
              if( tbeat[ vv[ iiiil + 1 ].second ][ vv[ iiiil ].second ] )
                  swap( vv[ iiiil ] , vv[ iiiil + 1 ] );
                continue;
            }
            if( iiiir - iiiil == 1 ) continue;
          }
        }
      }
    }
  }
  cnt ++;
  bool ok = false;
  for( int i = 0 ; i < 2 ; i ++ )
    if( vv[ i ].second == 0 ){
      ya ++;
      ok = true;
      break;
    }
  for( int l = 0 , r = 0 ; l < 4 ; l = r ){
    while( r < 4 && vv[ l ].first.first == vv[ r ].first.first ) r ++;
    if( r - l == 2 ){
      if( tbeat[ vv[ l + 1 ].second ][ vv[ l ].second ] )
        swap( vv[ l ] , vv[ l + 1 ] );
      continue;
    }
    if( r - l == 1 ) continue;
    for( int il = l , ir = l ; il < r ; il = ir ){
      while( ir < 4 && get<0>( vv[ il ].first.second ) == get<0>( vv[ ir ].first.second ) ) ir ++;
      if( ir - il == 2 ){
        if( tbeat[ vv[ il + 1 ].second ][ vv[ il ].second ] )
            swap( vv[ il ] , vv[ il + 1 ] );
          continue;
      }
      if( ir - il == 1 ) continue;
      for( int iil = il , iir = il ; iil < ir ; iil = iir ){
        while( iir < 4 && get<1>( vv[ iil ].first.second ) == get<1>( vv[ iir ].first.second ) ) iir ++;
        if( iir - iil == 2 ){
          if( tbeat[ vv[ iil + 1 ].second ][ vv[ iil ].second ] )
              swap( vv[ iil ] , vv[ iil + 1 ] );
            continue;
        }
        if( iir - iil == 1 ) continue;
        for( int iiil = iil , iiir = iil ; iiil < iir ; iiil = iiir ){
          while( iiir < 4 && get<2>( vv[ iiil ].first.second ) == get<2>( vv[ iiir ].first.second ) ) iiir ++;
          if( iiir - iiil == 2 ){
            if( tbeat[ vv[ iiil + 1 ].second ][ vv[ iiil ].second ] )
                swap( vv[ iiil ] , vv[ iiil + 1 ] );
              continue;
          }
          if( iiir - iiil == 1 ) continue;
          for( int iiiil = iiil , iiiir = iiil ; iiiil < iiir ; iiiil = iiiir ){
            while( iiiir < 4 && get<3>( vv[ iiiil ].first.second ) == get<3>( vv[ iiiir ].first.second ) ) iiiir ++;
            if( iiiir - iiiil == 2 ){
              if( tbeat[ vv[ iiiil + 1 ].second ][ vv[ iiiil ].second ] )
                  swap( vv[ iiiil ] , vv[ iiiil + 1 ] );
                continue;
            }
            if( iiiir - iiiil == 1 ) continue;
            reverse( vv + iiiil , vv + iiiir );
          }
        }
      }
    }
  }
  cnt ++;
  for( int i = 0 ; i < 2 ; i ++ )
    if( vv[ i ].second == 0 ){
      ya ++;
      break;
    }
}
void solve(){
  int id1 = -1 , id2 = -1;
  for( int i = 0 ; i < 4 ; i ++ ){
    bool gg = false;
    for( int j = i + 1 ; j < 4 ; j ++ )
      if( !play[ i ][ j ] ){
        id1 = i; id2 = j;
        gg = true;
        break;
      }
    if( gg ) break;
  }
  assert( id1 >= 0 );
  for( int sc1 = 0 ; sc1 <= 1000 ; sc1 ++ )
    for( int sc2 = 0 ; sc2 <= 1000 ; sc2 ++ ){
      if( sc1 == sc2 ) continue;
      for( int ot = 0 ; ot < 2 ; ot ++ ){
        if( ot && abs( sc1 - sc2 ) > 1 ) continue;
        go( id1 , id2 , sc1 , sc2 , ot );
      }
    }
  if( cnt == ya )
    puts( "Already in playoff!" );
  else if( ya == 0 )
    puts( "No chance" );
  else
    puts( "Believe in playoff!" );
}
int main(){
  init();
  solve();
}
