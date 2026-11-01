#include "ReportManager.h"

// ============================================================
// Constructor: set the CSV file names
// ============================================================
ReportManager::ReportManager() {
    comparisonCSV = "comparison_results.csv";
    mutationCSV = "mutation_records.csv";
}

// ============================================================
// Helper: Check if a file exists and is non-empty
// ============================================================
bool ReportManager::fileExistsAndNotEmpty(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    // Check if file has any content
    file.seekg(0, ios::end);
    bool hasContent = (file.tellg() > 0);
    file.close();
    return hasContent;
}

// ============================================================
// Helper: Get next unique Comparison ID
// Reads comparison_results.csv and finds the highest existing ID,
// then returns ID + 1. If file doesn't exist, starts from 1.
// ============================================================
int ReportManager::getNextComparisonID() {
    int maxID = 0;

    ifstream file(comparisonCSV);
    if (!file.is_open()) {
        return 1;  // First comparison ever
    }

    string line;
    // Skip header line
    getline(file, line);

    // Read each row and extract the Comparison_ID (first column)
    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string idStr;
        getline(ss, idStr, ',');

        // Convert string to int safely
        try {
            int id = stoi(idStr);
            if (id > maxID) {
                maxID = id;
            }
        } catch (...) {
            // Skip malformed rows
            continue;
        }
    }

    file.close();
    return maxID + 1;
}

// ============================================================
// Build a ComparisonResult struct using existing DNA class outputs
// ============================================================
ComparisonResult ReportManager::buildResult(string datasetName,
                                             string original,
                                             string mutated,
                                             int hammingDist,
                                             int matchingBases,
                                             double similarity,
                                             vector<int> substitutionPositions) {
    ComparisonResult result;
    result.comparisonID = getNextComparisonID();
    result.datasetName = datasetName;
    result.originalSequence = original;
    result.mutatedSequence = mutated;
    result.sequenceLength = original.length();
    result.hammingDistance = hammingDist;
    result.matchingBases = matchingBases;
    result.similarityPercentage = similarity;
    result.mutationCount = substitutionPositions.size();

    // Build mutation details from the 0-based positions returned by DNA::findSubstitutionPos
    for (int i = 0; i < substitutionPositions.size(); i++) {
        MutationDetail m;
        m.position = substitutionPositions[i] + 1;  // Convert to 1-based biological position
        m.originalBase = original[substitutionPositions[i]];
        m.mutatedBase = mutated[substitutionPositions[i]];
        result.mutations.push_back(m);
    }

    return result;
}

// ============================================================
// A. Display Detailed Mutation Report to console
// ============================================================
void ReportManager::displayDetailedReport(ComparisonResult result) {
    cout << endl;
    cout << "========================================================" << endl;
    cout << "          DETAILED MUTATION REPORT                       " << endl;
    cout << "========================================================" << endl;
    cout << endl;

    cout << "  Comparison ID      : " << result.comparisonID << endl;
    cout << "  Dataset Name       : " << result.datasetName << endl;
    cout << endl;

    // For very long sequences, show only first 60 characters with "..."
    if (result.originalSequence.length() > 60) {
        cout << "  Original Sequence  : " << result.originalSequence.substr(0, 60) << "..." << endl;
        cout << "  Mutated Sequence   : " << result.mutatedSequence.substr(0, 60) << "..." << endl;
    } else {
        cout << "  Original Sequence  : " << result.originalSequence << endl;
        cout << "  Mutated Sequence   : " << result.mutatedSequence << endl;
    }

    cout << endl;
    cout << "  Sequence Length    : " << result.sequenceLength << " bases" << endl;
    cout << "  Hamming Distance   : " << result.hammingDistance << endl;
    cout << "  Matching Bases     : " << result.matchingBases << endl;
    cout << "  Similarity         : " << fixed << setprecision(2) << result.similarityPercentage << "%" << endl;
    cout << "  Total Mutations    : " << result.mutationCount << endl;
    cout << endl;

    if (result.mutationCount == 0) {
        cout << "  No mutations found. The sequences are identical!" << endl;
    } else {
        cout << "  Mutation Details:" << endl;
        cout << "  -----------------" << endl;
        for (int i = 0; i < result.mutations.size(); i++) {
            cout << "    Position " << result.mutations[i].position
                 << ": " << result.mutations[i].originalBase
                 << " -> " << result.mutations[i].mutatedBase << endl;
        }
    }

    cout << endl;
    cout << "========================================================" << endl;
    cout << endl;
}

// ============================================================
// B. Save comparison summary to comparison_results.csv
// ============================================================
bool ReportManager::saveComparisonToCSV(ComparisonResult result) {
    bool writeHeader = !fileExistsAndNotEmpty(comparisonCSV);

    ofstream file(comparisonCSV, ios::app);
    if (!file.is_open()) {
        cerr << "Error: Could not open " << comparisonCSV << " for writing." << endl;
        return false;
    }

    // Write header only if file is new or empty
    if (writeHeader) {
        file << "Comparison_ID,Dataset_Name,Sequence_Length,Hamming_Distance,"
             << "Matching_Bases,Similarity_Percentage,Mutation_Count" << endl;
    }

    // Write the comparison data row
    file << result.comparisonID << ","
         << result.datasetName << ","
         << result.sequenceLength << ","
         << result.hammingDistance << ","
         << result.matchingBases << ","
         << fixed << setprecision(2) << result.similarityPercentage << ","
         << result.mutationCount << endl;

    file.close();
    return true;
}

