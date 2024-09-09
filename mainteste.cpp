#include "separation.h"
#include "dataFunction.h"

int main(int argc, char ** argv){
    Data * data = new Data(argc, argv[1]);
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
	
	return 0;
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