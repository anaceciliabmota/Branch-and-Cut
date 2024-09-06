#include <separation.h>

int main(){
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

    vector<vector<int>> teste = MinCut(teste, 4);
}