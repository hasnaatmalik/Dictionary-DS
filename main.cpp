#include <iostream>
#include <fstream>
#include <string>
using namespace std;
struct DictionaryNode
{
    string word;
    string meaning;
    int height;
    DictionaryNode *left;
    DictionaryNode *right;

    DictionaryNode(const string &w, const string &m)
        : word(w), meaning(m), height(0), left(nullptr), right(nullptr) {}
};

class DictionaryAVL
{
private:
    DictionaryNode *root;
    // height of the tree
    int getHeight(DictionaryNode *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        return node->height;
    }
    // update the height of the tree
    void updateHeight(DictionaryNode *node)
    {
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }
    int max(int x, int y)
    {
        if (x >= y)
        {
            return x;
        }
        else
            return y;
    }
    // rotate the tree to the right
    DictionaryNode *rotateRight(DictionaryNode *y)
    {
        DictionaryNode *x = y->left;
        DictionaryNode *T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }
    // rotate the tree to the left
    DictionaryNode *rotateLeft(DictionaryNode *x)
    {
        DictionaryNode *y = x->right;
        DictionaryNode *T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }
    // get the balancing factor
    int getBalance(DictionaryNode *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        return getHeight(node->left) - getHeight(node->right);
    }
    // insert the node in the tree
    DictionaryNode *insert(DictionaryNode *node, const string &word, const string &meaning)
    {
        if (node == nullptr)
        {
            return new DictionaryNode(word, meaning);
        }

        if (word < node->word)
        {
            node->left = insert(node->left, word, meaning);
        }
        else if (word > node->word)
        {
            node->right = insert(node->right, word, meaning);
        }
        else
        {
            // Word already exists in the dictionary
            return node;
        }

        updateHeight(node);

        int balance = getBalance(node);

        // single right Case
        if (balance > 1 && word < node->left->word)
        {
            return rotateRight(node);
        }

        // single left Case
        if (balance < -1 && word > node->right->word)
        {
            return rotateLeft(node);
        }

        // Left Right Case
        if (balance > 1 && word > node->left->word)
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Right Left Case
        if (balance < -1 && word < node->right->word)
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }
    // load the file
    void loadFromFile(const char *filename)
    {
        ifstream file(filename);
        if (!file.is_open())
        {
            cout << "Error: Unable to open file '" << filename << "'." << endl;
            exit(EXIT_FAILURE);
        }

        string word, meaning;
        while (file >> word >> ws && getline(file, meaning))
        {
            root = insert(root, word, meaning);
        }

        file.close();
    }

