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



#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/program_options.hpp>

#include "cnn/training.h"
#include "cnn/cnn.h"
#include "cnn/expr.h"
#include "cnn/nodes.h"
#include "cnn/lstm.h"
#include "cnn/rnn.h"


using namespace cnn::expr;
using namespace cnn;
using namespace std;
using namespace coref;

struct CorefBuilder{


explicit CorefBuilder(){}

 LookupParameters* p_w; //lookup for entity embeddings.
 
 Parameters* bias;
 Parameters* V;

 
 Parameters* p_start_of_entity;
 Parameters* p_end_of_entity;
 LSTMBuilder fw_lstm; // forward embedding of the entity.
 LSTMBuilder bw_lstm; // backwards embedding of the entity.

 Parameters* p_H; // head matrix for composition function - for "clustered" entities.

 


};







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
