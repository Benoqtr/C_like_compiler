class Tokenizer {
public:
    Tokenizer(const std::string& fileName);
    void tokenize();
    std::string getNextToken();

private:
    std::string program;
    std::queue<std::string> tokens;
};