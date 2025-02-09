#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

struct Job {
    std::optional<int> minute;
    std::optional<int> hour;
    std::string filename;
};

int main() {
    std::vector<Job> jobs;
    std::string line;
    std::string time;

    std::cout << "Hello, World!" << std::endl;

    while (std::getline(std::cin, line)) {

        if(line.find(':') != std::string::npos) {
            time = line;
            break;
        }

        // Use istringstream to parse the job line
        std::istringstream iss(line);
        Job job;
        std::string temp_minute, temp_hour, temp_filename;
        if ((iss >> temp_minute >> temp_hour >> temp_filename)) {
            if (temp_minute[0] == '*') {
                job.minute = std::nullopt;
            } else {
                job.minute = std::stoi(temp_minute);
            }
            if (temp_hour[0] == '*') {
                job.hour = std::nullopt;
            } else {
                job.hour = std::stoi(temp_hour);
            }
            job.filename = temp_filename;
        } else {
            std::cerr << "Error parsing job line: " << line << "\n";
            continue; // Skip this line if parsing fails
        }

        jobs.push_back(job);
    }

    int hour = 0, minute = 0;
    if(!time.empty()) {
        time[time.find(':')] = ' ';

        std::istringstream timeStream(time);
        if (!(timeStream >> hour  >> minute)) {
            std::cerr << "Error parsing final time: " << time << "\n";
            return 1;
        }
    } else {
        std::cerr << "No final time input was provided.\n";
        return 1;
    }

    for (auto& job : jobs) {
        std::string day = " today ";
        if (job.hour.has_value()) {
            if (job.hour < hour) {
                if (!job.minute.has_value()) {
                    job.minute = 0;
                }
                day = " tomorrow ";
            } else if (job.hour > hour) {
                if (!job.minute.has_value()) {
                    job.minute = 0;
                }
            } else {
                if (!job.minute.has_value()) {
                    job.minute = minute;
                }
                if (job.minute < minute) {
                    day = " tomorrow ";
                }
            }
        } else {
            if (!job.minute.has_value()) {
                job.minute = minute;
            }
            if (job.minute < minute) {
                job.hour = hour + 1;
                if (job.hour == 24) {
                    job.hour = 0;
                    day = " tomorrow ";
                }
            } else {
                job.hour = hour;
            }
        }
        std::cout << job.hour.value() << ":" << (job.minute.value() < 10 ? "0" : "") << job.minute.value() << day << "- " << job.filename << "\n";
    }

    return 0;
}