    // add the word in the file
    DictionaryNode *addWord(DictionaryNode *node, const string &word, const string &meaning, const char *filename)
    {
        if (node == nullptr)
        {
            DictionaryNode *newNode = new DictionaryNode(word, meaning);
            cout << "Word added successfully." << endl;
            updateFileToAddWord(newNode, filename); // Update file with the new word and meaning
            return newNode;
        }

        if (word < node->word)
        {
            node->left = addWord(node->left, word, meaning, filename);
        }
        else if (word > node->word)
        {
            node->right = addWord(node->right, word, meaning, filename);
        }
        else
        {
            cout << "Word already exists in the dictionary." << endl;
            return node;
        }

        updateHeight(node);

        int balance = getBalance(node);

        // single right Case
        if (balance > 1 && word < node->left->word)
        {
            return rotateRight(node);
        }

        // single left case
        if (balance < -1 && word > node->right->word)
        {
            return rotateLeft(node);
        }

        // Left Right Case
        if (balance > 1 && word > node->left->word)
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Right Left Case
        if (balance < -1 && word < node->right->word)
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }
    // update the file
    void updateFileToAddWord(DictionaryNode *node, const char *filename)
    {
        ofstream file(filename, ios::app);
        if (!file.is_open())
        {
            cout << "Error: Unable to open file '" << filename << "'." << endl;
            exit(EXIT_FAILURE);
        }

        file << node->word << "           " << node->meaning << endl;

        file.close();
    }
    // update the file to delete the word
    void updateFileToDelete(const char *filename, DictionaryNode *node)
    {
        ifstream file(filename);
        if (!file.is_open())
        {
            cout << "Error: Unable to open file '" << filename << "'." << endl;
            exit(EXIT_FAILURE);
        }

        ofstream temp("temp.txt");
        if (!temp.is_open())
        {
            cout << "Error: Unable to open file 'temp.txt'." << endl;
            exit(EXIT_FAILURE);
        }

        string word, meaning;
        while (file >> word >> ws && getline(file, meaning))
        {
            if (word != node->word)
            {
                temp << word << "           " << meaning << endl;
            }
        }

        file.close();
        temp.close();

        remove(filename);
        rename("temp.txt", filename);
    }
    // update the file to change the meaning of the word
    void updateFileToChangeMeaning(const char *filename, DictionaryNode *node)
    {
        ifstream file(filename);
        if (!file.is_open())
        {
            cout << "Error: Unable to open file '" << filename << "'." << endl;
            exit(EXIT_FAILURE);
        }

        ofstream temp("temp.txt");
        if (!temp.is_open())
        {
            cout << "Error: Unable to open file 'temp.txt'." << endl;
            exit(EXIT_FAILURE);
        }

        string word, meaning;
        while (file >> word >> ws && getline(file, meaning))
        {
            if (word != node->word)
            {
                temp << word << "           " << meaning << endl;
            }
            else
            {
                temp << word << "           " << node->meaning << endl;
            }
        }

        file.close();
        temp.close();

        remove(filename);
        rename("temp.txt", filename);
    }
    // search the word in the tree
    DictionaryNode *searchWord(DictionaryNode *node, const string &word)
    {
        if (node == nullptr)
        {
            return nullptr; // Word not found
        }

        if (word < node->word)
        {
            return searchWord(node->left, word);
        }
        else if (word > node->word)
        {
            return searchWord(node->right, word);
        }
        else
        {
            return node; // Word found
        }
    }
    // delete the word from the tree
    DictionaryNode *deleteWord(DictionaryNode *node, const string &word)
    {
        if (node == nullptr)
        {
            return nullptr; // Word not found
        }

        if (word < node->word)
        {
            node->left = deleteWord(node->left, word);
        }
        else if (word > node->word)
        {
            node->right = deleteWord(node->right, word);
        }
        else
        {
            // Word found, perform deletion
            if (node->left == nullptr && node->right == nullptr)
            {
                updateFileToDelete("Dictionary.txt", node); // Update file with deletion
                delete node;
                return nullptr;
            }
            else if (node->left == nullptr)
            {
                DictionaryNode *temp = node->right;
                updateFileToDelete("Dictionary.txt", node); // Update file with deletion
                delete node;
                return temp;
            }
            else if (node->right == nullptr)
            {
                DictionaryNode *temp = node->left;
                updateFileToDelete("Dictionary.txt", node); // Update file with deletion
                delete node;
                return temp;
            }
            else
            {
                // Node has two children, find the in-order successor (smallest node in the right subtree)
                DictionaryNode *temp = findMin(node->right);

                // Copy the in-order successor's data to this node
                node->word = temp->word;
                node->meaning = temp->meaning;

                // Delete the in-order successor
                node->right = deleteWord(node->right, temp->word);
            }
        }

        updateHeight(node);

        int balance = getBalance(node);
        
        // single right Case
        if (balance > 1 && word < node->left->word)
        {
            return rotateRight(node);
        }

        // single left case
        if (balance < -1 && word > node->right->word)
        {
            return rotateLeft(node);
        }

        // Left Right Case
        if (balance > 1 && word > node->left->word)
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Right Left Case
        if (balance < -1 && word < node->right->word)
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }
    // find the minimum node in the tree
    DictionaryNode *findMin(DictionaryNode *node)
    {
        while (node->left != nullptr)
        {
            node = node->left;
        }
        return node;
    }
    // confirm the deletion
    bool confirmDelete(const string &word)
    {
        cout << "Do you want to delete the word '" << word << "'?" << endl;
        cout << "1. Yes\n2. No\n";

        int choice;
        cin >> choice;
        if (choice == 1)
        {
            return true;
        }
        else if (choice == 2)
        {
            return false;
        }
        else
        {
            cout << "Invalid choice. Please try again." << endl;
            return confirmDelete(word);
        }
    }
    // update the word in the tree
    DictionaryNode *updateWord(DictionaryNode *node, const string &word, const string &newMeaning)
    {
        if (node == nullptr)
        {
            return nullptr; // Word not found
        }

        if (word < node->word)
        {
            node->left = updateWord(node->left, word, newMeaning);
        }
        else if (word > node->word)
        {
            node->right = updateWord(node->right, word, newMeaning);
        }
        else
        {
            node->meaning = newMeaning;
            updateFileToChangeMeaning("Dictionary.txt", node);
        }

        updateHeight(node);

        int balance = getBalance(node);

        if (balance > 1 && word < node->left->word)
        {
            return rotateRight(node);
        }

        // single left Case
        if (balance < -1 && word > node->right->word)
        {
            return rotateLeft(node);
        }

        // Left Right Case
        if (balance > 1 && word > node->left->word)
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Right Left Case
        if (balance < -1 && word < node->right->word)
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }
    // word suggestions
    void WordSuggestions(DictionaryNode *node, string word, int limit)
    {

        if (node == nullptr || limit < 0)
        {
            return;
        }
        if (root)
        {
            WordSuggestions(node->left, word, limit - 1);
            cout << node->word << endl;
            WordSuggestions(node->right, word, limit - 1);
        }
    }
    // make the tree AVL
    DictionaryNode *makeAVL(DictionaryNode *node)
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        node->left = makeAVL(node->left);
        node->right = makeAVL(node->right);
        return insert(node, node->word, node->meaning);
    }

