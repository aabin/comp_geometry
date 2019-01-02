// ====================================================================
//
// Change Log:
//
//    1/1/19   (pf)  - created: Point, Edge classes
//
//    1/2/19   (pf)  - added PointSet class
//
// (pf) Patrick Flynn
//
// ====================================================================

class Point
{
  public:
    double x, y;
};

class PointSet
{
  public:
    Point *points;
    int num_points;
};

class Edge
{
  public:
    Point point1, point2;
};
