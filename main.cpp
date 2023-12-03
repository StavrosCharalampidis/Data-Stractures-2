#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QMessageBox>
#include <QTreeView>
#include <QStandardItemModel>
#include <QStandardItem>

#include <iostream>
#include <string>
#include <vector>

template <typename T>
class BinaryNode {
    private:
        std::string User_Name;
        std::vector<std::string> contacts;
        BinaryNode<T> *Left, *Right, *Parent;

    public:
        BinaryNode(std::string User_Name){
            this->User_Name = User_Name;
            this->Parent, this->Left, this->Right = NULL;
        };

        BinaryNode(){
            this->Parent, this->Left, this->Right = NULL;
        };

        BinaryNode<T> * insert_BinaryNode(BinaryNode<T> **root, std::string User_Name) {
            if (*root == NULL) {
                BinaryNode<T> *new_BinaryNode = new BinaryNode<T>(User_Name);
                new_BinaryNode->Left = NULL;
                new_BinaryNode->Right = NULL;
                *root = new_BinaryNode;
                return new_BinaryNode;
            }

            if (User_Name < (*root)->User_Name) {
            (*root)->Left = insert_BinaryNode(&(*root)->Left, User_Name);
            }
            else {
            (*root)->Right = insert_BinaryNode(&(*root)->Right, User_Name);
            }
            return *root;
        }

        void inorder(BinaryNode<T> *root, QStandardItem *parent) {
            if (root == NULL){
                return;
            }
            
            QStandardItem *item = new QStandardItem(QString::fromStdString(root->User_Name));
            parent->appendRow(item);
            inorder(root->Left, item);
            inorder(root->Right, item);
        }

        void printPreOrder(BinaryNode<T> *root){
            if (root == NULL){
                return;
            }
            
          
            std::cout << root->User_Name << " ";
            printPreOrder(root->Left);
            printPreOrder(root->Right);
            

        }

        BinaryNode<T> * Delete(BinaryNode<T> *root, std::string User_Name) {
            if (root == NULL) {
                return root;
            }
            if (User_Name < root->User_Name) {
                root->Left = Delete(root->Left, User_Name);
            } else if (User_Name > root->User_Name) {
                root->Right = Delete(root->Right, User_Name);
            } else {
                if (root->Left == NULL) {
                    BinaryNode<T> *temp = root->Right;
                    delete root;
                    return temp;
                } else if (root->Right == NULL) {
                    BinaryNode<T> *temp = root->Left;
                    delete root;
                    return temp;
                }
                BinaryNode<T> *temp = root->Right;
                while (temp->Left != NULL) {
                    temp = temp->Left;
                }
                root->User_Name = temp->User_Name;
                root->Right = Delete(root->Right, temp->User_Name);
            }
            return root;
        }

        void add_contact(std::string contact) {
            contacts.push_back(contact);
        }

        void accept_friend_request(BinaryNode<T> *root, std::string friend_Name) {
            if (root == NULL){
                return;
            }
            
            if (root->User_Name == friend_Name) {
                root->add_contact(User_Name);
            } else if (friend_Name < root->User_Name) {
                accept_friend_request(root->Left, friend_Name);
            } else {
                accept_friend_request(root->Right, friend_Name);
            }
        }

        void update_connections(BinaryNode<T> *root, std::string user_Name, std::string friend_Name) {
            if (root == NULL){
                return;
            }
            
            if (root->User_Name == user_Name) {
                root->add_contact(friend_Name);
            } else if (user_Name < root->User_Name) {
                update_connections(root->Left, user_Name, friend_Name);
            } else {
                update_connections(root->Right, user_Name, friend_Name);
            }
        }
};


int main(int argc, char *argv[]) {
    BinaryNode<std::string> *root = NULL;
    int choice;
    std::string name, friend_name;

    while (choice != 0) {
        std::cout << "1. Insert user" << std::endl;
        std::cout << "2. Print binary tree in preorder traversal" << std::endl;
        std::cout << "3. Print binary tree in inorder traversal" << std::endl;
        std::cout << "4. Accept friend request" << std::endl;
        std::cout << "5. Find mutual friends" << std::endl;
        std::cout << "6. Check if two users are friends" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 1) {   
            std::cout << "Enter user name: ";
            std::cin >> name;        
            root->insert_BinaryNode(&root, name);
        }

        if (choice == 2) {
            std::cout << "Preorder traversal: ";
            root->printPreOrder(root);
            std::cout << std::endl;
        }

        if (choice == 3) {
            std::cout << "Inorder traversal: ";
            root->inorder(root, new QStandardItem(QString("Root")));
            std::cout << std::endl;
        }
        
        if (choice == 4) {
            std::cout << "Enter user name who accepted the friend request: ";
            std::cin >> name;
            std::cout << "Enter friend name: ";
            std::cin >> friend_name;
            root->accept_friend_request(root, friend_name);
            root->update_connections(root, name, friend_name);
        }

        if (choice == 5) {
            std::cout << "Enter first user name: ";
            std::cin >> name;
            std::cout << "Enter second user name: ";
            std::cin >> friend_name;
            find_mutual_friends(root, name, friend_name);
        }

        if (choice == 6) {
            std::cout << "Enter first user name: ";
            std::cin >> name;
            std::cout << "Enter second user name: ";
            std::cin >> friend_name;
            check_friends(root, name, friend_name);
        }
    }

    return 0;
}