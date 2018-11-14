template<typename T> struct Point
{
    T x, y;

    Point<T>(T x = 0, T y = 0): x(x), y(y) {}

    bool operator == (const Point<T> &c)
    {
        return x == c.x && y == c.y;
    }

    bool operator < (const Point<T> &c)
    {
        return x < c.x || (x == c.x && y < c.y);
    }

    friend ostream& operator << (ostream &os, Point<T> point)
    {
        os << point.x << ' ' << point.y;
        return os;
    }

    double distance(const Point<T> &c)
    {
        return sqrt((x - c.x) * (x - c.x) + (y - c.y) * (y - c.y));
    }
};

template<typename T> struct Vector2D
{
    T x, y;

    Vector2D<T>(T x = 0, T y = 0): x(x), y(y) {}

    Vector2D<T>(Point<T> from, Point<T> to)
    {
        x = to.x - from.x;
        y = to.y - from.y;
    }

    bool operator == (const Vector2D<T> &c) {return x == c.x && y == c.y;}
    bool operator < (const Vector2D<T> &c) {return x < c.x || (x == c.x && y < c.y);}

    Vector2D<T> operator += (const Vector2D<T> &a){x += a.x, y += a.y; return (*this);}
    Vector2D<T> operator -= (const Vector2D<T> &a) {x -= a.x, y -= a.y; return (*this);}
    Vector2D<T> operator *= (T a) {x *= a, y *= a; return (*this);}
    Vector2D<T> operator /= (T a) {x /= a, y /= a; return (*this);} 
    
    Vector2D<T> operator + (const Vector2D<T> &a){return Vector2D<T>(*this) += a;}
    Vector2D<T> operator - (const Vector2D<T> &a){return Vector2D<T>(*this) -= a;}
    Vector2D<T> operator * (T a){return Vector2D<T>(*this) *= a;}
    Vector2D<T> operator / (T a){return Vector2D<T>(*this) /= a;}

    friend ostream& operator << (const ostream &os, Vector2D<T> vect)
    {
        os << vect.x << ' ' << vect.y;
        return os;
    }

    T dot(const Vector2D<T> &c) {return x * c.x + y * c.y;}
    T cross(const Vector2D<T> &c) {return x * c.y - y * c.x;}

    double length() {return sqrt(x * x + y * y);}
    double angle(const Vector2D<T> &a) {return cross(a) / (length() * a.length());}
};

template<typename T> bool cw(Point<T> a, Point<T> b, Point<T> c)
{
    return (Vector2D<T>(a, b).cross(Vector2D<T>(b, c))) < 0;
} 

template<typename T> bool ccw(Point<T> a, Point<T> b, Point<T> c)
{
    return (Vector2D<T>(a, b).cross(Vector2D<T>(b, c))) > 0;
} 

template<typename T> struct Polygon
{
    vector< Point<T> > P;

    Polygon<T>() {};
    Polygon<T>(const vector< Point<T> > &P): P(P) {};

    int vertexCount() {return P.size();}

    T area()
    {
        T result = 0;
        for(int i = 0; i < vertexCount() - 1; i ++)
        {
            T x1 = P[i].x, y1 = P[i].y;
            T x2 = P[i + 1].x, y2 = P[i + 1].y;
            result += x1 * y2 - x2 * y1;
        }
        result += P[P.size() - 1].x * P[0].y - P[0].x * P[P.size() - 1].y;
        return abs(result) / 2;
    }

    void makeConvexHull()
    {
        if (vertexCount() == 1)
            return;
        sort(P.begin(), P.end());
        vector< Point<T> > result;
        result.push_back(P[0]);
        FOR(i, 1, vertexCount() - 1)
        {
            while(result.size() >= 2 && !cw(result[result.size() - 2], result[result.size() - 1], P[i]))
                result.pop_back();
            result.push_back(P[i]);
        }
        int lock = result.size();
        FORD(i, vertexCount() - 2, 0)
        {
            while(result.size() > lock && !cw(result[result.size() - 2], result[result.size() - 1], P[i]))
                result.pop_back();
            result.push_back(P[i]);
        }
        result.pop_back();
        P.clear();
        P = result;
    }
};