#include<iostream>
#include<cstdlib> // Interactua con el sistema
#include<cmath> // Funciones matematicas (Calculo)
#include<fstream> //Manipula archivos externos

double caidalibre(double pos_ini, double t){
    double g=9.77; //Aceleración gravitacional terrestre
    return {pos_ini-0.5*g*pow(t,2)};
}

int main(){
    
    int i;
    std::ofstream archivosalida("datos.txt");
        //Validar que el archivo si se abre
        if(!archivosalida.is_open()){
            std::cerr<<"Error el archivo no abre."<<std::endl;
        }
    // Escribir archivo
    archivosalida<<"#Datos caida libre 23/02/2024 :: 3:55 P-M"<<std::endl;

    for(i=0;i<=10;i++){
        std::cout<<i<<" "<<caidalibre(200,i)<<std::endl;
        archivosalida<<i<<" "<<caidalibre(200,i)<<std::endl;
    }
    archivosalida.close();
    system("gnuplot automatico.gp");
}
