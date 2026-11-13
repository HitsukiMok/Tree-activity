#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

Node* createNode(int val) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->data = val;
    n->left = n->right = NULL;
    return n;
}

//Insertion
Node* insertNode(Node *root, int data) {
    if (root == NULL) return createNode(data);
    if (data < root->data) root->left = insertNode(root->left, data);
    else if (data > root->data) root->right = insertNode(root->right, data);
    return root;
}

//Search
Node* searchNode(Node *root, int val) {
    if (root == NULL || root->data == val) return root;
    if (val < root->data) return searchNode(root->left, val);
    return searchNode(root->right, val);
}

//Min and Maximum
Node* finMin(Node *node) {
    if (node == NULL) {
        return NULL;
    }
    if (node->left) {
        return finMin(node->left);
    } else {
        return node;
    }
}

Node* finMax(Node *node) {
    if (node == NULL) {
        return NULL;
    }
    if (node->right) {
        return finMax(node->right);
    } else {
        return node;
    }
}

//Delete
Node* deleteNode(Node *node, int data) {
    Node *temp;
    if (node == NULL) {
        return NULL;
    }

    if (data > node->data) {
        node->right = deleteNode(node->right, data);
    } else if (data < node->data) {
        node->left = deleteNode(node->left, data);
    } else {
        if (node->left && node->right) {
            temp = finMin(node->right);
            node->data = temp->data;
            node->right = deleteNode(node->right, temp->data);
        } else {
            temp = node;
            if (node->left == NULL) {
                node = node->right;
            } else if (node->right == NULL) {
                node = node->left;
            }
            free(temp);
        }
    }
    return node;
}

//Display
void printInOrder(Node *root) {
    if (root == NULL) return;
    printInOrder(root->left);
    printf("%d ", root->data);
    printInOrder(root->right);
}

void printPreOrder(Node *root) {
    if (root == NULL) return;
    printf("%d ", root->data);
    printPreOrder(root->left);
    printPreOrder(root->right);
}

void printPostOrder(Node *root) {
    if (root == NULL) return;
    printPostOrder(root->left);
    printPostOrder(root->right);
    printf("%d ", root->data);
}

