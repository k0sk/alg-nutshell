#define CATCH_CONFIG_MAIN
#include <string>
#include "catch.hpp"
#include "rb_tree.h"

typedef RBNode<std::string, int> SINode;
typedef RBNode<int, int> IINode;

TEST_CASE( "RBTree<string, int> is constructed", "[rbtree]" ) {
    RBTree<std::string, int> tree;

    tree.insert("a", 1);
    REQUIRE(tree.root->key == "a");
    tree.insert("b", 2);
    tree.insert("c", 3);
    REQUIRE(tree.root->key == "b");
    REQUIRE(tree.root->color == SINode::BLACK);

    RBNode<std::string, int> *tmp;
    tmp = tree.minimum();
    REQUIRE(tmp->key == "a");
    REQUIRE(tmp->color == SINode::RED);

    tmp = tree.maximum();
    REQUIRE(tmp->key == "c");
    REQUIRE(tmp->color == SINode::RED);

    tree.print();
}

TEST_CASE( "RBTree<int, int> is constructed", "[rbtree]" ) {
   RBTree<int, int> tree;

   int arr[] = {22, 48, 69, 88, 123, 278, 309, -1};
   IINode::Color col[] = {
       IINode::BLACK, IINode::BLACK, IINode::BLACK,
       IINode::RED, IINode::RED, IINode::BLACK, IINode::RED
   };

    for (int i = 0; arr[i] != -1; i++) {
        tree.insert(arr[i], arr[i]);
    }

    REQUIRE(tree.root->key == 48);

    RBNode<int, int> *tmp;
    for (int i = 0; arr[i] != -1; i++) {
        tmp = tree.search(arr[i]);
        REQUIRE(tmp != tree.nil);
        REQUIRE(tmp->color == col[i]);
    }

    tmp = tree.minimum();
    REQUIRE(tmp->value == 22);
    REQUIRE(tmp->parent == tree.root);
    REQUIRE(tmp->left == tree.nil);
    REQUIRE(tmp->right == tree.nil);

    tmp = tree.maximum();
    REQUIRE(tmp->value == 309);
    REQUIRE(tmp->parent->key == 278);
    REQUIRE(tmp->left == tree.nil);
    REQUIRE(tmp->right == tree.nil);

    tree.insert(10, 10);
    REQUIRE(tree.minimum()->key == 10);
    tree.insert(405, 405);
    REQUIRE(tree.maximum()->key == 405);

    tree.print();
}

