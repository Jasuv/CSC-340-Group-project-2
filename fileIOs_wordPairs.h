// Author: Eric AhSue

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

namespace fileIOs {
    class FileIOs {
    public:
        void sentenceSplitter(string &fname, vector<string> &sentences);
        void wordpairMapping(vector<string> &sentences, map<pair<string, string>, int> &wordpairFreq_map);
        void freqWordpairMmap(map<pair<string, string>, int> &wordpairFreq_map, multimap<int, pair<string, string>> &freqWordpair_mmap);
        void printWordpairs(multimap<int, pair<string, string>> &freqWordpair_multimap, string outFname, int topCnt, int botCnt);

    private:
        // some vars
    };
} // namespace fileIOs