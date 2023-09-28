#include <iostream>

int main(int argc, char* argv[]) {

    std::string argumento2;

    if (argc != 1) {
        argumento2 = argv[1];
    }

    if (argc == 1) {
        // Se não tiver nenhuma assinatura:
        std::cout << "Nenhuma assinatura coletada ainda." << std::endl;
    } else if (argumento2 == "-a" || argumento2 == "--add") {
        // Para assinar documentos em cima do to_sign
    } else {
        // Se der erro na hora de executar.
        std::cout << "Bad usage!" << std::endl;
    }

    return 0;
}