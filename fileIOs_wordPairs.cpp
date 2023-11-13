// Author: Eric AhSue

#include "fileIOs_wordPairs.h"

namespace fileIOs {
    /*
    // Split sentences in a file and store them in a vector
    // listSentences: Vector of sentences from the file
    // resultingPairs: Empty map to store resulting word pairs and their frequencies
    function sentenceSplitter(fname, sentences):
        // Declare variables
        ifstream inFS
        string sentence

        // Open the file
        inFS.open(fname)

        // Check if the file is open
        if inFS.is_open:
            // Read each sentence in the file
            while (getline(inFS, sentence, '.')):
                stringstream ss(sentence)

                // Split each sentence by '?'
                while (getline(ss, sentence, '?')):
                    // Add the sentence to the vector
                    append(sentences, sentence)
            else:
                print "Couldn't open the file..."

        // Close the file
        inFS.close()
        return sentences
    */
    // used the suggested answer on this post how to use getline and multiple delimiters,
    // this is assuming '.' '?' '\n' are the only delimiters.
    // https://stackoverflow.com/questions/37957080/can-i-use-2-or-more-delimiters-in-c-function-getline#:~:text=std%3A%3Agetline()%20does,%2C%20into%20comma%2Dseparate%20values.
    void FileIOs::sentenceSplitter(string &fname, vector<string> &sentences) {
        ifstream inFS;
        string sentence;

        inFS.open(fname);

        if (inFS.is_open()) {
            while (getline(inFS, sentence, '.')) {
                stringstream ss(sentence);
                while (getline(ss, sentence, '?')) {
                    sentences.push_back(sentence);
                }
            }
        } else {
            cout << "Couldn't open the file..." << endl;
        }
        inFS.close();
    }
    /*
    // Generate word pairs and their frequencies
    // sentences: Vector of input sentences
    // wordpairFreq_map: Map to store resulting word pairs and their frequencies
    function wordpairMapping(sentences, wordpairFreq_map):
        // For each sentence in the input vector
        for each sentence in sentences:
            // Tokenize the sentence using istringstream
            stringstream iss(sentence)
            vector<string> uniqueTokens

            // For each token in the sentence
            while (iss >> token):
                // Convert the token to lowercase
                toLower(token) -> token

                // Check if the token is already in the uniqueTokens vector
                search(uniqueTokens, token) -> it
                if it not found:
                    // Token is not in the vector, so add it
                    append(uniqueTokens, token)

            // Generate word-pairs and update their frequency in the map
            len(uniqueTokens) -> len
            for i = 1 to len - 1:
                for j = i + 1 to len:
                    // Arrange the two words in lexicographical order
                    make_a_pair(uniqueTokens[i], uniqueTokens[j]) -> pair
                    // Increment the frequency of the word-pair in the map
                    incrementFreq(wordpairFreq_map[pair], 1)

        return wordpairFreq_map
    */
    void FileIOs::wordpairMapping(vector<string> &sentences, map<pair<string, string>, int> &wordpairFreq_map) {
        for (const auto &sentence : sentences) {
            istringstream iss(sentence);
            vector<string> uniqueTokens;

            string token;
            while (getline(iss, token, ' ')) {
                // convert the token to lowercase
                transform(token.begin(), token.end(), token.begin(), ::tolower);

                // check if the token is already in the uniqueTokens vector
                auto it = find(uniqueTokens.begin(), uniqueTokens.end(), token);
                if (it == uniqueTokens.end()) {
                    uniqueTokens.push_back(token);
                }
            }

            for (size_t i = 0; i < uniqueTokens.size(); ++i) {
                for (size_t j = i + 1; j < uniqueTokens.size(); ++j) {
                    // arrange the two words in lexicographical order
                    string word1 = uniqueTokens[i];
                    string word2 = uniqueTokens[j];
                    if (word1 > word2) {
                        swap(word1, word2);
                    }
                    wordpairFreq_map[{word1, word2}]++;
                }
            }
        }
    }
    /*
    // Generate a multimap of word pair frequencies
    // wordpairFreq_map: Map of word pairs and their frequencies
    // freqWordpair_mmap: Multimap to store frequencies and corresponding word pairs
    function freqWordpairMmap(wordpairFreq_map, freqWordpair_mmap):
        // For each pair and frequency in the input map
        for each pairFreq in wordpairFreq_map:
            // Insert the frequency and word pair into the multimap
            insert(freqWordpair_mmap, make_pair(pairFreq.second, pairFreq.first))

        return freqWordpair_mmap
    */
    void FileIOs::freqWordpairMmap(map<pair<string, string>, int> &wordpairFreq_map, multimap<int, pair<string, string>> &freqWordpair_mmap) {
        for (const auto &pairFreq : wordpairFreq_map) {
            freqWordpair_mmap.insert(std::make_pair(pairFreq.second, pairFreq.first));
        }
    }
    /*
    // Print top and bottom word pairs with their frequencies to a file
    // freqWordpair_multimap: Multimap of word pairs and their frequencies
    // outFname: Output file name
    // topCnt: Number of top most frequent word pairs to print
    // botCnt: Number of bottom least frequent word pairs to print
    function printWordpairs(freqWordpair_multimap, outFname, topCnt, botCnt):
        // Declare variables
        ofstream outFS

        // Open the output file
        outFS.open(outFname)

        // Check if the file is open
        if outFS.is_open:
            int count = 0

            // Write the top most frequent word-pairs to the file
            for each it in reverse order of freqWordpair_multimap and while count < topCnt:
                outFS << "<" << it->second.first << ", " << it->second.second << ">: " << it->first << endl
                count++

            count = 0

            // Write the bottom least frequent word-pairs to the file
            for each it in order of freqWordpair_multimap and while count < botCnt:
                outFS << "<" << it->second.first << ", " << it->second.second << ">: " << it->first << endl
                count++

        Else:
            Print "Couldn't open the file..."

        // Close the output file
        outFS.close()
    */
    void FileIOs::printWordpairs(multimap<int, pair<string, string>> &freqWordpair_multimap, string outFname, int topCnt, int botCnt) {
        ofstream outFS;
        outFS.open(outFname);

        if (outFS.is_open()) {
            int count = 0;
            // write the top most frequent word-pairs to the file
            for (auto it = freqWordpair_multimap.rbegin(); it != freqWordpair_multimap.rend() && count < topCnt; ++it) {
                outFS << "<" << it->second.first << ", " << it->second.second << ">: " << it->first << std::endl;
                count++;
            }

            count = 0;
            // write the bottom least frequent word-pairs to the file
            for (auto it = freqWordpair_multimap.begin(); it != freqWordpair_multimap.end() && count < botCnt; ++it) {
                outFS << "<" << it->second.first << ", " << it->second.second << ">: " << it->first << std::endl;
                count++;
            }

        } else {
            cout << "Couldn't open the file..." << endl;
        }
        outFS.close();
    }
} // namespace fileIOs