#include <iostream>
#include "analyzer.h"
#include <vector>
#include <fstream>
#include <string>

int main()
{
    std::vector<LogEntry> logs;
    std::vector<int> prefixErrors;
    prefixErrors.push_back(0);
    std::ifstream file("data/sample.log");
    int currentErrors = 0;
    if (!file.is_open())
    {
        std::cerr << "Failed to open file." << std::endl;
        return 1;
    }
    std::string line;
    while (std::getline(file, line))
    {
        if (!line.empty()) {
            logs.push_back(parseLogLine(line));
            if (logs.back().level == "ERROR" || logs.back().level == "CRITICAL") {
                currentErrors++;
            }
            prefixErrors.push_back(currentErrors);
        }
    }
    file.close();
    findLogsInTimeRange(logs, prefixErrors, "2026-07-17 08:30:00", "2026-07-17 09:00:00");
    return 0;
}