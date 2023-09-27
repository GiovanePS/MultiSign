#include <iostream>
#include <vector>
#include <fstream>

int main(int argc, char **argv) {
	
	std::ifstream pdfFile(argv[1]);
	int operadores;
	std::vector<std::string> chaves_adicionadas;
	std::string key;

	std::cout << "Quantos operadores?";
	std::cin >> operadores;
	for (int i = 0; i < operadores; i++) {
		std::cout << "Digite a chave do " << i << "º operador: ";
		std::cin >> key;
		chaves_adicionadas.push_back(key);
	}

	//Função para assinar o pdfFile com cada key de chaves_adicionadas.

	return 0;
}
