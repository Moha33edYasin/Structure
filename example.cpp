#include <iostream>
#include "Binary.h"

using namespace std;

int main()
{
    cout << "Setup..." << endl;
    ScriptNode test_set2[] =   {ScriptNode("left_leaf", "2"), // 0
                                ScriptNode("right_leaf", "3"), // 1
                                ScriptNode("null", "4"),  // 2
                                ScriptNode("null0", "5"), // 3
                                ScriptNode("null1", "6"), // 4
                                ScriptNode("_left_leaf", "8"), // 5 
                                ScriptNode("_right_leaf", "9"), // 6
                                ScriptNode("null_leaf", "10")
                                }; // 7
    cout << "loading.." << endl;
    BinaryTree<std::string> tree("1", "Number_Struct_Centery_Odd");

    cout << "Adding Some Nodes.." << endl;

    tree.add_node(test_set2[0], "0");
    cout << "test_set2[0] one added" << endl;
    tree.add_node(test_set2[1], "1");
    cout << "test_set2[1] one added" << endl;
    tree.add_node(test_set2[2], "01");
    cout << "test_set2[2] one added" << endl;
    tree.add_node(test_set2[3], "00");
    cout << "test_set2[3] one added" << endl;
    tree.add_node(test_set2[4], "10");
    cout << "test_set2[4] one added" << endl;
    tree.add_node(test_set2[5], "000");
    cout << "test_set2[5] one added" << endl;
    tree.add_node(test_set2[6], "001");
    cout << "test_set2[6] one added" << endl;
    tree.add_node(test_set2[7], "0000");
    cout << "test_set2[7] one added" << endl;

    cout << "This diagram of BinaryTree represent the relationship of data-data:" << endl;
    cout << endl << endl;
    cout << tree.get_diagram("-", " ", 80, false) << endl;
    cout << "The levels is as follow: " << endl << tree.rows 
    << "        length of the list is:" << (tree.length()) << endl;

    std::cout << "Ending Well..." << std::endl;

    return EXIT_SUCCESS;

}