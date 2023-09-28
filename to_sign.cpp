#include <iostream>
#include <fstream>
// #include <Signer.h>

using std::cout;
using std::endl;

int main(int argc, char* argv[]) {

    if (argc > 3) {
        cout << "Bad usage!" << '\n';
        cout << "Leia a documentação" << std::endl;
        return 1;
    }

    std::ifstream mlt_keys("mlt_keys", std::ios::in);

	if (!mlt_keys) {
		cout << "Arquivo mlt_keys não encontrado." << endl;
		return 1;
	}

    if (argc == 1) {
        // Se algum operador já tiver assinado mas não completamente.
        cout << "Faltam x assinaturas." << endl;
        // Se não tiver nenhuma assinatura:
        cout << "Nenhuma assinatura coletada ainda." << endl;
        //Se todos os operadores já tiverem assinado:
        cout << "Todas as assinaturas foram coletadas!" << endl;
        return 0;
    }
    
    std::string argv1 = argv[1];
    if (argv1 == "-a" || argv1 == "--add") {
        // Para assinar documentos em cima do to_sign
        cout << "Assinado com sucesso!" << endl;
    } else {
        // Se der erro na hora de executar.
        cout << "Bad usage!" << '\n';
        cout << "Leia a documentação";
    }

    return 0;
}