public:
    void wordSuggestion(string word)
    {
        int limit = 10;
        DictionaryNode *temp = root;
        temp = searchWord(root, word);
        temp = makeAVL(temp);
        WordSuggestions(temp, word, limit);
    }
    DictionaryAVL(const char *filename) : root(nullptr)
    {
        loadFromFile(filename);
    }

    void displayLoadingMessage()
    {
        cout << "Dictionary is loading..." << endl;
    }

    void printInOrder(DictionaryNode *node)
    {
        if (node != nullptr)
        {
            printInOrder(node->left);
            cout << node->word << ": " << node->meaning << endl;
            printInOrder(node->right);
        }
    }

    DictionaryNode *getRoot() const
    {
        return root;
    }

    void addWord(const string &word, const string &meaning)
    {
        root = addWord(root, word, meaning, "Dictionary.txt");
    }

    void searchAndDisplay(const string &word)
    {
        DictionaryNode *result = searchWord(root, word);

        if (result != nullptr)
        {
            cout << "Meaning of '" << word << "': " << result->meaning << endl;
        }
        else
        {
            cout << "Word not found." << endl;
        }
    }

    void deleteWord(const string &word)
    {
        DictionaryNode *nodeToDelete = searchWord(root, word);

        if (nodeToDelete != nullptr)
        {
            if (confirmDelete(word))
            {
                root = deleteWord(root, word);
                cout << "Word deleted successfully." << endl;
            }
            else
            {
                cout << "Deletion canceled." << endl;
            }
        }
        else
        {
            cout << "Word not found. Deletion canceled." << endl;
        }
    }

    void updateWord(const string &word, const string &newMeaning)
    {
        DictionaryNode *nodeToUpdate = searchWord(root, word);

        if (nodeToUpdate != nullptr)
        {
            // Word found, ask for confirmation before updating
            if (confirmUpdate(word))
            {
                root = updateWord(root, word, newMeaning);
                cout << "Word updated successfully." << endl;
            }
            else
            {
                cout << "Update canceled." << endl;
            }
        }
        else
        {
            cout << "Word not found. Update canceled." << endl;
        }
    }

    bool confirmUpdate(const string &word)
    {
        cout << "Do you want to update the meaning of the word '" << word << "'?" << endl;
        cout << "1. Yes\n2. No\n";

        int choice;
        cin >> choice;

        if (choice == 1)
        {
            return true;
        }
        else if (choice == 2)
        {
            return false;
        }
        else
        {
            cout << "Invalid choice. Please try again." << endl;
            return confirmUpdate(word);
        }
    }
};

