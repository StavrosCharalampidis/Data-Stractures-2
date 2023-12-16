#include <iostream>

// Forward declaration of the Node class
template <typename T>
class Node;

// Forward declaration of the Visitor class
template <typename T>
class Visitor;

// Abstract Visitor class
template <typename T>
class Visitor {
public:
    virtual void visit(Node<T>* node) = 0;
};

// Concrete Node class representing a node in the binary tree
template <typename T>
class Node {
public:
    virtual void accept(Visitor<T>* visitor) = 0;
};

// Concrete implementation of a binary tree node
template <typename T>
class TreeNode : public Node<T> {
public:
    T data;
    TreeNode<T>* left;
    TreeNode<T>* right;

    TreeNode(T value) : data(value), left(nullptr), right(nullptr) {}

    // Implementation of the accept method to allow a Visitor to visit this node
    virtual void accept(Visitor<T>* visitor) override {
        visitor->visit(this);
    }
};

// Concrete Visitor implementation for preorder traversal
template <typename T>
class PreorderVisitor : public Visitor<T> {
public:
    // Operation to be performed on each node during preorder traversal
    virtual void visit(Node<T>* node) override {
        TreeNode<T>* treeNode = dynamic_cast<TreeNode<T>*>(node);
        if (treeNode) {
            // Perform the desired operation (in this case, print the node's data)
            std::cout << treeNode->data << " ";
            
            // Recursively visit the left and right children
            if (treeNode->left) treeNode->left->accept(this);
            if (treeNode->right) treeNode->right->accept(this);
        }
    }
};

int main() {
    // Construct a sample binary tree with integer values
    TreeNode<int>* root = new TreeNode<int>(1);
    root->left = new TreeNode<int>(2);
    root->right = new TreeNode<int>(3);
    root->left->left = new TreeNode<int>(4);
    root->left->right = new TreeNode<int>(5);

    // Create a PreorderVisitor for integers
    PreorderVisitor<int> preorderVisitor;

    // Use the visitor to perform the preorder traversal and print the nodes
    root->accept(&preorderVisitor);

    // Clean up memory (in a real-world scenario, you would need to delete the nodes properly)
    return 0;
}
