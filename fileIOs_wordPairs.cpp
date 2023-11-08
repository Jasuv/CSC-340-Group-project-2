#include "fileIOs_wordPairs.h"

namespace fileIOs {
    void getTokenFreqVec(string& instr, vector<string>& tfVec) {
        string token;
        long unsigned int i;
        bool flag;
        TokenFreq t;
        istringstream isStream(instr);
        
        // Tokenizing string using stream
        while (isStream >> token) {
            // Turns token into lowercase
            transform(token.begin(), token.end(), token.begin(), [](unsigned char c){ return std::tolower(c); } );

            // Checks if token needs to be added as a new item to the list or can just increase the freq of an already existing token tfVec
            flag = true;
            for (i = 0; i < tfVec.size(); i++) {
                // If tfVec contains the frequency for the token
                if (tfVec[i].token == token) {
                    tfVec[i].freq += 1;
                    flag = false;
                }
            }

            // Inserts a new Token into tfVec if needed to
            if (flag) {
                t.token = token;
                tfVec.push_back(t);
            }
        }
    }
    void sentenceSplitter(string& fname, vector<string>& sentences) {

    }
    void wordpairMapping(vector<string>& sentences, map< pair<string,string>, int> &wordpairFreq_map) {

    }
    void freqWordpairMmap(map< pair<string,string>, int> &wordpairFreq_map, multimap<int, pair<string, string> > &freqWordpair_mmap ) {

    }
    void printWordpairs(multimap<int, pair<string, string> > &freqWordpair_multimap, string outFname, int topCnt, int botCnt) {

    }
}