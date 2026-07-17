#ifndef ANALYZER_H
#define ANALYZER_H

#include <string>
#include <vector>

struct LogEntry {
    std::string timestamp; 
    std::string level;     
    std::string ip;        
    std::string message;   
};
LogEntry parseLogLine(const std::string& line);
void generateReport(const std::vector<LogEntry>& logs);
void findLogsInTimeRange(const std::vector<LogEntry>& logs, const std::vector<int>& prefixErrors, const std::string& startTime, const std::string& endTime);

#endif