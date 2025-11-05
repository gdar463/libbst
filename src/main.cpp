#include <cstring>
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

Node *nextInOrder(Node *n) {
  if (!n)
    return nullptr;
  if (!n->left && !n->right) { // se non esistono figli
    return n;
  } else if (n->left && !n->right) { // se esiste solo figlio sinistro
    return n;
  } else { // se esistono entrambi o esiste solo destro
    return nextInOrder(n->right);
  }
}

void deleteLeafNode(Node *n, Node *&branch) {
  delete n;
  branch = nullptr;
}

void deletePartialNode(Node *n, Node *&branch) {
  if (n->left) {
    branch = n->left;
    delete n;
  } else {
    branch = n->right;
    delete n;
  }
}

//
// Fallisce in questa funzione, in alcuni casi, i.e. n == root
//
void deleteFullNode(Node *n, Node *&branch) {
  Node *next = nextInOrder(n->left);
  // si dà per scontato che next non abbia il figlio destro,
  // perchè nextInOrder l'avrebbe ritornato
  if (next->left) {
    next->right = n->right;
    delete n;
    branch = next;
  } else {
    std::swap(n->key, next->key);
    delete next;
  }
}

void switchForDelete(Node *n, Node *&branch) {
  if (!n->left && !n->right)
    return deleteLeafNode(n, branch);
  if (n->left && n->right)
    return deleteFullNode(n, branch);
  return deletePartialNode(n, branch);
}

bool deleteNodeNoRecurse(Node *&root, int key) {
  if (!root)
    return false;

  Node *p = root;
  // uso un puntatore bool per isLeft, per sfruttare il fatto che
  // se non toccato rimane ad un valore terzo da true e false, ovvero nullptr
  bool *isLeft = nullptr;
  while (p) {
    if (p->key == key)
      break;
    if (p->left && p->left->key == key) {
      isLeft = new bool(true);
      break;
    }
    if (p->right && p->right->key == key) {
      isLeft = new bool(false);
      break;
    }
    if (key > p->key) {
      p = p->right;
    } else {
      p = p->left;
    }
  }

  if (!isLeft && p == root) {
    switchForDelete(root, root);
  } else {
    if (*isLeft) {
      switchForDelete(p->left, p->left);
    } else {
      switchForDelete(p->right, p->right);
    }
  }
  delete isLeft;
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

void debug(Node *n);

int main(int argc, char **argv) {
  Node *root = new Node(50);
  root = insertNoRecurse(root, 30);
  std::cout << "inserted non-recursive 30" << std::endl;
  root = insert(root, 60);
  std::cout << "inserted 60" << std::endl;
  root = insert(root, 40);
  std::cout << "inserted 40" << std::endl;
  std::cout << "search 50: ";
  std::cout << (search(root, 50) ? "true" : "false") << std::endl;
  std::cout << "search 45: ";
  std::cout << (search(root, 45) ? "true" : "false") << std::endl;
  std::cout << "search non-recursive 60: ";
  std::cout << (searchNoRecurse(root, 60) ? "true" : "false") << std::endl;
  std::cout << "search non-recursive 45: ";
  std::cout << (searchNoRecurse(root, 45) ? "true" : "false") << std::endl;
  std::cout << "pre order: ";
  preOrder(root);
  std::cout << std::endl;
  std::cout << "in order: ";
  inOrder(root);
  std::cout << std::endl;
  std::cout << "post order: ";
  postOrder(root);
  std::cout << std::endl;
  if (argc == 3 && strcmp(argv[1], "--det") == 0) {
    int len = std::atoi(argv[2]);
    int *nodes = new int[len];
    std::cout << "enter space-delimeted nodes: ";
    for (int i = 0; i < len; i++) {
      std::cin >> nodes[i];
    }
    for (int *p = nodes; p != nodes + len; ++p) {
      insert(root, *p);
    }
    delete[] nodes;
  } else if (argc == 3 && strcmp(argv[1], "--rand") == 0) {
    std::cout << "random inserts: ";
    srand(time(NULL));
    for (int i = 0; i < std::atoi(argv[2]); i++) {
      int mark = rand() % 20 * 10;
      insert(root, mark);
      std::cout << mark << " ";
    }
    std::cout << std::endl;
  }
  debug(root);
  std::cout << std::endl;
  std::cout << "found 100: ";
  Node *found = search(root, 100);
  std::cout << (found ? "true" : "false") << std::endl;
  inOrder(root);
  std::cout << std::endl;
  std::cout << "deleting 60: ";
  std::cout << (deleteNodeNoRecurse(root, 60) ? "true" : "false") << std::endl;
  debug(root);
  std::cout << std::endl;
  return 0;
}

void debug(Node *n) {
  if (!n) {
    std::cout << "e ";
    return;
  } else {
    std::cout << " ";
  }

  std::cout << n->key;
  if (!n->left && !n->right) {
    std::cout << "f ";
    return;
  } else {
    std::cout << " ";
  }
  std::cout << "l";
  debug(n->left);
  std::cout << "r";
  debug(n->right);
}
