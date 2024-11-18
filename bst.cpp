#include <iostream>
#include <vector>

struct Node {
    int key;
    Node* left;
    Node* right;
};


class BST{
    public:
        BST()
        {
            root = NULL;
        }
        ~BST() { removeSubtree(root); }

        void insertKey(int newKey) { insertKeyPrivate(newKey, root); }

        bool hasKey(int searchKey) { return hasKeyPrivate(searchKey, root); }

        std::vector<int> inOrder() { return inOrderPrivate(root); }

        int getHeight() { return getHeightPrivate(root); }

    private:
        Node* root;
        std::vector<int>treeInOrder;

        void removeSubtree(Node* pointer)
        {
            if(pointer != NULL)
            {
                if(pointer->left != NULL)
                {
                    removeSubtree(pointer->left);
                }
                if(pointer->right != NULL)
                {
                    removeSubtree(pointer->right);
                }

                delete pointer;
            }
        }

        int getHeightPrivate(Node* pointer)
        {
            if(pointer == NULL)
            {
                return 0;
            }

            int leftHeight = getHeightPrivate(pointer->left);
            int rightHeight = getHeightPrivate(pointer->right);

            if(leftHeight > rightHeight) 
            {
                return leftHeight + 1;
            } else {
                return rightHeight + 1;
            }

        }

        bool hasKeyPrivate(int searchKey, Node* pointer)
        {
            if(pointer != NULL)
            {
                if(pointer->key == searchKey) 
                {
                    return true;
                }
                else {
                    if(searchKey < pointer->key)
                    {
                        return hasKeyPrivate(searchKey, pointer->left);
                    } else {
                        return hasKeyPrivate(searchKey, pointer->right);
                    }
                }
            }
            return false;
        }

        std::vector<int> inOrderPrivate(Node* pointer)
        {
            if(root != NULL)
            {
                if(pointer->left != NULL)
                {
                    inOrderPrivate(pointer->left);
                }
                treeInOrder.push_back(pointer->key);

                if(pointer->right != NULL)
                {
                    inOrderPrivate(pointer->right);
                }
            }
            return treeInOrder;
        }

        void insertKeyPrivate(int newKey, Node* pointer)
        {
            if(root == NULL)
            {
                root = new Node();
                root->key = newKey;

            } 

            else if(newKey < pointer->key) 
            {
                if(pointer->left != NULL)
                {
                    insertKeyPrivate(newKey, pointer->left);
                } else {
                    Node* newLeaf = new Node();
                    newLeaf->key = newKey;
                    pointer->left = newLeaf;
                }
            }

            else if(newKey > pointer->key) 
            {
                if(pointer->right != NULL)
                {
                    insertKeyPrivate(newKey, pointer->right);
                } else {
                    Node* newLeaf = new Node();
                    newLeaf->key = newKey;
                    pointer->right = newLeaf;
                }
            }
            else {
                std::cout << "The key is aldreay added to the binary tree: " << newKey << std::endl;
            }
        }
};

int main(){

    BST tree;
    std::cout << "Enter the numbers to be stored (end with a letter): ";

    while ( std::cin.good() ){
        int number;
        std::cin >> number;
        if ( std::cin.good() ){
            tree.insertKey(number);
        }
    }
    std::cin.clear();
    char dummy;
    std::cin >> dummy;
    std::cout << "Which number do you want to look up? ";
    int searchFor;
    std::cin >> searchFor;
    std::cout << searchFor << " is in the tree: " << (tree.hasKey(searchFor) ? "yes" : "no") << std::endl;

    std::vector<int> inOrder = tree.inOrder();
    std::cout << "The numbers in sorted order: ";
    for (int i=0; i<inOrder.size(); i++){
        std::cout << inOrder.at(i) << ' ';
    }
    std::cout << std::endl;
    std::cout << "Height of the tree: " << tree.getHeight() << std::endl;

    return 0;
}