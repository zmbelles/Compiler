//
//  main.cpp
//  LexicalAnalyzer
//
//  Created by Zach Belles on 9/21/21.
//

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>

using namespace std;

class LexAnalyzer{
    
    private:
    
        vector<string> lexemes;  // source code file lexemes
        vector<string> tokens;   // source code file tokens
        map<string, string> tokenmap;  // valid lexeme/token pairs
        // other private methods
    public:

    LexAnalyzer(istream& infile){}
    // pre: parameter refers to an open data file consisting of token and
    // lexeme pairs i.e.  s_and and t_begin begin t_int 27.  Each pair    // appears on its own input line.
    // post: tokenmap has been populated
        
    void scanFile(istream& infile, ostream& outfile);
    // pre: 1st parameter refers to an open text file that contains source
    // code in the language, 2nd parameter refers to an open empty output
    // file
    // post: If no error, the token and lexeme pairs for the given input
    // file have been written to the output file and the vectors have been // populated.  If there is an error, incomplete token/lexeme pairs are
    // written to the output file and populated in the vectors.  An error // message is also written to the file. A success or fail message has // printed to the console.

};


int main () {
    filebuf fb;
    cout << "Please enter the name of the file you wish to compile: ";
    string fileName;
    cin >> fileName;
    fb.open(fileName, ios::in);
    
    istream infile(&fb);
    
    LexAnalyzer LA(infile);
    
    fb.close();
    return 0;
}
