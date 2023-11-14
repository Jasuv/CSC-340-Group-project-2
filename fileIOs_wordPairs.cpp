// Author: Eric AhSue

#include "fileIOs_wordPairs.h"

namespace fileIOs {
    /*
    inFS = openFile(fname)
    if inFS is open
        while (line = readLine(inFS))
            sentence = ""
            for each character c in line
                if c is not a sentence delimiter
                    append c to sentence
                else if sentence has non-whitespace characters
                    if first character of sentence is " remove the first character from sentence
                    if first character of sentence is space remove the first character from sentence
                    add sentence to sentences
                    reset sentence to an empty string
            if sentence is not empty
                if first character of sentence is ' '
                    remove the first character from sentence
                add sentence to sentences
        closeFile(inFS)
    else
        print error
    */
   // used a comment on the suggested answer on this post for reference how to check for a all white spaces
   // https://stackoverflow.com/questions/6444842/efficient-way-to-check-if-stdstring-has-only-spaces
    void sentenceSplitter(string &fname, vector<string> &sentences) {
        ifstream inFS(fname);
        string line;
        string sentenceDelimiters = ".?";

        if (inFS.is_open()) {
            while (getline(inFS, line)) {
                string sentence;
                for (char c : line) {
                    if (sentenceDelimiters.find(c) == string::npos) {
                        sentence += c;
                    } else if (sentence.find_first_not_of(" \t\n\v\f\r") != string::npos) {
                        if (sentence[0] == '"')
                            sentence.erase(0, 1);
                        if (sentence[0] == ' ')
                            sentence.erase(0, 1);
                        sentences.push_back(sentence);
                        sentence = "";
                    }
                }
                if (!sentence.empty()) {
                    if (sentence[0] == ' ')
                        sentence.erase(0, 1);
                    sentences.push_back(sentence);
                }
            }
        } else {
            cout << "Error opening file: " << fname << endl;
        }
        inFS.close();
    }
    /*
    for each sentence in sentences
        isstream = createStringStream(sentence)
        uniqueTokens = createEmptySet()
        for each token in isstream, using ' ' as delimiter
            lowercaseToken = toLowercase(token)
            insert lowercaseToken into uniqueTokens
        for each word1 in uniqueTokens
            for each word2 in uniqueTokens
                if word1 < word2
                    increment wordpairFreq_map[{word1, word2}]
    */
    void wordpairMapping(vector<string> &sentences, map<pair<string, string>, int> &wordpairFreq_map) {
        for (const auto &sentence : sentences) {
            istringstream isstream(sentence);
            set<string> uniqueTokens;
            long unsigned int i, j;

            string token;
            while (getline(isstream, token, ' ')) {
                transform(token.begin(), token.end(), token.begin(), ::tolower);
                uniqueTokens.insert(token);
            }
            for (const auto &word1 : uniqueTokens) {
                for (const auto &word2 : uniqueTokens) {
                    if (word1 < word2) {
                        wordpairFreq_map[{word1, word2}]++;
                    }
                }
            }
        }
    }
    /*
    for each pairFreq in wordpairFreq_map
        freqWordpair_mmap.insert(make_pair(pairFreq.second, pairFreq.first))
    */
    void freqWordpairMmap(map<pair<string, string>, int> &wordpairFreq_map, multimap<int, pair<string, string>> &freqWordpair_mmap) {
        for (const auto &pairFreq : wordpairFreq_map) {
            freqWordpair_mmap.insert(std::make_pair(pairFreq.second, pairFreq.first));
        }
    }
    /*
    outFS = openFile(outFname)
    if outFS.is_open
        count = 0
        for it in freqWordpair_multimap in reverse
            if count >= topCnt break
            outFS << (pair, freq)
            add(count, 1)
        count = 0
        for it in freqWordpair_multimap
            if count >= botCnt break
            outFS << (pair, freq)
            add(count, 1)
    else
        print error
    closeFile(outFS)
    */
    void printWordpairs(multimap<int, pair<string, string>> &freqWordpair_multimap, string outFname, int topCnt, int botCnt) {
        ofstream outFS;
        outFS.open(outFname);

        if (outFS.is_open()) {
            int count = 0;
            for (auto it = freqWordpair_multimap.rbegin(); it != freqWordpair_multimap.rend() && count < topCnt; ++it) {
                outFS << "<" << it->second.first << ", " << it->second.second << ">: " << it->first << endl;
                count++;
            }
            count = 0;
            for (auto it = freqWordpair_multimap.begin(); it != freqWordpair_multimap.end() && count < botCnt; ++it) {
                outFS << "<" << it->second.first << ", " << it->second.second << ">: " << it->first << endl;
                count++;
            }

        } else {
            cout << "Couldn't open the file..." << endl;
        }
        outFS.close();
    }
} // namespace fileIOs