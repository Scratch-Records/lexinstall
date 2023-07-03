#include <bits/stdc++.h>
using namespace std;

typedef struct TreeNode {
    char op;
    int label;
    TreeNode* left;
    TreeNode* right;
} TreeNode;

void createTree(TreeNode*& rootNode) {
    rootNode = new TreeNode();
    rootNode->op = '-';
    rootNode->label = 2;

    TreeNode* n1 = new TreeNode();
    n1->op = '+';
    n1->label = 1;
    TreeNode* n2 = new TreeNode();
    n2->op = 'a';
    n2->label = 1;
    TreeNode* n3 = new TreeNode();
    n3->op = 'b';
    n3->label = 0;

    TreeNode* n4 = new TreeNode();
    n4->op = '-';
    n4->label = 2;
    TreeNode* n5 = new TreeNode();
    n5->op = 'e';
    n5->label = 1;
    TreeNode* n6 = new TreeNode();
    n6->op = '+';
    n6->label = 1;
    TreeNode* n7 = new TreeNode();
    n7->op = 'c';
    n7->label = 1;
    TreeNode* n8 = new TreeNode();
    n8->op = 'd';
    n8->label = 0;

    rootNode->left = n1;
    rootNode->right = n4;
    n1->left = n2;
    n1->right = n3;
    n4->left = n5;
    n4->right = n6;
    n6->left = n7;
    n6->right = n8;

    n2->left = nullptr;
    n2->right = nullptr;
    n3->left = nullptr;
    n3->right = nullptr;
    n5->left = nullptr;
    n5->right = nullptr;
    n7->left = nullptr;
    n7->right = nullptr;
    n8->left = nullptr;
    n8->right = nullptr;
}

void displayTree(TreeNode*& root) {
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode* top = q.front();
        q.pop();
        cout << top->label << " " << top->op << endl;
        if (top->left) {
            q.push(top->left);
        }
        if (top->right) {
            q.push(top->right);
        }
    }
}

void swapStack(stack<string>& Stack) {
    string temp = Stack.top();
    Stack.pop();
    string temp2 = Stack.top();
    Stack.pop();
    Stack.push(temp);
    Stack.push(temp2);
}

void genCode(TreeNode*& root, stack<string>& rStack, stack<string>& tStack) {
    if (root == nullptr)
        return;

    // Case 1: Reached a leaf node
    if (root->left == nullptr && root->right == nullptr && (int(root->op) >= 97 && int(root->op) <= 121)) {
        cout << "MOV( " << root->op << " ," << rStack.top() << " )" << endl;
        return;
    }

    // Case 2: Reached an interior node
    if (root->left != nullptr && root->right != nullptr && (root->left->left != nullptr || root->left->right != nullptr) &&
        (root->right->left == nullptr && root->right->right == nullptr)) {
        genCode(root->left, rStack, tStack);
        string operation = (root->op == '+') ? "ADD" : "SUB";
        cout << operation << "( " << root->right->op << " ," << rStack.top() << " )" << endl;
        return;
    }

    // Case 3:
    if (root->left != nullptr && root->right != nullptr && (root->left->left != nullptr || root->left->right != nullptr) &&
        (root->right->left != nullptr || root->right->right != nullptr) && (root->left->label < root->right->label)) {
        swapStack(rStack);
        genCode(root->right, rStack, tStack);
        string R1 = rStack.top();
        rStack.pop();
        genCode(root->left, rStack, tStack);
        string operation = (root->op == '+') ? "ADD" : "SUB";
        cout << operation << "( " << R1 << " ," << rStack.top() << " )" << endl;
        rStack.push(R1);
        swapStack(rStack);
        return;
    }

    // Case 4:
    if (root->left != nullptr && root->right != nullptr && (root->left->left != nullptr || root->left->right != nullptr) &&
        (root->right->left != nullptr || root->right->right != nullptr) && (root->right->label <= root->left->label)) {
        genCode(root->left, rStack, tStack);
        string R0 = rStack.top();
        rStack.pop();
        genCode(root->right, rStack, tStack);
        string operation = (root->op == '+') ? "ADD" : "SUB";
        cout << operation << "( " << rStack.top() << " ," << R0 << " )" << endl;
        rStack.push(R0);
        return;
    }

    // Case 5:
    if (root->left != nullptr && root->right != nullptr && (root->op == '+' || root->op == '-') &&
        (root->left->left != nullptr || root->left->right != nullptr) && (root->right->left != nullptr || root->right->right != nullptr) &&
        (root->right->label > 2 && root->left->label > 2)) {
        genCode(root->right, rStack, tStack);
        string TEMP = tStack.top();
        tStack.pop();
        cout << "MOV( " << rStack.top() << " ," << TEMP << " )" << endl;
        genCode(root->left, rStack, tStack);
        string operation = (root->op == '+') ? "ADD" : "SUB";
        cout << operation << "( " << TEMP << " ," << rStack.top() << " )" << endl;
        tStack.push(TEMP);
        return;
    }
}

int main() {
    TreeNode* root = nullptr;
    createTree(root);
    displayTree(root);

    stack<string> rStack;
    rStack.push("r1");
    rStack.push("r0");

    stack<string> tStack;
    tStack.push("t1");
    tStack.push("t0");

    genCode(root, rStack, tStack);

    return 0;
}
