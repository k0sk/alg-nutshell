#include <iostream>
#include <string>

template<typename K, typename V>
struct RBNode {
    public:
        enum Color {
            RED,
            BLACK
        };
        K key;
        V value;
        Color color;
        RBNode<K, V>* parent;
        RBNode<K, V>* left;
        RBNode<K, V>* right;

        RBNode() {
            this->color = RED;
        }

        RBNode(const K &key, const V &value, RBNode<K, V> *nil) : key(key), value(value) {
            this->color = RED;
            this->parent = nil;
            this->left = nil;
            this->right = nil;
        }
};

template<typename K, typename V>
class RBTree {
    typedef RBNode<K, V> Node;

    public:
        Node *root;
        Node *nil;

        RBTree() {
            this->nil = new Node();
            this->nil->color = Node::BLACK;
            this->root = this->nil;
        }

        void insert(const K &key, const V &value) {
            Node* new_node = new Node(key, value, this->nil);

            Node* new_parent = this->nil;
            Node* tmp = this->root;
            while (tmp != this->nil) {
                new_parent = tmp;
                if (key < tmp->key) tmp = tmp->left;
                else tmp = tmp->right;
            }

            new_node->parent = new_parent;

            if (new_parent == this->nil) this->root = new_node;
            else if (key < new_parent->key) new_parent->left = new_node;
            else new_parent->right = new_node;

            insert_fixup(new_node);
        }

        Node* search(const K &key) {
            return inorder_search(this->root, key);
        }

        Node* minimum() {
            Node *tmp = this->root;
            while (tmp->left != this->nil) tmp = tmp->left;

            return tmp;
        }

        Node* maximum() {
            Node *tmp = this->root;
            while (tmp->right != this->nil) tmp = tmp->right;

            return tmp;
        }

        void print() {
            inorder_print(this->root, 0);
        }

    private:
        void insert_fixup(Node *node) {
            Node *tmp;

            while (node->parent->color == Node::RED) {
                if (node->parent == node->parent->parent->left) {
                    tmp = node->parent->parent->right;

                    if (tmp->color == Node::RED) {
                        node->parent->color = Node::BLACK;
                        tmp->color = Node::BLACK;
                        node->parent->parent->color = Node::RED;
                        node = node->parent->parent;
                    } else {
                        if (node == node->parent->right) {
                            node = node->parent;
                            left_rotate(node);
                        }

                        node->parent->color = Node::BLACK;
                        node->parent->parent->color = Node::RED;
                        right_rotate(node->parent->parent);
                    }
                } else {
                    tmp = node->parent->parent->left;

                    if (tmp->color == Node::RED) {
                        node->parent->color = Node::BLACK;
                        tmp->color = Node::BLACK;
                        node->parent->parent->color = Node::RED;
                        node = node->parent->parent;
                    } else {
                        if (node == node->parent->left) {
                            node = node->parent;
                            right_rotate(node);
                        }

                        node->parent->color = Node::BLACK;
                        node->parent->parent->color = Node::RED;
                        left_rotate(node->parent->parent);
                    }
                }
            }

            this->root->color = Node::BLACK;
        }

        void left_rotate(Node *node) {
            Node *tmp = node->right;
            node->right = tmp->left;

            if (tmp->left != this->nil) tmp->left->parent = node;
            tmp->parent = node->parent;

            if (node->parent == this->nil) this->root = tmp;
            else if (node == node->parent->left) node->parent->left = tmp;
            else node->parent->right = tmp;

            tmp->left = node;
            node->parent = tmp;
        }

        void right_rotate(Node *node) {
            Node *tmp = node->left;
            node->left = tmp->right;

            if (tmp->right != this->nil) tmp->right->parent = node;
            tmp->parent = node->parent;

            if (node->parent == this->nil) this->root = tmp;
            else if (node == node->parent->right) node->parent->right = tmp;
            else node->parent->left = tmp;

            tmp->right = node;
            node->parent = tmp;
        }

        Node* inorder_search(Node *node, const K &key) {
            if (node == this->nil || key == node->key) return node;

            if (key < node->key) return inorder_search(node->left, key);
            else return inorder_search(node->right, key);
        }

        void inorder_print(const Node *node, int depth) {
            if (node != this->nil) {
                inorder_print(node->left, depth + 1);
                std::cout << std::string(depth, '-') << node->key;
                std::cout << " " << (node->color == Node::RED ? "RED" : "BLACK") << std::endl;
                inorder_print(node->right, depth + 1);
            }
        }
};

