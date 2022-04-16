struct Slope{
    ll x, y;
    Slope(ll _x = 0, ll _y = 0){
        x = _x;
        y = _y;
    }
    bool operator <=(Slope &b){
        return (y * b.x <= b.y * x);
    }
    bool operator <(Slope const &b){
        return (y * b.x < b.y * x);
    }
    bool operator >=(Slope &b){
        return (y * b.x >= b.y * x);
    }
    bool operator >(Slope const &b){
        return (y * b.x > b.y * x);
    }
};