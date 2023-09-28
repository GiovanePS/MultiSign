#include <iostream>
#include <fstream>
#include <SymmetricKey.h>
#include <ByteArray.h>

int main(int argc, char* argv[]) {
	
	if (argc < 2 || argc > 5) {
		cout << "Bad usage!" << '\n';
		cout << "Leia a documentação" << endl;
		return 1;
	}

	ByteArray base64Key = std::string("+QKrok03Mo5eg2QqKvK/WJO7AiiUADW08QbL558AD2E="); // Chave simétrica de 32 bits para todo binário mltsgn.
	SymmetricKey symmetricKey = SymmetricKey(base64Key, SymmetricKey::AES_128);


	std::string argv2 = argv[2];
	if (argv2 == "-s" || argv2 == "--signatures") {
		// Parte de iterar sobre arquivos para guardar as chaves privadas de dentro de uma pasta.
	}

	std::ifstream pdfFile(argv[1]);
	std::ofstream outputFile("mlt_keys");

	return 0;
}
