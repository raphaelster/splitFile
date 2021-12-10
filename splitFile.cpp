#include <iostream>
#include <string>
#include <regex>
#include <fstream>
#include <memory>
#include <sstream>
#include <cassert>

std::unique_ptr<std::string> readFile(const std::string& filename) {
	std::ifstream file(filename);
	std::stringstream out;
	
	if (!file.is_open()) return std::unique_ptr<std::string>(nullptr);
	
	std::string line;
	while (getline(file, line)) out << line << "\n";
	
	return std::make_unique<std::string>(out.str());
}

bool writeFile(const std::string& text, const std::string& filename) {
	std::ofstream file(filename);
	
	if (!file.is_open()) return false;
	
	file << text;
	
	file.close();
	
	return true;
}

std::vector<std::string> split(const std::string& file, const std::string& regexPattern) {
	std::regex regex(regexPattern);
	std::smatch matches;
	int offset = 0;
	
	std::vector<std::pair<int, int>> subFiles;
	
	while (std::regex_search(file.begin() + offset, file.end(), matches, regex)) {
		subFiles.push_back(std::pair<int, int>(offset, offset + matches.position(0)));
		offset += matches.position(0) + matches.length(0);
	}
	subFiles.push_back(std::pair<int, int>(offset, file.size()));
	
	std::vector<std::string> out;
	for (std::pair<int, int> range : subFiles) if (range.first != range.second) {
		out.push_back(file.substr(range.first, range.second - range.first));
	}
	
	return out;
}

void save(const std::string& file, const std::string& pattern, const std::string& extension) {
	std::regex regex(pattern);
	std::smatch matches;
	
	if (!std::regex_search(file, matches, regex)) {
		std::cerr<<"Couldn't find filename for subfile:\n"<<file<<std::endl;
		return;
	}
	
	std::string filename = matches[1];
	filename += "." + extension;
	
	if (!writeFile(file, filename)) std::cerr<<"Couldn't write to "<<filename<<extension<<" for subFile:"<<std::endl<<file<<std::endl;
	
	
}

int main(int argc, char* argv[]) {
	if (argc < 5) {
		std::cerr<<"splitString [FILE] [REGEX_CAPTURE] [REGEX_FILENAME (uses capture group 1)] [EXTENSION]"<<std::endl;
		return 1;
	}
	
	std::string file = *readFile(argv[1]);
	
	std::vector<std::string> splitFile = split(file, argv[2]);
	
	for (std::string s : splitFile) save(s, argv[3], argv[4]);
	
	
	return 0;
}