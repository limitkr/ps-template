#define SIZE 26

class TrieNode {
public:
  shared_ptr<TrieNode> child[SIZE];
  bool end;
  TrieNode() {
    for (auto &i : child) {
      i = shared_ptr<TrieNode>();
    }
    end = false;
  }
};

class interface {
public:
  interface() {
  }
  virtual ~interface() {
  }
  virtual int i2c(char) = 0;
  virtual void insert(string &) = 0;
  virtual bool del(string &) = 0;
  virtual bool search(string &) = 0;
  virtual bool is_empty(shared_ptr<TrieNode>) const = 0;
};

class Trie : public interface {
  shared_ptr<TrieNode> root;
  int total;

public:
  Trie() {
    root = make_shared<TrieNode>();
    total = 0;
  }
  ~Trie() override = default;
  int i2c(char c) override { return static_cast<int>(c - 'a'); }
  void insert(string &str) override {
    shared_ptr<TrieNode> curr = root;
    for (char c : str) {
      if (curr->child[i2c(c)] == shared_ptr<TrieNode>(nullptr)) {
        curr->child[i2c(c)] = make_shared<TrieNode>();
      }
      curr = curr->child[i2c(c)];
    }
    curr->end = true;
  }
  bool search(string &str) override {
    shared_ptr<TrieNode> curr = root;
    for (char c : str) {
      if (curr->child[i2c(c)] == shared_ptr<TrieNode>(nullptr)) return false;
      curr = curr->child[i2c(c)];
    }
    if (curr->end == true) return true;
    return false;
  }
  bool part_delete(const string &str, const shared_ptr<TrieNode> &checkout) {
    if (checkout == nullptr) return false;
    if (str.empty()) {
      if (checkout->end == true) {
        checkout->end = false;
        return true;
      }
      return false;
    }
    string part = str.substr(1);
    if (part_delete(part, checkout->child[i2c(str[0])])) {
      if (is_empty(checkout->child[i2c(str[0])])) {
        checkout->child[i2c(str[0])].reset();
        checkout->child[i2c(str[0])] = nullptr;
        return true;
      }
      return true;
    }
    return false;
  }

  bool del(string &str) override {
    if (part_delete(str, root)) return true;
    return false;
  }

  bool is_empty(shared_ptr<TrieNode> check) const override {
    /*
    for (const auto & i : check->child) {
      if (i != nullptr || check->end == true) return false;
    }
    return true;
    */
    return ranges::all_of(check->child,
                          [check](const auto &i) {
                            return i == nullptr && !check->end;
                          });
  }
};
