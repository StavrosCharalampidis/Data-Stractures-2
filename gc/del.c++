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