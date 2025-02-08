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

    // Output the parsed data
    //std::cout << "\nJobs parsed:\n";
    //for (const auto &job : jobs) {
        //std::cout << "Minute: " << job.minute
                  //<< ", Hour: " << job.hour
                  //<< ", File: " << job.filename << "\n";
    //}

    std::cout << "Final time: "
              << (hour < 10 ? "0" : "") << hour << ":"
              << (minute < 10 ? "0" : "") << minute << "\n";

    for (auto& job : jobs) {
        if (job.hour.has_value()) {
            if (job.hour < hour) {
                if (!job.minute.has_value()) {
                    job.minute = 0;
                }
                std::cout << job.hour.value() << ":" << job.minute.value() << " tomorrow - " << job.filename << "\n";
                continue;
            }
            if (job.hour > hour) {
                if (!job.minute.has_value()) {
                    job.minute = 0;
                }
                std::cout << job.hour.value() << ":" << job.minute.value() << " today - " << job.filename << "\n";
                continue;
            }
            if (!job.minute.has_value()) {
                job.minute = minute;
            }
            if (job.minute < minute) {
                std::cout << job.hour.value() << ":" << job.minute.value() << " tomorrow - " << job.filename << "\n";

            } else {
                std::cout << job.hour.value() << ":" << job.minute.value() << " today - " << job.filename << "\n";
            }
        } else {
            if (!job.minute.has_value()) {
                job.minute = minute;
            }
            if (job.minute < minute) {
                std::string day = " today ";
                job.hour = hour + 1;
                if (job.hour == 24) {
                    job.hour = 0;
                    day = " tomorrow ";
                }
                std::cout << job.hour.value() << ":" << job.minute.value() << day << job.filename << "\n";
            } else {
                std::cout << hour << ":" << job.minute.value() << " today - " << job.filename << "\n";
            }
        }
    }

    return 0;
}
