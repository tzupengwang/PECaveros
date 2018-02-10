#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL a , m , p , q , r , s;
vector< pair<int,int> > ans;
bool got;
int _cs , res[ 40 ];
bool better( const vector< pair<int,int> > v1 ,
             const vector< pair<int,int> > v2 ){
  int len1 = 0 , len2 = 0;
  for( auto i : v1 ) len1 += i.first;
  for( auto i : v2 ) len2 += i.first;
  if( len1 != len2 ) return len1 < len2;
  for( size_t i = 0 ; i < v1.size() and i < v2.size() ; i ++ ){
    if( v1[ i ].second != v2[ i ].second )
      return v1[ i ].second < v2[ i ].second;
    if( v1[ i ].first != v2[ i ].first ){
      if( v1[ i ].first < v2[ i ].first )
        return v1[ i + 1 ].second < v2[ i ].second;
      else
        return v1[ i ].second < v2[ i + 1 ].second;
    }
  }
  return false;
}
void solve(){
  printf( "Case %d:" , ++ _cs );
  got = false;
  ans.clear();
  for( int tms = 0 ; ; tms ++ ){
    if( q > s ) break;
    //cerr << p << " " << q << " " << r << " " << s << endl;
    {
      LL nda = max( ( r - p ) / a , 0LL );
      if( p + nda * a < r ) nda ++;
      LL tp = p + nda * a;
      LL tq = q + nda * a;
      LL atmst = ( s - q ) / a;
      if( r <= tp and tq <= s ){
        LL mr = (atmst - nda);

        for( int i = 0 ; i <= tms ; i ++ )
          res[ i ] = 0;
        for( int i = tms ; i ; i -- ){
          res[ i ] = nda % m;
          nda /= m;
        }
        res[ 0 ] = nda;

        LL bs = 1;

        for( int advanced = tms ; advanced >= 0 ; advanced -- ){

          for( int i = tms ; i ; i -- ){
            res[ i - 1 ] += res[ i ] / m;
            res[ i ] %= m;
          }

          vector< pair<int,int> > tans;
          for( int i = 0 ; i <= tms ; i ++ ){
            if( i ) tans.push_back( { 1 , 1 } );
            if( res[ i ] ) tans.push_back( { res[ i ] , 0 } );
          }

          if( tans.size() ){
            size_t nsz = 1;
            for( size_t i = 1 ; i < tans.size() ; i ++ ){
              if( tans[ i ].second == tans[ nsz - 1 ].second )
                tans[ nsz - 1 ].first += tans[ i ].first;
              else
                tans[ nsz ++ ] = tans[ i ];
            }
            tans.resize( nsz );
          }

          if( not got or better( tans , ans ) ){
            got = true;
            ans = tans;
          }

          if( advanced == 0 ) break;
          bool gg = false;
          if( res[ advanced ] ){
            LL nd = m - res[ advanced ];
            if( nd > mr / bs ){
              gg = true;
              break;
            }
            if( nd * bs > mr ){
              gg = true;
              break;
            }
            mr -= nd * bs;
            res[ advanced ] = 0;
            res[ advanced - 1 ] ++;
          }
          if( gg ) break;
          bs *= m;
        }
      }
    }
    if( m == 1 ) break;
    p *= m;
    q *= m;
  }
  if( not got ){
    puts( " impossible" );
    return;
  }
  if( ans.empty() ){
    puts( " empty" );
    return;
  }
  for( auto i : ans )
    printf( " %d%c" , i.first , "AM"[ i.second ] );
  puts( "" );
}
int main(){
  while( scanf( "%lld%lld%lld%lld%lld%lld" , &a , &m , &p , &q , &r , & s ) == 6 and a ){
    solve();
  }
}
