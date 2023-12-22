#include <iostream>
#include <string>
#include <vector>

template <typename T>
class BinaryTree
{
private:
    std::string User_ID;    
    std::string User_Name;
    std::string Last_Name;
    std::vector<std::string> contacts;
    BinaryTree<T> *Left, *Right;

public:
    BinaryTree(std::string User_Name, std::string User_ID, std::string Last_Name)
    {
        this->User_Name = User_Name;
        this->User_ID = User_ID;
        this->Last_Name = Last_Name;
        this->Left, this->Right = NULL;
    };

    BinaryTree()
    {
        this->Left, this->Right = NULL;
    };

    BinaryTree<T> *insert_BinaryTree(BinaryTree<T> **root, std::string User_Name, std::string User_ID, std::string Last_Name)
    {
        if (*root == NULL)
        {
            BinaryTree<T> *new_BinaryTree = new BinaryTree<T>(User_Name, User_ID, Last_Name);
            new_BinaryTree->Left = NULL;
            new_BinaryTree->Right = NULL;
            *root = new_BinaryTree;
            return new_BinaryTree;
        }

        if (User_Name < (*root)->User_Name)
        {
            (*root)->Left = insert_BinaryTree(&(*root)->Left, User_Name, User_ID, Last_Name);
        }
        else
        {
            (*root)->Right = insert_BinaryTree(&(*root)->Right, User_Name, User_ID, Last_Name);
        }
        return *root;
    }

   
    void inorder(BinaryTree<T> *root)
    {
        if (root == NULL)
        {
            return;
        }

        inorder(root->Left);
        std::cout << root->User_Name << " " << std::endl;
        inorder(root->Right);
    }

    BinaryTree<T> *Delete(BinaryTree<T> *root, std::string User_Name)
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
                BinaryTree<T> *temp = root->Right;
                delete root;
                return temp;
            }
            else if (root->Right == NULL)
            {
                BinaryTree<T> *temp = root->Left;
                delete root;
                return temp;
            }
            BinaryTree<T> *temp = root->Right;
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

    void accept_friend_request(BinaryTree<T> *root, std::string friend_Name)
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

    void update_connections(BinaryTree<T> *root, std::string user_Name, std::string friend_Name)
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

    void check_friends(BinaryTree<std::string> *root, std::string user1, std::string user2)
    {
        if (root == NULL)
        {
            std::cout << "The social network is empty." << std::endl;
            return;
        }

        BinaryTree<std::string> *user1_node = NULL;
        BinaryTree<std::string> *user2_node = NULL;

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

    void find_mutual_friends(BinaryTree<std::string> *root, std::string user1, std::string user2)
    {
        if (root == NULL)
        {
            std::cout << "The social network is empty." << std::endl;
            return;
        }

        BinaryTree<std::string> *user1_node = NULL;
        BinaryTree<std::string> *user2_node = NULL;

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

    int countUsers(BinaryTree<T> *root)
    {
        if (root == NULL)
        {
            return 0;
        }

        return 1 + countUsers(root->Left) + countUsers(root->Right);
    }

    // s
    BinaryTree<T> *searchUser(BinaryTree<T> *root, std::string name)
    {
        if (root == NULL)
        {
            return root;
        }
        
        if (root->User_Name == name)
        {
            return root;
        }

        if (name < root->User_Name)
        {
            return searchUser(root->Left, name);
        }
        else
        {
            return searchUser(root->Right, name);
        }
    }

    void searchAndDisplayUser(BinaryTree<T> *root, std::string name)
    {
        BinaryTree<std::string> *user = searchUser(root, name);

        if (user != NULL)
        {
            std::cout << "User found:" << std::endl;
            std::cout << "User ID: " << user->User_ID << " User Name: " << user->User_Name << " Last Name: " << user->Last_Name << std::endl;
            std::cout << "Contacts of " << user->User_Name << ": " << std::endl; // user->contacts
        }
        else
        {
            std::cout << "User with name " << name << " not found." << std::endl;
        }
    }
};

int main()
{
    BinaryTree<std::string> *root = NULL;
    int choice;
    std::string name, last, id;

    std::string friend_name, search_name, delname;
    std::cout << "Give choice: " << std::endl;
    std::cin >> choice;

    while (choice != 0)
    {
        if (choice == 1)
        {
            std::cout << "Give user name: " << std::endl;
            std::cin >> name;

            std::cout << "Give user last name: " << std::endl;
            std::cin >> last;

            std::cout << "Give user id: " << std::endl;
            std::cin >> id;
            root->insert_BinaryTree(&root, name, id, last);
        }

        if (choice == 2)
        {
            std::cout << "the number of count is : " << root->countUsers(root) << std::endl;
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

        if (choice == 7)
        {
            std::cout << "Give user name to find: " << std::endl;
            std::cin >> search_name;
            root->searchAndDisplayUser(root, search_name);
        }

        if (choice == 8)
        {
            std::cout << "Give user name to delete: " << std::endl;
            std::cin >> delname;
            root->Delete(root, delname);
            
        }
        
        std::cout << "Give choice: " << std::endl;
        std::cin >> choice;
    }

    return 0;
}