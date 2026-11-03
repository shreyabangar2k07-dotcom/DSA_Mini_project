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
    std::cout << "\n--- Available Datasets ---\n";
    std::cout << "1. Apis_mellifera\n";
    std::cout << "2. Arabidopsis_thaliana_histone_H2A\n";
    std::cout << "3. Bacillus_subtilis\n";
    std::cout << "4. Caenorhabditis_elegans\n";
    std::cout << "5. Canis_lupus_familiaris\n";
    std::cout << "6. Danio_rerio\n";
    std::cout << "7. Drosophila_melanogaster\n";
    std::cout << "8. Elephas_maximus\n";
    std::cout << "9. Helianthus_annuus\n";
    std::cout << "10. Human_HBB\n";
    std::cout << "11. Human_papillomavirus\n";
    std::cout << "12. Mycobacterium_tuberculosis\n";
    std::cout << "13. Oryza_sativa_TDNA_target\n";
    std::cout << "14. Panthera_tigris\n";
    std::cout << "15. Solanum_ycopersicum\n";
    std::cout << "Select a dataset (1-15): ";
    
    int choice;
    std::string file1, file2;
    
    if (!(std::cin >> choice)) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Invalid input.\n";
        return;
    }

    if (choice >= 1 && choice <= 15) {
        std::string datasets[] = {
            "Apis_mellifera", "Arabidopsis_thaliana_histone_H2A", "Bacillus_subtilis",
            "Caenorhabditis_elegans", "Canis_lupus_familiaris", "Danio_rerio",
            "Drosophila_melanogaster", "Elephas_maximus", "Helianthus_annuus",
            "Human_HBB", "Human_papillomavirus", "Mycobacterium_tuberculosis",
            "Oryza_sativa_TDNA_target", "Panthera_tigris", "Solanum_ycopersicum"
        };
        
        std::string selected = datasets[choice - 1];
        
        // Handle specific naming conventions in the dataset
        if (selected == "Human_HBB") {
            file1 = "Datasets/" + selected + "/human_hbb_yoruba_19_0_continuous.fasta";
            file2 = "Datasets/" + selected + "/human_hbb_yoruba_19_0_mutated.fasta";
        } else if (selected == "Human_papillomavirus") {
            file1 = "Datasets/" + selected + "/Human_papillomavirus_16_original.fasta";
            file2 = "Datasets/" + selected + "/Human_papillomavirus_16_mutated.fasta";
        } else if (selected == "Bacillus_subtilis") {
            file1 = "Datasets/" + selected + "/Bacillus_subtilis_continuous.fasta";
            file2 = "Datasets/" + selected + "/Bacillus_subtilis_mutated.fasta";
        } else {
            file1 = "Datasets/" + selected + "/" + selected + "_original.fasta";
            file2 = "Datasets/" + selected + "/" + selected + "_mutated.fasta";
        }
        std::cout << "\nLoading files:\nOriginal: " << file1 << "\nMutated: " << file2 << "\n";
    } else if (choice == 16) {
        std::cout << "\nEnter original FASTA filename/path: ";
        std::cin >> file1;
        std::cout << "Enter mutated FASTA filename/path: ";
        std::cin >> file2;
    } else {
        std::cout << "Invalid choice.\n";
        return;
    }

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
