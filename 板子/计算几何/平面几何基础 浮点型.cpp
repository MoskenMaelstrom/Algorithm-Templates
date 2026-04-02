
//这是平面几何基础内容，包括：
//法向量，极角，点积，叉积，模长，向量单位化，计算夹角，旋转向量
//两直线交点，两直线是否相交
//点到直线距离，点到线段最短距离，点到直线投影坐标，点是否在线段上
//计算三点构成的平行四边形面积，计算多边形面积，点与多边形关系

const double eps = 1e-9;
const double PI = acosl(-1.0);

double Acos(double x) {
	if(x < -1) return PI;
	if(x > 1) return 0;
	return acosl(x);
};

int sign(double x) {
    if (fabs(x) < eps) return 0;
    return x < 0 ? -1 : 1;
}

int cmp(double x, double y) {
    if (fabs(x - y) < eps) return 0;
    return x < y ? -1 : 1;
}

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    
    Point operator+(const Point& b) const { return Point(x + b.x, y + b.y); }
    Point operator-(const Point& b) const { return Point(x - b.x, y - b.y); }
    Point operator*(double k) const { return Point(x * k, y * k); }
    Point operator/(double k) const { return Point(x / k, y / k); }
    
    bool operator==(const Point& b) const { 
        return cmp(x, b.x) == 0 && cmp(y, b.y) == 0; 
    }
    
    bool operator<(const Point& b) const {
        int c = cmp(x, b.x);
        if (c != 0) return c == -1; 
        return cmp(y, b.y) == -1;   
    }
};
typedef Point Vector;

// ========================================================================

double dot(Vector a, Vector b) {
    return a.x * b.x + a.y * b.y;
}

double cross(Vector a, Vector b) {
    return a.x * b.y - b.x * a.y;
}

// 法向量
Vector normal(Vector a) { 
    return Vector(-a.y, a.x);
}

// 求向量的极角
double p_angle(Vector a) {
    return atan2(a.y, a.x);
}

// 极角排序
bool p_cmp(const Vector& a, const Vector& b) {
    int ha = (a.y > 0 or a.y == 0 and a.x > 0);
    int hb = (b.y > 0 or b.y == 0 and b.x > 0);
    if (ha != hb) return ha < hb;
    int c = cross(a, b);
    return c > 0;
}

// 获取向量的模长
double get_length(Vector a) {
    return hypot(a.x, a.y); 
}

// 将向量单位化
Vector unit(Vector a) {
    double l = get_length(a);
    if (sign(l) == 0) return a; // 防止除以 0 的情况
    return a / l;
}

// 计算两个非零向量的夹角
// 返回值：弧度制，范围 [0, PI]
double get_angle_robust(Vector a, Vector b) {
    return fabs(atan2(cross(a, b), dot(a, b))); 
}

// 向量 a 逆时针旋转 angle 角度 (弧度制)
Vector rotate(Vector a, double angle) {
    double c = cos(angle), s = sin(angle);
    return Vector(a.x * c - a.y * s, a.x * s + a.y * c);
}

// 计算点 a, b, c 构成的平行四边形有向面积 (以 a 为顶点)
double area(Point a, Point b, Point c) {
    return cross(b - a, c - a);
}

// 1. 判断两直线相交并求交点
// 直线表示形式：参数方程 P = p + v*t 和 Q = q + w*t
// 注意：需保证两直线不平行，即 cross(v, w) != 0
Point get_line_intersection(Point p, Vector v, Point q, Vector w) {
    assert(sign(cross(v, w)) != 0); // 确保直线不平行或共线
    Vector u = p - q;
    double t = cross(w, u) / cross(v, w);
    return p + v * t;
}

// 2. 求点 p 到直线 ab 的垂直距离
double distance_to_line(Point p, Point a, Point b) {
    Vector v1 = b - a; // 直线的方向向量
    Vector v2 = p - a; // a 到 p 的向量
    return fabs(cross(v1, v2) / get_length(v1)); // 面积除以底等于高
}

