#include <iostream>
#include <vector>
#include <fstream>
#include <RSAKeyPair.h>

int main(int argc, char **argv) {
	
	// std::ifstream pdfFile(argv[1]); // PDF de entrada.
	std::ofstream outputFile("rsa.priv");
	int operadores;
	std::vector<PrivateKey*> chaves_adicionadas;
	std::string key;

	operadores = 3;

	for (int i = 0; i < operadores; i++) {
		chaves_adicionadas.push_back(RSAKeyPair(2048).getPrivateKey());
	}

	outputFile << chaves_adicionadas[1]->getPemEncoded();

	//Função para assinar o pdfFile com cada key de chaves_adicionadas.

	return 0;
}