// ============================================================
// C. Save individual mutation records to mutation_records.csv
// ============================================================
bool ReportManager::saveMutationsToCSV(ComparisonResult result) {
    bool writeHeader = !fileExistsAndNotEmpty(mutationCSV);

    ofstream file(mutationCSV, ios::app);
    if (!file.is_open()) {
        cerr << "Error: Could not open " << mutationCSV << " for writing." << endl;
        return false;
    }

    // Write header only if file is new or empty
    if (writeHeader) {
        file << "Comparison_ID,Dataset_Name,Position,Original_Base,Mutated_Base" << endl;
    }

    // Write each mutation as a separate row
    // If zero mutations, no data rows are written (only header if needed)
    for (int i = 0; i < result.mutations.size(); i++) {
        file << result.comparisonID << ","
             << result.datasetName << ","
             << result.mutations[i].position << ","
             << result.mutations[i].originalBase << ","
             << result.mutations[i].mutatedBase << endl;
    }

    file.close();
    return true;
}

// ============================================================
// Convenience: Save both CSV files at once
// ============================================================
bool ReportManager::saveAllToCSV(ComparisonResult result) {
    bool compSaved = saveComparisonToCSV(result);
    bool mutSaved = saveMutationsToCSV(result);

    if (compSaved && mutSaved) {
        cout << "  Results saved to CSV files successfully!" << endl;
        return true;
    }

    // Don't display success if saving failed
    return false;
}

// ============================================================
// D. Display Comparison History from comparison_results.csv
// ============================================================
void ReportManager::displayComparisonHistory() {
    ifstream file(comparisonCSV);
    if (!file.is_open()) {
        cout << endl;
        cout << "  No comparison history found." << endl;
        cout << "  (Run a comparison first to generate records.)" << endl;
        cout << endl;
        return;
    }

    string line;
    // Read header
    if (!getline(file, line)) {
        cout << endl;
        cout << "  No comparison history found. The file is empty." << endl;
        cout << endl;
        file.close();
        return;
    }

    // Check if there are any data rows
    bool hasRecords = false;

    cout << endl;
    cout << "========================================================" << endl;
    cout << "             COMPARISON HISTORY                          " << endl;
    cout << "========================================================" << endl;
    cout << endl;

    cout << left
         << setw(6)  << "ID"
         << setw(30) << "Dataset"
         << setw(8)  << "Length"
         << setw(10) << "Hamming"
         << setw(10) << "Match"
         << setw(12) << "Similarity"
         << setw(10) << "Mutations" << endl;

    cout << string(86, '-') << endl;

    while (getline(file, line)) {
        if (line.empty()) continue;
        hasRecords = true;

        stringstream ss(line);
        string id, dataset, seqLen, hamming, matching, similarity, mutCount;

        getline(ss, id, ',');
        getline(ss, dataset, ',');
        getline(ss, seqLen, ',');
        getline(ss, hamming, ',');
        getline(ss, matching, ',');
        getline(ss, similarity, ',');
        getline(ss, mutCount, ',');

        cout << left
             << setw(6)  << id
             << setw(30) << dataset
             << setw(8)  << seqLen
             << setw(10) << hamming
             << setw(10) << matching
             << setw(12) << (similarity + "%")
             << setw(10) << mutCount << endl;
    }

    if (!hasRecords) {
        cout << "  No comparison records found." << endl;
    }

    cout << endl;
    cout << "========================================================" << endl;
    cout << endl;

    file.close();
}

// ============================================================
// D. Display mutation details for a specific Comparison_ID
// ============================================================
void ReportManager::displayMutationDetails(int comparisonID) {
    ifstream file(mutationCSV);
    if (!file.is_open()) {
        cout << endl;
        cout << "  No mutation records found." << endl;
        cout << "  (Run a comparison first to generate records.)" << endl;
        cout << endl;
        return;
    }

    string line;
    // Skip header
    getline(file, line);

    bool found = false;

    cout << endl;
    cout << "========================================================" << endl;
    cout << "   MUTATION DETAILS FOR COMPARISON ID: " << comparisonID << endl;
    cout << "========================================================" << endl;
    cout << endl;

    cout << left
         << setw(8)  << "ID"
         << setw(30) << "Dataset"
         << setw(12) << "Position"
         << setw(10) << "Original"
         << setw(10) << "Mutated" << endl;

    cout << string(70, '-') << endl;

    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string idStr, dataset, position, origBase, mutBase;

        getline(ss, idStr, ',');
        getline(ss, dataset, ',');
        getline(ss, position, ',');
        getline(ss, origBase, ',');
        getline(ss, mutBase, ',');

        // Check if this row matches the requested Comparison_ID
        try {
            int id = stoi(idStr);
            if (id == comparisonID) {
                found = true;
                cout << left
                     << setw(8)  << idStr
                     << setw(30) << dataset
                     << setw(12) << position
                     << setw(10) << origBase
                     << setw(10) << mutBase << endl;
            }
        } catch (...) {
            continue;
        }
    }

    if (!found) {
        cout << "  No mutation records found for Comparison ID " << comparisonID << "." << endl;
        cout << "  (The comparison may have had zero mutations, or the ID may not exist.)" << endl;
    }

    cout << endl;
    cout << "========================================================" << endl;
    cout << endl;

    file.close();
}
