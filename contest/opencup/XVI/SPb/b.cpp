#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
struct Drop7{
  int mode , level , maxChain , move , chain;
  LL score;
  int board[ 8 ][ 7 ];
  int to_int( char ctmp ){
    if( ctmp == '.' ) return 0;
    if( '1' <= ctmp and ctmp <= '7' )
      return ctmp - '0';
    if( 'a' <= ctmp and ctmp <= 'g' )
      return ( ctmp - 'a' + 1 ) + 8;
    if( 'A' <= ctmp and ctmp <= 'G' )
      return ( ctmp - 'A' + 1 ) + 16;
    assert( false );
    return -1;
  }
  char to_char( int x ){
    if( x == 0 ) return '.';
    return digit( x ) - 1 + "1aA"[ protect( x ) ];
  }
  int protect( int x ){ return x / 8; }
  int digit( int x ){ return x % 8; }
  char log[ 101010 ] , buf[ 101010 ];
  int logLen , logPtr;
  void init(){
    scanf( "%s" , buf );
    scanf( "%s" , buf );
    if( buf[ 0 ] == 'N' ) mode = 0;
    else mode = 1;
    for( int i = 0 ; i < 8 ; i ++ ){
      scanf( "%s" , buf );
      for( int j = 0 ; j < 7 ; j ++ )
        board[ i ][ j ] = to_int( buf[ j ] );
    }
    scanf( "%s" , log );
    logLen = strlen( log );
    logPtr = 0;
    level = 1;
    score = 0;
    maxChain = 0;
    move = 0;
  }
  bool win(){
    for( int i = 0 ; i < 7 ; i ++ )
      if( board[ 0 ][ i ] )
        return true;
    return false;
  }
  void put( int col , int disc ){
    ++ move;
    chain = 0;
    for( int i = 7 ; i >= 0 ; i -- )
      if( board[ i ][ col ] == 0 ){
        board[ i ][ col ] = disc;
        return;
      }
    assert( false );
  }
  void drop(){
    for( int j = 0 ; j < 7 ; j ++ ){
      vector<int> v;
      for( int i = 7 ; i >= 0 ; i -- ){
        if( board[ i ][ j ] )
          v.push_back( board[ i ][ j ] );
        board[ i ][ j ] = 0;
      }
      for( int i = 0 ; i < (int)v.size() ; i ++ )
        board[ 7 - i ][ j ] = v[ i ];
    }
  }
  int di[4]={0,0,1,-1};
  int dj[4]={1,-1,0,0};
  bool exp[ 8 ][ 7 ];
  bool gonna_exp( int ii , int jj ){
    if( protect( board[ ii ][ jj ] ) )
      return false;
    {
      int cc = 1;
      for( int i2 = ii + 1 ; i2 < 8 ; i2 ++ ){
        if( board[ i2 ][ jj ] == 0 ) break;
        cc ++;
      }
      for( int i2 = ii - 1 ; i2 >= 0 ; i2 -- ){
        if( board[ i2 ][ jj ] == 0 ) break;
        cc ++;
      }
      if( cc == digit( board[ ii ][ jj ] ) )
        return true;
    }
    {
      int cc = 1;
      for( int j2 = jj + 1 ; j2 < 7 ; j2 ++ ){
        if( board[ ii ][ j2 ] == 0 ) break;
        cc ++;
      }
      for( int j2 = jj - 1 ; j2 >= 0 ; j2 -- ){
        if( board[ ii ][ j2 ] == 0 ) break;
        cc ++;
      }
      if( cc == digit( board[ ii ][ jj ] ) )
        return true;
    }
    return false;
  }
  bool in( int ii , int jj ){
    return 0 <= ii and ii < 8 and
           0 <= jj and jj < 7;
  }
  LL f( int exp_disc , int i ){
    return exp_disc *
      ( 7LL * i * i * i + 72LL * i * i - 73LL * i + 36LL );
  }
  void explosion(){
    while( true ){
      int exp_disc = 0;
      for( int i = 0 ; i < 8 ; i ++ )
        for( int j = 0 ; j < 7 ; j ++ ){
          exp[ i ][ j ] = false;
          if( board[ i ][ j ] == 0 ) continue;
          if( gonna_exp( i , j ) ){
            exp_disc ++;
            exp[ i ][ j ] = true;
          }
        }
      if( exp_disc == 0 ){
        maxChain = max( maxChain , chain );
        return;
      }
      ++ chain;
      score += f( exp_disc , chain );
      for( int i = 0 ; i < 8 ; i ++ )
        for( int j = 0 ; j < 7 ; j ++ )
          if( exp[ i ][ j ] ){
            board[ i ][ j ] = 0;
            for( int dir = 0 ; dir < 4 ; dir ++ ){
              int nxti = i + di[ dir ];
              int nxtj = j + dj[ dir ];
              if( not in( nxti , nxtj ) ) continue;
              if( board[ nxti ][ nxtj ] == 0 ) continue;
              int pp = protect( board[ nxti ][ nxtj ] );
              pp = max( 0 , pp - 1 );
              board[ nxti ][ nxtj ] = pp * 8 + digit( board[ nxti ][ nxtj ] );
            }
          }
      drop();
    }
  }
  char next_log(){
    if( logPtr >= logLen ){
      puts( "Game log is not complete" );
      exit( 0 );
    }
    return log[ logPtr ++ ];
  }
  void level_up(){
    level ++;
    for( int i = 0 ; i < 7 ; i ++ )
      for( int j = 0 ; j < 7 ; j ++ )
        board[ i ][ j ] = board[ i + 1 ][ j ];
    for( int j = 0 ; j < 7 ; j ++ )
      board[ 7 ][ j ] = to_int( next_log() );
  }
  void print_board(){
    for( int i = 0 ; i < 8 ; i ++ , puts( "" ) )
      for( int j = 0 ; j < 7 ; j ++ )
        putchar( to_char( board[ i ][ j ] ) );
  }
  bool is_level_up(){
    int tsum = 0;
    if( mode == 0 ){
      for( int i = 30 ; i >= 6 ; i -- ){
        tsum += i;
        if( tsum == move ) return true;
        if( tsum > move ) return false;
      }
      return ( move - tsum ) % 5 == 0;
    }else
      return move and move % 5 == 0;
  }
  void game_set(){
    if( logPtr != logLen ){
      printf( "Error in game log at position %d\n" , logPtr + 1 );
      exit(0);
    }
    if( win() )
      printf( "Game is over!\n" );
    printf( "Score: %lld\n" , score / 6 );
    printf( "Longest chain: %d\n" , maxChain );
    printf( "Level reached: %d\n" , level );
    print_board();
    exit(0);
  }
  void play(){
    while( logPtr < logLen ){
      int disc = to_int( next_log() );
      int col = next_log() - '1';
      if( col < 0 or col > 6 ){
        printf( "Error in game log at position %d\n" , logPtr );
        exit(0);
      }
      put( col , disc );
      //printf( "move : %d\n" , move );
      //print_board();
      if( win() ) game_set();
      bool first = true;
      while( true ){
        explosion();
        if( first and is_level_up() ){
          first = false;
          level_up();
          if( mode == 0 ) score += 7000LL * 6;
          else score += 17000LL * 6;
        }else
          break;
        if( win() ) game_set();
      }
    }
    game_set();
  }
} game;
int main(){
  game.init();
  game.play();
}
