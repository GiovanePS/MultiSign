#include <iostream>

int main(int argc, char* argv[]) {

    if (argc == 1) {
        // Se não tiver nenhuma assinatura:
        std::cout << "Nenhuma assinatura coletada ainda." << std::endl;
        return 0;
    }
    
    std::string argv1 = argv[1];
    if (argv1 == "-a" || argv1 == "--add") {
        // Para assinar documentos em cima do to_sign
        std::cout << "Assinado com sucesso!" << std::endl;
    } else {
        // Se der erro na hora de executar.
        std::cout << "Bad usage!" << '\n';
        std::cout << "Leia a documentação";
    }

    return 0;
}