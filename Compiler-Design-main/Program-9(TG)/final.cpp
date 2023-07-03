#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    char data;
    int r;
    Node *left;
    Node *right;
    Node(char x)
    {
        data = x;
        left = right = nullptr;
    }
};

class rstack
{
private:
    char reg[10][10];
    int top;

public:
    rstack()
    {
        top = -1;
    }

    void init(int k, char *name)
    {
        char temp[10];
        for (int i = k - 1; i >= 0; i--)
        {
            strcpy(reg[++top], name);
            sprintf(temp, "%d", i);
            strcat(reg[top], temp);
        }
    }

    void swap()
    {
        char name[10];
        strcpy(name, reg[top]);
        strcpy(reg[top], reg[top - 1]);
        strcpy(reg[top - 1], name);
    }

    char *pop()
    {
        return (reg[top--]);
    }

    int topv()
    {
        return top;
    }

    void push(char *tr)
    {
        strcpy(reg[++top], tr);
    }

    char *topd()
    {
        return (reg[top]);
    }
};

class Tree
{
private:
    Node *root;
    int rg;
    rstack s, tstack;

public:
    Tree()
    {
        root = nullptr;
        rg = 0;
    }

    void setRegisters(int numRegisters)
    {
        rg = numRegisters;
    }

    Node *createNode()
    {
        char x;
        cout << "Enter node data: ";
        cin >> x;

        if (x == 'N')
            return nullptr;

        Node *p = new Node(x);
        cout << "Enter left child of " << x << ": ";
        p->left = createNode();
        cout << "Enter right child of " << x << ": ";
        p->right = createNode();

        return p;
    }

    void display(char c)
    {
        switch (c)
        {
        case '+':
            cout << "ADD ";
            break;
        case '*':
            cout << "MUL ";
            break;
        case '-':
            cout << "SUB ";
            break;
        case '/':
            cout << "DIV ";
            break;
        }
    }
    void create()
    {
        root = createNode();
    }
    void preorder()
    {
        preorder(root);
    }
    void preorder(Node *t)
    {
        if (!t)
        {
            return;
        }
        cout << t->data << "\t(label=" << t->r << ")\t" << endl;
        preorder(t->left);
        preorder(t->right);
    }
    void label(Node *t)
    {
        if (t->left && !t->left->left && !t->left->right)
        {
            t->left->r = 1;
        }

        if (t->left && (t->left->left || t->left->right))
        {
            label(t->left);
        }

        if (t->right && !t->right->left && !t->right->right)
        {
            t->right->r = 0;
        }

        if (t->right && (t->right->left || t->right->right))
        {
            label(t->right);
        }

        if (t->left && t->right)
        {
            if (t->left->r > t->right->r)
                t->r = t->left->r;
            else if (t->right->r > t->left->r)
                t->r = t->right->r;
            else
                t->r = t->left->r + 1;
        }
    }
    void label()
    {
        label(root);
    }
    void generateCode(Node *t)
    {
        stack<char *> regStack;
        char *name;
        if (t->r == 1 && !t->left && !t->right)
        {
            cout << "MOV " << t->data << ", " << s.topd() << "\n";
        }
        else if (t->left && t->right && t->right->r == 0)
        {
            generateCode(t->left);
            display(t->data);
            cout << t->right->data << " " << s.topd() << "\n";
        }
        else if (t->left && t->right && t->left->r < t->right->r && t->left->r < rg)
        {
            // cout << "SWAP\n";
            s.swap();
            generateCode(t->right);
            name = s.pop();
            // cout << "POP\n";
            generateCode(t->left);
            display(t->data);
            cout << name << " ," << s.topd() << "\n";
            s.push(name);
            s.swap();
            // cout << "PUSH\n";
            // cout << "SWAP\n";
        }
        else if (t->left && t->right && t->right->r <= t->left->r && t->right->r < rg)
        {
            generateCode(t->left);
            name = s.pop();
            // cout << "POP\n";
            generateCode(t->right);
            display(t->data);
            cout << s.topd() << "," << name << "\n";
            s.push(name);
            // cout << "PUSH\n";
        }
        else
        {
            generateCode(t->right);
            name = tstack.pop();
            cout << "MOV " << s.topd() << ", " << name << "\n";
            generateCode(t->left);
            display(t->data);
            cout << name << "," << s.topd() << "\n";
            tstack.push(name);
            // cout << "PUSH T\n";
        }
    }
    void generateCode()
    {
        int rg;
        cout << "Enter registers: ";
        cin >> rg;
        s.init(rg, "R");
        tstack.init(5, "T");
        generateCode(root);
    }
};

int main()
{
    Tree* t = new Tree();
    int choice;
    bool flag = true;
    while (flag)
    {
        cout << "1. Create Tree\n";
        cout << "2. Preorder\n";
        cout << "3. Label\n";
        cout << "4. Generate Code\n";
        cout << "5. Exit\n";
        cout << "Enter your choice number: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            t->create();
            break;
        case 2:
            t->preorder();
            break;
        case 3:
            t->label();
            break;
        case 4:
            t->generateCode();
            break;
        case 5:
            flag = false;
            break;
        default:
            exit(0);
        }
    }
    return 0;
}
