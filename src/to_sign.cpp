#include <iostream>
#include <fstream>
#include <vector>
#include <ByteArray.h>
#include <RSAPublicKey.h>
#include <RSAPrivateKey.h>
#include <MessageDigest.h>
#include <Signer.h>

using std::cout;
using std::endl;
using std::cerr;

int main(int argc, char* argv[]) {

    if (argc != 1 && argc != 3) {
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
    std::vector<string> vectorStrPublicKeys;
    std::vector<RSAPublicKey> public_keys;
    bool append_it = false;
    bool in_keys_space = true;
    bool is_hash = false;
    std::string docHash;
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
            } else if (line == "-----END PUBLIC KEY-----") {
                public_keyString += line;
                vectorStrPublicKeys.push_back(public_keyString);
                public_keys.push_back(RSAPublicKey(public_keyString));
                public_keyString.clear();
                append_it = false;
            }

            if (append_it) {
                public_keyString += line + '\n';
            }
        }

        if (is_hash) {
            docHash = line;
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
        std::ifstream filePrivateKey(argv[2], std::ios::in);

        if (!filePrivateKey) {
            cerr << "Erro ao encontrar o arquivo da chave privada." << endl;
            return 1;
        }

        std::string privateKeyStr;
        std::string line;
        while (getline(filePrivateKey, line)) {
            privateKeyStr += line + '\n';
        }

        RSAPrivateKey privateKey = RSAPrivateKey(privateKeyStr);

        bool found = false;
        ByteArray hash = std::string(docHash);
        ByteArray assinatura = Signer::sign(privateKey, hash, MessageDigest::SHA256);
        cout << hash.toString() << endl;
        for (unsigned int i = 0; i < public_keys.size(); i++) {
            // ESTÁ TUDO DANDO TRUE: RESOLVER
            cout << public_keys[i].getPemEncoded();
            cout << Signer::verify(public_keys[i], assinatura, hash, MessageDigest::SHA256) << endl;
            if (Signer::verify(public_keys[i], assinatura, hash, MessageDigest::SHA256)) {
                cout << "Assinado com sucesso!" << endl;
                found = true;
                break;
            }
        }

        if (!found) {
            cerr << "Chave privada não corresponde a nenhuma chave privada presente em mlt_keys." << endl;
            return 1;
        }
    } else {
        cout << "Bad usage!" << '\n';
        cout << "Leia a documentação";
    }

    //EDIÇÃO DE MLT_KEYS PARA REMOVER UMA PUBLIC KEY E ADICIONAR A ASSINATURA.

    return 0;
}