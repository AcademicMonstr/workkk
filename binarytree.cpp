#include <iostream>

struct BSTNode {
    int val;
    BSTNode *left, *right;
    BSTNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

void insertBST(BSTNode*& root, int val) {
    if (!root) { root = new BSTNode(val); return; }
    if (val < root->val) insertBST(root->left, val);
    else insertBST(root->right, val);
}

bool searchBST(BSTNode* root, int val) {
    if (!root) return false;
    if (root->val == val) return true;
    return (val < root->val) ? searchBST(root->left, val) : searchBST(root->right, val);
}

void inorder(BSTNode* root) { // Выводит отсортированный массив!
    if (!root) return;
    inorder(root->left);
    std::cout << root->val << " ";
    inorder(root->right);
}

// Удаление узла (классический экзаменационный код)
BSTNode* findMin(BSTNode* node) {
    while (node && node->left) node = node->left;
    return node;
}

BSTNode* deleteBST(BSTNode* root, int val) {
    if (!root) return root;
    if (val < root->val) root->left = deleteBST(root->left, val);
    else if (val > root->val) root->right = deleteBST(root->right, val);
    else {
        if (!root->left) { BSTNode* temp = root->right; delete root; return temp; }
        if (!root->right) { BSTNode* temp = root->left; delete root; return temp; }
        BSTNode* temp = findMin(root->right);
        root->val = temp->val;
        root->right = deleteBST(root->right, temp->val);
    }
    return root;
}

int main() {
    BSTNode* root = nullptr;
    insertBST(root, 50);
    insertBST(root, 30);
    insertBST(root, 70);
    insertBST(root, 20);
    insertBST(root, 40);

    std::cout << "Inorder (должно быть отсортировано): ";
    inorder(root); // 20 30 40 50 70
    std::cout << "\n";

    std::cout << "Search 40: " << (searchBST(root, 40) ? "Yes" : "No") << "\n";
    
    root = deleteBST(root, 50); // Удаляем корень
    std::cout << "Inorder after deleting 50: ";
    inorder(root); // 20 30 40 70
    std::cout << "\n";
    return 0;
}