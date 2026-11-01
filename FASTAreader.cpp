#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

class FASTAReader {
public:

    bool readFASTA(string filename, string& sequence) {

        ifstream file(filename);

        if (!file.is_open()) {
            cout << "Unable to open " << filename << endl;
            return false;
        }

        string line;
        bool headerFound = false;
        sequence = "";

        while (getline(file, line)) {
            if (!line.empty() && line[0] == '>') {

                if (headerFound) {
                    cout << "Multiple FASTA records found." << endl;
                    file.close();
                    return false;
                }

                headerFound = true;
                continue;
            }

            // Extract DNA bases and ignore whitespace
            for (char ch : line) {
                if (!isspace(static_cast<unsigned char>(ch))) {
                    sequence += toupper(static_cast<unsigned char>(ch));
                }
            }
        }

        file.close();

        if (!headerFound) {
            cout << "FASTA header missing." << endl;
            return false;
        }

        if (sequence.empty()) {
            cout << "DNA sequence is empty." << endl;
            return false;
        }

        return true;
    }

    bool validateDNA(string sequence) {

        for (char base : sequence) {

            if (base != 'A' && base != 'T' &&
                base != 'G' && base != 'C') {

                cout << "Invalid DNA base found: " << base << endl;
                return false;
            }
        }

        return true;
    }

    bool checkLength(string original, string mutated) {

        if (original.length() != mutated.length()) {
            cout << "DNA sequences have different lengths." << endl;
            return false;
        }

        return true;
    }
};

int main() {

    FASTAReader reader;

    string original;
    string mutated;

    if (!reader.readFASTA("original.fasta", original)) {
        return 0;
    }

    if (!reader.readFASTA("mutated.fasta", mutated)) {
        return 0;
    }

    if (!reader.validateDNA(original)) {
        return 0;
    }

    if (!reader.validateDNA(mutated)) {
        return 0;
    }

    if (!reader.checkLength(original, mutated)) {
        return 0;
    }

    cout << "\nBoth DNA sequences are valid!" << endl;

    cout << "Original sequence length: " << original.length() << endl;
    cout << "Mutated sequence length: " << mutated.length() << endl;

    cout << "\nSequences are ready for comparison." << endl;

    return 0;
}
