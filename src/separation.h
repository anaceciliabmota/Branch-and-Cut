//---------------------------------------------------------------------------

/***************************************************/
/* Functions prototypes by Prof. Anand Subramanian */
/***************************************************/

#ifndef Separation_H
#define Separation_H

//#include <ilcplex/ilocplex.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>
#include <iterator>
#include <pthread.h>
#include <set>
#include <iostream>
#include <unordered_set>

#define EPSILON 0.00000001

using namespace std;

typedef struct{
    vector<int> nodes;
    int id;
    bool is_vertexA;
} vertex_type;

extern vector <vector<int> > MaxBack(double** x, int n);
extern vector <vector<int> > MinCut(double** x, int n);
pair<vector<vector<int>>, pair<int, int>> internalMaxBack(double**x, int n, double * weight, vector<unordered_set<int>>& vertices, int cont);
double xFunction(set<int>& s, int n, double **x, vector<double> & mb, vector<unordered_set<int>>& vertices);
#endif

//---------------------------------------------------------------------------
