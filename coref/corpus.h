#ifndef CORPUS_H_
#define CORPUS_H_

#include <string>
#include <iostream>
#include <cassert>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <functional>
#include <vector>
#include <string>

namespace coref {

  // Convert strings to unique unsigned values, and vice versa.
  struct StringEncoder {
    std::vector<std::string> id2string;
    std::unordered_map<std::string, unsigned> string2id;

    // This is the main interface to safely convert an id to a string
    std::string get_string(unsigned id) const {
      assert(id2string.size() > id);
      return id2string[id];
    }

    // This is the main interface for adding/retrieving string ids.
    unsigned get_or_add_id(std::string str) {
      if (string2id.count(str) == 0) {
	string2id[str] = id2string.size();
	id2string.push_back(str);
      } 
      return string2id[str];
    }
  };

  // Token-level information read from the CoNLL file.
  struct Token {
    unsigned word_id = 0;
    unsigned pos_id = 0;
  };

  // A mention specifies the start and end indexes of a mention within a document.
  struct Mention {
    unsigned from_token_index = 0;
    unsigned to_token_index = 0;
  };
  
  // An entity consists of a list of mentions.
  // An entity id is unique within a given document.
  struct Entity {
    unsigned id = 0;
    std::vector<Mention> mentions;
  };

  // A document is a collection of entities, and a list of tokens.
  struct Document {
    std::string name;
    std::vector<Token> tokens;
    std::unordered_map<unsigned, Entity> entities;
  };

  // A corpus is a collection of documents. 
  // Vocabulary is shared across multiple corpora.
  class Corpus {
  public:

    // Constructors.
    Corpus(std::string filename);

    // Local variables.
    std::string filename;
    std::vector<Document> documents;
    // Useful for random access to a word type in this corpus.
    std::vector<unsigned> word_types, pos_tags;
    // Useful for determining whether a word appears in this corpus.
    std::unordered_set<unsigned> set_of_word_types, set_of_pos_tags;
      
    // Shared variables.
    static StringEncoder global_vocab;
    
    // Constants.
    static constexpr auto UNK = "UNK";
    static constexpr unsigned MIN_CONLL_FIELDS = 12;

  private:
    // Split strings.
    void SplitString(const std::string& full_string, char delimiter, std::vector<std::string>& parts);
  };
}

#endif
