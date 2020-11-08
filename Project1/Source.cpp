#include <iostream>
#include <fstream>
#include <map>
int main() {

	std::ifstream is1("text1.txt", std::ios::binary);
	std::ifstream is2("text2.txt", std::ios::binary);
	std::ofstream os1("result.txt");

	if (!(is1 && is2 && os1)) {
		std::cout << "The error has occure\n";
		return -1;
	}

	char* bufIs1;
	char* bufIs2;

	int sizeIs1;
	int sizeIs2;

	is1.seekg(0, std::ios::end);
	sizeIs1 = is1.tellg();
	is1.seekg(0, std::ios::beg);

	is2.seekg(0, std::ios::end);
	sizeIs2 = is2.tellg();
	is2.seekg(0, std::ios::beg);

	bufIs1 = new char[sizeIs1];
	bufIs2 = new char[sizeIs2];

	is1.read(bufIs1, sizeIs1);
	is2.read(bufIs2, sizeIs2);
	bufIs1[sizeIs1] = '\0';
	bufIs2[sizeIs2] = '\0';

	std::string tmpIs1 = "";
	std::string tmpIs2 = "";

	std::map<std::string, bool> matches;

	for (int indexIs1 = 0, indexIs2 = 0; indexIs1 <= sizeIs1; ++indexIs1) {
		if (bufIs1[indexIs1] == ' ' || bufIs1[indexIs1] == '.' || bufIs1[indexIs1] == ',' || bufIs1[indexIs1] == '\0') {
			if (!matches[tmpIs1] && tmpIs1 != "") {
				for (indexIs2 = 0; indexIs2 <= sizeIs2; ++indexIs2) {
					if (bufIs2[indexIs2] == ' ' || bufIs2[indexIs2] == '.' || bufIs2[indexIs2] == ',' || bufIs2[indexIs2] == '\0') {
						if (tmpIs1 == tmpIs2 ) {
							matches[tmpIs2] = true;
							break;
						}
						tmpIs2 = "";
						continue;
					}
					tmpIs2 += bufIs2[indexIs2];
				}
			}

			tmpIs1 = "";
			tmpIs2 = "";
			continue;
		}
		tmpIs1 += bufIs1[indexIs1];
	}
	int common = 0;
	for (int index = 0; index <= sizeIs1 && index <= sizeIs2; ++index) {
		if (bufIs1[index] == bufIs2[index]) {
			++common;
		}
	}
	std::cout << sizeIs1 + sizeIs2 - common << "%\n";
	std::map<std::string, bool>::iterator it = matches.begin();
	while (it != matches.end()) {
		if(it->second)
			os1 << it->first << '\n';
		++it;
	}

	is1.close();
	is2.close();
	os1.close();
	return 1;
}