
// ====================================================================
//
// Program: slow_convex_hull.cpp
//
//      Finds the convex hull for a set of 2D points
//
//          ./slow_convex_hull input_filename output_filename
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
//    1/1/19   (pf)  - created
//
//    1/2/19   (pf)  - added read_in_points() to read in points from a file 
//                   - added use of PointSet class to store info read in from
//                     file
//
// (pf) Patrick Flynn
//
// ====================================================================

// standard includes
#include <iostream>
#include <fstream>
#include <string>

// custom includes
#include "comp_geo.h"

using namespace std;

// ====================================================================

enum  Output_level { NONE, NORMAL, HIGH, HIGHEST };
const Output_level OUTPUT_LEVEL = HIGHEST;

// ====================================================================

// Reads in input points from a file

PointSet read_in_points(char *inputfile)
{    
    PointSet pset;
    int num_points = 0;;
    double px = -1.0;
    double py = -1.0;

    ifstream point_file(inputfile);
    if (point_file.is_open())
    {
        point_file >> num_points;
        pset.num_points = num_points;
        pset.points = new Point[num_points];
        
        for (int k = 0; k < num_points; k++) {
            point_file >> px >> py;
            pset.points[k].x = px;
            pset.points[k].y = py;
        }
        
        point_file.close();
 
    } else cout << "Unable to open file"; 

  return pset;
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

int main(int argc, char* argv[])
{
    char *inputfile  = argv[1];
    char *outputfile = argv[2];
    
    PointSet pset = read_in_points(inputfile);
    
    Point *points =  pset.points;
    int num_points = pset.num_points;
    
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
