#include "Lexer.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"
#include "CommaAutomaton.h"
#include "PeriodAutomaton.h"
#include "Token.h"
#include "QMarkAutomaton.h"
#include "LeftParenAutomaton.h"
#include "RightParenAutomaton.h"
#include "MultiplyAutomaton.h"
#include "AddAutomaton.h"
#include "SchemesAutomaton.h"
#include "FactsAutomaton.h"
#include "RulesAutomata.h"
#include "QueriesAutomaton.h"
#include "IdAutomaton.h"
#include "LineCommentAutomaton.h"
#include "BlockCommentAutomaton.h"
#include "StringAutomaton.h"
#include "BadStringAutomaton.h"

/*  For reasons I'm not aware of, the program throws an error if I don't include
 *  the .cpp files for Token, ColonAutomaton, and ColonDashAutomaton (it seems
 *  to be unable to find the definitions for Token's functions and a vtable
 *  for ColonAutomaton and ColonDashAutomaton), but it throws different errors
 *  when I do include PeriodAutomaton's .cpp file and CommaAutomaton's .cpp file.
 *
 *  From what I read online, including .cpp files is not a good idea, but
 *  the program seems to work when I have them in, so I'm not going to touch this
 *  until I get a better idea of what's going on, and how to fix it.
 * */

//#include "Token.cpp"
//#include "ColonDashAutomaton.cpp"
//#include "ColonAutomaton.cpp"
//#include "PeriodAutomaton.cpp"
//#include "CommaAutomaton.cpp"

Lexer::Lexer() {
    CreateAutomata();
}

Lexer::~Lexer() {
    // TODO: (maybe done check back) need to clean up the memory in `automata` and `tokens`
    for (Automaton* automaton : automata) {
        delete automaton;
    }
    automata.clear();

    for (Token* token : tokens) {
        delete token;
    }
    tokens.clear();
}

void Lexer::CreateAutomata() {
    //Add one Automaton of each.
    automata.push_back(new ColonAutomaton());
    automata.push_back(new ColonDashAutomaton());
    automata.push_back(new CommaAutomaton());
    automata.push_back(new PeriodAutomaton());
    automata.push_back(new QMarkAutomaton());
    automata.push_back(new LeftParenAutomaton());
    automata.push_back(new RightParenAutomaton());
    automata.push_back(new MultiplyAutomaton());
    automata.push_back(new AddAutomaton());
    automata.push_back(new SchemesAutomaton());
    automata.push_back(new FactsAutomaton());
    automata.push_back(new RulesAutomaton());
    automata.push_back(new QueriesAutomaton());
    automata.push_back(new IdAutomaton());
    automata.push_back(new LineCommentAutomaton());
    automata.push_back(new BlockCommentAutomaton());
    automata.push_back(new StringAutomaton());
    automata.push_back(new BadStringAutomaton());
    // TODO: Add the other needed automata here
    //We will loop through these for every new token to see which fits.
}

void Lexer::Run(std::string& input) {
    // DONE: (maybe done come back later) convert this pseudo-code with the algorithm into actual C++ code
    //Start at line 1
    int lineNumber = 1;

    //Loop until we run out of characters in the input string.
    while (!input.empty()) {

        //The parallel max algorithm needs us to loop through every automaton, so start at the beginning
        int maxRead = 0;
        maxAutomaton = automata[0];

        //Handle white space (delete it until we get something else)
        while (true) {
            if (std::isspace(input[0])) {
                if (input.substr(0,1) == "\n") {
                    //If our whitespace is a newline, we need to keep track of it.
                    //We still delete it, though.
                    lineNumber++;
                    input.erase(0, 1);
                } else {
                    input.erase(0, 1);
                }
            } else {
                break;
            }
        }
        //This won't bother things like comments and identifiers that rely on whitespace to end
        //because we only delete the whitespace at the beginning.

        //Since the last bits of the file might have been whitespace, we have to make sure
        //that there's still something to read after deleting it.
        if (input.empty()) {
            break;
        }

        //Loop through the automata. If they read more than our current best contender,
        //they become the next new maxAutomaton. By the end we'll know which read the most,
        //which we'll use to make the token.
        for (Automaton* automaton : automata) {
            int inputRead = automaton->Start(input);
            if (inputRead > maxRead) {
                maxRead = inputRead;
                maxAutomaton = automaton;
            }
        }

        //If we read something, make a token with the info from the maxAutomaton
        if (maxRead > 0) {
            Token* newToken = maxAutomaton->CreateToken(input.substr(0, maxRead), lineNumber);
            lineNumber += maxAutomaton->NewLinesRead();
            tokens.push_back(newToken);
        } else { //If we didn't read more than 0 characters, we have an undefined token.
            maxRead = 1;
            Token* newToken = new Token(TokenType::UNDEFINED, input.substr(0, 1), lineNumber);
            tokens.push_back(newToken);
            //We'll have an undefined token automaton to find unfinished block comments and unfinished
            //strings, but this takes care of the odd characters we shouldn't expect.
        }

        //remove maxRead characters from input (so we start after the token we just found)
        //if we read a newline, update lineNumber
        for (int i = 0; i < maxRead; i++) {
            if (input[i] == '\n') {
                lineNumber++;
            }
        }
        input.erase(0, maxRead);
    }

    //Once we're done, that's the end of the file, put an EOF token at the end with the line number.
    tokens.push_back(new Token(TokenType::END_OF_FILE, "", lineNumber));
    /*
    set lineNumber to 1
    // While there are more characters to tokenize
    loop while input.size() > 0 {
        set maxRead to 0
        set maxAutomaton to the first automaton in automata

        // DONE: (maybe done check back) you need to handle whitespace inbetween tokens

        // Here is the "Parallel" part of the algorithm
        //   Each automaton runs with the same input
        foreach automaton in automata {
            inputRead = automaton.Start(input)
            if (inputRead > maxRead) {
                set maxRead to inputRead
                set maxAutomaton to automaton
            }
        }
        // Here is the "Max" part of the algorithm
        if maxRead > 0 {
            set newToken to maxAutomaton.CreateToken(...)
                increment lineNumber by maxAutomaton.NewLinesRead()
                add newToken to collection of all tokens
        }
        // No automaton accepted input
        // Create single character undefined token
        else {
            set maxRead to 1
                set newToken to a  new undefined Token
                (with first character of input)
                add newToken to collection of all tokens
        }
        // Update `input` by removing characters read to create Token
        remove maxRead characters from input
    }
    add end of file token to all tokens
    */
}

std::vector<Token*> Lexer::getTokens() {
    return tokens;
}
