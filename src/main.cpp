#include <iostream>
struct Node {
  int key;
  Node *left, *right;

  Node(int _key = 0) {
    key = _key;
    left = nullptr;
    right = nullptr;
  }
  Node(const Node &other) {
    key = other.key;
    left = other.left;
    right = other.right;
  }
  Node(const Node *other) {
    key = other->key;
    left = other->left;
    right = other->right;
  }
};

struct Bst {
  Node *root;

  Bst(Node *_root = nullptr) { root = _root; }
};

bool insertNoRecurse(Bst *tree, int key) {
  if (!tree)
    return false;
  if (!tree->root) {
    tree->root = new Node(key);
    return true;
  }
  Node *p = tree->root;
  while (true) {
    if (p->key == key)
      return false;
    if (key < p->key) {
      if (!p->left) {
        p->left = new Node(key);
        return true;
      }
      p = p->left;
    } else {
      if (!p->right) {
        p->right = new Node(key);
        return true;
      }
      p = p->right;
    }
  }
}

int main() {
  Bst *tree = new Bst();
  std::cout << (insertNoRecurse(tree, 5) ? "true" : "false") << std::endl;
  return 0;
}
