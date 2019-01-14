#include <iostream>

using namespace std;

struct node

    {
  int key;
    
  node* parent;
    
  char color;
    
  node* left;
    
  node* right;
    
};

class RBtree
    
    {
    
 public:
    
  node* root;
    
  node *q, *p;

  RBеree()

  {
    q = nullptr;

    root = nullptr;
  }

  void insert();

  void insertfix(node*);

  void leftrotate(node*);

  void rightrotate(node*);

  void del();

  node* successor(node*);

  void delfix(node*);

  friend void display(node*, int space);

  void search();

  ostream& display_for_operator(node* p, int space, ostream& os);

  friend ostream& operator<<(ostream& os, RBtree& tree);
};

void RBtree::insert()

{
  int z, i = 0;

  cout << "\nEnter key of the node to be inserted: ";

  cin >> z;

  node* q;

  node* t = new node;

  t->key = z;

  t->left = nullptr;

  t->right = nullptr;

  t->color = 'r';

  p = root;

  q = nullptr;

  if (root == nullptr)

  {
    root = t;

    t->parent = nullptr;
  }

  else

  {
    while (p != nullptr)

    {
      q = p;

      if (p->key < t->key)

        p = p->right;

      else

        p = p->left;
    }

    t->parent = q;

    if (q->key < t->key)

      q->right = t;

    else

      q->left = t;
  }

  insertfix(t);
}

void RBtree::insertfix(node* t)

{
  node* u;

  if (root == t)

  {
    t->color = 'b';

    return;
  }

  while (t->parent != nullptr && t->parent->color == 'r')

  {
    node* g = t->parent->parent;

    if (g->left == t->parent)

    {
      if (g->right != nullptr)

      {
        u = g->right;

        if (u->color == 'r')

        {
          t->parent->color = 'b';

          u->color = 'b';

          g->color = 'r';

          t = g;
        }
      }

      else

      {
        if (t->parent->right == t)

        {
          t = t->parent;

          leftrotate(t);
        }

        t->parent->color = 'b';

        g->color = 'r';

        rightrotate(g);
      }
    }

    else

    {
      if (g->left != nullptr)

      {
        u = g->left;

        if (u->color == 'r')

        {
          t->parent->color = 'b';

          u->color = 'b';

          g->color = 'r';

          t = g;
        }
      }

      else

      {
        if (t->parent->left == t)

        {
          t = t->parent;

          rightrotate(t);
        }

        t->parent->color = 'b';

        g->color = 'r';

        leftrotate(g);
      }
    }

    root->color = 'b';
  }
}

void RBtree::del()

{
  if (root == nullptr)

  {
    cout << "\nEmpty Tree.";

    return;
  }

  int x;

  cout << "\nEnter the key of the node to be deleted: ";

  cin >> x;

  node* p;

  p = root;

  node* y = nullptr;

  node* q = nullptr;

  int found = 0;

  while (p != nullptr && found == 0)

  {
    if (p->key == x) found = 1;

    if (found == 0)

    {
      if (p->key < x)

        p = p->right;

      else

        p = p->left;
    }
  }

  if (found == 0)

  {
    cout << "\nElement Not Found.";

    return;
  }

  else

  {
    cout << "\nDeleted Element: " << p->key;

    cout << "\nColour: ";

    if (p->color == 'b')

      cout << "Black\n";

    else

      cout << "Red\n";

    if (p->parent != nullptr)

      cout << "\nParent: " << p->parent->key;

    else

      cout << "\nThere is no parent of the node. ";

    if (p->right != nullptr)

      cout << "\nRight Child: " << p->right->key;

    else

      cout << "\nThere is no right child of the node. ";

    if (p->left != nullptr)

      cout << "\nLeft Child: " << p->left->key;

    else

      cout << "\nThere is no left child of the node. ";

    cout << "\nNode Deleted.";

    if (p->left == nullptr || p->right == nullptr)

      y = p;

    else

      y = successor(p);

    if (y->left != nullptr)

      q = y->left;

    else

    {
      if (y->right != nullptr)

        q = y->right;

      else

        q = nullptr;
    }

    if (q != nullptr) q->parent = y->parent;

    if (y->parent == nullptr)

      root = q;

    else

    {
      if (y == y->parent->left)

        y->parent->left = q;

      else

        y->parent->right = q;
    }

    if (y != p)

    {
      p->color = y->color;

      p->key = y->key;
    }

    if (y->color == 'b') delfix(q);
  }
}

void RBtree::delfix(node* p)

