#include "UIManager.h"
#include "FastaReader.h"
#include "SequenceAnalyzer.h"
#include "ReportManager.h"
#include <iostream>
#include <cstdlib>

void UIManager::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void UIManager::displayMenu() {
    std::cout << "\n=========================================\n";
    std::cout << "          DNA Sequence Analyzer      \n";
    std::cout << "=========================================\n";
    std::cout << "1. Compare DNA Sequences (FASTA)\n";
    std::cout << "2. View Comparison History (CSV)\n";
    std::cout << "3. Exit\n";
    std::cout << "=========================================\n";
    std::cout << "Enter your choice: ";
}

void UIManager::handleCompare() {
    std::string file1, file2;
    std::cout << "\nEnter original FASTA filename (e.g., original.fasta): ";
    std::cin >> file1;
    std::cout << "Enter mutated FASTA filename (e.g., mutated.fasta): ";
    std::cin >> file2;

    std::string header1, seq1, header2, seq2;
    if (!FastaReader::readFasta(file1, header1, seq1)) {
        std::cout << "Error: Could not read " << file1 << "\n";
        return;
    }
    if (!FastaReader::readFasta(file2, header2, seq2)) {
        std::cout << "Error: Could not read " << file2 << "\n";
        return;
    }

    if (!FastaReader::validateSequence(seq1) || !FastaReader::validateSequence(seq2)) {
        std::cout << "Validation failed: Sequences must contain only A, C, G, T, N characters.\n";
        return;
    }

    AnalysisResult result = SequenceAnalyzer::compare(seq1, header1, seq2, header2);

    std::cout << "\n--- Analysis Results ---\n";
    std::cout << "Similarity: " << result.similarity << "%\n";
    std::cout << "Hamming Distance: " << result.hammingDistance << "\n";
    std::cout << "Matching Bases: " << result.matchCount << "\n";
    std::cout << "Substitutions found: " << result.substitutionPositions.size() << "\n";

    ReportManager::saveReport(result);
    std::cout << "\n[Success] Report saved to comparison_history.csv\n";
}

void UIManager::handleViewHistory() {
    ReportManager::viewHistory();
}

void UIManager::start() {
    int choice;
    while (true) {
        displayMenu();
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }
        switch (choice) {
            case 1: handleCompare(); break;
            case 2: handleViewHistory(); break;
            case 3: std::cout << "Exiting DNA Analyzer...\n"; return;
            default: std::cout << "Invalid choice. Please enter 1, 2, or 3.\n";
        }
    }
}
