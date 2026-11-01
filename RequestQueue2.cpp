#include <iostream>
#include <string>
using namespace std;

struct ComparisonRequest {
    string originalDNA;
    string mutatedDNA;
};

class RequestQueue {
private:
    ComparisonRequest requests[100];
    int front;
    int rear;
    int count;

public:
    RequestQueue() {
        front = 0;
        rear = -1;
        count = 0;
    }

    void addRequest() {
        if (count == 100) {
            cout << "Queue is full\n";
            return;
        }

        ComparisonRequest request;

        cout << "Enter original DNA dataset ID: ";
        cin >> request.originalDNA;

        cout << "Enter mutated DNA dataset ID: ";
        cin >> request.mutatedDNA;

        rear = (rear + 1) % 100;
        requests[rear] = request;
        count++;

        cout << "Request added\n";
    }

    void viewRequests() {
        if (count == 0) {
            cout << "No pending requests\n";
            return;
        }

        cout << "\nPending Comparison Requests:\n";

        for (int i = 0; i < count; i++) {
            int index = (front + i) % 100;

            cout << i + 1 << ". "
                 << requests[index].originalDNA
                 << " -> "
                 << requests[index].mutatedDNA << '\n';
        }
    }

    void processRequest() {
        if (count == 0) {
            cout << "No requests available to process\n";
            return;
        }

        cout << "\nProcessing DNA Comparison:\n";
        cout << "Original Dataset: "
             << requests[front].originalDNA << '\n';

        cout << "Mutated Dataset: "
             << requests[front].mutatedDNA << '\n';

        front = (front + 1) % 100;
        count--;

        cout << "Request processed\n";
    }
};

int main() {
    RequestQueue requests;
    int choice;

    do {
        cout << "\n BaseX Request Queue \n";
        cout << "1. Add Comparison Request\n";
        cout << "2. View Pending Requests\n";
        cout << "3. Process Next Request\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                requests.addRequest();
                break;

            case 2:
                requests.viewRequests();
                break;

            case 3:
                requests.processRequest();
                break;

            case 4:
                cout << "Exiting\n";
                break;

            default:
                cout << "Invalid choice\n";
        }

    } while (choice != 4);

    return 0;
}
