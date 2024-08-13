#include <iostream>
#include <string>

class Calculadora {
public:
    Calculadora(double PrimerNumero, double SegundoNumero)
        : PrimerNumero(PrimerNumero), SegundoNumero(SegundoNumero) {}

    void Suma() const {
        double resultado = PrimerNumero + SegundoNumero;
        std::cout << "La suma de " << PrimerNumero << " y " << SegundoNumero << " es igual a: " << resultado << std::endl;
    }

    void Resta() const {
        double resultado = PrimerNumero - SegundoNumero;
        std::cout << "La resta de " << PrimerNumero << " y " << SegundoNumero << " es igual a: " << resultado << std::endl;
    }

    void Multiplicacion() const {
        double resultado = PrimerNumero * SegundoNumero;
        std::cout << "La multiplicación de " << PrimerNumero << " y " << SegundoNumero << " es igual a: " << resultado << std::endl;
    }

protected:
    double PrimerNumero;
    double SegundoNumero;
};

int menu() {
    int opc;
    std::cout << "Por favor escoja la operación que desea usar." << std::endl;
    std::cout << "1. Suma\n2. Resta\n3. Multiplicacion\n4. Salir" << std::endl;
    std::cin >> opc;
    return opc;
}

int main() {
    double PrimerNumero;
    double SegundoNumero;

    std::cout << "Bienvenido a la Calculadora de Suma, Resta y Multiplicación, porfavor ingrese los numeros que quiere usar en la calculadora." << std::endl;
    std::cout << "Primer número" << std::endl;
    std::cin >> PrimerNumero;
    std::cout << "Segundo número" << std::endl;
    std::cin >> SegundoNumero;

    Calculadora calculadora(PrimerNumero, SegundoNumero);

    int opcion;
    do {
        opcion = menu();
        switch (opcion) {
            case 1:
                calculadora.Suma();
                break;
            case 2:
                calculadora.Resta();
                break;
            case 3:
                calculadora.Multiplicacion();
                break;
            case 4:
                std::cout << "Gracias por usarme." << std::endl;
                break;
            default:
                std::cout << "Opción no válida" << std::endl;
                break;
        }
    } while (opcion != 4);

    return 0;
}
