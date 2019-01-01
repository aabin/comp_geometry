
// ====================================================================
//
// Program: slow_convex_hull.cpp
//
//      Finds the convex hull for a set of 2D points
//
//      ( slow naive version from:                               )
//      (                                                        )
//      (           Computational Geometry, 3rd edition          )
//      (           authors: de Berg, Cheong, Dreveld, Overmars  )
//      (           chapter 1, pages 3-4                         )
//
// ====================================================================
//
// Change Log:
//
//    1/1/19 (pf)  - created
//
//
// (pf) Patrick Flynn
//
// ====================================================================

// standard includes
#include <iostream>

// custom includes
#include "comp_geo.h"

using namespace std;

// ====================================================================

enum  Output_level { NONE, NORMAL, HIGH, HIGHEST };
const Output_level OUTPUT_LEVEL = HIGHEST;

// ====================================================================

// Creates points (for testing)

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

// Initializes edges (to "no edges" value)

void init_edges(Edge edges[], int num_edges)
{
    const int INIT_VALUE = -1.0;
    
    for (int k = 0; k < num_edges; k++) {
        edges[k].point1.x = INIT_VALUE;
        edges[k].point1.y = INIT_VALUE;

        edges[k].point2.x = INIT_VALUE;
        edges[k].point2.y = INIT_VALUE;
    }
}

// ---------------------------------------------------------------------

// Prints points

void print_points(Point points[], int num_points)
{
    cout << endl;
    for (int k = 0; k < num_points; k++) {
        
        cout << "Point " << k << ":  ";
        cout << "\t (" << points[k].x << ", " << points[k].y << ")" << endl;
    }
    cout << endl;
}

// ---------------------------------------------------------------------

// Prints edges

void print_edges(Edge edges[], int num_edges, Point points[])
{
 
    for (int k = 0; k < num_edges; k++) {
        
        cout << "Edge " << k+1 << ":" << endl;
        cout << "\t";
        cout << "(" << edges[k].point1.x << "," << edges[k].point1.y << ")\t";
        cout << "(" << edges[k].point2.x << "," << edges[k].point2.y << ")" << endl;
    }
}

// ---------------------------------------------------------------------

// Determines if point r is to the left of the line through pq

bool is_left_of_line(Point p, Point q, Point r)
{
    //               | 1 p_x p_y |
    // determinant:  | 1 q_x q_y |
    //               | 1 r_x r_y |
    
    double det =  (q.x * r.y - r.x * q.y) - (p.x * r.y - r.x * p.y) + (p.x * q.y - q.x * p.y);

    return det >= 0;
    
    // if (det >= 0) return true;
    // else return false;
}

// ---------------------------------------------------------------------

// Finds the convex hull of a set of points

int convex_hull(Point points[], int num_points, Edge edges[], int num_edges)
{
    int edge_count = 0; // how many edges of the convex hull have we found?
    
    for (int i = 0; i < num_points; i++) {
        for (int j = 0; j < num_points; j++) {
            
            if (i != j) {
            
                bool valid = true;
                for (int k = 0; k < num_points; k++) {
                    
                    if (k != i && k != j) {
                        
                        if (OUTPUT_LEVEL > NORMAL) 
                            cout << "\ti = " << i << "  j = " << j << "  k = " << k;
                        
                        if (is_left_of_line(points[i], points[j], points[k])) {
                            valid = false;
                            if (OUTPUT_LEVEL > NORMAL) {
                                cout << "  (invalid)" << endl;
                                if (OUTPUT_LEVEL < HIGHEST) break; // this one affects computation
                            }
                        } else 
                            if (OUTPUT_LEVEL > NORMAL) cout << "  (valid)" << endl;
                        
                    }
                }
                
                if (valid) {
                    edges[edge_count].point1 = points[i];
                    edges[edge_count].point2 = points[j];
                    edge_count++;
                    
                    if (OUTPUT_LEVEL > NORMAL) cout << "\tEDGE FOUND" << endl;
                }
                
                if (OUTPUT_LEVEL > NORMAL) cout << endl;
            } 
        }
    }
    
    return edge_count;
}

// ====================================================================

int main()
{
    // points to find convex hull of
    Point *points = NULL;
    int num_points = 5;
    points = new Point[num_points];
    init_points(points, num_points);
    
    if (OUTPUT_LEVEL > NORMAL) print_points(points, num_points);

    // will contain edges of the convex hull
    Edge *ch_edges = NULL;
    // max # of edges in convex hull is number of points
    int num_max_edges = num_points;
    ch_edges = new Edge[num_max_edges];
    init_edges(ch_edges, num_max_edges);

    // find convex hull
    int num_edges_found = 0;
    num_edges_found = convex_hull(points, num_points, ch_edges, num_max_edges);

    if (OUTPUT_LEVEL > NONE) 
        cout << endl << "# of edges found = " << num_edges_found << endl << endl;
    
    if (OUTPUT_LEVEL > NORMAL) {
        print_edges(ch_edges, num_edges_found, points);
        cout << endl;
    }
}