int main()
{
    // to clear the screen
    cout << "\033[2J\033[1;1H";
    DictionaryAVL dictionary("Dictionary.txt");
    // learnt how to add colors from here
    // https://stackoverflow.com/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal
    cout << "\033[1;31mDictionary is loading...\033[0m" << endl;
    // DictionaryAVL dictionary("Dictionary.txt");

    cout << "\n\033[1;35mWelcome to the Dictionary!\033[0m" << endl;
    do
    {
        cout << "\n1. Search for a word\n2. Add a word\n3. Delete a word\n4. Update the meaning of a word\n5. Display all words\n6. Exit\n\n";
        cout << "\033[1;32mEnter your choice: \033[0m";
        int choice;
        cin >> choice;
        // to clear the screen
        // Check for invalid input
        if (cin.fail() || choice < 1 || choice > 6)
        {
            cin.clear();                                                   // clear the error flag
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
            cout << "\033[1;31mInvalid input. Please enter a valid number between 1 and 6.\033[0m" << endl;
            continue;
        }

        cout << "\033[2J\033[1;1H";
        switch (choice)
        {
        case 1:
        {
            cout << "\nEnter the word to search: ";
            string word;
            getline(cin >> ws, word);
            if (word.empty())
            {
                cout << "\033[1;31mInvalid input. Please enter a non-empty word.\033[0m" << endl;
                continue;
            }
            dictionary.searchAndDisplay(word);
            cout << "\nWord Suggestions:\n";
            dictionary.wordSuggestion(word);
            break;
        }
        case 2:
        {
            cout << "\nEnter the word to add: ";
            string word;
            getline(cin >> ws, word);
            if (word.empty())
            {
                cout << "\033[1;31mInvalid input. Please enter a non-empty word.\033[0m" << endl;
                continue;
            }
            cout << "Enter the meaning of '" << word << "': ";
            string meaning;
            getline(cin >> ws, meaning);
            if (meaning.empty())
            {
                cout << "\033[1;31mInvalid input. Please enter a non-empty meaning.\033[0m" << endl;
                continue;
            }
            dictionary.addWord(word, meaning);
            break;
        }
        case 3:
        {
            cout << "\nEnter the word to delete: ";
            string word;
            getline(cin >> ws, word);
            if (word.empty())
            {
                cout << "\033[1;31mInvalid input. Please enter a non-empty word.\033[0m" << endl;
                continue;
            }
            dictionary.deleteWord(word);
            break;
        }
        case 4:
        {
            cout << "\nEnter the word to update: ";
            string word;
            getline(cin >> ws, word);
            if (word.empty())
            {
                cout << "\033[1;31mInvalid input. Please enter a non-empty word.\033[0m" << endl;
                continue;
            }
            cout << "Enter the new meaning of '" << word << "': ";
            string newMeaning;
            getline(cin >> ws, newMeaning);
            if (newMeaning.empty())
            {
                cout << "\033[1;31mInvalid input. Please enter a non-empty meaning.\033[0m" << endl;
                continue;
            }
            dictionary.updateWord(word, newMeaning);
            break;
        }
        case 5:
        {
            cout << "\nWords in the dictionary:" << endl;
            dictionary.printInOrder(dictionary.getRoot());
            break;
        }
        case 6:
        {
            cout << "\nThank you for using the Dictionary!" << endl;
            exit(EXIT_SUCCESS);
        }
        default:
            cout << "\n\033[1;31mInvalid choice. Please try again.\033[0m" << endl;
        }
    } while (true);
    return 0;
}