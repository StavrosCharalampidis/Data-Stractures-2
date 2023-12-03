#include <iostream>
#include <string>
#include <vector>

template <typename T>
class BinaryNode
{
private:
    std::string User_Name;
    std::vector<std::string> contacts;
    BinaryNode<T> *Left, *Right, *Parent;

public:
    BinaryNode(std::string User_Name)
    {
        this->User_Name = User_Name;
        this->Parent, this->Left, this->Right = NULL;
    };

    BinaryNode()
    {
        this->Parent, this->Left, this->Right = NULL;
    };

    BinaryNode<T> *insert_BinaryNode(BinaryNode<T> **root, std::string User_Name)
    {
        if (*root == NULL)
        {
            BinaryNode<T> *new_BinaryNode = new BinaryNode<T>(User_Name);
            new_BinaryNode->Left = NULL;
            new_BinaryNode->Right = NULL;
            *root = new_BinaryNode;
            return new_BinaryNode;
        }

        if (User_Name < (*root)->User_Name)
        {
            (*root)->Left = insert_BinaryNode(&(*root)->Left, User_Name);
        }
        else
        {
            (*root)->Right = insert_BinaryNode(&(*root)->Right, User_Name);
        }
        return *root;
    }

    void inorder(BinaryNode<T> *root)
    {
        if (root == NULL)
        {
            return;
        }

        inorder(root->Left);
        std::cout << root->User_Name << " ";
        inorder(root->Right);
    }


    BinaryNode<T> *Delete(BinaryNode<T> *root, std::string User_Name)
    {
        if (root == NULL)
        {
            return root;
        }
        if (User_Name < root->User_Name)
        {
            root->Left = Delete(root->Left, User_Name);
        }
        else if (User_Name > root->User_Name)
        {
            root->Right = Delete(root->Right, User_Name);
        }
        else
        {
            if (root->Left == NULL)
            {
                BinaryNode<T> *temp = root->Right;
                delete root;
                return temp;
            }
            else if (root->Right == NULL)
            {
                BinaryNode<T> *temp = root->Left;
                delete root;
                return temp;
            }
            BinaryNode<T> *temp = root->Right;
            while (temp->Left != NULL)
            {
                temp = temp->Left;
            }
            root->User_Name = temp->User_Name;
            root->Right = Delete(root->Right, temp->User_Name);
        }
        return root;
    }

    void add_contact(std::string contact)
    {
        contacts.push_back(contact);
    }

    void accept_friend_request(BinaryNode<T> *root, std::string friend_Name)
    {
        if (root == NULL)
        {
            return;
        }

        if (root->User_Name == friend_Name)
        {
            root->add_contact(User_Name);
        }
        else if (friend_Name < root->User_Name)
        {
            accept_friend_request(root->Left, friend_Name);
        }
        else
        {
            accept_friend_request(root->Right, friend_Name);
        }
    }

    void update_connections(BinaryNode<T> *root, std::string user_Name, std::string friend_Name)
    {
        if (root == NULL)
        {
            return;
        }

        if (root->User_Name == user_Name)
        {
            root->add_contact(friend_Name);
        }
        else if (user_Name < root->User_Name)
        {
            update_connections(root->Left, user_Name, friend_Name);
        }
        else
        {
            update_connections(root->Right, user_Name, friend_Name);
        }
    }

    void check_friends(BinaryNode<std::string> *root, std::string user1, std::string user2)
    {
        if (root == NULL)
        {
            std::cout << "The social network is empty." << std::endl;
            return;
        }

        BinaryNode<std::string> *user1_node = NULL;
        BinaryNode<std::string> *user2_node = NULL;

        while (root != NULL)
        {
            if (root->User_Name == user1)
            {
                user1_node = root;
                break;
            }
            else if (user1 < root->User_Name)
            {
                root = root->Left;
            }
            else
            {
                root = root->Right;
            }
        }

        if (user1_node == NULL)
        {
            std::cout << user1 << " is not a user in the social network." << std::endl;
            return;
        }

        for (std::string contact : user1_node->contacts)
        {
            if (contact == user2)
            {
                std::cout << user1 << " and " << user2 << " are friends." << std::endl;
                return;
            }
        }

        std::cout << user1 << " and " << user2 << " are not friends." << std::endl;
    }

