// Author: Eric AhSue

/* Design Doc: communicate your thought process in English.
 
0. List of members who contributed to the implementation of this project:
   
  Eric AhSue
  
1. What are the expected input and outputs of your file.

  Input: textFile                     //file of plain text
  Output: {<w1, 2w2>: freq(<w1, w2>)} //w1 & w2 are in lower case; w1<w2 they are lexicographically ordered
                                      //w1 & w2 are required to be in the same sentence
                                      //freq(<w1, w2>): number of sentences that contain this pair

2. Describe your algorithm for the sentenceSplitter( ) function in pseudocode.

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

3. Describe your algorithm for the wordpairMapping( ) function in pseudocode.

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