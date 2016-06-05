#include<bits/stdc++.h>
using namespace std;
#define PB push_back
#define X first
#define Y second
const int MXL = 5000;
const double eps = 1e-8;
typedef pair<double, double> Pt;
typedef pair<Pt, Pt> Line;
Pt operator+( const Pt p1, const Pt p2 ){
	return { p1.X + p2.X, p1.Y + p2.Y };
}
Pt operator-( const Pt p1, const Pt p2 ){
	return { p1.X - p2.X, p1.Y - p2.Y };
}
Pt operator*( const Pt p, const double c ){
	return { p.X * c, p.Y * c };
}
double operator^( const Pt p1 , const Pt p2 ){
	return p1.X * p2.Y - p2.X * p1.Y;
}
vector<Line> lnlst;
double atn[ MXL ];
bool lncmp( int l1 , int l2 ){
	return atn[ l1 ] < atn[ l2 ];	
}
Pt interPnt( Pt p1, Pt p2, Pt q1, Pt q2 ){
	double f1 = ( p2 - p1 ) ^ ( q1 - p1 );
	double f2 = ( p2 - p1 ) ^ ( p1 - q2 );
	double f = ( f1 + f2 );
	if( fabs( f ) < eps ) return Pt(nan(""), nan(""));
	return q1 * ( f2 / f ) + q2 * ( f1 / f );
}
deque<Line> dq;
void halfPlaneInter(){
	int n = lnlst.size();
	vector<int> stlst;
	for( int i = 0 ; i < n ; i ++ ){
		stlst.PB( i );
		Pt d = lnlst[ i ].second - lnlst[ i ].first;
		atn[ i ] = atan2( d.Y, d.X );
	}
	sort( stlst.begin(), stlst.end(), lncmp );
	vector<Line> lst;
	for( int i = 0 ; i < n ; i ++ ){
		if( i ){
			int j = i - 1;
			Line li = lnlst[ stlst[ i ] ];
			Line lj = lnlst[ stlst[ j ] ];
			Pt di = li.second - li.first;
			Pt dj = lj.second - lj.first;
			if( fabs( di ^ dj ) < eps ){
				if( di ^ ( lj.second - li.second ) < 0 )
					lst.pop_back();
				else continue;
			}
		}
		lst.PB( lnlst[ stlst[ i ] ] );
	}
	dq.PB( lst[0] );
	dq.PB( lst[1] );
	for( int i = 2 ; i < n ; i ++ ){
		int dsz = dq.size();
		Line l = lst[ i ];
		while( dsz >= 2 ){
			Line l1 = dq[ dsz-1 ];
			Line l2 = dq[ dsz-2 ];
			Pt it12 = interPnt( l1.first , l1.second ,
                          l2.first , l2.second );
			if( (l.second-l.first) ^ (it12-l.first) < 0 ){
				dq.pop_back();
				dsz --;
			}else break;
		}
		while( dsz >= 2 ){
			Line l1 = dq[ 0 ];
			Line l2 = dq[ 1 ];
			Pt it12 = interPnt( l1.first , l1.second ,
                          l2.first , l2.second );
			if( (l.second-l.first) ^ (it12-l.first) < 0 ){
				dq.pop_front();
				dsz --;
			}else break;
		}
		Line l1 = dq[ dsz - 1 ];
		if( !std::isnan( interPnt( l.first , l.second ,
                          l1.first , l1.second ).X ) )
			dq.PB(l);
	}
	int dsz = dq.size();
	while( dsz >= 2 ){
		Line l1 = dq[ dsz - 1 ];
		Line l2 = dq[ dsz - 2 ];
		Line l = dq[ 0 ];
		Pt it12 = interPnt( l1.first, l1.second,
                        l2.first, l2.second );
		if( std::isnan( it12.X ) ){
			dq.pop_back();
			dq.pop_back();
			dsz -= 2;
		}else if( (l.second-l.first)^(it12-l.first)<0 ){
			dq.pop_back();
			dsz --;
		}else break;
	}
}
void solve(){	
	int N;
	cin >> N;
	for( int i = 0 ; i < N ; i ++ ){
		double x1, x2, y1, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		lnlst.PB( { Pt( x1 , y1 ), Pt( x2 , y2 ) } );
    // --^--(x1,y1)--^--(x2,y2)--^-- upper
	}
	halfPlaneInter();
	int dsz = dq.size();
  // if dsz < 3: no intersection !!
	cout << dsz << endl;
	for(int i = 0 ; i < dsz ; i ++ ){
		int j = ( i + 1 ) % dsz;
		Pt it = interPnt( dq[ i ].first, dq[ i ].second,
                      dq[ j ].first, dq[ j ].second );
		cout << it.X << ' ' << it.Y << endl;
	}
}
