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
        returns true if an element was added to the outfile
     */
    bool checkMap(const string& thisCode, ostream& outfile){
        bool added = false;
        string thisLex;
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
    /*
     pre:
        param 1: the unchecked code segment containing a string
        param 2: an open output file to write to
     post:
        thisCode is checked for the entire string which is reflected
        in the outfile. all after the end quote is also processed.
        returns true if endquote is present
     */
    bool findStringFull(const string& thisCode, ostream& outfile){
        char thisChar;
        bool eos = false;
        string fullString;
        for(int i=0; i<thisCode.size(); i++){
            thisChar = thisCode[i];
            if(thisChar == '"'){
                eos = true;
                outfile << "t_str" << " : " << fullString << endl;
            }
            else if(!isalnum(thisChar) && eos == true){
                string thisSym(1,thisChar);
                checkMap(thisSym, outfile);
            }
            fullString += thisChar;
        }
        return eos;
    }
    /*
     pre:
        param 1: the unchecked code segment containing an integer
        param 2: an open output file to write to
     post:
        thisCode is checked for the entire integer which is reflected
        in the outfile. all after the delimiter is also processed.
        returns true if valid integer is present
     */
    bool findIntFull(const string& thisCode, ostream& outfile){
        string fullInt;
        bool found = false;
        int size = thisCode.size();
        for(int i=0; i<size; i++){
            if(isdigit(thisCode[i])){
                fullInt += thisCode[i];
            }
            else if(!isalnum(thisCode[i])){
                if(thisCode[i] != '\n'){
                    outfile << "t_int" << " : " << fullInt << endl;
                    found = true;
                }
            }
            else if(isalpha(thisCode[i])){
                outfile << "A compilation error has occured. " << fullInt << "is not a valid integer" << endl;
                cout << "A compilation error has occured. " << fullInt << "is not a valid integer" << endl;
                found = false;
            }
        }
        return found;
    }
    /*
     pre:
        param 1: the segment of code to be concatinated and checked
        param 2: the output file to pass to checkMap when needed
     post:
        the keyword/string is passed back to the function that called it with operators posted to outfile
     */
    string concatSourceCode(const string& thisCode, ostream& outfile){
        string codeConcat;
        string untestedString;
        bool eos;
        
        for(int i=0; i< thisCode.size(); i++){
            char thisChar = thisCode[i];
            
            if(!isalnum(thisChar)){
                
                eos = checkMap(codeConcat, outfile);
                if(!eos && codeConcat != ""){
                    outfile << "t_id : " << codeConcat << endl;
                }
                codeConcat = "";
                
                if((thisChar == '"' || thisChar == '\'')){
                    untestedString.assign(thisCode.begin()+i+1, thisCode.end());
                    eos = findStringFull(untestedString, outfile);
                    
                    if(!eos && untestedString != ""){
                        cout << "Compiliation Error: No end quotation of string" << endl;
                        outfile << "Compiliation Error: No end quotation of string. " << endl;
                        outfile << "t_id : " << untestedString << endl;
                        return "str_fail";
                    }
                    i = thisCode.size()-1;
                }
                else{
                    string nonalnum(1, thisChar);
                    checkMap(nonalnum, outfile);
                }
            }
            
            else if(isdigit(thisChar)){
                untestedString.assign(thisCode.begin()+i, thisCode.end());
                eos = findIntFull(untestedString, outfile);
                
                if(!eos){
                    
                    cout << "Compiliation Error: No end quotation of string" << endl;
                    outfile << "Compiliation Error: No end quotation of string" << endl;
                    return "int_fail";
                }
            }
            else
                codeConcat += thisChar;
        }
        return codeConcat;
    }
    
    public:
    
    // pre: parameter refers to an open data file consisting of token and
    // lexeme pairs i.e.  s_and and t_begin begin t_int 27.  Each pair
    // appears on its own input line.
    // post: tokenmap has been populated
    LexAnalyzer(istream& infile){
        
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
    // pre: 1st parameter refers to an open text file that contains source
    // code in the language, 2nd parameter refers to an open empty output
    // file
    // post: If no error, the token and lexeme pairs for the given input
    // file have been written to the output file and the vectors have been
    // populated.  If there is an error, incomplete token/lexeme pairs are
    // written to the output file and populated in the vectors.  An error
    // message is also written to the file. A success or fail message has
    // printed to the console.
    
    void scanFile(istream& infile, ostream& outfile){
        
        string thisCode;
        string wordToken;
        while(getline(infile, thisCode, '\n')){
            string wordToken = concatSourceCode(thisCode, outfile);
            if(wordToken == "str_fail" || wordToken == "int_fail"){
                return;
            }
            checkMap(wordToken, outfile);
        }
        cout << "done" << endl;
    }
};

int main () {
    ifstream tokenFile;
    tokenFile.open("token.txt");
    LexAnalyzer la(tokenFile);
    cout << "source code file name: ";
    string sourceString;
    sourceString = cin.get();
    ifstream sourceCode;
    sourceCode.open(sourceString);
    ofstream outFile;
    outFile.open("OutputFile.txt");
    la.scanFile(sourceCode, outFile);
}
