#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
struct Order{
  int id , v , cv , tv;
};
#define N 50505
map<int,int> _id;
set<int> wt4buy , wt4sell;
int _mid;
inline int ID( int price ){
  auto it = _id.find( price );
  if( it != _id.end() ) return it->second;
  return _id[ price ] = _mid ++;
}
deque<Order> sell[ N ] , buy[ N ];
void print( const deque<Order>& dq , int T , int P ){
  for( const auto& i : dq )
    printf( "%d %d %d %d %d %d\n" ,
            i.id , T , P , i.v , i.tv , i.cv );
}
map< tuple<int,int,int> , int > traded;
void trade( int buy_id , int sell_id , int pri , int vv ){
  tuple<int,int,int> tp = make_tuple( buy_id , sell_id , pri );
  traded[ tp ] += vv;
}
bool decrease( Order& ord , int vv ){
  ord.cv -= vv;
  ord.v -= vv;
  if( ord.cv <= 0 ){
    ord.cv = min( ord.v , ord.tv );
    return ord.cv > 0;
  }
  return false;
}
void trading( deque<Order>& wt_lst , int pri , int bid , int& V , int T ){
  while( V > 0 and not wt_lst.empty() ){
    int nsz = (int)wt_lst.size();
    for( int _ = 0 ; _ < nsz and V > 0 ; _ ++ ){
      int tk = min( V , wt_lst[ 0 ].cv );
      if( T == 1 )
        trade( bid , wt_lst[ 0 ].id , pri , tk );
      else
        trade( wt_lst[ 0 ].id , bid , pri , tk );
      V -= tk;
      if( decrease( wt_lst[ 0 ] , tk ) ){
        wt_lst.push_back( wt_lst[ 0 ] );
        wt_lst.pop_front();
      }else if( wt_lst[ 0 ].cv == 0 )
        wt_lst.pop_front();
    }
    if( V == 0 or wt_lst.empty() )
      break;
    int mx = 1e9;
    LL totv = 0;
    for( size_t i = 0 ; i < wt_lst.size() and mx > 0 ; i ++ ){
      mx = min( mx , wt_lst[ i ].v / wt_lst[ i ].tv );
      totv += wt_lst[ i ].tv;
    }
    mx = min( (LL)mx , V / totv );
    if( mx == 0 ) continue;
    nsz = (int)wt_lst.size();
    while( nsz -- ){
      if( T == 1 )
        trade( bid , wt_lst[ 0 ].id , pri , mx * wt_lst[ 0 ].tv );
      else
        trade( wt_lst[ 0 ].id , bid , pri , mx * wt_lst[ 0 ].tv );
      decrease( wt_lst[ 0 ] , mx * wt_lst[ 0 ].tv );
      V -= mx * wt_lst[ 0 ].tv;
      if( wt_lst[ 0 ].cv )
        wt_lst.push_back( wt_lst[ 0 ] );
      wt_lst.pop_front();
    }
  }
  if( wt_lst.empty() ){
    if( T == 1 )
      wt4buy.erase( pri );
    else
      wt4sell.erase( pri );
  }
}
void Buy( int id , int P , int V , int TV ){
  while( wt4buy.size() and *wt4buy.begin() <= P and V > 0 )
    trading( sell[ ID( *wt4buy.begin() ) ] , *wt4buy.begin() , id , V , 1 );
  if( V > 0 ){
    wt4sell.insert( P );
    int wid = ID( P );
    buy[ wid ].push_back( { id , V , min( V , TV ) , TV } );
  }
}
void Sell( int id , int P , int V , int TV ){
  while( wt4sell.size() and *wt4sell.rbegin() >= P and V > 0 )
    trading( buy[ ID( *wt4sell.rbegin() ) ] , *wt4sell.rbegin() , id , V , 2 );
  if( V > 0 ){
    wt4buy.insert( P );
    int wid = ID( P );
    sell[ wid ].push_back( { id , V , min( V , TV ) , TV } );
  }
}
int main(){
#ifndef EDDY
  freopen( "iceberg.in" , "r" , stdin );
  freopen( "iceberg.out" , "w" , stdout );
#endif
  int _; scanf( "%d" , &_ ); while( _ -- ){
    int id , T , P , V , TV;
    scanf( "%d%d%d%d%d" , &id , &T , &P , &V , &TV );
    if( T == 1 ) Buy( id , P , V , TV );
    else Sell( id , P , V , TV );
    for( auto i : traded )
      printf( "%d %d %d %d\n" ,
              get<0>( i.first ) ,
              get<1>( i.first ) ,
              get<2>( i.first ) ,
              i.second );
    traded.clear();
  }
  puts( "" );
  for( auto i : _id ){
    print( buy[ i.second ] , 1 , i.first );
    print( sell[ i.second ] , 2 , i.first );
  }
}
