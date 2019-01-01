// standard includes
#include <iostream>

using namespace std;

// custom includes
#include "comp_geo.h"

// ====================================================================

void init_points(Point points[], int num_points)
{
    points[0].x =  0.0;
    points[0].y =  0.0;

    points[1].x =  0.0;
    points[1].y = 10.0;

    points[2].x = 10.0;
    points[2].y = 10.0;

    points[3].x = 10.0;
    points[3].y =  0.0;

    points[4].x =  5.0;
    points[4].y =  5.0;    
}

// ---------------------------------------------------------------------

void init_edges(Edge edges[], int num_edges)
{
    for (int k = 0; k < num_edges; k++) {
        edges[k].point1.x = -1.0;
        edges[k].point1.y = -1.0;

        edges[k].point2.x = -1.0;
        edges[k].point2.y = -1.0;
    }
}

// ---------------------------------------------------------------------

double is_left_of_line(Point p, Point q, Point r)
{
    // determinant
    double det =  (q.x * r.y - r.x * q.y) - (p.x * r.y - r.x * p.y) + (p.x * q.y - q.x * p.y);    
    if (det >= 0) return true;
    else return false;
}

// ---------------------------------------------------------------------

int convex_hull(Point points[], int num_points, Edge edges[], int num_edges)
{
    int edge_num = 0; // how many edges of the convex hull have we found?
    
    for (int i = 0; i < num_points; i++) {
        for (int j = 0; j < num_points; j++) {
            
            if (i != j) {
            
                bool valid = true;
                for (int k = 0; k < num_points; k++) {
                    
                    if (k != i && k != j) {
                        cout << "\ti = " << i << "  j = " << j << "  k = " << k;
                        if (is_left_of_line(points[i], points[j], points[k])) {
                            valid = false;
                            cout << "  (invalid)\n";
                            // break;
                        } else { cout << "  (valid)\n";}
                        
                    }
                }
                
                if (valid) {
                    edges[edge_num].point1 = points[i];
                    edges[edge_num].point2 = points[j];
                    edge_num++;
                    cout << "\tEDGE FOUND\n";
                }
                cout << "\n";
            } 
        }
    }
    
    return edge_num;
}

// ---------------------------------------------------------------------

void print_edges(Edge edges[], int num_edges, Point points[])
{
 
    for (int k = 0; k < num_edges; k++) {
        cout << "Edge " << k+1 << ":\n";
        cout << "\t";
        cout << "(" << edges[k].point1.x << "," << edges[k].point1.y << ")\t";
        cout << "(" << edges[k].point2.x << "," << edges[k].point2.y << ")\n";
    }
    cout << "\n";
}
// ====================================================================

int main()
{    
    Point *points = NULL;
    int num_points = 5;
    points = new Point[num_points];
    init_points(points, num_points);
    
    for (int k = 0; k < num_points; k++) {
        
        cout << "Point " << k << "\n";
        cout << "\tx = " << points[k].x << "\n";
        cout << "\ty = " << points[k].y << "\n\n";
    }
    
    Edge *edges = NULL;
    int num_edges = num_points;
    edges = new Edge[num_edges];
    init_edges(edges, num_edges);

    int num_edges_found = 0;
    num_edges_found = convex_hull(points, num_points, edges, num_edges);

    cout << "\n\n# of edges found = " << num_edges_found << "\n\n";
    print_edges(edges, num_edges_found, points);
    
}
