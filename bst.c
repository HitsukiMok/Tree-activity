#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node *left, *right;
}Node;

Node* createNode(int value){
     Node* n = (Node*)malloc(sizeof(Node));
     n->data = value;
     n->left = n->right = NULL;
     return n;
}

//insertion
Node* insertNode(Node *root, int data){
 if (root==NULL) return createNode(data);
 if(data < root->data) root->left = insertNode(root->left, data);
 else if (data > root->data) root->right = insertNode(root->right, data);
 return root;
}

//Search
Node* search(Node* root, int val) {
    if (root == NULL || root->data == val) return root;   
    if (val < root->data) return search(root->left, val);
    return search(root->right, val);
}


//min and maximum
Node* finMin(Node *node){

    if(node == NULL){
        return NULL;
    }

    if(node->left){
        return finMin(node->left);
    }else {
        return node;
    }
}

Node* finMax(Node *node){
    if(node == NULL){
        return NULL;
    }

    if(node->right){
        return finMax(node->right);
    }else{
        return node;
    }
}


//delete
Node *delete(Node *node, int data){
    Node *temp;
    if(node == NULL){
        return NULL;
    }

    if(data > node->data){
        node->right= delete(node->right, data);
    }else if(data < node->data){
        node->left = delete(node->left,data);
    }else{
        if(node->left && node -> right){
            temp = finMin(node->right);
            node->data = temp->data;
            node->right = delete(node->right, temp->data);
        }else{
            temp = node;
            if(node->left == NULL){
                node = node->right;
            }else if(node->right == NULL){
                node = node->left;
            }free(temp);
        }
    }return node;
}


//Display
void printInOrder(Node* root){
    if(root == NULL) return ;
    printInOrder(root->left);
    printf("%d", root->data);
    printInOrder(root->right);
}

void printPreOrder( Node* root) {    
    if (root == NULL) return;
    printf("%d ", root->data);
    printPreOrder(root->left);
    printPreOrder(root->right);
}

void printPostOrder( Node* root) { 
    if (root == NULL) return;
    printPostOrder(root->left);
    printPostOrder(root->right);
    printf("%d ", root->data);
}

int countNodes(Node* root){
    if (root == NULL) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

int countLeafNodes(Node* root){
    if (root == NULL) return 0;
    if (root->left ==NULL && root->right ==NULL) return 1;

    return countLeafNodes(root->left) + countLeafNodes(root->right);
}

int main(void){
    Node* root = NULL;

    printf("Hello world");


    return 0;
}
