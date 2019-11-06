# MultipleTestingSystem
Implementation of a concurrent testing framework

## How to compile and run
an input and output text files are given
input file: multiple test file locations
output file: expected output of complementary input test

use gcc to compile .c files and run the following command in your console:
./test-framework --input="/path/to/input" --output="/path/to/output

using multiple parallel WINAPI threads and processes tests are performed concurrently
a signal is returned if a test succeeded or failed/crashed/timed out.

## IDE
Written and compiled in Visual Studio 2017

## License
[MIT](https://choosealicense.com/licenses/mit/)
