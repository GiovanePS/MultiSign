#include <iostream>
#include <vector>
#include <fstream>
#include <RSAKeyPair.h>
#include <Signer.h>
#include <AsymmetricKey.h>

int main(int argc, char* argv[]) {
	
	// std::ifstream pdfFile(argv[1]); // PDF de entrada.
	std::ofstream outputFile("arquivo_estado");
	int operadores;
	std::vector<PublicKey*> chaves_adicionadas;
	std::string key;

	std::cout << "Quantos operadores: ";
	std::cin >> operadores;

	for (int i = 0; i < operadores; i++) {
		chaves_adicionadas.push_back(RSAKeyPair(2048).getPublicKey());
		std::cout << chaves_adicionadas[i]->getPemEncoded();
		outputFile << chaves_adicionadas[i]->getPemEncoded();
	}



	//Função para assinar o pdfFile com cada key de chaves_adicionadas.

	return 0;
}
