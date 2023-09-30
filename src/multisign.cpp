#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <dirent.h>
#include <ByteArray.h>
#include <KeyPair.h>

using std::cout;
using std::endl;
using std::cerr;

using std::string;

int main(int argc, char* argv[]) {
	
	// if (argc != 5) {
	// 	cout << "Bad usage!" << '\n';
	// 	cout << "Leia a documentação" << endl;
	// 	return 1;
	// }
	std::ofstream outputFile("mlt_keys", std::ios::out);
	

	string bufferString;
	string flag1 = argv[1];
	if (flag1 == "-s" || flag1 == "--signatures") {
		// Parte de iterar sobre arquivos para guardar as chaves privadas de dentro de uma pasta.
		DIR* dir = opendir(argv[3]);
		if (!dir) {
			cerr << "Erro ao abrir pasta." << endl;
			return 1;
		}

		struct dirent* entry;
		while ((entry = readdir(dir))) {
			std::cout << entry->d_name << std::endl;
		}
	}

	// string flag2 = argv[3];
	// if (flag2 == "-i" || flag2 == "--input") {
	// 	// Parte de abrir arquivo PDF que irá ser assinado.
	// 	std::ifstream pdfFile(argv[4]);
	// }

	// outputFile << bufferString;

	// outputFile << output.toString();

	return 0;
}
