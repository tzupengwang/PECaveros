#include <bits/stdc++.h>
using namespace std;
#define Round 10000
#define double long double
const double eps = 1e-9;
#define BS 10
int n , dice[ 10 ][ 6 ];

vector<double> prob_table( const vector<int>& ord ){
  vector<double> pre , now;
  for( int _ = n - 1 ; _ >= 0 ; _ -- ){
    swap( pre , now );
    now.resize( 111 );
    for( int j = 0 ; j < 111 ; j ++ )
      now[ j ] = 0;
    int cur = ord[ _ ];
    if( _ == n - 1 ){
      for( int i = 0 ; i < 6 ; i ++ )
        now[ dice[ cur ][ i ] + BS ] += 1. / 6;
      continue;
    }
    for( int i = 0 ; i < 6 ; i ++ ){
      double better = 0;
      for( int j = dice[ cur ][ i ] + 2 + BS ; j < 111 ; j ++ )
        better += pre[ j ];
      if( better > .5 - eps ){
        for( int j = 1 ; j < 111 ; j ++ )
          now[ j - 1 ] += pre[ j ] / 6.;
      }else
        now[ dice[ cur ][ i ] + BS ] += 1. / 6;
    }
  }
  return now;
}

bool no[ 10 ][ 111 ];
void make_no( const vector<int>& ord ){
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < 6 ; j ++ ){
      no[ i ][ dice[ ord[ i ] ][ j ] ] = false;

      double better = 0.;
      double keep = 1;

      for( int ii = i + 1 , penalty = 1 ; ii < n ; ii ++ , penalty ++ ){
        int _keep = 0;
        for( int jj = 0 ; jj < 6 ; jj ++ )
          if( dice[ ord[ ii ] ][ jj ] - penalty > dice[ ord[ i ] ][ j ]  )
            better += keep / 6.;
          else
            _keep ++;
        keep *= (_keep / 6.);
      }
      if( better > .5 - eps )
        no[ i ][ dice[ ord[ i ] ][ j ] ] = true;
    }
}

#ifdef TEST
vector<int> op;
bool op_no[ 10 ][ 111 ];
void make_op(){
  for( int i = 0 ; i < n ; i ++ )
    op.push_back( i );
  random_shuffle( op.begin() , op.end() );
  make_no( op );
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < 111 ; j ++ )
      op_no[ i ][ j ] = no[ i ][ j ];
}
int op_val(){
  for( int i = 0 ; i < n ; i ++ ){
    int now = op[ i ];
    int gt = dice[ now ][ rand() % 6 ];
    if( op_no[ i ][ gt ] )
      continue;
    return gt - i;
  }
  assert( false );
  return -1;
}
#endif



#define PER 400
vector<int> ord;

#ifdef TEST
int my_val(){
  for( int i = 0 ; i < n ; i ++ ){
    int now = ord[ i ];
    int gt = dice[ now ][ rand() % 6 ];
    if( no[ i ][ gt ] )
      continue;
    return gt - i;
  }
  assert( false );
  return -1;
}
#endif

vector< pair<double, vector<double> > > history;
double sqr( double _x ){ return _x * _x; }

double cal_prob( const vector<int>& tord ){
  vector<double> pp = prob_table( tord );
  for( int i = 1 ; i < 111 ; i ++ )
    pp[ i ] += pp[ i - 1 ];
  double ret = 0.;
  for( auto dat : history ){
    double win_rate = 0;
    for( int i = 0 ; i < 111 ; i ++ )
      win_rate += dat.second[ i ] * pp[ i ];
    ret += sqr( win_rate - dat.first );
  }
  return ret;
}

#define GENERATIONS 30
#define MAX_ALIVE 10
#define MUTATE_TIMES 20
#define CROSSS_TIMES 20


vector<int> mutate( vector<int> _v ){
  int l = rand() % n;
  int r = rand() % n;
  if( l >= r ) swap( l , r );
  random_shuffle( _v.begin() + l , _v.begin() + r + 1 );
  return _v;
}

