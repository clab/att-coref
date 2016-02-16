#ifndef CORPUS_HPP_
#define CORPUS_HPP_

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

  struct TokenInfo {
    unsigned word_id = 0;
    unsigned pos_id = 0;
    bool training_oov = true;
  };

  class Corpus {
  public:
    
    // Constructors
    Corpus(std::string filename);

    // Variables
    std::string filename;
  };
}

#endif
