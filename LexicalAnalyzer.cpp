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
    /*
     pre:
        param 1: an string to hold each lexeme
        param 2: the segment of code to be checked
        param 3: the outputfile to write to
     post:
        thisCode is found in thisLex, and paired with mitr->second in outfile
     */
    bool checkMap(string& thisLex, string& thisCode, ostream& outfile){
        bool added = false;
        map<string, string>::iterator mitr;
        for(mitr=tokenmap.begin(); mitr != tokenmap.end(); mitr++){
            thisLex = mitr->first;
            if(thisCode == thisLex){
                thisLex = mitr->second;
                outfile << thisLex << " : " << thisCode << endl;
                added = true;
            }
        }
        return added;
    }
    bool findStringFull(string thisCode, ostream& outfile){
        char thisChar;
        bool eos = false;
        string fullString;
        for(int i=0; i<thisCode.size(); i++){
            thisChar = thisCode[i];
            if(thisChar == '"'){
                eos == true;
                outfile << "t_str" << fullString;
            }
            fullString += thisChar;
        }
        return eos;
    }
    /*
     pre:
        param 1: the segment of code to be concatinated and checked
        param 2: the output file to pass to checkMap when needed
     post:
        the keyword/string is passed back to the function that called it with operators posted to outfile
     */
    string concatSourceCode(string& thisCode, ostream& outfile, istream& infile){
        string codeConcat;
        string thisLex;
        bool endOfString = true;
        for(int i=0; i< thisCode.size(); i++){
            char thisChar = thisCode[i];
            if(!isalpha(thisChar)){
                if((thisChar == '"' || thisChar == '\'')&& !endOfString){
                    bool eos = findStringFull(thisCode, outfile);
                    if(!eos){
                        cout << "Compiliation Error: No end quotation of string" << endl;
                        outfile << "Compiliation Error: No end quotation of string" << endl;
                    }
                }
                string codeSeg(1, thisChar);
                bool added = checkMap(thisLex, codeSeg, outfile);
                if(!added){
                    cout << "an unexpected error occured" << endl;
                    string why;
                    cin >> why;
                }
            }
            else{
                codeConcat += thisCode[i];
            }
        }
        return codeConcat;
    }
    
    public:

    LexAnalyzer(istream& infile){
        // pre: parameter refers to an open data file consisting of token and
        // lexeme pairs i.e.  s_and and t_begin begin t_int 27.  Each pair
        // appears on its own input line.
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
        string wordToken;
        string thisLex;
        while(getline(infile, thisCode)){
            string wordToken = concatSourceCode(thisCode, outfile, infile);
            checkMap(thisLex, wordToken, outfile);
            infile >> thisCode;
        }
    }
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
