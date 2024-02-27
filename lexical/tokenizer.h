#pragma once
#include "config.h"
#include <sstream>
#include <queue>

namespace lexical{

using tokensPtr = std::shared_ptr<std::vector<
    std::pair<std::string,std::string>>>;

using rawTokenPtr = std::shared_ptr<std::queue<std::string>>;

using config::Config;

class Tokenizer {
public:
    Tokenizer(const Config& config, const std::string& filePath);
    rawTokenPtr getRawToken();
    tokensPtr getTokens();

private:
    bool gotRawToken = false;
    rawTokenPtr raw_tokens; //split words
    Config config;
    std::string sourceFilePath;
    std::vector<std::pair<std::string, std::string>> tokens;
    std::stringstream program;

    bool splitToken();
    void match();
};

}