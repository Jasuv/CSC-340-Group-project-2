// Author: Eric AhSue

#include "fileIOs_wordPairs.h"
using namespace fileIOs;

// Tests the 4 functions from fileIOs_wordPairs.cpp

string speech = "speech.txt";
string output = "output.txt";
vector<string> sentences;
map<pair<string, string>, int> wordpairFreq_map;
multimap<int, pair<string, string>> freqWordpair_mmap;

bool test_sentenceSplitter() {
    sentenceSplitter(speech, sentences);
    return sentences.size() == 148;
}

bool test_wordpairMapping() {
    sentences = {
        "The first story is about connecting the dots",
        "The first story is about connecting the dots",
        "The first story is about connecting the dots"
    };
    cout << sentences.size();
    wordpairMapping(sentences, wordpairFreq_map);
    return wordpairFreq_map.size() == 21;
}

bool test_freqWordpairMmap() {
    freqWordpairMmap(wordpairFreq_map, freqWordpair_mmap);
    return wordpairFreq_map.size() == 21;
}

//TODO finish this
bool test_printWordpairs() {
    printWordpairs(freqWordpair_mmap, output, 10, 0);
    std::vector<std::string> lines;
    std::ifstream file(output);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            lines.push_back(line);
        }
        file.close();
    } else {
        std::cerr << "Error opening file: " << output << std::endl;
    }
    std::vector<std::string> expected = {
        "<story, the>: 3",
        "<is, the>: 3",
        "<is, story>: 3",
        "<first, the>: 3",
        "<first, story>: 3",
        "<first, is>: 3",
        "<dots, the>: 3",
        "<dots, story>: 3",
        "<dots, is>: 3",
        "<dots, first>: 3"
    };
    return expected == lines;
}

int main() {
    cout << "Testing sentence splitter... " << ((test_sentenceSplitter()) ? "Success!!!" : "Failed...") << endl;
    cout << "Testing word pair mapping... " << ((test_wordpairMapping()) ? "Success!!!" : "Failed...") << endl;
    cout << "Testing frequency word pair map... " << ((test_freqWordpairMmap()) ? "Success!!!" : "Failed...") << endl;
    cout << "Testing print word pairs... " << ((test_printWordpairs()) ? "Success!!!" : "Failed...") << endl;
    return 0;
}