#include "lab1.hpp"

class AVLTree : tree {

    private:
        unordered_map<tree_node*, int> _dep;

    public:
        AVLTree() {}

        int calcDep (tree_node *node1, tree_node *node2) {
            int l = _dep[node1];
            int d = _dep[node2];
            if (l > d) return l + 1;
            return d + 1;
        }

        tree_node *RightRotation (tree_node *B) {
            tree_node *L = B->left_node;
            if (L) {
                B->left_node = L->right_node;
                L->right_node = B;
                _dep[L] = calcDep(L->left_node, L->right_node);
            }
            _dep[B] = calcDep(B->left_node, B->right_node);
            return (L == NULL ? B : L);
        }

        tree_node *LeftRotation (tree_node *B) {
            tree_node *R = B->right_node;
            if (R) {
                B->right_node = R->left_node;
                R->left_node = B;
                _dep[R] = calcDep(R->left_node, R->right_node);
            }
            _dep[B] = calcDep(B->left_node, B->right_node);
            return (R == NULL ? B : R);
        }

        int FR (tree_node *node) {
            tree_node *node1 = node->left_node;
            tree_node *node2 = node->right_node;
            return _dep[node1] - _dep[node2];
        }
        
        tree_node *insert (tree_node *node, tree_node *new_node, char key) {
            if (node == NULL) {
                return new_node;
            }
            if (key > node->c) {
                node->right_node = insert(node->right_node, new_node, key);
                if (FR(node) == -2) {
                    if (key > node->right_node->c) node = LeftRotation(node); 
                    else {
                        node->right_node = RightRotation(node->right_node);
                        node = LeftRotation(node);
                    }
                }
            } else if (key < node->c) {
                node->left_node = insert(node->left_node, new_node, key);
                if (FR(node) == 2) {
                    if (key < node->left_node->c) node = RightRotation(node);
                    else {
                        node->left_node = LeftRotation(node->left_node);
                        node = RightRotation(node);
                    }
                }
            }
            _dep[node] = calcDep(node->left_node, node->right_node);
            return node;
        }

        void InsertElement (char key) {
            tree_node *node = new tree_node(key);
            _tree[key]=node;
            _dep[node] = 1;
            root_node = insert(root_node, node, key);
        }

        pair<char*, char*> getChildrenNodesValues (char *key=NULL) {
            pair<char*, char*> rj;
            tree_node *node;
            rj.first = NULL;
            rj.second = NULL; 
            
            if (key) node = _tree[*key];
            else {
                node = root_node;
            }
            if (node) {
                if (node->left_node) rj.first = &(node->left_node->c);
                if (node->right_node) rj.second = &(node->right_node->c);

            }
            return rj;
        }

        char *getRootNode() {
            return &root_node->c;
        }

        string PreOrderTraversal() {
            return traverse_pre_order();
        }

        string PostOrderTraversal() {
            return traverse_post_order();
        }
        void printTree() {
        _printTree("",root_node,true);
        }
        void _printTree(string p,tree_node *root,bool isLeft) {
            cout << p;
            cout << (!isLeft ? "├──" : "└──" );
            if(root!=NULL) {
                cout << root->c << endl;
            
                if(root->right_node || root->left_node) {
                    _printTree(p+(!isLeft ? "│   ":"    "),root->right_node,false);
                    _printTree(p+(!isLeft ? "│   ":"    "),root->left_node,true);
                }
            } else cout << endl;
        }
};

/*example of main function*/
/*int main() {
    AVLTree *avl = new AVLTree();
    string ispis="";
    char *root_value, *l, *d;
    char test = 'B';
    char test2 = 'Z';

    root_value = avl->getRootNode();
    cout << "Korijen: ";
    if (root_value == NULL) cout << "NULL";
    cout << endl;

    avl->InsertElement('L');
    avl->InsertElement('D');
    avl->InsertElement('B');
    avl->InsertElement('C');
    avl->InsertElement('G');
    avl->InsertElement('E');
    avl->InsertElement('J');
    avl->InsertElement('H');
    avl->InsertElement('K');
    avl->InsertElement('V');
    avl->InsertElement('O');
    avl->InsertElement('N');
    avl->InsertElement('M');
    avl->InsertElement('R');
    avl->InsertElement('P');
    avl->InsertElement('W');
    avl->InsertElement('Y');

    cout << "Ispis djece korijenskog cvora:";
    pair<char *, char *> kids = avl->getChildrenNodesValues();
    cout << (kids.first ? *kids.first:NULL) << " " << (kids.second ? *kids.second:NULL) << endl;
    //cout << *kids.first;
    //cout << *kids.second << endl;

    cout << "Ispis djece cvora B:";
    pair<char *, char *> kids2 = avl->getChildrenNodesValues(&test);
    cout << (kids2.first ? *kids2.first:NULL) << " " << (kids2.second ? *kids2.second:NULL) << endl;
    //cout << *kids2.first;
    //cout << *kids2.second << endl;
    
    cout << "Ispis djece cvora Z:";
    pair<char *, char *> kids3 = avl->getChildrenNodesValues(&test2);
    cout << (kids3.first ? *kids3.first:NULL) << " " << (kids3.second ? *kids.second:NULL) << endl;
    //cout << *kids2.first;
    //cout << *kids2.second << endl;

    cout <<"Ispis stabla:\n";
    avl->printTree();
    cout << endl;

    root_value = avl->getRootNode();
    cout << "Korijen: ";
    cout << *root_value;
    cout << endl;

    ispis = avl->PreOrderTraversal();
    cout << "PreOrder: ";
    cout << ispis;
    cout << endl;
    
    ispis = avl->PostOrderTraversal();
    cout << "PostOrder: ";
    cout << ispis;
    return 0;
}*/
 