namespace lexical{

using tokensPtr = compile::tokensPtr;

using compileConfig = compile::compileConfig;

class Tokenizer {
public:
    Tokenizer(compileConfig config,
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