#include <iostream>
#include <utility>

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

Node *insertNoRecurse(Node *root, int key) {
  if (!root) {
    return new Node(key);
  }
  Node *p = root;
  while (true) {
    if (p->key == key)
      break;
    if (key < p->key) {
      if (!p->left) {
        p->left = new Node(key);
        break;
      }
      p = p->left;
    } else {
      if (!p->right) {
        p->right = new Node(key);
        break;
      }
      p = p->right;
    }
  }
  return root;
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

bool deleteNode(Node *root, int key) {
  if (!root)
    return false;

  Node *prev = root;
  bool isLeft;
  while (!prev) {
    if (prev->left && prev->left->key == key) {
      isLeft = true;
      break;
    } else if (prev->right && prev->right->key == key) {
      isLeft = false;
      break;
    }
    if (key > prev->key) {
      prev = prev->right;
    } else {
      prev = prev->left;
    }
  }
  if (!prev)
    return false;

  Node *curr = isLeft ? prev->left : prev->right;
  if (!curr->left && !curr->right) { // caso 1: nessun figlio
    if (isLeft) {
      delete prev->left;
      prev->left = nullptr;
    } else {
      delete prev->right;
      prev->right = nullptr;
    }
  } else if (curr->left && !curr->right) { // caso 2a: solo sinistro
    std::swap(curr->key, curr->left->key);
    delete curr->left;
    curr->left = nullptr;
  } else if (!curr->left && curr->right) { // caso 2b: solo destra
    std::swap(curr->key, curr->right->key);
    delete curr->right;
    curr->right = nullptr;
  } else { // caso 3: tutti e due figli
  }

  return true;
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
  Node *root = new Node();
  root = insertNoRecurse(root, 5);
  std::cout << "inserted non-recursive 5" << std::endl;
  root = insert(root, 10);
  std::cout << "inserted 10" << std::endl;
  root = insert(root, 4);
  std::cout << "inserted 4" << std::endl;
  std::cout << "search 5: " << (search(root, 5) ? "true" : "false")
            << std::endl;
  std::cout << "search 3: " << (search(root, 3) ? "true" : "false")
            << std::endl;
  std::cout << "search non-recursive 10: "
            << (searchNoRecurse(root, 10) ? "true" : "false") << std::endl;
  std::cout << "search non-recursive 3: "
            << (searchNoRecurse(root, 3) ? "true" : "false") << std::endl;
  std::cout << "pre order: ";
  preOrder(root);
  std::cout << std::endl;
  std::cout << "in order: ";
  inOrder(root);
  std::cout << std::endl;
  std::cout << "post order: ";
  postOrder(root);
  std::cout << std::endl;
  return 0;
}
