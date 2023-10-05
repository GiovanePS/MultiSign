#include <iostream>
#include <fstream>
#include <dirent.h>
#include <certificate/Certificate.h>
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
	std::vector<string> names;

	string flag1 = argv[1];
	if (flag1 == "-c" || flag1 == "--certificates") {
		// Iterando sobre a pasta dada como argumento de certificates, para guardar as chaves públicas dos certificados em mlt_keys.
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
					string certificateStr;

					if (fileOpened) {
						while (getline(fileOpened, line)) {
							certificateStr += line +'\n';
						}

						try {
							Certificate certificadoAtual = Certificate(certificateStr);
							string nomeAtual = certificadoAtual.getSubject().getEntries(RDNSequence::COMMON_NAME)[0];
							mlt_keys_output << certificadoAtual.getPublicKey()->getPemEncoded();
							names.push_back(nomeAtual);
						} catch(EncodeException e) {
							cerr << "Arquivo fora do modelo de certificado x509 encontrado." << '\n';
							cerr << "Coloque somente certificados válidos no diretório." << endl;
							return 1;
						}

						fileOpened.close();
					} else {
						cerr << "Ocorreu um erro ao abrir um dos arquivos da pasta." << '\n';
						cerr << "Deixe somente arquvos de chave pública na pasta." << endl;
						return 1;
					}
				}
			}
			mlt_keys_output << "END KEYS" << '\n';
			closedir(dir);

			mlt_keys_output << "NAMES" << '\n';
			size_t qntNames = names.size();
			for (size_t i = 0; i < qntNames; i++) {
				mlt_keys_output << names[i] << '\n';
			}
			mlt_keys_output << "END NAMES" << '\n';
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

			mlt_keys_output << "HASH" << '\n';
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

	cout << "MultiKeys criado com sucesso!" << endl;

	return 0;
}