#include <ilcplex/ilocplex.h>
#include <vector>
#include <iostream>
#include "separation.h"
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For seeding rand()
#include <iomanip>  // For setting precision



ILOSTLBEGIN


double** generateSymmetricGraph(int n, double min_weight , double max_weight ) ;

void printGraph(double** graph, int n);

int main() {
    // Number of nodes in the graph
    int n = 100;

    // Define the adjacency matrix (capacities)
    double** x = generateSymmetricGraph(n, 0.0, 2.0);
    printGraph(x, n);

    int v1, v2;

    vector<vector<int>> testinho = MinCut(x, n, &v1, &v2);

    
    

    // Environment and model
    IloEnv env;
    try {
        IloModel model(env);

        // Binary decision variables for y[i]
        IloBoolVarArray y(env, n);

        IloArray<IloBoolVarArray> z(env, n);
        
        // Initialize each row of the 2D array
        for (int i = 0; i < n; i++) {
            z[i] = IloBoolVarArray(env, n);  // Each row has 'cols' boolean variables
        }

        // Add variables to the model (optional, based on constraints or objective function)
        /*for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                model.add(z[i][j]);  // Add variable z[i][j] to the model
            }
        }*/

        // Objective function: Minimize the cut value
        IloExpr obj(env);
        for (int i = 0; i < n; ++i) {
            for (int j = i+1; j < n; ++j) {
                if (i != j && x[i][j] > 0) {
                    // Only add if capacity exists (i.e., x[i][j] > 0)
                    obj += x[i][j] * (z[i][j]);
                }
            }
        }

        model.add(IloMinimize(env, obj));
        obj.end();

        // Constraints:
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                model.add(z[i][j] >= y[i]- y[j]);
                model.add(z[i][j] >= y[j]- y[i]);

                model.add(z[i][j] <= y[i] + y[j]);
                model.add(z[i][j] <= 2 - y[i] - y[j]);
            }
        }
        IloExpr xsum(env);
        for(int i = 0; i < n; i++){
            xsum+=y[i];
        }
        model.add(xsum>=1);
         model.add(xsum<=n-1);
        // Solve the model
        IloCplex cplex(model);
        cplex.setOut(env.getNullStream()); // Suppress output for cleaner console

        if (cplex.solve()) {
            std::cout << "Minimum Cut Value: " << cplex.getObjValue() << std::endl;

            // Output the solution
            std::cout << "Partition (y[i]):" << std::endl;
            for (int i = 0; i < n; ++i) {
                std::cout << "y[" << i << "] = " << cplex.getValue(y[i]) << std::endl;
            }
        } else {
            std::cout << "No solution found!" << std::endl;
        }

    } catch (IloException& e) {
        std::cerr << "Error: " << e << std::endl;
    } catch (...) {
        std::cerr << "Unknown exception caught!" << std::endl;
    }

    // Clean up environment
    env.end();

    
    return 0;
}

void printGraph(double** graph, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << std::fixed << std::setprecision(2) << graph[i][j] << ",";
        }
        std::cout << std::endl;
    }
}

double** generateSymmetricGraph(int n, double min_weight, double max_weight ) {
    // Allocate memory for the matrix
    double** graph = new double*[n];
    for (int i = 0; i < n; i++) {
        graph[i] = new double[n];
    }

    // Seed the random number generator
    std::srand(std::time(nullptr));

    // Fill the matrix with random weights
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (i == j) {
                // Set diagonal to 0 (no self-loops)
                graph[i][j] = 0.0;
            } else {
                // Generate a random weight between min_weight and max_weight
                double weight = min_weight + (max_weight - min_weight) * (rand() / (double)RAND_MAX);
                graph[i][j] = weight;
                graph[j][i] = weight;  // Ensure the matrix is symmetric
            }
        }
    }

    return graph;
}
/*


	double **teste = new double *[4];
	for (int i = 0; i < 4; i++)
	{
		teste[i] = new double[4];
		for (int j = 0; j < 4; j++)
		{
			teste[i][j] = 0;
		}
	}

    teste[0][1] = 20;
    teste[0][2] = 25;
    teste[1][2] = 8;
    teste[1][3] = 10;
    teste[2][3] = 18;
	*/

/*Data * data = new Data(argc, argv[1]);
    data->readData();

	int n = data->getDimension();
    
	double **cost = new double *[data->getDimension()];
	for (int i = 0; i < data->getDimension(); i++)
	{
		cost[i] = new double[data->getDimension()];
		for (int j = 0; j < data->getDimension(); j++)
		{
			cost[i][j] = data->getDistance(i, j);
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << cost[i][j] << " ";
		}
		cout << endl;
	}

    vector<vector<int>> testinho = MinCut(cost, n);
	for(int i = 0; i < testinho[0].size(); i++){
		cout << testinho[0][i] << " ";
	}
	*/

/*    double **teste = new double *[8];
	for (int i = 0; i < 8; i++)
	{
		teste[i] = new double[8];
		for (int j = 0; j < 8; j++)
		{
			teste[i][j] = 0;
		}
	}

    teste[0][1] = 2;
    teste[0][4] = 3;
    teste[1][4] = 2;
    teste[1][2] = 3;
    teste[1][5] = 2;
    teste[2][3] = 4;
    teste[2][6] = 2;
    teste[3][6] = 2;
    teste[3][7] = 2;
    teste[4][5] = 3;
    teste[5][6] = 1;
    teste[6][7] = 3;

    vector<vector<int>> testinho = MinCut(teste, 8);
	for(int i = 0; i < testinho[0].size(); i++){
		cout << testinho[0][i] << " ";
	}
*/
/*
0.00 0.59 1.76 1.50 0.33 1.82 1.53 0.85 
0.59 0.00 0.71 0.70 1.46 1.32 0.25 0.59 
1.76 0.71 0.00 1.93 0.23 0.10 0.89 1.22 
1.50 0.70 1.93 0.00 1.70 0.24 0.65 0.71 
0.33 1.46 0.23 1.70 0.00 0.76 0.29 0.03 
1.82 1.32 0.10 0.24 0.76 0.00 1.28 0.29 
1.53 0.25 0.89 0.65 0.29 1.28 0.00 1.46 
0.85 0.59 1.22 0.71 0.03 0.29 1.46 0.00 
*/