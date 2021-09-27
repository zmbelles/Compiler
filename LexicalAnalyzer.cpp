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
    int findPairs(const string& thisCode, const string& thisLex){
        
        int done;
        done = thisCode.find(thisLex);
        if(done != -1){
            if(thisCode == thisLex){
                done = 0;
            }
            else{
                done = 1;
            }
        }
        return done;
    }
    
    void splitString(string& thisCode, ostream& outFile){
        bool found = false;
        string alpha = "qwertyuiopasdfghjklzxcvbnm";
        for(int i=0; i<thisCode.size(); i++){
            for(int j=0; j<alpha.size(); j++){
                if(thisCode[i]==alpha[j]){
                    found = true;
                    break;
                }
            }
            if(found == false){
                char code = thisCode[i];
                string newCode(1, code);
                map<string, string>::iterator mitr;
                for(mitr=tokenmap.begin(); mitr != tokenmap.end(); ++mitr){
                    string thisLex = mitr->first;
                    int done = findPairs(newCode, thisLex);
                    if(done == 0){
                        thisLex = mitr->second;
                        outFile << thisLex << " : " << newCode << endl;
                        cout << "yerp" << endl;

                    }
                }
            }
            found = false;
        }
        
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
            tokenmap.insert(pair<string,string>(thisToken, lex));
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
        // pre: 1st parameter refers to an open text file that contains source
        // code in the language, 2nd parameter refers to an open empty output
        // file
        // post: If no error, the token and lexeme pairs for the given input
        // file have been written to the output file and the vectors have been
        // populated.  If there is an error, incomplete token/lexeme pairs are
        // written to the output file and populated in the vectors.  An error
        // message is also written to the file. A success or fail message has
        // printed to the console.
        
        string thisCode;
        string thisLex;
        infile >> thisCode;
        while(!infile.eof()){
            
            map<string, string>::iterator mitr;
            for(mitr=tokenmap.begin(); mitr != tokenmap.end(); mitr++){
                thisLex = mitr->first;
                int done = findPairs(thisCode, thisLex);
                if(done == 0){
                    outfile << thisLex << " : " << thisCode << endl;
                }
                else if(done == 1){
                    splitString(thisCode, outfile);
                }
            }
        }
    }
    
        /*
     what is needed?
    
     each line needs:
     
        if '(', check for ')'
        if '"', check for '"'
        
     Check each symbol/string/int against its key, value pair
     */
};


int main () {
    ifstream tokenFile;
    tokenFile.open("token.txt");
    LexAnalyzer la(tokenFile);
    /*
    cout << "source code file name: ";
    string sourceString;
    sourceString = cin.get();
    ofstream outFile;
    outFile.open("OutputFile.txt");
     */
    ifstream sourceCode;
    sourceCode.open("SampleCode.txt");
    ofstream outFile;
    outFile.open("OutputFile.txt");
    la.scanFile(sourceCode, outFile);
}