vector<int> cross( const vector<int>& v1 ,
                   const vector<int>& v2 ){
  vector< pair<int,int> > vv;
  for( size_t i = 0 ; i < v1.size() ; i ++ )
    for( size_t j = 0 ; j < v2.size() ; j ++ )
      if( v1[ i ] == v2[ j ] )
        vv.push_back( { (i + j) * 100 + rand() % 100 , v1[ i ] } );
  sort( vv.begin() , vv.end() );
  vector<int> ret;
  for( auto i : vv )
    ret.push_back( i.second );
  return ret;
}

void rebuild(){
  //fprintf( stderr , "Starting rebuiling...\n" );

  vector< pair< double , vector<int> > > alives;
  while( (int)alives.size() < MAX_ALIVE ){
    vector<int> tmp;
    for( int i = 0 ; i < n ; i ++ )
      tmp.push_back( i );
    random_shuffle( tmp.begin() , tmp.end() );
    alives.push_back( { cal_prob( tmp ) , tmp } );
  }

  for( int _ = 0 ; _ < GENERATIONS ; _ ++ ){
    vector< pair< double , vector<int> > > sons;
    for( auto i : alives )
      sons.push_back( i );

    for( int __ = 0 ; __ < MUTATE_TIMES ; __ ++ ){
      vector<int> res = mutate( alives[ rand() % alives.size() ].second );
      sons.push_back( { cal_prob( res ) , res } );
    }
    for( int __ = 0 ; __ < CROSSS_TIMES ; __ ++ ){
      vector<int> res = cross( alives[ rand() % alives.size() ].second ,
                               alives[ rand() % alives.size() ].second );
      sons.push_back( { cal_prob( res ) , res } );
    }

    sort( sons.begin() , sons.end() );
    sons.resize( unique( sons.begin() , sons.end() ) - sons.begin() );
    if( (int)sons.size() > MAX_ALIVE )
      sons.resize( MAX_ALIVE );

    alives.swap( sons );
  }

  ord = alives[ 0 ].second;
  make_no( ord );
}

bool win[ PER ];

int main(){

  srand( time( 0 ) );

  scanf( "%d" , &n );
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < 6 ; j ++ )
      scanf( "%d" , &dice[ i ][ j ] );

#ifdef TEST
  make_op();
#endif

  for( int i = 0 ; i < n ; i ++ )
    ord.push_back( i );
  random_shuffle( ord.begin() , ord.end() );
  make_no( ord );
  
  int win_count = 0 , phase_win = 0;

  for( int rnd = 1 ; rnd <= Round ; rnd ++ ){
#ifdef TEST
    int myy = my_val();
    int opp = op_val();
    win[ rnd % PER ] = myy >= opp;
#else
    for( size_t i = 0 ; i < ord.size() ; i ++ ){
      printf( "%d\n" , ord[ i ] + 1 );
      fflush( stdout );
      int ret; scanf( "%d" , &ret );
      if( no[ i ][ ret + i ] ){
        puts( "No" );
        fflush( stdout );
        continue;
      }
      puts( "Yes" );
      fflush( stdout );
      break;
    }
    char buf[ 32 ];
    scanf( "%s" , buf );
    win[ rnd % PER ] = (buf[ 0 ] == 'W');
#endif
    if( win[ rnd % PER ] ) win_count ++ , phase_win ++;
    if( rnd % PER == 0 ){
      //for( auto i : ord )
        //printf( "%d " , i );
      //puts( "" );
      history.push_back( { phase_win / (double)PER ,
                           prob_table( ord ) } );
      phase_win = 0;
      rebuild();
    }
  }
#ifdef TEST
  printf( "Win %d times\n" , win_count );
  printf( "Real : " );
  for( auto i : op )
    printf( "%d " , i );
  puts( "" );
  if( win_count < 5000 ){
    for( int i = 0 ; i < n ; i ++ , puts( "" ) )
      for( int j = 0 ; j < 6 ; j ++ )
        printf( "%d " , dice[ i ][ j ] );
  }
#endif
}
