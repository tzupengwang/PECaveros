#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef vector< pair<int,int> > curve;
typedef pair<curve, pair<int,int> > state;
#define C first
#define A second.first
#define B second.second
string name;
int m;
vector<int> card;
int read(){
  char buf[ 20 ];
  scanf( "%s" , buf );
  int ret;
  if( sscanf( buf , "%dR" , &ret ) == 1 )
    return (ret << 1);
  if( sscanf( buf , "%dB" , &ret ) == 1 )
    return (ret << 1) | 1;
  assert( false );
  return -1;
}


map<state,int> dp;
int Goal( int c1 , int c2 , int c3 , int who ){
  int cnt[ 2 ] = {};
  cnt[ c1 & 1 ] ++;
  cnt[ c2 & 1 ] ++;
  cnt[ c3 & 1 ] ++;
  int ret = c1 / 2 + c2 / 2 + c3 / 2;
  if( cnt[ 0 ] > cnt[ 1 ] ){
    if( who == 0 )
      return ret;
    return -ret;
  }
  if( who == 0 )
    return -ret;
  return +ret;
}

int DP( state st , int who , int nxt ){
  auto it = dp.find( st );
  if( it != dp.end() ) return it->second;
  if( nxt == m + m ){
    curve cc = st.C;
    int Acard = st.A;
    int Bcard = st.B;
    int val = 0;
    if( Acard ){
      if( (Acard & 1) == who ) val += Acard / 2;
      else val -= Acard / 2;
    }
    if( Bcard ){
      if( (Bcard & 1) == who ) val += Bcard / 2;
      else val -= Bcard / 2;
    }
    return dp[ st ] = val;
  }
  curve cc = st.C;
  int Acard = st.A;
  int Bcard = st.B;
  int val = 0;
  bool gt = false;

  int take_card = card[ nxt ];
  if( !Acard ){
    {
      state nxt_st;
      nxt_st.C = cc;
      nxt_st.A = take_card;
      nxt_st.B = Bcard;
      int ret = DP( nxt_st , 1 - who , nxt + 1 );
      if( !gt or ret > val )
        val = ret;
    }
    for( size_t j = 0 ; j + 1 < cc.size() ; j ++ )
      if( cc[ j ].first == -1 and cc[ j + 1 ].first == +1 ){
        state nxt_st;
        int bns = Goal( cc[ j ].second ,
                        cc[ j + 1 ].second , 
                        take_card , who );
        nxt_st.A = Bcard;
        nxt_st.B = 0;
        for( size_t k = 0 ; k < j ; k ++ )
          nxt_st.C.push_back( cc[ k ] );
        nxt_st.C.push_back( { 0 , take_card } );
        for( size_t k = j + 2 ; k < cc.size() ; k ++ )
          nxt_st.C.push_back( cc[ k ] );
        int ret = DP( nxt_st , 1 - who , nxt + 1 );
        ret += bns;
        if( !gt or ret > val )
          val = ret;
      }
  }else{
  for( size_t j = 0 ; j + 1 < cc.size() ; j ++ )
    if( cc[ j ].first == -1 and cc[ j + 1 ].first == +1 ){
      {
        state nxt_st;
        int bns = Goal( cc[ j ].second ,
                                  cc[ j + 1 ].second , 
                                  take_card , who );
        nxt_st.A = Bcard;
        nxt_st.B = Acard;
        for( size_t k = 0 ; k < j ; k ++ )
          nxt_st.C.push_back( cc[ k ] );
        nxt_st.C.push_back( { 0 , take_card } );
        for( size_t k = j + 2 ; k < cc.size() ; k ++ )
          nxt_st.C.push_back( cc[ k ] );
        int ret = DP( nxt_st , 1 - who , nxt + 1 );
        ret += bns;
        if( !gt or ret > val )
          val = ret;
      }
      {
        state nxt_st;
        int bns = Goal( cc[ j ].second ,
                                  cc[ j + 1 ].second , 
                                  Acard , who );
        nxt_st.B = take_card;
        nxt_st.A = Bcard;
        for( size_t k = 0 ; k < j ; k ++ )
          nxt_st.C.push_back( cc[ k ] );
        nxt_st.C.push_back( { 0 , Acard } );
        for( size_t k = j + 2 ; k < cc.size() ; k ++ )
          nxt_st.C.push_back( cc[ k ] );
        int ret = DP( nxt_st , 1 - who , nxt + 1 );
        ret += bns;
        if( !gt or ret > val )
          val = ret;
      }
    }
  for( size_t j = 0 ; j < cc.size() ; j ++ )
    if( cc[ j ].first == 0 ){
      state nxt_st;
      int bns = Goal( cc[ j ].second ,
                                Acard ,
                                take_card , who );
      nxt_st.B = 0;
      nxt_st.A = Bcard;
      {
        for( size_t k = 0 ; k < j ; k ++ )
          nxt_st.C.push_back( cc[ k ] );
        nxt_st.C.push_back( { +1 , Acard } );
        nxt_st.C.push_back( { -1 , take_card } );
        for( size_t k = j + 1 ; k < cc.size() ; k ++ )
          nxt_st.C.push_back( cc[ k ] );
        int ret = DP( nxt_st , 1 - who , nxt + 1 );
        ret += bns;
        if( !gt or ret > val )
          val = ret;
      }
      {
        nxt_st.C.clear();
        for( size_t k = 0 ; k < j ; k ++ )
          nxt_st.C.push_back( cc[ k ] );
        nxt_st.C.push_back( { +1 , take_card } );
        nxt_st.C.push_back( { -1 , Acard } );
        for( size_t k = j + 1 ; k < cc.size() ; k ++ )
          nxt_st.C.push_back( cc[ k ] );
        int ret = DP( nxt_st , 1 - who , nxt + 1 );
        ret += bns;
        if( !gt or ret > val )
          val = ret;
      }
          }
  }
  return dp[ st ] = val;
}

int _cs;

int main(){
  while( cin >> name ){
    if( name == "End" ) break;
    cin >> m;
    card.resize( m + m );
    dp.clear();
    for( int i = 0 ; i < m + m ; i ++ )
      card[ i ] = read();
    state ori;
    for( int i = 0 ; i < 8 ; i ++ )
      ori.C.push_back( { (i&1) ? -1 : +1 , card[ i ] } );
    ori.A = ori.B = 0;
    int first = card[ 0 ] & 1;

    int ret = DP( ori , first , 8 );

    printf( "Case %d: " , ++ _cs )  ;

    if( ret == 0 )
      puts( "Axel and Birgit tie" );     
    else if( (ret > 0 and first == 0 and name[ 0 ] == 'A') or
             (ret < 0 and first == 1 and name[ 0 ] == 'A') or
             (ret < 0 and first == 0 and name[ 0 ] == 'B') or
             (ret > 0 and first == 1 and name[ 0 ] == 'B'))
      cout << name << " wins " << abs( ret ) << endl;
    else
      cout << name << " loses " << abs( ret ) << endl;
  }
}
