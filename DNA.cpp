#include <iostream>
#include <vector>
#include "ReportManager.h"
using namespace std;

class DNA {

    public:
        int calcHammingDist(string original, string mutated) {
            int hammingDist = 0;

            if(original.length() != mutated.length()) {
                cout << "Sequences must have equal lengths" << endl;
                return -1;
            }

            for(int i=0; i<original.length(); i++) {
                if(original[i] != mutated[i])
                    hammingDist++;
            }

            return hammingDist;
        }

        vector<int> findSubstitutionPos(string original, string mutated) {
            vector<int> subPos;

            for(int i=0; i<original.length(); i++) {
                if(original[i] != mutated[i])
                    subPos.push_back(i);
            }

            return subPos;
        }

        int calcMatchingBases(string original, string mutated) {
            int hammingDist = calcHammingDist(original, mutated);
            
            if(hammingDist == -1) {
                return -1;
            }

            return original.length() - hammingDist;
        }

        double calcSeqSimilarityPercentage(string original, string mutated) {
            int similarBases = calcMatchingBases(original, mutated);

            if(similarBases == -1) {
                return -1;
            }

            return (double) similarBases / original.length() * 100.0;
        }
};

int main() {
    DNA dna;
    ReportManager report;
    int choice;

    cout << "========================================================" << endl;
    cout << "     BaseX - DNA Sequence Analyzer                      " << endl;
    cout << "========================================================" << endl;

    do {
        cout << endl;
        cout << "  MENU:" << endl;
        cout << "  1. Compare DNA Sequences" << endl;
        cout << "  2. View Comparison History" << endl;
        cout << "  3. View Mutation Details by Comparison ID" << endl;
        cout << "  4. Exit" << endl;
        cout << endl;
        cout << "  Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1: {
                string datasetName, original, mutated;

                cout << endl;
                cout << "  Enter dataset name: ";
                cin.ignore();
                getline(cin, datasetName);

                cout << "  Enter original DNA sequence: ";
                getline(cin, original);

                cout << "  Enter mutated DNA sequence: ";
                getline(cin, mutated);

                // Use existing DNA class methods for comparison
                int hammingDist = dna.calcHammingDist(original, mutated);

                if (hammingDist == -1) {
                    cout << "  Comparison aborted due to unequal sequence lengths." << endl;
                    break;
                }

                int matchingBases = dna.calcMatchingBases(original, mutated);
                double similarity = dna.calcSeqSimilarityPercentage(original, mutated);
                vector<int> subPos = dna.findSubstitutionPos(original, mutated);

                // Build the result using ReportManager
                ComparisonResult result = report.buildResult(
                    datasetName, original, mutated,
                    hammingDist, matchingBases, similarity, subPos
                );

                // A. Display the detailed mutation report
                report.displayDetailedReport(result);

                // B & C. Save to both CSV files
                report.saveAllToCSV(result);

                break;
            }
            case 2: {
                // D. Display comparison history
                report.displayComparisonHistory();
                break;
            }
            case 3: {
                int searchID;
                cout << endl;
                cout << "  Enter Comparison ID to view details: ";
                cin >> searchID;

                // D. Display mutation details for the given ID
                report.displayMutationDetails(searchID);
                break;
            }
            case 4: {
                cout << endl;
                cout << "  Thank you for using BaseX! Goodbye." << endl;
                cout << endl;
                break;
            }
            default: {
                cout << "  Invalid choice. Please try again." << endl;
                break;
            }
        }
    } while(choice != 4);

    return 0;
}