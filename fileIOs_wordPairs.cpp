// Author: Eric AhSue

#include "fileIOs_wordPairs.h"

namespace fileIOs {
    /*
    open file "fname"
    if file opened
        read each line in the file until '.' delimiter
            add line to the sentences vector
        end reading
        close the file
    else
        display an error message
    end if
    */
    void sentenceSplitter(string &fname, vector<string> &sentences) {
        ifstream inFS;
        string sentence;

        inFS.open(fname);

        if (inFS.is_open()) {
            while (getline(inFS, sentence, '.')) {
                sentences.push_back(sentence);
            }
        } else {
            cout << "Couldn't open the file..." << endl;
        }

        inFS.close();
    }
    /*
    for each sentence in sentences do
        create an input string stream 'iss' from the sentence
        create an empty string 'prevWord'

        while able to extract 'word' from iss do
            create a word-pair 'wordPair' from 'prevWord' and 'word'
            increment the frequency count of 'wordPair' in 'wordpairFreq_map'
            set 'prevWord' as 'word' for the next pair
        end while
    end for
    */
    void wordpairMapping(vector<string> &sentences, map<pair<string, string>, int> &wordpairFreq_map) {
        auto tokenizeAndLower = [](const string& sentence) {
            istringstream iss(sentence);
            vector<string> tokens;
            string token;

            while (iss >> token) {
                transform(token.begin(), token.end(), token.begin(), ::tolower);
                tokens.push_back(token);
            }

            sort(tokens.begin(), tokens.end());
            tokens.erase(unique(tokens.begin(), tokens.end()), tokens.end());

            return tokens;
        };

        for (const auto& sentence : sentences) {
            vector<string> uniqueTokens = tokenizeAndLower(sentence);
            int len = uniqueTokens.size();

            for (int i = 0; i < len - 1; ++i) {
                for (int j = i + 1; j < len; ++j) {
                    pair<string, string> wordPair = make_pair(uniqueTokens[i], uniqueTokens[j]);
                    auto it = wordpairFreq_map.find(wordPair);

                    if (it != wordpairFreq_map.end()) {
                        it->second++;
                    } else {
                        wordpairFreq_map[wordPair] = 1;
                    }
                }
            }
        }
    }
    /*
    for each pairFreq in wordpairFreq_map do
        insert pairFreq's value as a key and pairFreq's key as a value into freqWordpair_mmap
    end for
    */
    void freqWordpairMmap(map<pair<string, string>, int> &wordpairFreq_map, multimap<int, pair<string, string>> &freqWordpair_mmap) {
        for (const auto &pairFreq : wordpairFreq_map) {
            freqWordpair_mmap.insert(std::make_pair(pairFreq.second, pairFreq.first));
        }
    }
    /*
    open outputFile named outFname

    if outputFile cannot be opened then
        display an error message
        return
    end if

    count = 0
    for each word-pair in freqWordpair_multimap by frequency in descending order do
        if count is less than topCnt then
            write the word-pair and its frequency to outputFile
            increment count
        end if
    end for

    count = 0
    for each word-pair in freqWordpair_multimap by frequency in ascending order do
        if count is less than botCnt then
            write the word-pair and its frequency to outputFile
            increment count
        end if
    end for

    close outputFile
    */
    void printWordpairs(multimap<int, pair<string, string>> &freqWordpair_multimap, string outFname, int topCnt, int botCnt) {
        ofstream outFS;
        outFS.open(outFname);

        if (outFS.is_open()) {
            int count = 0;
            // Write the top most frequent word-pairs to the file
            for (auto it = freqWordpair_multimap.rbegin(); it != freqWordpair_multimap.rend() && count < topCnt; ++it) {
                outFS << "<" << it->second.first << ", " << it->second.second << ">: " << it->first << std::endl;
                count++;
            }

            count = 0;
            // Write the bottom least frequent word-pairs to the file
            for (auto it = freqWordpair_multimap.begin(); it != freqWordpair_multimap.end() && count < botCnt; ++it) {
                outFS << "<" << it->second.first << ", " << it->second.second << ">: " << it->first << std::endl;
                count++;
            }
            /*
            auto it = freqWordpair_multimap.begin(); // Start at the beginning of the word-pair list

            while (count < botCnt) {                     // Keep going until we've written 'botCnt' word-pairs
                if (it == freqWordpair_multimap.end()) { // If we reach the end, stop
                    break;
                }
                outputFile << "<" << it->second.first << ", " << it->second.second << ">: " << it->first << std::endl; // Write the word-pair to the file
                count++;                                                                                               // Move to the next word-pair
                it++;                                                                                                  // Move to the next word-pair in the list
            }
            */

        } else {
            cout << "Couldn't open the file..." << endl;
        }

        outFS.close();
    }
} // namespace fileIOs