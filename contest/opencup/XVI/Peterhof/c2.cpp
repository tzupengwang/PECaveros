#include <bits/stdc++.h>
using namespace std;
struct Per5{
  int p[ 5 ];
  Per5(){
    for( int i = 0 ; i < 5 ; i ++ )
      p[ i ] = i;
  }
  void init( const vector<int>& vv ){
    for( int i = 0 ; i < 5 ; i ++ )
      p[ i ] = vv[ i ];
  }
  bool ok(){
    int ret = 0;
    for( int i = 0 ; i < 5 ; i ++ )
      for( int j = i + 1 ; j < 5 ; j ++ )
        if( p[ i ] > p[ j ] )
          ret = 1 - ret;
    return !ret;
  }
  bool iden(){
    for( int i = 0 ; i < 5 ; i ++ )
      if( p[ i ] != i )
        return false;
    return true;
  }
  vector<int> to_vec() const{
    vector<int> vv;
    for( int i = 0 ; i < 5 ; i ++ )
      vv.push_back( p[ i ] );
    return vv;
  }
  Per5 operator*( const Per5& he ) const{
    Per5 ret;
    for( int i = 0 ; i < 5 ; i ++ )
      ret.p[ i ] = p[ he.p[ i ] ];
    return ret;
  }
  void print(){
    for( int i = 0 ; i < 5 ; i ++ )
      cerr << p[ i ] << " ";
    cerr << endl;
  }
};
// time: O(n^2 lg^3 |G| + t n lg |G|)
// mem : O(n^2 lg |G| + tn)
// t : number of generator
typedef vector<int> Permu;
typedef vector<Permu> Bucket;
typedef vector<int> Table;
typedef pair<int,int> pii;	
namespace SchreierSimsAlgorithm{
  Permu inv( const Permu& p ){
    Permu ret( p.size() );
    for( int i = 0; i < int(p.size()); i ++ )
      ret[ p[ i ] ] = i;
    return ret;
  }
	Permu operator*( const Permu& a, const Permu& b ){
		Permu ret( a.size() );
		for( int i = 0 ; i < (int)a.size(); i ++ )
			ret[ i ] = b[ a[ i ] ];
		return ret;
	}
	int n, m;
	vector<Bucket> bkts, bktsInv;
	vector<Table> lookup;
	int fastFilter( const Permu &g, bool addToG = 1 ){
		n = bkts.size();
		Permu p = g;
		for( int i = 0 ; i < n ; i ++ ){
			int res = lookup[ i ][ p[ i ] ];
			if( res == -1 ){
				if( addToG ){
					bkts[ i ].push_back( p );
					bktsInv[ i ].push_back( inv( p ) );
					lookup[ i ][ p[i] ] = (int)bkts[i].size()-1;
				}
				return i;
			}
			p = p * bktsInv[i][res];
		}
		return -1;
	}
	long long calcTotalSize(){
		long long ret = 1;
		for( int i = 0 ; i < n ; i ++ )
			ret *= bkts[i].size();
		return ret;
	}
	bool inGroup( const Permu &g ){
		return fastFilter( g, false ) == -1;
	}
	void Solve( Bucket gen, int _n ){
    sort( gen.begin() , gen.end() );
    gen.resize( unique( gen.begin() , gen.end() ) - gen.begin() );
		n = _n, m = gen.size(); // m perm[0..n-1]s
    //for( auto i : gen ){
      //for( auto j : i )
        //cerr << j << " ";
      //cerr << endl;
    //}
		{//clear all
      bkts.clear();
      bktsInv.clear();
      lookup.clear();
      lookup.resize( n );
      bkts.resize( n );
      bktsInv.resize( n );
		}
		for(int i = 0 ; i < n ; i ++ ){
			lookup[i].resize(n);
			fill(lookup[i].begin(), lookup[i].end(), -1);
		}
		Permu id( n );
		for(int i = 0 ; i < n ; i ++ ) id[i] = i;
		for(int i = 0 ; i < n ; i ++ ){
			bkts[i].push_back(id);
			bktsInv[i].push_back(id);
			lookup[i][i] = 0;
		}
		for(int i = 0 ; i < m ; i ++)
			fastFilter( gen[i] );
		queue< pair<pii,pii> > toUpd;
		for(int i = 0; i < n; i ++)
			for(int j = i; j < n; j ++)
				for(int k = 0; k < (int)bkts[i].size(); k ++)
					for(int l = 0; l < (int)bkts[j].size(); l ++)
						toUpd.push( {pii(i,k), pii(j,l)} );
		while( !toUpd.empty() ){
			pii a = toUpd.front().first;
			pii b = toUpd.front().second;
			toUpd.pop();
			int res = fastFilter(bkts[a.first][a.second] *
                           bkts[b.first][b.second]);
			if(res == -1) continue;
			pii newPair(res, (int)bkts[res].size() - 1);
			for(int i = 0; i < n; i ++)
				for(int j = 0; j < (int)bkts[i].size(); ++j){
					if(i <= res)
						toUpd.push(make_pair(pii(i , j), newPair));
					if(res <= i)
						toUpd.push(make_pair(newPair, pii(i, j)));
				}
		}
	}
}
vector<Per5> cand;
vector< pair<Per5,Per5> > gp;
using namespace SchreierSimsAlgorithm;
bool ok( const Per5& p1 , const Per5& p2 ){
  Per5 tmp = p1 * p1;
  if( not tmp.iden() ) return false;
  Per5 tmp2 = p2 * p2 * p2;
  if( not tmp2.iden() ) return false;
  Per5 tmp3;
  for( int i = 0 ; i < 5 ; i ++ ){
    tmp3 = tmp3 * p1;
    tmp3 = tmp3 * p2;
  }
  if( not tmp3.iden() ) return false;
  vector<Permu> buk;
  buk.push_back( p1.to_vec() );
  buk.push_back( p2.to_vec() );
	Solve( buk , 5 );
	if( calcTotalSize() != 60 )
    return false;
  return true;
}
map< vector<int> , vector<int> > M;
char c[ 101010 ];
int main(){
  vector<int> vv;
  for( int i = 0 ; i < 5 ; i ++ )
    vv.push_back( i );
  do{
    Per5 tp;
    tp.init( vv );
    if( tp.ok() )
      cand.push_back( tp );
  }while( next_permutation( vv.begin() , vv.end() ) );
  for( auto i : cand )
    for( auto j : cand )
      if( ok( i , j ) )
        gp.push_back( { i , j } );
  //cerr << gp.size() << endl;
  Per5 aa = gp[ 0 ].first;
  Per5 bb = gp[ 0 ].second;
  //aa.print();
  //bb.print();
  int n; scanf( "%d" , &n );
  for( int i = 1 ; i <= n ; i ++ ){
    scanf( "%s" , c );
    Per5 e;
    for( int j = 0 ; c[ j ] ; j ++ )
      if( c[ j ] == '0' )
        e = e * aa;
      else
        e = e * bb;
    M[ e.to_vec() ].push_back( i );
  }
  printf( "%d\n" , (int)M.size() );
  vector< vector<int> > ans;
  for( auto i : M )
    ans.push_back( i.second );
  sort( ans.begin() , ans.end() );
  for( auto i : ans ){
    printf( "%d" , (int)i.size() );
    for( auto j : i )
      printf( " %d" , j );
    puts( "" );
  }
}