// 3. 求点 p 到线段 ab 的最短距离
double distance_to_segment(Point p, Point a, Point b) {
    if (a == b) return get_length(p - a); // 线段退化为点
    
    Vector v1 = b - a, v2 = p - a, v3 = p - b;
    // 判断 p 在线段所在直线的投影位置
    if (sign(dot(v1, v2)) < 0) return get_length(v2);   // 投影在端点 a 外侧
    if (sign(dot(v1, v3)) > 0) return get_length(v3);   // 投影在端点 b 外侧
    return distance_to_line(p, a, b);                   // 投影在线段 ab 内部
}

// 4. 求点 p 在直线 ab 上的投影点坐标
Point get_line_projection(Point p, Point a, Point b) {
    Vector v = b - a;
    // 利用点积求出投影长度的比例
    return a + v * (dot(v, p - a) / dot(v, v));
}

// 5. 判断点 p 是否在线段 ab 上
// 注意：该函数假设已知 p、a、b 三点共线，或者在调用前使用了叉积验证共线。
// 判断依据：p 和 a、b 构成的叉积为0（共线），且点积 <= 0（说明 p 在 a 和 b 中间或端点上）。
bool on_segment(Point p, Point a, Point b) {
    return sign(cross(p - a, p - b)) == 0 && sign(dot(p - a, p - b)) <= 0;
}

// 6. 判断两线段 a1a2 和 b1b2 是否相交（严格相交或端点相交）
bool segment_intersection(Point a1, Point a2, Point b1, Point b2) {
    // 步骤一：快速排斥实验 (Bounding Box 检查)
    // 排除两线段外接矩形完全不相交的情况
    if (min(a1.x, a2.x) > max(b1.x, b2.x) || max(a1.x, a2.x) < min(b1.x, b2.x) ||
        min(a1.y, a2.y) > max(b1.y, b2.y) || max(a1.y, a2.y) < min(b1.y, b2.y)) {
        return false;
    }
    
    // 步骤二：跨立实验 (利用叉积判断线段是否在彼此的两侧)
    double c1 = cross(a2 - a1, b1 - a1), c2 = cross(a2 - a1, b2 - a1);
    double c3 = cross(b2 - b1, a1 - b1), c4 = cross(b2 - b1, a2 - b1);
    return sign(c1) * sign(c2) <= 0 && sign(c3) * sign(c4) <= 0;
}

// 求多边形的面积
// 参数：多边形顶点的 vector，需按顺时针或逆时针顺序给出
double polygon_area(const vector<Point>& p) {
    double res = 0;
    int n = p.size();
    for (int i = 0; i < n; i++) {
        res += cross(p[i], p[(i + 1) % n]); // 累加三角形的有向面积
    }
    return fabs(res / 2.0);
}

// 判断点 p 与多边形 poly 的位置关系 (基于射线法/环绕数法)
// 返回值：2 表示点在多边形边界上，1 表示在多边形内部，0 表示在外部
int is_point_in_polygon(Point p, const vector<Point>& poly) {
    int n = poly.size();
    int wn = 0; // Winding Number 环绕数
    for (int i = 0; i < n; i++) {
        Point a = poly[i], b = poly[(i + 1) % n];
        
        // 检查是否在当前边的边界上
        if (on_segment(p, a, b)) return 2; 
        
        // 判断射线向右穿过边的次数
        int k = sign(cross(b - a, p - a));
        int d1 = sign(a.y - p.y);
        int d2 = sign(b.y - p.y);
        
        if (k > 0 && d1 <= 0 && d2 > 0) wn++;      // 逆时针方向穿过射线向上
        if (k < 0 && d2 <= 0 && d1 > 0) wn--;      // 顺时针方向穿过射线向下
    }
    return wn != 0 ? 1 : 0;
}
