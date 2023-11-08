#include<iostream>
#include<string>
#include<vector>
#include<sstream>
#include<map>
#include<algorithm>

using namespace std;

namespace fileIOs {
    struct TokenFreq {
        void getTokenFreqVec(string& instr, vector<string>& tfVec);
        string token;
        int freq = 1;
    };


    class FileIOs {
        public:
            void sentenceSplitter(string& fname, vector<string>& sentences);
            void wordpairMapping(vector<string>& sentences, map< pair<string,string>, int> &wordpairFreq_map);
            void freqWordpairMmap(map< pair<string,string>, int> &wordpairFreq_map, multimap<int, pair<string, string> > &freqWordpair_mmap );
            void printWordpairs(multimap<int, pair<string, string> > &freqWordpair_multimap, string outFname, int topCnt, int botCnt);
        private:
            //some vars
    };
}