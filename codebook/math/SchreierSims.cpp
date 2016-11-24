// time: O(n^2 lg^3 |G| + t n lg |G|)
// mem : O(n^2 lg |G| + tn)
// t : number of generator
namespace SchreierSimsAlgorithm{
  typedef vector<int> Permu;
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
	typedef vector<Permu> Bucket;
	typedef vector<int> Table;
	typedef pair<int,int> pii;	
	int n, m;
	vector<Bucket> bkts, bktsInv;
	vector<Table> lookup;
	int fastFilter( const Permu &g, bool addToG = 1 ){
		n = bkts.size();
		Permu p;
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
	void solve( const Bucket &gen, int _n ){
		n = _n, m = gen.size(); // m perm[0..n-1]s
		{//clear all
      bkts.clear();
      bktsInv.clear();
      lookup.clear();
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
