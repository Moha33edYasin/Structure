#include <cmath>
#include "CString.h"
#include "Group.h"

#ifndef BINARY_H
#define BINARY_H

using std::ostream, std::string, std::string_view,
      std::cout, std::endl,
      std::pow, std::size;

// Node<T> is the basic holder (T) data in Binary Tree System
template <typename T>
class Node
{   
private:
    /* display perameters */
    string Middle;
    string start;

    // data to store
    T _data_;

public:
    /* Node holding info */
    string BINCode;
    string name;
    Node* left;
    Node* right;

Node(string _NAME_="<defaultNode>", T _DATA_=T()): name(_NAME_), _data_(_DATA_)
{
    if(_DATA_ != T())
    {
        left = new Node("<defaultLeftNode>", T());
        right = new Node("<defaultRightNode>", T());
    }
}
Node(const Node& source): name(source.name), _data_(source._data_), 
                            left(source.left), right(source.right),
                            BINCode(source.BINCode), start(source.start)  
{
}
virtual~Node()
{
    left = nullptr;
    right = nullptr;
};

// Getters
string hold_place() const
{
    return start;
}

string arrow_point() const
{
    return Middle;
}

T& data()
{
    return _data_;
}

// Setters
void arrow_point_to(string point)
{
    Middle = point;
}

void SetData(T newdata)
{
    _data_ = newdata;
}

void operator=(Node source)
{
    name = source.name; _data_ = source._data_; 
    left = source.left; right = source.right;
    BINCode = source.BINCode; start = source.start;
}

friend ostream& operator<<(ostream& out, Node& right)
{
    out << right.data();
    return out;
}
/* 
compare due to the distance from the root to current Node and its side (left or right)
   left is considered as larger
   example:-
   001 > 000 (true)
   011 < 100 (true) 
   ----------------
               <         root         >
               /                      \
           <    1      >         <     0      >
           /           \         /            \
        < 11  >      < 01  >    < 01  >      < 00  >
        /     \      /     \    /     \      /     \
      <111>  <110> <011> <010> <011> <010> <001>   <000>
*/
friend bool operator>(Node& left, Node& right)
{
    return left.BINCode > right.BINCode;
}
friend bool operator<(Node& left, Node& right)
{
    return left.BINCode < right.BINCode;
}
friend bool operator>=(Node& left, Node& right)
{
    return left.BINCode >= right.BINCode;
}
friend bool operator<=(Node& left, Node& right)
{
    return left.BINCode <= right.BINCode;
}
// equal means same
friend bool operator==(Node& left, Node& right)
{
    return (
        left._data_ == right._data_ &&
        left.name == right.name &&
        left.BINCode == right.BINCode &&
        left.left == right.left &&
        left.right == right.right
        );
}

/* display node struct */
string build(const string cfiller, const int offset, bool by_name=false)
{
    if (by_name)
    {
        start = multiple_str(cfiller, offset - (int) name.length() / 2 - 1);
        return (name == "")? start + "  " : start + "<" + name + ">";
    }else
    {
        start = multiple_str(cfiller, offset - (int) data().length() / 2 - 1);
        return (data() == T())? start + " " + data() + " " : start + "<" + data() + ">";
    }        
}


string build(const string cfill, bool by_name=false)
{
    if (by_name)
    {
        start = cfill.substr(0, cfill.length() - (int) name.length() / 2 - 1);
        return (name == "")? start + "  " : start + "<" + name + ">";     
    }else
    {
        start = cfill.substr(0, cfill.length() - (int) data().length() / 2 - 1);
        return (data() == T())? start + "  " : start + "<" + data() + ">";
    }     
}

string build(const string cfill, const string icon, const string empty_char, bool by_name=false)
{
    start = (icon.length()==0)? cfill:cfill.substr(0, cut_out_neg((int) cfill.length() - (int) icon.length() / 2 - 1));
    return (is_empty_str(icon, empty_char))? start + empty_char + icon + empty_char : start + "<" + icon + ">";     
}
};

typedef Node<int> NumaricalNode;
typedef Node<bool> LogicalNode;
typedef Node<string> ScriptNode;

