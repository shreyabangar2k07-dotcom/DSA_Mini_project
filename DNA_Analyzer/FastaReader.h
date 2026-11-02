#ifndef FASTA_READER_H
#define FASTA_READER_H
#include <string>
#include <vector>

class FastaReader {
public:
    static bool readFasta(const std::string& filename, std::string& header, std::string& sequence);
    static bool validateSequence(const std::string& sequence);
};
#endif
