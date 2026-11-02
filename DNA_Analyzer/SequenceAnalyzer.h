#ifndef SEQUENCE_ANALYZER_H
#define SEQUENCE_ANALYZER_H
#include <string>
#include <vector>

struct AnalysisResult {
    int hammingDistance;
    int matchCount;
    double similarity;
    std::vector<int> substitutionPositions;
    std::string seq1Header;
    std::string seq2Header;
};

class SequenceAnalyzer {
public:
    static AnalysisResult compare(const std::string& seq1, const std::string& header1, const std::string& seq2, const std::string& header2);
};
#endif
