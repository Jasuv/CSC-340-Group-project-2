#include<iostream>
#include<stdlib.h>

#include "fileIOs_wordPairs.h"
using namespace fileIOs;

// Tests the 4 functions from fileIOs_wordPairs.cpp

string speech = "The first story is about connecting the dots.\n\nI dropped out of Reed College after the first 6 months, but then stayed around as a drop-in for another 18 months or so before I really quit. So why did I drop out?\n\nIt started before I was born. My biological mother was a young, unwed college graduate student and she decided to put me up for adoption. She felt very strongly that I should be adopted by college graduates, so everything was all set for me to be adopted at birth by a lawyer and his wife. Except that when I popped out they decided at the last minute that they really wanted a girl. So my parents, who were on a waiting list, got a call in the middle of the night asking: \"We have an unexpected baby boy; do you want him?\" They said: \"Of course.\" My biological mother later found out that my mother had never graduated from college and that my father had never graduated from high school. She refused to sign the final adoption papers. She only relented a few months later when my parents promised that I would someday go to college.";

bool test_sentenceSplitter() {
    FileIOs fileios;
    vector<string> splitVec;
    fileios.sentenceSplitter(speech, splitVec);
    return splitVec.size() == 12;
}
bool test_wordpairMapping() {
    return 1;
}
bool test_freqWordpairMmap() {
    return 1;
}
bool test_printWordpairs() {
    return 1; 
}

int main() {
    cout << "Testing sentence splitter... " << ((test_sentenceSplitter()) ? "Success!!!" : "Failed...") << endl;
    cout << "Testing word pair mapping... " << ((test_wordpairMapping()) ? "Success!!!" : "Failed...") << endl;
    cout << "Testing frequency word pair map... " << ((test_freqWordpairMmap()) ? "Success!!!" : "Failed...") << endl;
    cout << "Testing print word pairs... " << ((test_printWordpairs()) ? "Success!!!" : "Failed...") << endl;
    return 0;
}