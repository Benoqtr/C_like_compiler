#include <cstdlib>
#include <iostream>
#include <string>

class OBJconstructor {
public:
    OBJconstructor(const std::string& inputFileName, const std::string& outputFileName)
        : inputFileName(inputFileName), outputFileName(outputFileName) {}

    void execute() {
        std::string command = "clang -c " + inputFileName + " -o " + outputFileName;
        int result = std::system(command.c_str());

        if (result == 0) {
            std::cout << "Command executed successfully.\n";
        } else {
            std::cerr << "Error executing the command.\n";
        }
    }

private:
    std::string inputFileName;
    std::string outputFileName;
};