    void find_mutual_friends(BinaryNode<std::string> *root, std::string user1, std::string user2)
    {
        if (root == NULL)
        {
            std::cout << "The social network is empty." << std::endl;
            return;
        }

        BinaryNode<std::string> *user1_node = NULL;
        BinaryNode<std::string> *user2_node = NULL;

        while (root != NULL)
        {
            if (root->User_Name == user1)
            {
                user1_node = root;
                break;
            }
            else if (user1 < root->User_Name)
            {
                root = root->Left;
            }
            else
            {
                root = root->Right;
            }
        }

        if (user1_node == NULL)
        {
            std::cout << user1 << " is not a user in the social network." << std::endl;
            return;
        }

        bool is_friend = false;
        for (std::string contact : user1_node->contacts)
        {
            if (contact == user2)
            {
                is_friend = true;
                break;
            }
        }

        if (!is_friend)
        {
            std::cout << user1 << " and " << user2 << " are not friends." << std::endl;
            return;
        }

        user2_node = NULL;
        while (root != NULL)
        {
            if (root->User_Name == user2)
            {
                user2_node = root;
                break;
            }
            else if (user2 < root->User_Name)
            {
                root = root->Left;
            }
            else
            {
                root = root->Right;
            }
        }

        if (user2_node == NULL)
        {
            std::cout << user2 << " is not a user in the social network." << std::endl;
            return;
        }

        std::vector<std::string> mutual_friends;
        for (std::string contact : user1_node->contacts)
        {
            for (std::string friend_name : user2_node->contacts)
            {
                if (contact == friend_name)
                {
                    mutual_friends.push_back(contact);
                    break;
                }
            }
        }

        if (mutual_friends.empty())
        {
            std::cout << user1 << " and " << user2 << " do not have any mutual friends." << std::endl;
            return;
        }

        std::cout << user1 << " and " << user2 << " have the following mutual friends: ";
        for (std::string friend_name : mutual_friends)
        {
            std::cout << friend_name << " ";
        }
        std::cout << std::endl;
    }

    int countUsers(BinaryNode<T> *root){
        int count;
        if (root == NULL)
        {
            return -1;
        }
        return 1 + countUsers(root->Left) + countUsers(root->Right);
    }
};

int main()
{
    BinaryNode<std::string> *root = NULL;
    int choice;
    std::string name, friend_name;
    std::cout << "Give choice: " << std::endl;
    std::cin >> choice;

    while (choice != 0)
    {
        if (choice == 1)
        {
            std::cout << "Give user name: " << std::endl;
            std::cin >> name;
            root->insert_BinaryNode(&root, name);
        }

        if (choice == 2)
        {
           std::cout << "the number of count is %d: " << root->countUsers(root) << std::endl; 
        }

        if (choice == 3)
        {
            printf("inorder \n");
            root->inorder(root);
        }

        if (choice == 4)
        {
            std::cout << "Give user name who accepted the friend request: " << std::endl;
            std::cin >> name;
            std::cout << "Give friend name: " << std::endl;
            std::cin >> friend_name;
            root->accept_friend_request(root, friend_name);
            root->update_connections(root, name, friend_name);
        }

        if (choice == 5)
        {
            std::cout << "Give first user name: " << std::endl;
            std::cin >> name;
            std::cout << "Give second user name: " << std::endl;
            std::cin >> friend_name;
            root->find_mutual_friends(root, name, friend_name);
        }

        if (choice == 6)
        {
            std::cout << "Give first user name: " << std::endl;
            std::cin >> name;
            std::cout << "Give second user name: " << std::endl;
            std::cin >> friend_name;
            root->check_friends(root, name, friend_name);
        }

        std::cout << "Give choice: " << std::endl;
        std::cin >> choice;
    }

    return 0;
}