/* BinarayTree<T> represents the system which hold (T) data in dynamic Group */ 
template <typename T>
class BinaryTree
{
private:
const char LeftCode = '1';
const char RightCode = '0';

unsigned int header = 0; // point to last node number 
string name = "Binary_Tree::=<default>";


public:
Group<Group<Node<T>>> rows; // all data will store here as row data
ScriptNode root = ScriptNode(name, "root"); // the base of the tree is represented as the name of the tree


BinaryTree(string root_data, string_view treename)
{
    name = treename;
    root.name = treename; root.SetData(root_data); root.BINCode = "";
    rows[0].ref_append(root); header++;
}
BinaryTree(string root_data, string_view treename, auto& child)
: BinaryTree(root_data, treename){
    append_node(child);
}

BinaryTree(string root_data, string_view treename, int sizeof_children, auto* children)
: BinaryTree(root_data, treename){
    if(children){
        for(int i=0; i<sizeof_children; i++){
            append_node(children[i]);
        }
    }else{
        cout << "failed to allocate data..";
    }
}

virtual~BinaryTree(){
    rows.~Group();
};

// Getters
auto& last()
{
    return rows[rows.length()-1][0];
}

int length() const
{
    return header;
}

Group<Group<Node<T>>> all_levels() const
{
    return rows;
}

auto& operator[](string __iterator_path)
{
    auto* current_location = &root;
    static auto garbage = Node<string>("<GarbgeNode>", "\0");
    for(int __nBit=0; __nBit<size(__iterator_path); __nBit++){
        current_location = (__iterator_path[__nBit] == LeftCode)? current_location->left:current_location->right;
        if(current_location->data() == "\0" && __nBit + 1 <size(__iterator_path)){
            cout << "Connet acess unconnect <Node>: (" << __iterator_path << ") exceed last (" << last().BINCode << ")" << endl;
            return garbage;
        }
    }
    return *current_location;
};

/* @brief counts number of nodes from start level to end  */
int sum(int start = 0, int end = -1)
{
    int sum_of_levels = 0;
    if (end < 0) end += rows.length();
    for(int i=start; i<end; i++)
    {
        sum_of_levels += rows[i].length();
    }
    return sum_of_levels;
}

/* @brief return is the node is within th tree struct */
bool is_connected(auto* target)
{
    for(int i=0; i<rows; i++){
        for(int j=0; j<rows[i].length(); j++)
        {
            if(target == &rows[i][j])
                return true;
        }
    }
    return false;
}


void add_node(auto& newNode, string __path)
{
    unsigned int __n = __path.length();
    int __r (0);
    string pre_(__path, 0, __n-1);
    auto& prev_location = (*this)[pre_];
    auto& current_location = (*this)[__path];
    if(current_location.data() == T())
    {
        char post_ = __path[__n-1];
        newNode.BINCode = __path;

        if(rows[__n].length() > 0)
        {
            __r = get_location(__path)[0];
        }else
        {
            char poss = '1';
            for(int i=0; i<(int) pow((float) (2.0f), (float) __n); i++)
            {
            rows[__n][i].BINCode = rows[__n-1][i/2].BINCode + poss;
            poss = (poss == '1')? '0' : '1';
            }
            rows[__n].changable(false);
            __r = get_location(__path)[0];
        }
        if(post_ == LeftCode)
        {
            prev_location.left = &newNode;
        }else if (post_ == RightCode)
        {
            prev_location.right = &newNode;
        }
        rows[__n][__r] = newNode; header++;
    }else{
        cout << "AsignError: Can not modify data that was filled up" << endl;
    }
    return;
}


void add_node(auto* newNode, std::string __path)
{
    this->add_node(*newNode, __path);
}


void append_node(auto& newNode)
{
    if(last().BINCode[last().BINCode.length()-1] == '0')
        add_node(newNode, last().BINCode.substr(0, last().BINCode.length()-1) + "1");
    else
        add_node(newNode, last().BINCode + "0");
}


void append_node(auto* newNode)
{
    append_node(*newNode);
}

/* returns Point object with x: index in the row y: row index */
Point<int, int> get_location(string path)
{
    int level_eq = path.length();
    int decim_eq = 0;

    for(int i=0; i<level_eq; i++)
    {
        if((char) path[(level_eq - i - 1)] == '1')
            decim_eq += pow(2, i);
    }
    decim_eq = rows[level_eq].length() - decim_eq - 1;
    return Point<int, int>(decim_eq, level_eq);
}


Point<int, int> get_location(auto& node)
{
    return get_location(node.BINCode);
}

/*  @brief generate a diagram for the tree
    @param frofill stands for outer style
    @param infill stands for icons or nodes style
    @param offset offset the tree by a particular value
    @param by_name (true) node will been built as <(dynamic-space)name(dynamic-space)> 
                   (false) node will been built as default <(dynamic-space)data(dynamic-space)> 
    @param fix for set dynamic spaces
*/  
string get_diagram(const string frofill=" ", const string infill = " ", const int offset=20, bool by_name=false, bool fix=true)
{
    string diagram;
    string icon;
    string lwhitespace;
    string rwhitespace;
    Node<T> parent;
    string Filler = multiple_str(frofill, offset);
    Group<Group<string>> Icons;
    int _F;
    if(fix)
    {
    /* fix icons to emiulate preceed whitespace */
    _F = rows.length()-1;
    for(int i=0; i<rows[_F].length(); i++)
        Icons[_F][i] = (by_name)? rows[_F][i].name:rows[_F][i].data();

    for(int i=_F-1; i>=0; i--)
    {
        for(int j=0; j<rows[i].length(); j++)
        {
            if (rows[i][j].name == "<defaultNode>" ||
                rows[i][j].name == "<defaultLeftNode>" ||
                rows[i][j].name == "<defaultRightNode>"
                    )
            {
                lwhitespace = multiple_str(frofill, Icons[i+1][j*2].length() + 1);
                rwhitespace = multiple_str(frofill, Icons[i+1][j*2 + 1].length() + 1);
            }else
            {
                lwhitespace = (is_empty_str(Icons[i+1][j*2], infill))? multiple_str(infill, Icons[i+1][j*2].length() + 1):multiple_str(infill, Icons[i+1][j*2].length() + 2);
                rwhitespace = (is_empty_str(Icons[i+1][j*2 + 1], infill))? multiple_str(infill, Icons[i+1][j*2 + 1].length() + 1):multiple_str(infill, Icons[i+1][j*2 + 1].length() + 2);
            }
            if(by_name)
            {
                Icons[i][j] = (string) (lwhitespace + rows[i][j].name + rwhitespace);
            }
            else
            {
                Icons[i][j] = (string) (lwhitespace + rows[i][j].data() + rwhitespace);
            }
        }
    }
    }else{
        for(int i=_F-1; i>=0; i--)
        {
            for(int j=0; j<rows[i].length(); j++)
                Icons[i][j] = (by_name)? rows[i][j].name:rows[i][j].data();
        }
    }
    /* row build for each node */
    diagram += rows[0][0].build(Filler, Icons[0][0], infill, by_name) + "\n";
    for(int i=1; i<rows.length(); i++)
    {
        for(int j=0; j<rows[i].length(); j++)
        {
            icon = (rows[i][j].name == "<defaultNode>" ||
                    rows[i][j].name == "<defaultLeftNode>" ||
                    rows[i][j].name == "<defaultRightNode>"
                        )? frofill:infill;
            if(j%2 == 0)
            {
                parent = rows[cut_out_neg(i-1)][j/2];
                rows[i][j].arrow_point_to(parent.hold_place());
                diagram += (is_empty_str(Icons[i][j],  icon))? rows[i][j].arrow_point() + frofill : rows[i][j].arrow_point() + "/";
            }else
            {
                rows[i][j].arrow_point_to(multiple_str(frofill, Icons[cut_out_neg(i-1)][j/2].length()));
                diagram += (is_empty_str(Icons[i][j], icon))? rows[i][j].arrow_point() + frofill : rows[i][j].arrow_point() + "\\";
            }
        }
        diagram += "\n";
        diagram += rows[i][0].build(rows[i][0].arrow_point(), Icons[i][0],(rows[i][0].name == "<defaultNode>" ||
                                                                            rows[i][0].name == "<defaultLeftNode>" ||
                                                                            rows[i][0].name == "<defaultRightNode>"
                                                                            )? frofill:infill, by_name);
        for(int j=1; j<rows[i].length(); j++)
        {
            icon = (by_name)? rows[i][j-1].name:rows[i][j-1].data();
            _F = (Icons[i][j].length() == 0)? 0:cut_out_neg(
                                                                (int) Icons[i][j-1].length() - 
                                                                (int) rows[i][j-1].arrow_point().length() + 
                                                                (int) rows[i][j-1].hold_place().length() + 1
                                                                );
            if(j%2 == 0)
            {   
                Filler = rows[i][j].arrow_point().substr(0, 
                                                rows[i][j].arrow_point().length() - _F - 1
                                                );

            }else
            {
                Filler = multiple_str(frofill, 
                        Icons[cut_out_neg(i-1)][j/2].length() - _F - 1
                                            );
            }
            diagram += rows[i][j].build(Filler, Icons[i][j], (rows[i][j].name == "<defaultNode>" ||
                                                                rows[i][j].name == "<defaultLeftNode>" ||
                                                                rows[i][j].name == "<defaultRightNode>"
                                                                    )? frofill:infill, by_name);
        }
        diagram += "\n";
    }
    return diagram;
}
};
#endif // BINARY_H
