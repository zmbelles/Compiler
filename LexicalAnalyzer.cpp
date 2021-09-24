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
    bool symbolChecker(string symbol){
        bool missingPair = false;
        
        
        return missingPair;
    }
    /*
     pre:
        param: an empty file
     post:
        file populated with each key value pair in chronological order of source code
     */
        
    void writeToFile(istream& oFile){
        
    }
    public:

    LexAnalyzer(istream& infile){
        // pre: parameter refers to an open data file consisting of token and
        // lexeme pairs i.e.  s_and and t_begin begin t_int 27.  Each pair    // appears on its own input line.
        // post: tokenmap has been populated
        string thisToken;
        string lex;
        
        infile >> lex;
        infile >> thisToken;
        while(!infile.eof()){
            tokenmap.insert(pair<string,string>(lex, thisToken));
            infile >> lex;
            infile >> thisToken;
        }
        
        //may need later
        
//        map<string, string>::iterator mitr;
//        for(mitr = tokenmap.begin(); mitr != tokenmap.end(); ++mitr){
//            cout << mitr->first << " " << mitr->second << endl;
//        }
    }
    
    //DO NOT CARE ABOUT SYNTAX
    void scanFile(istream& infile, ostream& outfile){
        
        string thisSegment;
        infile >> thisSegment;
        map<string, string>::iterator mitr;
            for(mitr = tokenmap.begin(); mitr != tokenmap.end(); ++mitr){
                if(thisSegment == mitr->second){
                    cout << "we're here" << endl;
                }
            }
    }
    
    // pre: 1st parameter refers to an open text file that contains source
    // code in the language, 2nd parameter refers to an open empty output
    // file
    // post: If no error, the token and lexeme pairs for the given input
    // file have been written to the output file and the vectors have been // populated.  If there is an error, incomplete token/lexeme pairs are
    // written to the output file and populated in the vectors.  An error // message is also written to the file. A success or fail message has // printed to the console.
    
    /*
     what is needed?
    
     each line needs:
     
        if '(', check for ')'
        if '"', check for '"'
        
     Check each symbol/string/int against its key, value pair
     */
};


int main () {
    filebuf fb;
    
    cout << endl;
    fb.open("token.txt", ios::in);
    
    istream infile(&fb);
    
    LexAnalyzer LA(infile);
    fb.close();
    //    cout << "Please enter the name of the file you wish to compile: ";
    //    string fileName;
    //    cin >> fileName;
    fb.open("SampleCode.txt", ios::in);
    LA.scanFile(<#istream &infile#>, <#ostream &outfile#>)
    
    
    return 0;
}
