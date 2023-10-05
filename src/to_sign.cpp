#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ByteArray.h>
#include <RSAPublicKey.h>
#include <RSAPrivateKey.h>
#include <MessageDigest.h>
#include <Signer.h>

using std::cout;
using std::endl;
using std::cerr;

std::string hexValueInByteArray(std::string);

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
        Parte de desencriptar mlt_keys.
    */

    // Parte de leitura de mlt_keys.
    std::vector<RSAPublicKey*> public_keys;
    std::vector<string> names;
    std::vector<string> assinaturas_names;
    std::vector<ByteArray*> assinaturas;
    bool in_keys_space = true;
    bool in_names_space = false;
    bool is_hash = false;
    bool append_it = false;
    bool in_signs = false;
    bool troca = true;
    std::string docHash;
    std::string public_keyString;
    std::string line;
    while (getline(mlt_keys, line)) {
        if (line == "END KEYS") {
            in_keys_space = false;
        }

        if (line == "END NAMES") {
            in_names_space = false;
        }

        if (line == "NAMES") {
            in_names_space = true;
            continue;
        }

        if (line == "ASSINATURAS") {
            in_signs = true;
            continue;
        }

        if (line == "HASH") {
            is_hash = true;
            in_signs = false;
            continue;
        }
        
        if (in_keys_space) {
            if (line == "-----BEGIN PUBLIC KEY-----") {
                append_it = true;
            } else if (line == "-----END PUBLIC KEY-----") {
                public_keyString += line + '\n';
                RSAPublicKey* publicKey = new RSAPublicKey(public_keyString);
                public_keys.push_back(publicKey);
                public_keyString.clear();
                append_it = false;
            }

            if (append_it) {
                public_keyString += line + '\n';
            }
        }

        if (in_names_space) {
            names.push_back(line);
        }

        if (in_signs) {
            if (troca) {
                assinaturas_names.push_back(line);
                troca = false;
            } else {
                ByteArray* assinaturaAtual = new ByteArray(hexValueInByteArray(line));
                assinaturas.push_back(assinaturaAtual);
                troca = true;
            }
        }

        if (is_hash) {
            docHash = line;
        }
    }

    mlt_keys.close();
    size_t public_keys_length = public_keys.size();
    size_t names_length = names.size();
    size_t assinaturas_length = assinaturas.size();

    if (argc == 1) {
        if (public_keys_length) {
            cout << "Faltam as assinaturas de:" << '\n';
            for (size_t i = 0; i < names_length; i++) {
                std::cout << names[i] << '\n';
            }
        } else {
            cout << "Todas as assinaturas foram coletadas!" << '\n';
            cout << "Assinaturas:" << '\n';
            for (size_t i = 0; i < assinaturas_length; i++) {
                cout << assinaturas_names[i] << '\n';
                cout << assinaturas[i]->toHex() << '\n';
            }
        }
        return 0;
    }

    string subjNameFound;
    ByteArray hash = hexValueInByteArray(docHash);
    ByteArray assinatura;
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
        bool verify;
        bool found = false;
        assinatura = Signer::sign(privateKey, hash, MessageDigest::SHA256);

        for (size_t i = 0; i < public_keys_length; i++) {
            verify = Signer::verify(*(public_keys[i]), assinatura, hash, MessageDigest::SHA256);
            if (verify) {
                cout << "Assinado com sucesso!" << endl;
                public_keys.erase(public_keys.begin()+i);
                subjNameFound = names[i];
                names.erase(names.begin()+i);
                found = true;
                break;
            }
        }

        if (!found) {
            cerr << "Chave privada não corresponde a nenhuma chave pública presente em mlt_keys." << endl;
            return 1;
        }
    } else {
        cout << "Bad usage!" << '\n';
        cout << "Leia a documentação";
        return 1;
    }


    // Gerando um novo mlt_keys com a nova assinatura e a remoção da public key da assinatura.
    std::fstream mlt_keys_output("mlt_keys", std::ios::out);
    public_keys_length = public_keys.size();
    if (public_keys_length) {
        for (size_t i = 0; i < public_keys_length; i++) {
            mlt_keys_output << public_keys[i]->getPemEncoded();
        }
        mlt_keys_output << "END KEYS" << '\n';
    }

    names_length = names.size();
    if (names_length) {
        mlt_keys_output << "NAMES" << '\n';
        for (size_t i = 0; i < names_length; i++) {
            mlt_keys_output << names[i] << '\n';
        }
        mlt_keys_output << "END NAMES" << '\n';
    }
    
    mlt_keys_output << "ASSINATURAS" << '\n';
    assinaturas.push_back(&assinatura);
    assinaturas_names.push_back(subjNameFound);
    assinaturas_length = assinaturas.size();
    for (size_t i = 0; i < assinaturas_length; i++) {
        mlt_keys_output << assinaturas_names[i] << '\n';
        mlt_keys_output << (*assinaturas[i]).toHex() << '\n';
    }

    mlt_keys_output << "HASH" << '\n';
    mlt_keys_output << hash.toHex() << endl;

    /*
        Parte de encriptar mlt_keys novamente.
    */

    mlt_keys_output.close();

    return 0;
}


std::string hexValueInByteArray(std::string hexVal) {
    std::string hexPair;
    std::string hexAppend;
    char caractere;
    size_t hexVal_length = hexVal.size();
    for (size_t i = 0; i < hexVal_length; i += 2) {
        hexPair = hexVal.substr(i, 2);
        caractere = strtoul(hexPair.c_str(), NULL, 16);
        hexAppend += caractere;
    }

    return hexAppend;
}