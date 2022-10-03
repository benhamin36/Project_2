#ifndef TOKEN_H
#define TOKEN_H
#include <string>

enum class TokenType {
    COMMA,
    PERIOD,
    Q_MARK,
    LEFT_PAREN,
    RIGHT_PAREN,
    COLON,
    COLON_DASH,
    MULTIPLY,
    ADD,
    SCHEMES,
    FACTS,
    RULES,
    QUERIES,
    ID,
    STRING,
    COMMENT,
    END_OF_FILE,
    // DONE: added other token types
    UNDEFINED
};

class Token
{
private:
    // DONE: (maybe done, but check back) add member variables for information needed by Token
    TokenType type;
    std::string value;
    int line;

public:
    Token(TokenType type, std::string description, int line);
    // DONE: (maybe done, but check back) add other needed methods

    TokenType getType();
    std::string getValue();
    int getLine();

    static std::string typeToString(TokenType type);
    std::string toString();
};

#endif // TOKEN_H

