#include <iostream>
#include <string>
#include "WordCount.h"
#include "tddFuncs.h"
#include <ostream> 
#include <sstream> 

using namespace std; 
int main() {
   
    WordCount words; 

    std::ostringstream output; 

    string line1 = "Hi, how are you. hi not much how are you????"; 

    words.addAllWords(line1); 


    ASSERT_EQUALS(1, words.getWordCount("much")); 
    ASSERT_EQUALS(1, words.getWordCount("not")); 
    ASSERT_EQUALS(2, words.getWordCount("hi")); 
    ASSERT_EQUALS(2, words.getWordCount("how")); 
    ASSERT_EQUALS(2, words.getWordCount("are")); 
    ASSERT_EQUALS(2, words.getWordCount("you")); 

    string expectedSortOutput = "you,2\nnot,1\nmuch,1\nhow,2\nhi,2\nare,2\n"; 

    words.dumpWordsSortedByWord(output); 
    ASSERT_EQUALS(expectedSortOutput, output.str());

    WordCount words2; 

    string line2 = "Sentence.   ** ** **   is a fun fun sentence"; 

    std::ostringstream output2; 

    string expectedSortOutput2 = "a,1\nis,1\nfun,2\nsentence,2\n"; 

    words2.addAllWords(line2); 

    words2.dumpWordsSortedByOccurence(output2); 
    ASSERT_EQUALS(expectedSortOutput2, output2.str());





    return 0;
}