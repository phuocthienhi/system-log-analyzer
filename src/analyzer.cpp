#include "analyzer.h"
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <algorithm>

LogEntry parseLogLine(const std::string& line) {
    LogEntry entry;
    std::istringstream iss(line);
    std::string date, time;

    if (iss >> date >> time) entry.timestamp = date.substr(1) + " " + time.substr(0, time.length() - 1);
    if (iss >> entry.level) entry.level = entry.level.substr(1, entry.level.length() - 2);
    if (iss >> entry.ip) entry.ip = entry.ip.substr(1, entry.ip.length() - 2);
    
    std::string word;
    while (iss >> word) {
        entry.message += word + " ";
    }
    if (!entry.message.empty()) {
        entry.message.pop_back();
    }
    return entry;
}

void generateReport(const std::vector<LogEntry>& logs) {

    std::unordered_map<std::string, int> errorCount;
    int totalErr = 0;
    for (const auto& log : logs) {
        if (log.level == "ERROR" || log.level == "CRITICAL") {
            errorCount[log.message]++;
            totalErr++;
        }
    }

    std::cout << "\n=== System Report ===" << std::endl;
    std::cout << "Total logs: " << logs.size() << std::endl;
    std::cout << "Total errors: " << totalErr << std::endl;

    if (totalErr > 0) {
        std::string mostFrequentError;
        int maxCount = 0;
        for (const auto& pair : errorCount) {
            if (pair.second > maxCount) {
                maxCount = pair.second;
                mostFrequentError = pair.first;
            }
        }
        std::cout << "Most frequent error: " << mostFrequentError << " (" << maxCount << " occurrences)" << std::endl;
    }
    std::cout << "========================\n" << std::endl;
}

// ... (Giữ nguyên hàm parseLogLine và generateReport ở trên)

void findLogsInTimeRange(const std::vector<LogEntry>& logs, const std::vector<int>& prefixErrors, const std::string& startTime, const std::string& endTime) {
    auto cmp_1 = [](const LogEntry& a, const std::string& val) {
        return a.timestamp < val;
    };
    auto cmp_2 = [](const std::string& val, const LogEntry& a) {
        return val < a.timestamp;
    };
    
    auto lower = std::lower_bound(logs.begin(), logs.end(), startTime, cmp_1);
    auto upper = std::upper_bound(logs.begin(), logs.end(), endTime, cmp_2);

    int start_idx = std::distance(logs.begin(), lower);
    int end_idx = std::distance(logs.begin(), upper);

    std::cout << "Logs found between " << startTime << " and " << endTime << ":" << std::endl;
    for (auto it = lower; it != upper; ++it) {
        std::cout << "[" << it->timestamp << "] " << it->level << " " << it->ip << " " << it->message << std::endl;
    }
    int count = end_idx - start_idx;
    int errorsInRange = prefixErrors[end_idx] - prefixErrors[start_idx];
    std::cout << "Total logs found: " << count << std::endl;
    std::cout << "Total errors found (ERROR/CRITICAL): " << errorsInRange << std::endl;
}