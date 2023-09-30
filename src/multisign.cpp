#include <iostream>
#include <fstream>
#include <dirent.h>
#include <ByteArray.h>
#include <KeyPair.h>

using std::cout;
using std::endl;
using std::cerr;

using std::string;

int main(int argc, char* argv[]) {
	
	if (argc < 3 || argc > 5) { // ALTERAR DEPOIS PARA ACEITAR SOMENTE 5 ARGUMENTOS.
		cout << "Bad usage!" << '\n';
		cout << "Leia a documentação" << endl;
		return 1;
	}

	std::ofstream mlt_keys_output("mlt_keys", std::ios::out);

	string flag1 = argv[1];
	if (flag1 == "-s" || flag1 == "--signatures") {
		// Iterando sobre a pasta dada como argumento de signatures, para guardar as chaves públicas em mlt_keys.
		char* folderPath = argv[2];
		DIR* dir = opendir(folderPath);
		if (dir) {
			string line;
			string filename;
			string filepath;
			struct dirent* file;
			while ((file = readdir(dir))) {
				if (file->d_type == DT_REG) {
					filename = file->d_name;
					filepath = string(folderPath) + filename;

					std::ifstream fileOpened(filepath.c_str(), std::ios::in);

					if (fileOpened.is_open()) {
						while (getline(fileOpened, line)) {
							mlt_keys_output << line << '\n';
						}

						fileOpened.close();
					} else {
						cerr << "Ocorreu um erro ao abrir um dos arquivos." << '\n';
						cerr << "Deixe somente arquvos de chave pública na pasta." << endl;
						return 1;
					}
				}
			}
			closedir(dir);
		} else {
			cerr << "Erro ao abrir pasta." << endl;
			return 1;
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