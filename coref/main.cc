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
  Corpus train("/usr1/home/wammar/git/att-coref/coref/data/conll-2012/all_train.v4_gold_conll");
  Corpus dev("/usr1/home/wammar/git/att-coref/coref/data/conll-2012/all_development.v4_gold_conll");
  cerr << "att-coref: hello world!" << endl;
}
