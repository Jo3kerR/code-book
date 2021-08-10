template<typename T>
struct frac{
    T num ,den ;
    frac(T x,T y) {
        num = x, den = y ; 
        T g = __gcd(x,y) ;
        num /= g , den /= g ;
    }

    bool operator > (const frac &b) { return num * b.den > b.num * den ;}
    bool operator < (const frac &b) { return num * b.den < b.num * den ;}
    bool operator <= (const frac &b) { return num * b.den <= b.num * den ;}
    bool operator >= (const frac &b) { return num * b.den >= b.num * den ;}
    bool operator == (const frac &b) { return num * b.den == b.num * den ;}
    bool operator != (const frac &b) { return num * b.den != b.num * den ;}

    frac operator - (const frac &b) {
        frac f((num * b.den - b.num * den) , den * b.den); 
        T g = __gcd(f.num, f.den) ; 
        f.num /= g; f.num /= g ;
        return f ;
    }

    frac operator + (const frac &b) {
        frac f((num * b.den + b.num * den) , den * b.den) ;
        T g = __gcd(f.num, f.den) ; 
        f.num /= g; f.num /= g ;
        return f ;
    }

    frac operator * (const frac &b) {
        frac f(num * b.num , den * b.den ) ;
        T g = __gcd(f.num, f.den) ; 
        f.num /= g; f.num /= g ;
        return f ;
    }

    frac operator / (const frac &b) {
        frac f(num * b.den , den * b.num) ;
        T g = __gcd(f.num, f.den) ; 
        f.num /= g; f.num /= g ;
        return f ;
    }

};
