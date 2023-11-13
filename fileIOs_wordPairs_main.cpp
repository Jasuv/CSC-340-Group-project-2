// Author: Eric AhSue

#include "fileIOs_wordPairs.h"
using namespace fileIOs;

// Tests the 4 functions from fileIOs_wordPairs.cpp

FileIOs fileios;
string speech = "speech.txt";
string output = "output.txt";
vector<string> sentences;
map<pair<string, string>, int> wordpairFreq_map;
multimap<int, pair<string, string>> freqWordpair_mmap;

bool test_sentenceSplitter() {
    fileios.sentenceSplitter(speech, sentences);
    return sentences.size() == 12;
}
bool test_wordpairMapping() {
    sentences = {"The first story is about connecting the dots.",
                 "The first story is about connecting the dots.",
                 "The first story is about connecting the dots."};
    fileios.wordpairMapping(sentences, wordpairFreq_map);
    return wordpairFreq_map.size() == 21;
}
bool test_freqWordpairMmap() {
    fileios.freqWordpairMmap(wordpairFreq_map, freqWordpair_mmap);
    return wordpairFreq_map.size() == 21;
}
//TODO finish this
bool test_printWordpairs() {
    fileios.printWordpairs(freqWordpair_mmap, output, 1, 2);
    return 0;
}

int main() {
    cout << "Testing sentence splitter... " << ((test_sentenceSplitter()) ? "Success!!!" : "Failed...") << endl;
    cout << "Testing word pair mapping... " << ((test_wordpairMapping()) ? "Success!!!" : "Failed...") << endl;
    cout << "Testing frequency word pair map... " << ((test_freqWordpairMmap()) ? "Success!!!" : "Failed...") << endl;
    cout << "Testing print word pairs... " << ((test_printWordpairs()) ? "Success!!!" : "Failed...") << endl;
    return 0;
}