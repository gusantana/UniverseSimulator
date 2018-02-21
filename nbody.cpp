#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>

using namespace std;

ofstream out("nbody_result.txt");


//Estrutura dos corpos
/*
 * Px = Posição em X
 * Py = Posição em y
 * Vx = Vetor em X
 * Vy = Vetor em y
 * m = massa
*/
struct Body{
  long double Px, Py, Vx, Vy, m;
  
  void swap(Body& other){
    std::swap(Px, 	other.Px);
    std::swap(Py, 	other.Py);
    std::swap(Vx, 	other.Vx);
    std::swap(Vy, 	other.Vy);
    std::swap(m, 	other.m);
  }
  
  //O operador >> deve ser usado para ler cada linha do ifstream
  friend istream& operator>>(istream& str, Body& data){
    string line,stmp;
    Body tmp;
    if(getline(str,line)){
      stringstream iss(line);
      getline(iss, stmp, ' ');
      tmp.Px = stold(stmp);
      getline(iss, stmp, ' ');
      tmp.Py = stold(stmp);
      getline(iss, stmp, ' ');
      tmp.Vx = stold(stmp);
      getline(iss, stmp, ' ');
      tmp.Vy = stold(stmp);
      getline(iss, stmp, '\n');
      tmp.m = stold(stmp);
      
      data.swap(tmp);
    }
    return str;
  }
  
  //Já o << é para escrita
  friend ostream& operator<<(ostream& str, Body& data){
    str << data.Px << " " << data.Py << " " << data.m << "\n"; 
        
    return str;
  }
  
};


//Função que recbe o nome da entrada e retorna um vector com os corpos
vector<Body> loadBodys(string file){
  Body tmp;
  string line;
  int n;
  long double universe;
  vector<Body> bodys;
  ifstream readFile(file);
  
  getline(readFile, line);
  n = stoi(line);
  cout << n << "\n";
  
  getline(readFile, line);
  universe = stold(line);
  cout << universe << "\n";
  
  for(int i = 0;i < n; i++){
    readFile >> tmp;
    bodys.push_back(tmp);
  }
  
  out << bodys.size() << "\n";
  out << universe << "\n";
  
  return bodys;
}

//função para gravar os resultados no ofstream "out"
void writeResult(vector<Body> &bodys){
  for(int i = 0; i<bodys.size(); i++){
    out << bodys[i];
  }
  out << "\n";
}

int main(){
  vector<Body> bodys;
  bodys = loadBodys("galaxy.txt");
  
  //Aqui fica o cálculo a ser feito. A cada iteração a função writeResult deve ser executada para gravar os resultados parciais
  
  cout << std::scientific;
  for(int i=0; i<bodys.size();i++){
    cout << bodys[i].Px << "  ";
    cout << bodys[i].Py << "  ";
    cout << bodys[i].Vx << "  ";
    cout << bodys[i].Vy << "  ";
    cout << bodys[i].m << "\n";
  }
}
