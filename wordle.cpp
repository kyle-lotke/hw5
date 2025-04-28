#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void gen_possibilties(string& partial_word, int indx, 
int missing_letters, string included_letters, 
const set<string>& dict, set<string>& possibilities);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    set<string> possible_words;
    int word_len = in.size();
    int num_dashes = 0;
    for(int i=0; i < word_len; i++) {
        if(in[i] == '-') num_dashes++;
    }

    string curr = in;
    gen_possibilties(curr, 0, num_dashes, floating, dict, possible_words);

    return possible_words;
}

// Define any helper functions here

void gen_possibilties(string& partial_word, int indx, 
int missing_letters, string included_letters, 
const set<string>& dict, set<string>& possibilities) {
    if(indx == partial_word.size()) {
        if(dict.count(partial_word) && included_letters.empty()) {
            possibilities.insert(partial_word);
            return;
        }
        return;
    }

    if(partial_word[indx] != '-') { // if letter is known go to next and recurse
        gen_possibilties(partial_word, indx + 1, missing_letters, included_letters, dict, possibilities);
        return;
    }

    for(char letter = 'a'; letter <= 'z'; letter++) {
        string included_updated = included_letters;
        int letter_indx = included_updated.find(letter);
        if(letter_indx != string::npos) {
            included_updated.erase(letter_indx, 1);
        }
        else if(missing_letters <= (int)included_letters.size()) {
            continue;
        }

        partial_word[indx] = letter;
        gen_possibilties(partial_word, indx + 1, missing_letters - 1, included_updated, dict, possibilities);

    }

    partial_word[indx] = '-';

}
