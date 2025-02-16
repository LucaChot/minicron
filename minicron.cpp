#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

// Uses std::nullopt to represent * case
struct Job {
    int minute;
    int hour;
    std::string filename;
};

// Parses input string and creates corresponding Job struct
// Returns optional type in the case when the string can't be parse
int parse_job(std::string line, Job& job){
    // Use istringstream to parse the job line
    try {
    std::istringstream iss(line);
    std::string temp_minute, temp_hour, temp_filename;
    if ((iss >> temp_minute >> temp_hour >> temp_filename)) {
        if (temp_minute[0] == '*') {
            job.minute = 60;
        } else {
            job.minute = std::stoi(temp_minute);
        }
        if (temp_hour[0] == '*') {
            job.hour = 24;
        } else {
            job.hour = std::stoi(temp_hour);
        }
        job.filename = temp_filename;
        return 0;
    }
    throw std::invalid_argument("invalid argument");
    }
    catch (...) {
    std::cerr << "Error parsing job line: " << line << std::endl;
    return 1;
    }
}

int main(int argc, char* argv[]) {
    std::vector<Job> jobs;
    std::string line;
    std::string time;

    // Checks for current time argument
    if (argc != 2) {
        std::cerr << "Usage: ./main HH:MM" << std::endl;
        return 1;
    }

    // Parses current time argument using istringstream
    std::string current_time = argv[1];
    int hour = 0, minute = 0;
    current_time[current_time.find(':')] = ' ';

    std::istringstream timeStream(current_time);
    if (!(timeStream >> hour  >> minute)) {
        std::cerr << "Error parsing final time: " << current_time << "\n";
        return 1;
    }


    // Loops over input buffer, parsing over each line and calculating the next
    // time the job will run
    while (std::getline(std::cin, line)) {
        Job job;
        // Skips if line fails to parse
        if (parse_job(line, job)) {
            continue;
        }

        // Handles the every hour case
        if (job.hour == 24) {
            job.hour = hour;

            // If every minute -> run now
            if (job.minute == 60) {
                job.minute = minute;
            }

            // If we missed the minute -> run next hour
            if (job.minute < minute) {
                job.hour = (hour + 1) % 24;
            }
        }

        // Base case is runs today
        std::string day = " today ";

        // Handles different timing cases
        if (job.hour < hour) {
            // If every minute -> run in the first minute
            if (job.minute == 60) {
                job.minute = 0;
            }
            day = " tomorrow ";
        } else if (job.hour > hour) {
            // If every minute -> run in the first minute
            if (job.minute == 60) {
                job.minute = 0;
            }
        } else {
            // If every minute -> run this minute
            if (job.minute == 60) {
                job.minute = minute;
            }
            if (job.minute < minute) {
                day = " tomorrow ";
            }
        }
        // Outputs the next time the job will run
        std::cout << job.hour << ":"
                  << (job.minute < 10 ? "0" : "") << job.minute
                  << day << "- " << job.filename << std::endl;
    }

    return 0;
}
