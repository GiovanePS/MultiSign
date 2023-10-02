#include <iostream>
#include <fstream>
#include <vector>
#include <RSAPublicKey.h>
#include <Signer.h>

using std::cout;
using std::endl;
using std::cerr;

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

    /*
        Parte de desencriptar arquivo.
    */

    //PARTE DE LEITURA DE MLT_KEYS.
    std::vector<RSAPublicKey> public_keys;
    bool append_it = false;
    bool in_keys_space = true;
    bool is_hash = false;
    std::string hash;
    std::string public_keyString;
    std::string line;
    while (getline(mlt_keys, line)) {
        if (line == "END KEYS") {
            in_keys_space = false;
        }

        if (line == "HASH") {
            is_hash = true;
            continue;
        }
        
        if (in_keys_space) {
            if (line == "-----BEGIN PUBLIC KEY-----") {
                append_it = true;
            }

            if (line == "-----END PUBLIC KEY-----") {
                public_keyString += line;
                public_keys.push_back(RSAPublicKey(public_keyString));
                public_keyString.clear();
                append_it = false;
            }
                
            if (append_it) {
                public_keyString += line + '\n';
            }
        }

        if (is_hash) {
            hash = line;
        }
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

    //EDIÇÃO DE MLT_KEYS PARA REMOVER UMA PUBLIC KEY E ADICIONAR A ASSINATURA.

    return 0;
}