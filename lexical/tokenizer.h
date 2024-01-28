#include "config.h"

namespace lexical{

using tokensPtr = std::shared_ptr<std::vector<
    std::pair<std::string,std::string>>>;

using config::Config;

class Tokenizer {
public:
    Tokenizer(Config config,
    const std::string& fileName);
    tokensPtr getTokens();

private:
    compileConfig config;
    std::string sourceFilePath;
    std::queue<std::string> raw_tokens;
    std::vector<std::pair<std::string, std::string>> tokens;
    std::stringstream program;

    void tokenize();
    void match();
};

}