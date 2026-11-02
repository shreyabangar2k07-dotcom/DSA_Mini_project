#ifndef UI_MANAGER_H
#define UI_MANAGER_H

class UIManager {
public:
    void start();
private:
    void clearScreen();
    void displayMenu();
    void handleCompare();
    void handleViewHistory();
};
#endif
