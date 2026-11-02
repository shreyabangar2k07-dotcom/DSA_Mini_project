#include "SequenceAnalyzer.h"
#include <algorithm>

AnalysisResult SequenceAnalyzer::compare(const std::string& seq1, const std::string& header1, const std::string& seq2, const std::string& header2) {
    AnalysisResult res;
    res.seq1Header = header1.empty() ? "Original" : header1;
    res.seq2Header = header2.empty() ? "Mutated" : header2;
    res.hammingDistance = 0;
    res.matchCount = 0;

    size_t len = std::min(seq1.length(), seq2.length());
    int lengthDiff = std::max(seq1.length(), seq2.length()) - len;

    for (size_t i = 0; i < len; ++i) {
        if (seq1[i] != seq2[i]) {
            res.hammingDistance++;
            res.substitutionPositions.push_back(i + 1);
        } else {
            res.matchCount++;
        }
    }
    res.hammingDistance += lengthDiff;
    res.similarity = (static_cast<double>(res.matchCount) / std::max(seq1.length(), seq2.length())) * 100.0;
    return res;
}
