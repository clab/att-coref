#include <cstdlib>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>
#include <limits>
#include <cmath>
#include <chrono>
#include <ctime>

#include <unordered_map>
#include <unordered_set>

#include <execinfo.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

#include "corpus.h"

using namespace std;
using namespace coref;

int main(int argc, char** argv) {
  Corpus train("../data/conll-2012/all_train.v4_gold_conll");
  Corpus dev("../data/conll-2012/all_development.v4_gold_conll");

  // This is how to traverse documents and their content:
  cerr << "count of documents in the development corpus: " << dev.documents.size() << endl << endl;
  for (const auto& document : dev.documents) {
    cerr << "document name: " << document.name << endl;
    cerr << "  tokens count: " << document.tokens.size() << endl;
    cerr << "  first token: " << endl;
    cerr << "    pos id: " << document.tokens[0].pos_id << endl;
    cerr << "    pos string: " << Corpus::global_vocab.get_string(document.tokens[0].pos_id) << endl;
    cerr << "    word id: " << document.tokens[0].word_id << endl;
    cerr << "    word string: " << Corpus::global_vocab.get_string(document.tokens[0].word_id) << endl;
    cerr << "    appears in the training corpus? " << train.set_of_word_types.count(document.tokens[0].word_id) << endl;
    cerr << endl;
  }
}
