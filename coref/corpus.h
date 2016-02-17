#ifndef CORPUS_H_
#define CORPUS_H_

#include <string>
#include <iostream>
#include <cassert>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <unordered_map>
#include <functional>
#include <vector>
#include <map>
#include <string>

namespace coref {

  // Convert strings to unique unsigned values, and vice versa.
  struct StringEncoder {
    std::vector<std::string> id2string;
    std::unsorted_map<std::string, unsigned> string2id;

    // This is the main interface for adding/retrieving string ids.
    unsigned get_or_add_id(std::string);
  };

  struct Token {
    unsigned word_id = 0;
    unsigned pos_id = 0;
  };

  struct Mention {
    unsigned from_token_index, to_token_index;
  };

  struct Entity {
    unsigned id;
    std::vector<const Mention*> mentions;
  };

  struct Document {
    std::string name;
    std::vector<Token> tokens;
    std::unsorted_map<unsigned, Entity> entities;
  };

  // A corpus is a collection of documents. 
  // We make a distinction between a training corpus and a non-training corpus (e.g., development or test).
  // Vocabulary is shared across multiple corpora.
  class Corpus {
  public:

    // Constructors.
    Corpus(std::string filename, bool is_training_corpus);

    // Variables.
    constexpr auto UNK_string = "UNK";
    std::string filename;
    bool is_training_corpus;
    vector<Document> documents;
    vector<unsigned> word_types;
    vector<unsigned> pos_tag_set;
    
    // Static variables
    static StringEncoder global_vocab;
  };
}

#endif
