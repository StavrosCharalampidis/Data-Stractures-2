#include <iostream>
#include <string>
#include <vector>

template <typename T>
class BinaryNode
{
private:
    std::string User_ID;
    std::string User_Name;
    std::string Last_Name;
    std::vector<std::string> contacts;
    BinaryNode<T> *Left, *Right;

public:
    BinaryNode(std::string User_Name, std::string User_ID, std::string Last_Name)
    {
        this->User_Name = User_Name;
        this->User_ID = User_ID;
        this->Last_Name = Last_Name;
        this->Left, this->Right = NULL;
    };

    BinaryNode()
    {
        this->Left, this->Right = NULL;
    };

    BinaryNode<T> *insert_BinaryNode(BinaryNode<T> **root, std::string User_Name, std::string User_ID, std::string Last_Name)
    {
        if (*root == NULL)
        {
            BinaryNode<T> *new_BinaryNode = new BinaryNode<T>(User_Name, User_ID, Last_Name);
            new_BinaryNode->Left = NULL;
            new_BinaryNode->Right = NULL;
            *root = new_BinaryNode;
            return new_BinaryNode;
        }

        if (User_Name < (*root)->User_Name)
        {
            (*root)->Left = insert_BinaryNode(&(*root)->Left, User_Name, User_ID, Last_Name);
        }
        else
        {
            (*root)->Right = insert_BinaryNode(&(*root)->Right, User_Name, User_ID, Last_Name);
        }
        return *root;
    }

    void DisplayUserAlphabetically(BinaryNode<T> *root)
    {
        if (root == NULL)
        {
            return;
        }

        DisplayUserAlphabetically(root->Left);
        std::cout << root->User_Name << " " << std::endl;
        DisplayUserAlphabetically(root->Right);
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

    void check_friends(BinaryNode<T> *root, std::string user1, std::string user2)
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

    void find_mutual_friends(BinaryNode<T> *root, std::string user1, std::string user2)
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

    int countUsers(BinaryNode<T> *root)
    {
        if (root == NULL)
        {
            return 0;
        }

        return 1 + countUsers(root->Left) + countUsers(root->Right);
    }

    void searchAndDisplayUser(BinaryNode<T> *root, std::string targetUser)
    {
        if (root == NULL)
        {
            std::cout << "The social network is empty." << std::endl;
            return;
        }

        BinaryNode<T> *userNode = NULL;

        while (root != NULL)
        {
            if (root->User_Name == targetUser)
            {
                userNode = root;
                break;
            }
            else if (targetUser < root->User_Name)
            {
                root = root->Left;
            }
            else
            {
                root = root->Right;
            }
        }

        if (userNode == NULL)
        {
            std::cout << "User with User Name '" << targetUser << "' not found in the social network." << std::endl;
            return;
        }

        std::cout << "User Details:" << std::endl;
        std::cout << "User Name: " << userNode->User_Name << std::endl;
        std::cout << "User ID: " << userNode->User_ID << std::endl;
        std::cout << "Last Name: " << userNode->Last_Name << std::endl;

        if (!userNode->contacts.empty())
        {
            std::cout << "Contacts: ";
            for (const std::string &contact : userNode->contacts)
            {
                std::cout << contact << " ";
            }
            std::cout << std::endl;
        }
        else
        {
            std::cout << "No contacts for this user." << std::endl;
        }
    }
};

int main()
{
    BinaryNode<std::string> *root = NULL;
    int choice;
    std::string name, last;
    int id = 0;
    std::string friend_name, search_name, delname;

    while (true)
    {

        // menu
        std::cout << " " << std::endl;
        std::cout << "Give 0 for exit: " << std::endl;
        std::cout << "Give 1 for insert User in Tree: " << std::endl;
        std::cout << "Give 2 for count all Users in Tree: " << std::endl;
        std::cout << "Give 3 for Display User Alphabetically: " << std::endl;
        std::cout << "Give 4 for Update connections between users: " << std::endl;
        std::cout << "Give 5 for find mutual friends: " << std::endl;
        std::cout << "Give 6 for check friends: " << std::endl;
        std::cout << "Give 7 Search for a user and display their details: " << std::endl;
        std::cout << "Give 8 User to delete: " << std::endl;

        std::cout << "Give choice: " << std::endl;
        std::cin >> choice;

        if (choice == 0)
        {
            exit(0);
        }

        if (choice == 1)
        {
            std::cout << "Give user name: " << std::endl;
            std::cin >> name;

            std::cout << "Give user last name: " << std::endl;
            std::cin >> last;

            id += 1;
            root->insert_BinaryNode(&root, name, std::to_string(id), last);
        }

        if (choice == 2)
        {
            std::cout << "the number of count is : " << root->countUsers(root) << std::endl;
        }

        if (choice == 3)
        {
            printf("print all users alphabetically \n");
            root->DisplayUserAlphabetically(root);
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
    }

    return 0;
}