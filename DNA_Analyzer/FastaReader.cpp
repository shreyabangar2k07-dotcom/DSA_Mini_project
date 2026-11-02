#include "FastaReader.h"
#include <fstream>
#include <cctype>

bool FastaReader::readFasta(const std::string& filename, std::string& header, std::string& sequence) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;
    std::string line;
    sequence = "";
    header = "";
    bool isFirstLine = true;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        if (line[0] == '>') {
            if (isFirstLine) { header = line.substr(1); isFirstLine = false; }
        } else {
            for (char c : line) {
                if (!std::isspace(c)) sequence += std::toupper(c);
            }
        }
    }
    return true;
}

bool FastaReader::validateSequence(const std::string& sequence) {
    for (char c : sequence) {
        if (c != 'A' && c != 'C' && c != 'G' && c != 'T' && c != 'N') return false;
    }
    return !sequence.empty();
}
