#include "Lexer.h"
#include "Parser.h"
#include <iostream>
#include <fstream>
#include <sstream>

//I've read it's bad to include .cpp files, but I get an error
//if I don't include this. When I find another way to make the
//program work I'll cut this out.
//#include "Lexer.cpp"

using namespace std;

int main(int argc, char** argv) {

    Lexer* lexer = new Lexer();
    Parser* parser = new Parser();

    // TODO (we're just doing testing now, but this might work for the main method. We'll see if it needs tweaks before we submit)
    string filePath = argv[1];
    //string fileName = filePath + " " + argv[2]; Not sure why this was working for certain files, but it works now without it lol
    ifstream t(filePath);
    stringstream buffer;
    buffer << t.rdbuf();

    string file = buffer.str();
    string& input = file;

    lexer->Run(input);

    /*for (Token* token : lexer->getTokens()) {
        cout << token->toString() << "\n";
    }*/

    std::vector<Token*> outPut = lexer->getTokens();

    try {
        cout << parser->Run(outPut).toString();
    } catch (...) {
        std::cout << "Failure!\n  " + parser->currentToken()->toString();
    }

    delete lexer;
    delete parser;

    return 0;
}