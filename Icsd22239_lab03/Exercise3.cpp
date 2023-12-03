
#include <iostream>

template <typename T>
class BinaryNode {
    private:

        T User_ID;
        BinaryNode<T> *Left, *Right;

    public:
        BinaryNode(T User_ID){
            this->User_ID = User_ID;
            this->Left = NULL;
            this->Right = NULL;
        };

        BinaryNode(){
            this->Left = NULL;
            this->Right = NULL;
        };

        BinaryNode<T> * insert_BinaryNode(BinaryNode<T> **root, T User_ID) {
            if (*root == NULL) {
                BinaryNode<T> *new_BinaryNode = new BinaryNode<T>(User_ID);
                new_BinaryNode->Left = NULL;
                new_BinaryNode->Right = NULL;
                return new_BinaryNode;
            }

            if (User_ID < (*root)->User_ID) {
            (*root)->Left = insert_BinaryNode(&(*root)->Left, User_ID);
            }
            else {
            (*root)->Right = insert_BinaryNode(&(*root)->Right, User_ID);
            }
            return *root;
        }

        void inorder(BinaryNode<T> *root) {
            if (root == NULL){
                return;
            }
            
            inorder(root->Left);
            printf("%d ", root->User_ID);
            inorder(root->Right);
            
        }

        void printPreOrder(BinaryNode<T> *root){
            if (root == NULL){
                return;
            }
            
            printf("%d ", root->User_ID);
            printPreOrder(root->Left);
            printPreOrder(root->Right);
            

        }

        BinaryNode<T> * Delete(BinaryNode<T> *root, T User_ID) {

            if (root == NULL) {
                std::cout << "BinaryNode not found ";
                return NULL;
            }

            if (root->User_ID > User_ID) {
                root->Left = Delete(root->Left, User_ID);
            }

            else if (root->User_ID < User_ID) {
                root->Right = Delete(root->Right, User_ID);
            }

            else {

                if (root->Left == NULL) {
                    BinaryNode<T> *temp = root->Right;
                    free(root);
                    return temp;
                }

                else if (root->Right == NULL) {
                    BinaryNode<T> *temp = root->Left;
                    free(root);
                    return temp;
                }

                else {
                    BinaryNode<T> *temp = root->Right;

                    while (temp->Left != NULL){
                        temp = temp->Left;
                    }

                    root->User_ID = temp->User_ID;
                    root->Right = Delete(root->Right, temp->User_ID);
                }
            }
            return root;
        }

};






    

int main(int argc, char const *argv[]) {
    BinaryNode<int> *root = new BinaryNode<int>();
    

    int choice, val, del_val;
    std::cout << "Give choice: " << std::endl;
    std::cin >> choice;

    while (choice != 0) {
        
        if (choice == 1) {
            std::cout << "Give data: " << std::endl;
            std::cin >> val;
            
            (*root).insert_BinaryNode(&root, val);
        }

        if (choice == 2) {
            printf("\npreorder \n");
            (*root).printPreOrder(root);
        }

        if (choice == 3) {
            printf("inorder \n");
            (*root).inorder(root);
        }
        
        if (choice == 4) {
            std::cout << "Give data to delete: " << std::endl;
            std::cin >> del_val;
            printf("Delete \n");
            (*root).Delete (root, del_val);
        }
        

        std::cout << "Give choice: " << std::endl;
        std::cin >> choice;
    }

    return 0;
}