//Counting Nodes
int countNodes(Node *root) {
    if (root == NULL) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

//Counting Leaf Nodes
int countLeafNodes(Node *root) {
    if (root == NULL) return 0;
    if (root->left == NULL && root->right == NULL) return 1;
    return countLeafNodes(root->left) + countLeafNodes(root->right);
}

//Checking Height
int max(int a, int b) {
    if (a > b)
        return a;
    else
        return b;
}

int treeHeight(Node *root) {
    if (root == NULL) return 0;
    return max(treeHeight(root->left), treeHeight(root->right)) + 1;
}

int countOneChildNodes(Node *root) {
    if (root == NULL) return 0;
    int hasOneChild = ((root->left != NULL && root->right == NULL) ||
                       (root->left == NULL && root->right != NULL)) ? 1 : 0;
    return hasOneChild + countOneChildNodes(root->left) + countOneChildNodes(root->right);
}

int isEmpty(Node *root) {
    return (root == NULL);
}

Node* findParent(Node *root, int val) {
    if (root == NULL || root->data == val) {
        return NULL;
    }
    if ((root->left != NULL && root->left->data == val) ||
        (root->right != NULL && root->right->data == val)) {
        return root;
    }
    if (val < root->data) {
        return findParent(root->left, val);
    } else {
        return findParent(root->right, val);
    }
}

int isSubset(Node *tree1, Node *tree2) {
    if (tree1 == NULL) return 1;
    if (searchNode(tree2, tree1->data) == NULL) return 0;
    return isSubset(tree1->left, tree2) && isSubset(tree1->right, tree2);
}

int haveSameValues(Node *root1, Node *root2) {
    if (countNodes(root1) != countNodes(root2)) {
        return 0;
    }
    return isSubset(root1, root2);
}

void freeTree(Node *root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main(void) {
    Node* root = NULL;
    Node* minNode = NULL;
    Node* maxNode = NULL;
    Node* parent = NULL;
    Node* root2 = NULL;
    int choice, val, quitConfirm, n, tempVal;
    int quit = 0;

    do {
        printf("======================\n");
        printf("Binary Search Tree\n");
        printf("======================\n");
        printf("[1] Insert Node\n");
        printf("[2] Search Node\n");
        printf("[3] Delete Node\n");
        printf("[4] In Order Traversal\n");
        printf("[5] Pre Order Traversal\n");
        printf("[6] Post Order Traversal\n");
        printf("[7] Find Minimum Value\n");
        printf("[8] Find Maximum Value\n");
        printf("[9] Count Total Nodes\n");
        printf("[10] Count Leaf Nodes\n");
        printf("[11] Find Tree Height (Total Levels)\n");
        printf("[12] Count Nodes with Exactly One Child\n");
        printf("[13] Check if BST is Empty\n");
        printf("[14] Find Parent of a Node\n");
        printf("[15] Compare with Another BST\n");
        printf("[16] Exit\n");

        printf("Enter your Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Your Number: ");
                scanf("%d", &val);
                if (searchNode(root, val) != NULL) {
                    printf("It Already Exist\n");
                } else {
                    root = insertNode(root, val);
                    printf("Succesfully Entered the Number!\n");
                }
                break;

            case 2:
                printf("What Number Would You Like to Know If It Exist in the Tree: ");
                scanf("%d", &val);
                if (searchNode(root, val) != NULL) {
                    printf("It Exist Inside the Tree!\n");
                } else {
                    printf("It Doesn't Exist Inside the Tree!\n");
                }
                break;

            case 3:
                printf("What Number Would You Like to Delete: ");
                scanf("%d", &val);
                if (searchNode(root, val) != NULL) {
                    root = deleteNode(root, val);
                    printf("It Is Successfully Removed!\nThis Is The Current Tree!\n");
                    printInOrder(root);
                    printf("\n");
                } else {
                    printf("It Doesn't Even Exist!\n");
                }
                break;

            case 4:
                printf("This Is The In Order Traversal Of The Tree!\n");
                printInOrder(root);
                printf("\n");
                break;

            case 5:
                printf("This Is The Pre Order Traversal Of The Tree!\n");
                printPreOrder(root);
                printf("\n");
                break;

            case 6:
                printf("This Is The Post Order Traversal Of The Tree!\n");
                printPostOrder(root);
                printf("\n");
                break;

            case 7:
                minNode = finMin(root);
                if (minNode != NULL) {
                    printf("This Is The Minimum Value Inside The Tree: %d\n", minNode->data);
                } else {
                    printf("The Tree Is Empty!\n");
                }
                break;

            case 8:
                maxNode = finMax(root);
                if (maxNode != NULL) {
                    printf("This Is The Maximum Value Inside The Tree: %d\n", maxNode->data);
                } else {
                    printf("The Tree Is Empty!\n");
                }
                printf("\n");
                break;

            case 9:
                printf("The Total Nodes Present In The Tree is: %d\n", countNodes(root));
                break;

            case 10:
                printf("The Total Leaf Nodes Present In the Tree is: %d\n", countLeafNodes(root));
                break;

            case 11:
                printf("The Total Height Of The Tree is : %d\n", treeHeight(root));
                break;

            case 12:
                printf("The Total Nodes With Exactly One Child is: %d\n", countOneChildNodes(root));
                break;

            case 13:
                if (isEmpty(root)) {
                    printf("The Tree Is Empty!\n");
                } else {
                    printf("The Tree Is Not Empty!\n");
                }
                break;

            case 14:
                printf("Enter the Node Value to Find its Parent: ");
                scanf("%d", &val);
                if (searchNode(root, val) == NULL) {
                    printf("It Doesn't Exist Inside the Tree!\n");
                } else if (root->data == val) {
                    printf("This Node is the Root and Has No Parent!\n");
                } else {
                    parent = findParent(root, val);
                    if (parent != NULL) {
                        printf("The Parent of %d is: %d\n", val, parent->data);
                    }
                }
                break;

            case 15:
                root2 = NULL;
                printf("How many nodes do you want to enter in the second BST: ");
                scanf("%d", &n);
                for (int i = 0; i < n; i++) {
                    printf("Enter value #%d: ", i + 1);
                    scanf("%d", &tempVal);
                    if (searchNode(root2, tempVal) == NULL) {
                        root2 = insertNode(root2, tempVal);
                    } else {
                        printf("It Already Exist\n");
                    }
                }
                if (haveSameValues(root, root2)) {
                    printf("The Two BSTs Contain the Same Values!\n");
                } else {
                    printf("The Two BSTs Do Not Contain the Same Values!\n");
                }
                freeTree(root2);
                break;

            case 16:
                printf("Are you sure you wanna quit the program?\n");
                printf("1 - Yes\n2 - No\n");
                scanf("%d", &quitConfirm);
                if (quitConfirm == 1) {
                    printf("Exitting....\n");
                    quit = 1;
                }
                break;

            default:
                printf("Invalid Choice\n");
                break;
        }

        if (quit == 1)
            break;
    } while (1);

    freeTree(root);
    return 0;
}
