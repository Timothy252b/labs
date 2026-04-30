#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class PRINT {
protected:
    string name;
    string author;
public:
    PRINT() : name(""), author("") {}
    PRINT(string n, string a) : name(n), author(a) {}
    virtual ~PRINT() {}
    virtual void input() = 0;
    virtual void output() const = 0;
    virtual string getName() const { return name; }
    virtual string getAuthor() const { return author; }
};

class MAGAZIN : public PRINT {
private:
    int pages;
public:
    MAGAZIN() : PRINT(), pages(0) {}
    MAGAZIN(string n, string a, int p) : PRINT(n, a), pages(p) {}
    void input() override {
        cout << "Enter name: "; cin >> name;
        cout << "Enter author: "; cin >> author;
        cout << "Enter pages: "; cin >> pages;
    }
    void output() const override {
        cout << "[" << name << ", " << author << ", " << pages << "p]";
    }
    string getName() const { return name; }
};

struct TreeNode {
    MAGAZIN* data;
    vector<TreeNode*> children;
    TreeNode* parent;
    
    TreeNode(MAGAZIN* m) : data(m), parent(nullptr) {}
    ~TreeNode() { delete data; for(auto child : children) delete child; }
};

class Tree {
protected:
    TreeNode* root;
    int size;
    
    TreeNode* findNode(TreeNode* node, const string& name) {
        if(!node) return nullptr;
        if(node->data->getName() == name) return node;
        for(auto child : node->children) {
            TreeNode* found = findNode(child, name);
            if(found) return found;
        }
        return nullptr;
    }
    
    void printTree(TreeNode* node, int level) {
        if(!node) return;
        for(int i = 0; i < level; i++) cout << "  ";
        node->data->output();
        cout << endl;
        for(auto child : node->children) {
            printTree(child, level + 1);
        }
    }
    
    void printNames(TreeNode* node) {
        if(!node) return;
        for(int i = 0; i < 2; i++) cout << " ";
        cout << node->data->getName() << endl;
        for(auto child : node->children) {
            printNames(child);
        }
    }
    
    void clear(TreeNode* node) {
        if(node) {
            for(auto child : node->children) clear(child);
            delete node;
        }
    }
    
public:
    Tree() : root(nullptr), size(0) {}
    ~Tree() { clear(root); }
    
    void addRoot(MAGAZIN* m) {
        if(!root) {
            root = new TreeNode(m);
            size++;
        }
    }
    
    bool addChild(const string& parentName, MAGAZIN* m) {
        TreeNode* parent = findNode(root, parentName);
        if(parent) {
            TreeNode* child = new TreeNode(m);
            child->parent = parent;
            parent->children.push_back(child);
            size++;
            return true;
        }
        return false;
    }
    
    bool removeNode(const string& name) {
        if(!root) return false;
        if(root->data->getName() == name) {
            clear(root);
            root = nullptr;
            size = 0;
            return true;
        }
        TreeNode* node = findNode(root, name);
        if(node && node->parent) {
            auto& siblings = node->parent->children;
            siblings.erase(std::remove(siblings.begin(), siblings.end(), node), siblings.end());
            delete node;
            size--;
            return true;
        }
        return false;
    }
    
    void display() {
        if(!root) cout << "Empty tree" << endl;
        else {
            cout << "\n=== Tree Structure ===" << endl;
            printTree(root, 0);
        }
    }
    
    void displayNames() {
        if(!root) cout << "Empty tree" << endl;
        else {
            cout << "\n=== Magazine Names ===" << endl;
            printNames(root);
        }
    }
    
    int getSize() const { return size; }
    int operator~() const { return size; }
    TreeNode* getRoot() { return root; }
};

class Dialog : public Tree {
public:
    void run() {
        char cmd;
        cout << "=== Magazine Tree Manager ===" << endl;
        cout << "First, create root node!" << endl;
        
        while (true) {
            cout << "\nCommands:" << endl;
            cout << "  m   - create root magazine" << endl;
            cout << "  +   - add child magazine (asks for parent name)" << endl;
            cout << "  -   - remove magazine" << endl;
            cout << "  s   - show tree structure" << endl;
            cout << "  z   - show magazine names" << endl;
            cout << "  q   - quit" << endl;
            cout << "Enter command: ";
            cin >> cmd;
            
            if (cmd == 'm') {
                if(root) {
                    cout << "Root already exists! Use + to add children." << endl;
                } else {
                    MAGAZIN* m = new MAGAZIN();
                    cout << "--- Create Root Magazine ---" << endl;
                    m->input();
                    addRoot(m);
                    cout << "\nRoot created. Size: " << ~(*this) << endl;
                }
            }
            else if (cmd == '+') {
                if(!root) {
                    cout << "Create root first using 'm' command!" << endl;
                    continue;
                }
                string parentName;
                cout << "Enter parent magazine name: "; cin >> parentName;
                if(!findNode(root, parentName)) {
                    cout << "Parent not found!" << endl;
                    continue;
                }
                MAGAZIN* m = new MAGAZIN();
                cout << "--- Create Child Magazine ---" << endl;
                m->input();
                if(addChild(parentName, m)) {
                    cout << "\nAdded child to '" << parentName << "'. Size: " << ~(*this) << endl;
                }
            }
            else if (cmd == '-') {
                if(!root) {
                    cout << "Tree is empty!" << endl;
                    continue;
                }
                string name;
                cout << "Enter name to remove: "; cin >> name;
                if(removeNode(name)) cout << "\nRemoved. Size: " << ~(*this) << endl;
                else cout << "\nNot found or cannot remove" << endl;
            }
            else if (cmd == 's') {
                display();
            }
            else if (cmd == 'z') {
                displayNames();
            }
            else if (cmd == 'q') {
                cout << "\nGoodbye!" << endl;
                break;
            }
            else {
                cout << "\nUnknown command!" << endl;
            }
        }
    }
    
    TreeNode* findNode(TreeNode* node, const string& name) {
        if(!node) return nullptr;
        if(node->data->getName() == name) return node;
        for(auto child : node->children) {
            TreeNode* found = findNode(child, name);
            if(found) return found;
        }
        return nullptr;
    }
};

int main() {
    Dialog dlg;
    dlg.run();
    return 0;
}
