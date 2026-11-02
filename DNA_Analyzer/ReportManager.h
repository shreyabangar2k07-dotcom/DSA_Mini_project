#ifndef REPORT_MANAGER_H
#define REPORT_MANAGER_H
#include "SequenceAnalyzer.h"
#include <string>

class ReportManager {
public:
    static void saveReport(const AnalysisResult& res, const std::string& filename = "comparison_history.csv");
    static void viewHistory(const std::string& filename = "comparison_history.csv");
};
#endif
