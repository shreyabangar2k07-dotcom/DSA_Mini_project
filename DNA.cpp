#include <iostream>
#include <vector>
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
    string original = "ATCGGCTA";
    string mutated = "ATCAGCTT";

    cout << "Hamming Distance: " << dna.calcHammingDist(original, mutated) << endl;
    cout << "Matching Bases: " << dna.calcMatchingBases(original, mutated) << endl;
    vector<int> subPos = dna.findSubstitutionPos(original, mutated);
    for(int pos: subPos)
        cout << pos << ", ";
    cout << endl;
    cout << "Similarity Percentage: " << dna.calcSeqSimilarityPercentage(original, mutated) << "%" << endl;

    return 0;
}