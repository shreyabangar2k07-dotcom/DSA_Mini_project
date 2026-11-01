#ifndef REPORTMANAGER_H
#define REPORTMANAGER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// Structure to hold details of a single mutation
struct MutationDetail {
    int position;       // 1-based biological position
    char originalBase;
    char mutatedBase;
};

// Structure to hold a complete comparison result
struct ComparisonResult {
    int comparisonID;
    string datasetName;
    int sequenceLength;
    int hammingDistance;
    int matchingBases;
    double similarityPercentage;
    int mutationCount;
    string originalSequence;
    string mutatedSequence;
    vector<MutationDetail> mutations;
};

class ReportManager {
    private:
        string comparisonCSV;   // filename for comparison_results.csv
        string mutationCSV;     // filename for mutation_records.csv

        // Helper: get next unique comparison ID by reading existing CSV
        int getNextComparisonID();

        // Helper: check if a file exists and is non-empty
        bool fileExistsAndNotEmpty(string filename);

    public:
        // Constructor: sets the CSV filenames
        ReportManager();

        // A. Display detailed mutation report to console
        void displayDetailedReport(ComparisonResult result);

        // B. Save comparison summary to comparison_results.csv
        bool saveComparisonToCSV(ComparisonResult result);

        // C. Save individual mutation records to mutation_records.csv
        bool saveMutationsToCSV(ComparisonResult result);

        // Convenience: save both CSVs at once
        bool saveAllToCSV(ComparisonResult result);

        // D. Display comparison history from comparison_results.csv
        void displayComparisonHistory();

        // D. Display mutation details for a specific Comparison_ID
        void displayMutationDetails(int comparisonID);

        // Build a ComparisonResult using the existing DNA class methods
        // (The actual DNA object is passed from main; positions are converted here)
        ComparisonResult buildResult(string datasetName,
                                     string original,
                                     string mutated,
                                     int hammingDist,
                                     int matchingBases,
                                     double similarity,
                                     vector<int> substitutionPositions);
};

#endif
