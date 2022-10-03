#include "Token.h"

Token::Token(TokenType type, std::string description, int line) {
    // DONE: (Probably done but check back) initialize all member variables
    Token::type = type;
    Token::value = description;
    Token::line = line;

}

int Token::getLine() {return line;}

std::string Token::getValue() {return value;}

TokenType Token::getType() {return type;}

std::string Token::typeToString(TokenType type) {
    switch (type) {
        case TokenType::COMMA:
            return "COMMA";
        case TokenType::PERIOD:
            return "PERIOD";
        case TokenType::Q_MARK:
            return "Q_MARK";
        case TokenType::LEFT_PAREN:
            return "LEFT_PAREN";
        case TokenType::RIGHT_PAREN:
            return "RIGHT_PAREN";
        case TokenType::COLON:
            return "COLON";
        case TokenType:: COLON_DASH:
            return "COLON_DASH";
        case TokenType::MULTIPLY:
            return "MULTIPLY";
        case TokenType::ADD:
            return "ADD";
        case TokenType::SCHEMES:
            return "SCHEMES";
        case TokenType::FACTS:
            return "FACTS";
        case TokenType::RULES:
            return "RULES";
        case TokenType::QUERIES:
            return "QUERIES";
        case TokenType::ID:
            return "ID";
        case TokenType::STRING:
            return "STRING";
        case TokenType::COMMENT:
            return "COMMENT";
        case TokenType::UNDEFINED:
            return "UNDEFINED";
        case TokenType::END_OF_FILE:
            return "EOF";
        default:
            return "UNDEFINED";
    }
}
std::string Token::toString() {
    return  "(" + Token::typeToString(Token::type) + ",\"" + Token::value + "\"," + std::to_string(Token::line) + ")";
}
