# Dictionary AVL Tree

This project is a simple implementation of a dictionary using an AVL tree in C++. The AVL tree is a self-balancing binary search tree where the difference between the heights of left and right subtrees cannot be more than one for all nodes. This ensures that the operations such as insertion, deletion, and lookup are efficient.

## Features

- **Insert Word**: Add a word and its meaning to the dictionary.
- **Search Word**: Look up the meaning of a word.
- **Delete Word**: Remove a word from the dictionary.
- **Update Word**: Change the meaning of an existing word.
- **Word Suggestions**: Get suggestions for similar words.
- **Display All Words**: Print all words in the dictionary in alphabetical order.

## File Structure

- `DictionaryAVL.h`: Contains the definition of the `DictionaryNode` structure and `DictionaryAVL` class.
- `main.cpp`: Contains the `main` function and the user interface for interacting with the dictionary.
- `Dictionary.txt`: The file where the words and their meanings are stored.

## Installation

To compile and run this project, you'll need a C++ compiler. Follow these steps:

1. **Clone the repository**:
git clone https://github.com/hasnaatmalik/Dictionary-DS.git
cd Dictionary-DS
2. **Compile the code**:
g++ main.cpp -o dictionary
3. **Run the program**:
./dictionary
## Usage

Upon running the program, you will be presented with a menu with the following options:

1. **Search for a word**: Enter a word to look up its meaning. If the word is not found, you will be notified.
2. **Add a word**: Add a new word along with its meaning to the dictionary.
3. **Delete a word**: Remove a word from the dictionary after confirming the deletion.
4. **Update the meaning of a word**: Update the meaning of an existing word in the dictionary.
5. **Display all words**: Display all the words in the dictionary in alphabetical order.
6. **Exit**: Exit the program.

### Example Usage

1. **Search for a word**:
Enter the word to search: example
Meaning of 'example': A representative form or pattern.
Word Suggestions:
2. **Add a word**:
Enter the word to add: example
Enter the meaning of 'example': A representative form or pattern.
Word added successfully.
3. **Delete a word**:
Enter the word to delete: example
Do you want to delete the word 'example'?
1. Yes
2. No
1
Word deleted successfully.
4. **Update the meaning of a word**:
Enter the word to update: example
Enter the new meaning of 'example': A thing characteristic of its kind or illustrating a general rule.
Word updated successfully.
5. **Display all words**:
Words in the dictionary:
example: A thing characteristic of its kind or illustrating a general rule.

## Contributing

Contributions are welcome! Feel free to submit a pull request or open an issue to discuss any changes or suggestions.

## Acknowledgements

- The AVL tree implementation is inspired by common algorithms for self-balancing binary search trees.
- The user interface incorporates techniques from various C++ resources and tutorials.

Enjoy using your AVL Tree Dictionary! If you have any questions or need further assistance, feel free to reach out.
