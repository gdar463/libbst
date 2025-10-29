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

Node *insert(Node *n, int key) {
  if (!n)
    return new Node(key);
  if (key == n->key)
    return n;

  if (key > n->key) {
    n->right = insert(n->right, key);
  } else {
    n->left = insert(n->left, key);
  }
  return n;
}

Node *searchNoRecurse(Node *root, int key) {
  if (!root)
    return nullptr;
  if (root->key == key)
    return root;

  Node *p = root;
  while (!p) {
    if (p->key == key)
      return p;
    if (key > p->key) {
      p = p->right;
    } else {
      p = p->left;
    }
  }
  return nullptr;
}

Node *search(Node *n, int key) {
  if (!n)
    return nullptr;
  if (n->key == key)
    return n;

  if (key > n->key)
    return search(n->right, key);
  return search(n->left, key);
}

void preOrder(Node *n) {
  if (!n)
    return;

  std::cout << n->key << " ";
  preOrder(n->left);
  preOrder(n->right);
}

void inOrder(Node *n) {
  if (!n)
    return;

  inOrder(n->left);
  std::cout << n->key << " ";
  inOrder(n->right);
}

void postOrder(Node *n) {
  if (!n)
    return;

  postOrder(n->left);
  postOrder(n->right);
  std::cout << n->key << " ";
}

int main() {
  Bst *tree = new Bst();
  std::cout << (insertNoRecurse(tree, 5) ? "true" : "false") << std::endl;
  std::cout << (insert(tree->root, 10) ? "true" : "false") << std::endl;
  std::cout << (insert(tree->root, 4) ? "true" : "false") << std::endl;
  std::cout << (search(tree->root, 5) ? "true" : "false") << std::endl;
  std::cout << (searchNoRecurse(tree->root, 3) ? "true" : "false") << std::endl;
  preOrder(tree->root);
  std::cout << std::endl;
  inOrder(tree->root);
  std::cout << std::endl;
  postOrder(tree->root);
  std::cout << std::endl;
  return 0;
}
