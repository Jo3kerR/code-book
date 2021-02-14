// Declaration : frac f(4, 5) , equivalent to 4/5

struct frac{
	int num , den ;

	frac f(int x,int y) {
		int g = __gcd(x,y) ;
		x/=g , y/=g ;

		frac f1 = {x,y};
		return f1; 
	}

	bool operator > (const frac &b) {
		return num * b.den > b.num * den ;
	}

	bool operator < (const frac &b) {
		return num * b.den < b.num * den ;
	}

	bool operator <= (const frac &b) {
		return num * b.den <= b.num * den ;
	}

	bool operator >= (const frac &b) {
		return num * b.den >= b.num * den ;
	}

	bool operator == (const frac &b) {
		return num * b.den == b.num * den ;
	}

	frac operator - (const frac &b) {
		frac f1 = { (num * b.den - b.num * den) , den * b.den } ;
		int g = __gcd(f1.num, f1.den) ; 
		f1.num /= g; f1.num /= g ;
		return f1 ;
	}

	frac operator + (const frac &b) {
		frac f1 = { (num * b.den + b.num * den) , den * b.den } ;
		int g = __gcd(f1.num, f1.den) ; 
		f1.num /= g; f1.num /= g ;
		return f1 ;
	}

	frac operator * (const frac &b) {
		frac f1 = { num * b.num , den * b.den } ;
		int g = __gcd(f1.num, f1.den) ; 
		f1.num /= g; f1.num /= g ;
		return f1 ;
	}

	frac operator / (const frac &b) {
		frac f1 = { num * b.den , den * b.num } ;
		int g = __gcd(f1.num, f1.den) ; 
		f1.num /= g; f1.num /= g ;
		return f1 ;
	}

};
