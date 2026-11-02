#include "ReportManager.h"
#include <fstream>
#include <iostream>
#include <iomanip>

void ReportManager::saveReport(const AnalysisResult& res, const std::string& filename) {
    std::ifstream checkFile(filename);
    bool writeHeader = !checkFile.is_open();
    checkFile.close();

    std::ofstream file(filename, std::ios::app);
    if (writeHeader) {
        file << "Original_Sequence,Mutated_Sequence,Matches,Hamming_Distance,Similarity(%),Substitutions_Positions\n";
    }
    file << res.seq1Header << "," << res.seq2Header << ","
         << res.matchCount << "," << res.hammingDistance << ","
         << std::fixed << std::setprecision(2) << res.similarity << ",";

    if (res.substitutionPositions.empty()) {
        file << "None";
    } else {
        for (size_t i = 0; i < res.substitutionPositions.size(); ++i) {
            file << res.substitutionPositions[i];
            if (i != res.substitutionPositions.size() - 1) file << ";";
        }
    }
    file << "\n";
}

void ReportManager::viewHistory(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "No history found. Try running a comparison first.\n";
        return;
    }
    std::string line;
    std::cout << "\n--- Comparison History (CSV) ---\n";
    while (std::getline(file, line)) {
        std::cout << line << "\n";
    }
    std::cout << "----------------------------------\n";
}
