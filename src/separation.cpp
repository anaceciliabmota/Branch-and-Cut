#include "separation.h"

/// ajeitar o cont

extern vector <vector<int> > MaxBack(double** x, int n){
    pair<vector<vector<int>>, pair<int, int>> p;
    double weight;

    vector<unordered_set<int>> vertices(n);

    for(int i = 0; i < n; i++){
        unordered_set<int> setinho;
        setinho.insert(i);
        vertices[i] = setinho;
    }

    p = internalMaxBack(x, n, &weight, vertices, n);
    

    return p.first;
}
extern vector <vector<int> > MinCut(double** x, int n){
    vector<vector<int>> subconjuntos;
    vector<unordered_set<int>> vertices(n);

    for(int i = 0; i < n; i++){
        unordered_set<int> setinho;
        setinho.insert(i);
        vertices[i] = setinho;
    }
    unordered_set<int> best_vertices;

    double weight, best_weight; 

    int v1, v2;

    set<int> s;
    for(int i  = 0; i < n; i++){
        s.insert(i);
    }// s= {0, 1, 2, 3}

    pair<vector<vector<int>>, pair<int, int>> solution = internalMaxBack(x, n, &weight, vertices, n);
    
    cout << "weight: " << weight << endl;
    best_weight = weight;

    double ** x_copy = new double*[n];
    for(int i = 0; i < n; i++){
        x_copy[i] = new double[n];
        for(int j = 0; j < n; j++){
            x_copy[i][j] = x[i][j];
        }
    }

    /*for(int i = 0; i < solution.first.size(); i++){
        subconjuntos.push_back(solution.first[i]);
    }*/

    if(solution.second.first < solution.second.second){
        v1 = solution.second.first;
        v2 = solution.second.second;
    }else{
        v2 = solution.second.first;
        v1 = solution.second.second;
    }
    
    for(int i = 0;i < n; i++){
        cout << "{ " ;
        for(unordered_set<int>::iterator it = vertices[i].begin(); it != vertices[i].end(); it++){
            cout << *it << ", ";
        }
        cout << "} " << endl;
    }
    vertices[v2].merge(vertices[v1]);
    vertices[v1].clear();
    best_vertices = vertices[v2];

    for(int i = 0;i < n; i++){
        cout << "{ " ;
        for(unordered_set<int>::iterator it = vertices[i].begin(); it != vertices[i].end(); it++){
            cout << *it << ", ";
        }
        cout << "} " << endl;
    }

    best_vertices = vertices[v2];

    cout << v1 << " " << v2 << endl;
    
    s.erase(v1);
    int cont = n-1;
    // v1 entra v2 
    while(s.size() > 2){ 

        cout << "size: " << s.size() << endl;
        //essa primeira iteração de cada loop parece desnecessaria
        //tqv
        //funciona mas ta esquisito
        
        for(int i = 0; i < v1; i++){
            x_copy[i][v2] += x_copy[i][v1];
            x_copy[i][v1] = numeric_limits<double>::infinity();
        }

        x_copy[v1][v2] = numeric_limits<double>::infinity();

        for(int i = v2 +1 ; i < n; i++){
            x_copy[v2][i] += x_copy[v1][i];
            x_copy[v1][i] = numeric_limits<double>::infinity();
        }
        for(int i = v1+1; i < v2; i++){
            x_copy[i][v2] += x_copy[v1][i];
            x_copy[v1][i] = numeric_limits<double>::infinity();
        }

        for (int i = 0; i < n; i++)
	    {
            for (int j = 0; j < n; j++)
            {
                cout << x_copy[i][j] << " ";
            }
            cout << endl;
	    }
        solution = internalMaxBack(x_copy, n, &weight, vertices, cont);
       
        cout << "w: " << weight << endl;

        if(weight < best_weight){
            best_weight = weight;
            best_vertices = vertices[v2];
        }

        /*for(int i = 0; i < solution.first.size(); i++){
            subconjuntos.push_back(solution.first[i]);
        }*/
        if(solution.second.first < solution.second.second){
            v1 = solution.second.first;
            v2 = solution.second.second;
        }else{
            v2 = solution.second.first;
            v1 = solution.second.second;
        }
        cout << v1 << " " << v2 << endl;

        vertices[v2].merge(vertices[v1]);
        vertices[v1].clear();

        

        for(int i = 0;i < n; i++){
        cout << "{ " ;
        for(unordered_set<int>::iterator it = vertices[i].begin(); it != vertices[i].end(); it++){
            cout << *it << ", ";
        }
        cout << "} " << endl;
        }

        s.erase(v1);
        if(cont < 0) break;
        cont--;
    }
    vector<int> aux(best_vertices.begin(), best_vertices.end());
    subconjuntos.push_back(aux);
    return subconjuntos;
}
pair<vector<vector<int>>, pair<int, int>> internalMaxBack(double**x, int n, double * weight, vector<unordered_set<int>>& vertices, int cont){
    pair<vector<vector<int>>, pair<int, int> > retorno;
    vector<vector<int>> subconjuntos;
   
    set<int> s = {n-1};
    vector<double> max_back(n, 0);
   
    int v;  

    double cutmin = xFunction(s, n, x, max_back, vertices);
    if(cutmin < 2){
        vector<int> v(s.begin(), s.end());
        subconjuntos.push_back(v);
    }

    double cutval = cutmin;
    set<int> smin = s;

    while(s.size() <= cont){
        double max_value = -numeric_limits<double>::infinity();
        
        for(int i = 0; i < n; i++){
            if(s.find(i) == s.end() && !vertices[i].empty()){
               if(max_value + EPSILON < max_back[i]){
                    max_value = max_back[i];
                    v = i;
               }
            }
        }
        s.insert(v);
        if(s.size() == cont){
            retorno.second.second = v;
            *weight = max_back[v];
            break;  
        }
        if(s.size() == cont-1){
            retorno.second.first = v;
        }
        
        cutval = cutval + 2 -2*max_back[v];
        max_back[v] = 0;
        if(cutval + EPSILON < 2){
            vector<int> v(s.begin(), s.end());
            subconjuntos.push_back(v);
        }
        for(int i = 0; i < n; i++){
            if(s.find(i) == s.end() && !vertices[i].empty()){
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

double xFunction(set<int>& s, int n, double **x, vector<double>& mb, vector<unordered_set<int>>& vertices){
    double sum = 0;
    for(int i = 0; i < n; i++){
        double max_back = 0; //max_back de v = 2 eh o corte de s com 2 (2 nao pertence a s)
        if(s.find(i) == s.end() && !vertices[i].empty()){
            //nao ta em s
            for (set<int>::iterator it = s.begin(); it != s.end(); ++it){
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


