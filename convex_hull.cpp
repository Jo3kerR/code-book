struct Point {
	int x,y;
	bool operator<(const Point& p) const {
    		if(x == p.x ) return y < p.y ;
    		return x < p.x ;
    	}
};

vector<vector<Point> > v;
bool cw(Point a,Point b,Point c) {return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y) <= 0 ;}
bool ccw(Point a, Point b, Point c) {return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y) >= 0 ;}
bool convex_hull(multiset<Point> &s) {
	if(sz(s) < 3 ) return 0; 
	vector<Point> points ;
	for(auto i : s ) points.pb(i);
	sort(all(points)) ;
	Point p1 = points[0] , p2 = points.back();
	vector<Point> up, down ;
	up.pb(p1); down.pb(p1) ;
	for(int i = 1; i < sz(points) ; ++i) {
		if( i == sz(points) -1 || cw(p1,points[i],p2)) {
			while(sz(up) >=2 && !cw(up[sz(up)-2] , up[sz(up)-1], points[i])) up.pop_back();
			up.pb(points[i]);
		}
		if( i == sz(points) -1 || ccw(p1,points[i] , p2)) {
			while(sz(down)>=2 && !ccw(down[sz(down)-2] , down[sz(down)-1] , points[i])) down.pop_back();
			down.pb(points[i]); 
		}
	}
	vector<Point> temp ;
	for(int i = 0 ; i < sz(up) ; ++i) {
		s.erase(up[i]);
		temp.pb(up[i]);
	}
	for(int i = sz(down)-2; i > 0 ; --i) {
		s.erase(down[i]);
		temp.pb(down[i]);
	}
	if(sz(temp)>2) return v.pb(temp), 1;
	return 0;
}