{
  node* s;

  while (p != root && p->color == 'b')

  {
    if (p->parent->left == p)

    {
      s = p->parent->right;

      if (s->color == 'r')

      {
        s->color = 'b';

        p->parent->color = 'r';

        leftrotate(p->parent);

        s = p->parent->right;
      }

      if (s->right->color == 'b' && s->left->color == 'b')

      {
        s->color = 'r';

        p = p->parent;
      }

      else

      {
        if (s->right->color == 'b')

        {
          s->left->color = 'b';

          s->color = 'r';

          rightrotate(s);

          s =

              p->parent->right;
        }

        s->color = p->parent->color;

        p->parent->color = 'b';

        s->right->color = 'b';

        leftrotate(p->parent);

        p = root;
      }
    }

    else

    {
      s = p->parent->left;

      if (s->color == 'r')

      {
        s->color = 'b';

        p->parent->color = 'r';

        rightrotate(p->parent);

        s = p->parent->left;
      }

      if (s->left->color == 'b' && s->right->color == 'b')

      {
        s->color = 'r';

        p = p->parent;
      }

      else

      {
        if (s->left->color == 'b')

        {
          s->right->color = 'b';

          s->color = 'r';

          leftrotate(s);

          s = p->parent->left;
        }

        s->color = p->parent->color;

        p->parent->color = 'b';

        s->left->color = 'b';

        rightrotate(p->parent);
      }

      p->color = 'b';

      root->color = 'b';
    }
  }

  void RBtree::leftrotate(node * p)

  {
    if (p->right == nullptr)

      return;

    else

    {
      node* y = p->right;

      if (y->left != nullptr)

      {
        p->right = y->left;

        y->left->parent = p;
      }

      else

        p->right = nullptr;

      if (p->parent != nullptr) y->parent = p->parent;

      if (p->parent == nullptr)

        root = y;

      else

      {
        if (p == p->parent->left)

          p->parent->left = y;

        else

          p->parent->right = y;
      }

      y->left = p;

      p->parent = y;
    }
  }

  void RBtree::rightrotate(node * p)

  {
    if (p->left == nullptr)

      return;

    else

    {
      node* y = p->left;

      if (y->right != nullptr)

      {
        p->left = y->right;

        y->right->parent = p;
      }

      else

        p->left = nullptr;

      if (p->parent != nullptr) y->parent = p->parent;

      if (p->parent == nullptr)

        root = y;

      else

      {
        if (p == p->parent->left)

          p->parent->left = y;

        else

          p->parent->right = y;
      }

      y->right = p;

      p->parent = y;
    }
  }

  node* RBtree::successor(node * p)

  {
    node* y = nullptr;

    if (p->left != nullptr)

    {
      y = p->left;

      while (y->right != nullptr) y = y->right;
    }

    else

    {
      y = p->right;

      while (y->left != nullptr) y = y->left;
    }

    return y;
  }

  void display(RBtree & obj, node * p, int space)

  {
    if (obj.root == nullptr)

    {
      cout << "\nEmpty Tree.";

      return;
    }

    if (p != nullptr)

    {
      int count = 1;

      space += count;

      display(obj, obj.p->right, space);

      cout << endl;

      for (int i = count; i < space; i++)

      {
        cout << " ";
      }

      cout << "--" << p->key << "(" << p->color << ")" << endl;

      display(obj, obj.p->left, space);
    }
  }

  void RBtree::search()

  {
    if (root == nullptr)

    {
      cout << "\nEmpty Tree\n";

      return;
    }

    int x;

    cout << "\n Enter key of the node to be searched: ";

    cin >> x;

    node* p = root;

    int found = 0;

    while (p != nullptr && found == 0)

    {
      if (p->key == x) found = 1;

      if (found == 0)

      {
        if (p->key < x)

          p = p->right;

        else

          p = p->left;
      }
    }

    if (found == 0)

      cout << "\nElement Not Found.";

    else

    {
      cout << "\n\t FOUND NODE: ";

      cout << "\n Key: " << p->key;

      cout << "\n Colour: ";

      if (p->color == 'b')

        cout << "Black";

      else

        cout << "Red";

      if (p->parent != nullptr)

        cout << "\n Parent: " << p->parent->key;

      else

        cout << "\n There is no parent of the node. ";

      if (p->right != nullptr)

        cout << "\n Right Child: " << p->right->key;

      else

        cout << "\n There is no right child of the node. ";

      if (p->left != nullptr)

        cout << "\n Left Child: " << p->left->key;

      else

        cout << "\n There is no left child of the node. ";

      cout << endl;
    }
  }

  ostream& RBtree::display_for_operator(node * p, int space, ostream& os)

  {
    if (root == nullptr)

    {
      os << "\nEmpty Tree.";
    }

    if (p != nullptr)

    {
      int count = 1;

      space += count;

      display_for_operator(p->right, space, os);

      os << endl;

      for (int i = count; i < space; i++)

      {
        os << " ";
      }

      os << "--" << p->key << "(" << p->color << ")" << endl;

      display_for_operator(p->left, space, os);
    }

    return os;
  }

  ostream& operator<<(ostream & os, RBtree & tree) {
    return tree.display_for_operator(tree.root, 0, os);
  }

  int main()

  {
    int ch, y = 0;

    RBtree obj;

    do

    {
      cout << "\n\t RED BLACK TREE ";

      cout << "\n 1. Insert in the tree ";

      cout << "\n 2. Delete a node from the tree";

      cout << "\n 3. Search for an element in the tree";

      cout << "\n 4. Display the tree";

      cout << "\n 5. Display the tree by « operator";

      cout << "\n 6. Exit ";

      cout << "\nEnter Your Choice: ";

      cin >> ch;

      switch (ch)

      {
        case 1:
          obj.insert();

          cout << "\nNode Inserted.\n";

          break;

        case 2:
          obj.del();

          break;

        case 3:
          obj.search();

          break;

        case 4:
          display(obj, obj.p, 0);

          break;

        case 5:
          cout << obj;

          break;

        case 6:
          y = 1;

          break;

        default:
          cout << "\nEnter a Valid Choice.";
      }

      cout << endl;

    } while (y != 1);

    return 0;
  }
