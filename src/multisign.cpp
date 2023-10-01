#include <iostream>
#include <fstream>
#include <dirent.h>
#include <MessageDigest.h>

using std::cout;
using std::endl;
using std::cerr;

using std::string;

int main(int argc, char* argv[]) {
	
	if (argc != 5) {
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

					if (fileOpened) {
						while (getline(fileOpened, line)) {
							mlt_keys_output << line << '\n';
						}

						fileOpened.close();
					} else {
						cerr << "Ocorreu um erro ao abrir um dos arquivos da pasta." << '\n';
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
	} else {
		cout << "Bad usage!" << '\n';
		cout << "Leia a documentação" << endl;
		return 1;
	}

	string flag2 = argv[3];
	if (flag2 == "-i" || flag2 == "--input") {
		// Abrir arquivo PDF que irá ser assinado.
		std::ifstream docInputFile(argv[4], std::ios::binary);

		if (docInputFile) {
			MessageDigest msgDgst = MessageDigest(MessageDigest::SHA256);

			ByteArray bufferByteArray;
			string buffer;
			while (getline(docInputFile, buffer)) {
				bufferByteArray = buffer + '\n';
				msgDgst.update(bufferByteArray);
			}

			mlt_keys_output << msgDgst.doFinal().toHex() << endl;
			docInputFile.close();
		} else {
			cerr << "Arquivo não encontrado." << '\n';
			return 1;
		}
	} else {
		cout << "Bad usage!" << '\n';
		cout << "Leia a documentação" << endl;
		return 1;
	}

	mlt_keys_output.close();

	return 0;
}