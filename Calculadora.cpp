#include<iostream>
#include<string>



class Calculadora{

    public:

    

        Calculadora(double PrimerNumero, double SegundoNumero): PrimerNumero(PrimerNumero), SegundoNumero(SegundoNumero) {}

    

        void Suma() const{

            double resultado=PrimerNumero+SegundoNumero;
	        std::cout<<"La suma de "<<PrimerNumero<<" y "<<SegundoNumero<<" es igual a: "<<resultado<<std::endl;

        }

        void Resta() const{

            double resultado=PrimerNumero-SegundoNumero;
	        std::cout<<"La resta de "<<PrimerNumero<<" y "<<SegundoNumero<<" es igual a: "<<resultado<<std::endl;

        }

        void Multiplicación() const{

            double resultado=PrimerNumero*SegundoNumero;
	        std::cout<<"La multiplicación de "<<PrimerNumero<<" y "<<SegundoNumero<<" es igual a: "<<resultado<<std::endl;

        }


    

        
    protected:

        double PrimerNumero;
        double SegundoNumero;


};




int main(){
double PrimerNumero;
double SegundoNumero;

std::cout<<"Ingrese el primer numero entero"<<std::endl;
std::cin>>PrimerNumero;
std::cout<<"Ingrese el segundo número entero"<<std::endl;
std::cin>>SegundoNumero;

Calculadora Suma( PrimerNumero, SegundoNumero);
Calculadora Resta( PrimerNumero, SegundoNumero);
Calculadora Multiplicacion( PrimerNumero, SegundoNumero);

int menu() {
    int opc;
    cout << "Bienvenido a la calculadora de suma, resta y multiplicacion" << endl;
    cout << "1. Suma\n2. Resta\n3. Multiplicacion\n4." << endl;
    cin >> opc;
    return opc;

int opcion = menu();

    switch (opcion){

        case 1:{

            

        }





    }
} 
}