# MultipleTestingSystem
Implementation of a concurrent testing framework

## How to compile and run
an input and output text files are given
input file: multiple test file locations
output file: expected output of complementary input test

### On Windows OS: 
1. download and install MinGW: https://osdn.net/projects/mingw/downloads/68260/mingw-get-setup.exe/
2. download all project files into the same folder, insert the following command: cd /...your_file_path.../
3. insert the following command: gcc *.c -o FrameWork
4. insert the following command: FrameWork --input="/path/to/input" --output="/path/to/output

using multiple parallel WINAPI threads and processes tests are performed concurrently
a signal is returned if a test succeeded or failed/crashed/timed out.

## IDE
Written and compiled in Visual Studio 2017

## License
[MIT](https://choosealicense.com/licenses/mit/)
