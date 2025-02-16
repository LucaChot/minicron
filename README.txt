STRUCTURE
- minicron.cpp // Source code for simplified cron parser
- test.sh // Script that runs multiple test cases on `minicron` to check its
  basic correctness
- test_cases // Directory containing the test cases used by `test.sh`

STEPS
To compile and run minicron
- Run `g++ -o minicron minicron.cpp`
- Execute `cat [config file name] | minicron [current time in HH:MM]

To run the test.sh script
- Run chmod +x test.sh
- Ensure SCRIPT variable in test.sh is pointing to `minicron` program
- Ensure test_cases directory exists
- Run `./test.sh`
