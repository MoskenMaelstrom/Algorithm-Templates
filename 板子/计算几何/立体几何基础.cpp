
const double eps = 1e-9;

int sign(double x) {
    if (fabs(x) < eps) return 0;
    return x < 0 ? -1 : 1;
}

int cmp(double x, double y) {
    if (fabs(x - y) < eps) return 0;
    return x < y ? -1 : 1;
}

// ========================================================

struct Point {
    double x, y, z;
    Point(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}

    Point operator+(const Point& b) const { return Point(x + b.x, y + b.y, z + b.z); }
    Point operator-(const Point& b) const { return Point(x - b.x, y - b.y, z - b.z); }
    Point operator*(double k) const { return Point(x * k, y * k, z * k); }
    Point operator/(double k) const { return Point(x / k, y / k, z / k); }

    bool operator==(const Point& b) const { 
        return cmp(x, b.x) == 0 && cmp(y, b.y) == 0 && cmp(z, b.z) == 0; 
    }

    bool operator<(const Point& b) const {
        if (cmp(x, b.x) != 0) return x < b.x;
        if (cmp(y, b.y) != 0) return y < b.y;
        return z < b.z;
    }
};
typedef Point Vector;


// 点积
double dot(Vector a, Vector b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

// 叉积
Vector cross(Vector a, Vector b) {
    return Vector(a.y * b.z - a.z * b.y, 
                    a.z * b.x - a.x * b.z, 
                    a.x * b.y - a.y * b.x);
}

// 向量模长
double get_length(Vector a) {
    return sqrt(dot(a, a));
}

// 向量单位化
Vector unit(Vector a) {
    double l = get_length(a);
    if (sign(l) == 0) return a;
    return a / l;
}

// 两个非零向量的夹角 [0, PI]
double get_angle(Vector a, Vector b) {
    return acos(dot(a, b) / (get_length(a) * get_length(b)));
}

// 混合积 (a * (b x c))：返回由三个向量构成的平行六面体的有向体积
// 若混合积为 0，则说明这三个向量（或四个点）共面
double mix(Vector a, Vector b, Vector c) {
    return dot(a, cross(b, c));
}

// 空间三角形的面积：叉积的模长是平行四边形面积，除以2即为三角形面积
double area_triangle(Point a, Point b, Point c) {
    return get_length(cross(b - a, c - a)) / 2.0;
}

// 四面体体积：混合积的绝对值除以 6
double volume_tetrahedron(Point a, Point b, Point c, Point d) {
    return fabs(mix(b - a, c - a, d - a)) / 6.0;
}

// 直线由一点 p 和 方向向量 v 表示
// 平面由一点 p0 和 法向量 n 表示

// 1. 点 p 到平面 (p0, n) 的距离
double distance_point_to_plane(Point p, Point p0, Vector n) {
    return fabs(dot(p - p0, n)) / get_length(n);
}

// 2. 点 p 在平面 (p0, n) 上的投影点
Point get_plane_projection(Point p, Point p0, Vector n) {
    double d = dot(p - p0, n) / get_length(n); // 有向距离
    return p - unit(n) * d;
}

// 3. 直线 (p1, v) 与平面 (p0, n) 的交点
// 注意：调用前需保证直线不平行于平面，即 sign(dot(v, n)) != 0
Point line_plane_intersection(Point p1, Vector v, Point p0, Vector n) {
    assert(sign(dot(v, n)) != 0);
    double t = dot(p0 - p1, n) / dot(v, n);
    return p1 + v * t;
}

// 4. 点 p 到直线 ab 的垂直距离
double distance_point_to_line(Point p, Point a, Point b) {
    Vector v1 = b - a;
    Vector v2 = p - a;
    // 面积除以底等于高
    return get_length(cross(v1, v2)) / get_length(v1); 
}

// 5. 求点 p 到线段 ab 的最短距离
double distance_point_to_segment(Point p, Point a, Point b) {
    if (a == b) return get_length(p - a);
    Vector v1 = b - a, v2 = p - a, v3 = p - b;
    if (sign(dot(v1, v2)) < 0) return get_length(v2);   // 投影在 a 外侧
    if (sign(dot(v1, v3)) > 0) return get_length(v3);   // 投影在 b 外侧
    return distance_point_to_line(p, a, b);             // 投影在线段上
}

// 6. 求两异面直线 (a, u) 和 (b, v) 之间的最短距离
// u, v 分别为两直线的方向向量

double distance_skew_lines(Point a, Vector u, Point b, Vector v) {
    Vector n = cross(u, v); 
    if (sign(get_length(n)) == 0) {
        // 两直线平行，退化为点到直线的距离
        return distance_point_to_line(a, b, b + v); 
    }
    // 构造一个包含直线 (b, v) 且法向量为 n 的平面，计算点 a 到该平面的距离
    return fabs(dot(a - b, n)) / get_length(n);
}
