#ifndef TREE_H
#define TREE_H

struct node
{
  int key_value;
  node *left;
  node *right;
};

class btree
{
    public:
        btree();
        ~btree();

        void insert(int key, node* parent, int side);
        //node *search(int key);
        void destroy_tree();

    private:
        void destroy_tree(node *leaf);
        //void insert(int key, node *leaf);
        //node *search(int key, node *leaf);
        
        node *root;
};

#endif
