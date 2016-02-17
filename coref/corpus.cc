#include "corpus.h"

using namespace std;
using namespace coref;

// Definition of static variables in Corpus.
StringEncoder Corpus::global_vocab;

// Read the corpus.
Corpus::Corpus(string filename) : filename(filename) {

  // Keep track of seen word types and pos tags.
  unsigned unk_id = global_vocab.get_or_add_id(Corpus::UNK);
  set_of_word_types.insert(unk_id);
  set_of_pos_tags.insert(unk_id);
  
  // Interpret one line at a time.
  ifstream conll_file(filename);
  assert(conll_file.is_open() && "Unable to open the specified conll file.");
  unordered_map<unsigned, vector<Mention>> entity_id_to_open_mentions;
  string current_document_name;
  while (conll_file.good()) {
    string line;
    std::getline(conll_file, line);
    
    // Skip empty lines.
    if (line.size() == 0 || line[0] == '#') { continue; }
    vector<string> splits;
    SplitString(line, ' ', splits);

    // Read important CoNLL-2012 fields.
    assert(splits.size() >= Corpus::MIN_CONLL_FIELDS);
    string document_name = splits[0] + "_part" + splits[1];
    string word = splits[3];
    string pos = splits[4];
    string coref = splits[splits.size() - 1];

    // Create new document if need be.
    if (current_document_name != document_name) {
      current_document_name = document_name;
      Document new_document;
      new_document.name = document_name;
      documents.push_back(new_document);
    }
    Document& current_document = documents.back();

    // Create a new token.
    Token current_token;
    unsigned current_token_index = current_document.tokens.size();
    current_token.word_id = global_vocab.get_or_add_id(word);
    current_token.pos_id = global_vocab.get_or_add_id(pos);
    current_document.tokens.push_back(current_token);
    set_of_word_types.insert(current_token.word_id);
    set_of_pos_tags.insert(current_token.pos_id);

    // Does this token mark the beginning of a mention?
    unsigned search_from_index = 0;
    do {
      size_t index_of_open_bracket = coref.find('(', search_from_index);
      if (index_of_open_bracket == string::npos) { break; }

      // Open bracket found!
      size_t index_of_entity_id = index_of_open_bracket + 1;
      assert(coref[index_of_entity_id] >= '0' && coref[index_of_entity_id] <= '9');
      size_t size_of_entity_id = 1;
      while (index_of_entity_id + size_of_entity_id < coref.size() && 
	     coref[index_of_entity_id + size_of_entity_id] >= '0' && 
	     coref[index_of_entity_id + size_of_entity_id] <= '9') {
	++size_of_entity_id;
      }
      search_from_index = index_of_entity_id + size_of_entity_id;
      stringstream entity_id_string(coref.substr(index_of_entity_id, size_of_entity_id));
      unsigned entity_id;
      entity_id_string >> entity_id;

      // Create a new entity, if need be.
      if (current_document.entities.count(entity_id) == 0) {
	Entity new_entity;
	new_entity.id = entity_id;
	current_document.entities[entity_id] = new_entity;
      }

      // Create a new mention.
      Mention new_mention;
      new_mention.from_token_index = current_token_index;
      entity_id_to_open_mentions[entity_id].push_back(new_mention);

    } while (true); // Loop over open brackets ends here.

    // Does this token mark the end of a mention?
    search_from_index = 0;
    do {
      size_t index_of_closing_bracket = coref.find(')', search_from_index);
      if (index_of_closing_bracket == string::npos) { break; }
      search_from_index = index_of_closing_bracket + 1;

      // Closing bracket found!
      size_t size_of_entity_id = 1;
      assert(coref[index_of_closing_bracket - size_of_entity_id]);
      while (index_of_closing_bracket > size_of_entity_id &&
	     coref[index_of_closing_bracket - size_of_entity_id - 1] >= '0' &&
	     coref[index_of_closing_bracket - size_of_entity_id - 1] <= '9') {
	++size_of_entity_id;
      }
      size_t index_of_entity_id = index_of_closing_bracket - size_of_entity_id;
      stringstream entity_id_string(coref.substr(index_of_entity_id, size_of_entity_id));
      unsigned entity_id;
      entity_id_string >> entity_id;

      // Move this mention from entity_id_to_open_mentions to entities.mentions
      assert(entity_id_to_open_mentions.count(entity_id) == 1 && entity_id_to_open_mentions[entity_id].size() > 0);
      Mention current_mention = entity_id_to_open_mentions[entity_id].back();
      entity_id_to_open_mentions[entity_id].pop_back();
      current_mention.to_token_index = current_token_index;
      current_document.entities[entity_id].mentions.push_back(current_mention);
      if (entity_id_to_open_mentions[entity_id].size() == 0) { 
	entity_id_to_open_mentions.erase(entity_id);
      }

    } while (true); // Loop over closing brackets ends here.
  }

  // copy the sets into vectors.
  std::copy(set_of_word_types.begin(), set_of_word_types.end(), std::back_inserter(word_types));
  std::copy(set_of_pos_tags.begin(), set_of_pos_tags.end(), std::back_inserter(pos_tags));
}

void Corpus::SplitString(const string& s, char delim, std::vector<string>& elems) {
  stringstream ss(s);
  string item;
  while(getline(ss, item, delim)) {
    if(item.size() == 0) { continue; }
    elems.push_back(item);
  }
}
