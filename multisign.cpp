#include <iostream>
#include <vector>
#include <fstream>
#include <RSAKeyPair.h>
#include <Signer.h>
#include <AsymmetricKey.h>

int main(int argc, char* argv[]) {
	
	if (argc == 1) {
		std::cout << "Bad Usage!" << '\n';
		std::cout << "Argumentos faltando!" << std::endl;
		return 1;
	}

	std::string argv2 = argv[2];
	if (argv2 == "-s" || argv2 == "--signatures") {}

	// std::ifstream pdfFile(argv[1]);
	std::ofstream outputFile("mlt_keys");
	int operadores;
	std::vector<KeyPair> chaves_adicionadas;
	std::string key;

	std::cout << "Quantos operadores: ";
	std::cin >> operadores;

	for (int i = 0; i < operadores; i++) {
		chaves_adicionadas.push_back(RSAKeyPair(2048));
		std::cout << chaves_adicionadas[i].getPemEncoded();
	}



	//Função para assinar o pdfFile com cada key de chaves_adicionadas.

	return 0;
}
