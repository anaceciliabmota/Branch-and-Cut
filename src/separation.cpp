#include "separation.h"


extern vector <vector<int> > MaxBack(double** x, int n){
    pair<vector<vector<int>>, pair<int, int>> p;
    p = internalMaxBack(x, n);
    
    /////execução e teste

    /*double **teste = new double *[4];
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

    pair<vector<vector<int>>, pair<int, int>> pteste;
    pteste = internalMaxBack(teste, 4);
    cout << pteste.second.first << " " << pteste.second.second << endl;*/


    return p.first;
}
extern vector <vector<int> > MinCut(double** x, int n){
    vector<vector<int>> subconjuntos;
    pair<set<int>, set<int> >vertices;

    int v1, v2;

    set<int> s;
    for(int i  = 0; i < n; i++){
        s.insert(i);
    }// s= {0, 1, 2, 3}

    pair<vector<vector<int>>, pair<int, int>> solution = internalMaxBack(x, n);
    
    for(int i = 0; i < solution.first.size(); i++){
        subconjuntos.push_back(solution.first[i]);
    }

    if(solution.second.first < solution.second.second){
        v1 = solution.second.first;
        v2 = solution.second.second;
    }else{
        v2 = solution.second.first;
        v1 = solution.second.second;
    }
   
    vertices.first.insert(v1);
    vertices.first.insert(v2);

    cout << v1 << " " << v2 << endl;
    
    // v1 entra v2 
    while(s.size() > 2){
        cout << "interação 1 do while" << endl; 
        s.erase(v1);
        //essa primeira iteração de cada loop parece desnecessaria
        //tqv
        //funciona mas ta esquisito
        for(int i = v1 -1; i >= 0; i--){
            x[i][v2] += x[i][v1];
            x[i][v1] = numeric_limits<double>::infinity();
        }
        x[v1][v2] = numeric_limits<double>::infinity();
        for(int i = v2 +1 ; i < n; i++){
            x[v2][i] += x[v1][i];
            x[v1][i] = numeric_limits<double>::infinity();
        }
        solution = internalMaxBack(x, n);

        for(int i = 0; i < solution.first.size(); i++){
            subconjuntos.push_back(solution.first[i]);
        }
        if(solution.second.first < solution.second.second){
            v1 = solution.second.first;
            v2 = solution.second.second;
        }else{
            v2 = solution.second.first;
            v1 = solution.second.second;
        }

        if(vertices.first.find(v1) == s.end() && vertices.first.find(v2) == s.end()){
            vertices.second.insert(v1);
            vertices.second.insert(v2);
        }else{
            vertices.first.insert(v1);
            vertices.first.insert(v2);
        }

        break;

    }
  
    return subconjuntos;

}
pair<vector<vector<int>>, pair<int, int>> internalMaxBack(double**x, int n){
    pair<vector<vector<int>>, pair<int, int> > retorno;
    vector<vector<int>> subconjuntos;
   
    set<int> s = {0};
    vector<double> max_back(n, 0);
    int v;  

    double cutmin = xFunction(s, n, x, max_back);
    if(cutmin < 2){
        vector<int> v(s.begin(), s.end());
        subconjuntos.push_back(v);
    }

    double cutval = cutmin;
    set<int> smin = s;


    while(s.size() < n){
        double max_value = -numeric_limits<double>::infinity();
        
        for(int i = 0; i < n; i++){
            if(s.find(i) == s.end()){
               if(max_value + EPSILON < max_back[i]){
                    max_value = max_back[i];
                    v = i;
               }
            }
        }
        if(s.size() == n-1){
            retorno.second.second = v;
            break;  
        }else if(s.size() == n-2){
            retorno.second.first = v;
        }
        s.insert(v);
        cutval = cutval + 2 -2*max_back[v];
        max_back[v] = 0;
        if(cutval + EPSILON < 2){
            vector<int> v(s.begin(), s.end());
            subconjuntos.push_back(v);
        }
        for(int i = 0; i < n; i++){
            if(s.find(i) == s.end()){
                max_back[i] += (i < v ? x[i][v] : x[v][i]);
            }
        }
        if(cutval + EPSILON < cutmin){
            cutmin = cutval;
            smin = s;
        }  
    }
    retorno.first = subconjuntos;

    return retorno;
}


//função que determina a soma dos pesos das arestas que ligam s a complemento de s
//determina o peso do corte
//essa função ja faz o b(v) para todos os v
//retorna pelo ponteiro qual o prox vertice a entrar em s


double xFunction(set<int>& s, int n, double **x, vector<double>& mb){
    double sum = 0;
    for(int i = 0; i < n; i++){
        double max_back = 0; //max_back de v= 2 eh o corte de s com 2 (2 nao pertence a s)
        if(s.find(i) == s.end()){
            //nao ta em s
            for (set<int>::iterator it = s.begin(); it!=s.end(); ++it){
                int j = *it;
                if(i < j){
                    sum += x[i][j];
                    max_back += x[i][j];
                }else{
                    sum += x[j][i];
                    max_back += x[j][i];
                }
            }   
        }
        mb[i] = max_back;
    }
    return sum;
}


