#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char ipAddress[16];
    struct Node *left;
    struct Node *right;
};

struct Node *insert(struct Node *root, const char *ipAddress) {
    if (root == NULL) {
        struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
        if (!newNode) exit(EXIT_FAILURE);
        strcpy(newNode->ipAddress, ipAddress);
        newNode->left = newNode->right = NULL;
        printf("\nElement '%s' is inserted...", newNode->ipAddress);
        return newNode;
    }
    if (strcmp(ipAddress, root->ipAddress) < 0) {
        root->left = insert(root->left, ipAddress);
    } else if (strcmp(ipAddress, root->ipAddress) > 0) {
        root->right = insert(root->right, ipAddress);
    }
    return root;
}

struct Node *search(struct Node *root, const char *ipAddress) {
    if (root == NULL || strcmp(root->ipAddress, ipAddress) == 0) {
        return root;
    }
    if (strcmp(ipAddress, root->ipAddress) > 0) {
        return search(root->right, ipAddress);
    }
    return search(root->left, ipAddress);
}

struct Node *findMinValueNode(struct Node *node) {
    struct Node *current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

struct Node *deleteNode(struct Node *root, const char *ipAddress) {
    if (root == NULL) return root;
    if (strcmp(ipAddress, root->ipAddress) < 0) {
        root->left = deleteNode(root->left, ipAddress);
    } else if (strcmp(ipAddress, root->ipAddress) > 0) {
        root->right = deleteNode(root->right, ipAddress);
    } else {
        if (root->left == NULL) {
            struct Node *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node *temp = root->left;
            free(root);
            return temp;
        }
        struct Node *temp = findMinValueNode(root->right);
        strcpy(root->ipAddress, temp->ipAddress);
        root->right = deleteNode(root->right, temp->ipAddress);
    }
    return root;
}

void inorderTraversal(struct Node *root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%s\n", root->ipAddress);
        inorderTraversal(root->right);
    }
}

int isValidIp(const char *ipAddress) {
    int seg = 0, count = 0;
    const char *ptr = ipAddress;
    while (*ptr) {
        if (*ptr == '.') {
            if (seg < 0 || seg > 255) return 0;
            count++;
            seg = 0;
        } else if (*ptr >= '0' && *ptr <= '9') {
            seg = seg * 10 + (*ptr - '0');
        } else {
            return 0;
        }
        ptr++;
    }
    return count == 3 && seg >= 0 && seg <= 255;
}

int main() {
    struct Node *root = NULL;
    char ipAddress[20];
    int choice;

    do {
        printf("\n*********IP ADDRESS MANAGEMENT SYSTEM**********\n");
        printf("1. Insert IP Address\n");
        printf("2. Search IP Address\n");
        printf("3. Delete IP Address\n");
        printf("4. Display All IP Addresses\n");
        printf("5. Exit\n\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) exit(EXIT_FAILURE);

        switch (choice) {
            case 1:
                printf("\n\nEnter IP Address to insert: ");
                scanf("%s", ipAddress);
                if (isValidIp(ipAddress)) {
                    root = insert(root, ipAddress);
                } else {
                    printf("Invalid IP Address.\n");
                }
                break;

            case 2:
                printf("\n\nEnter IP Address to search: ");
                scanf("%s", ipAddress);
                if (search(root, ipAddress) != NULL) {
                    printf("IP Address found in the tree.\n");
                } else {
                    printf("IP Address not found in the tree.\n");
                }
                break;

            case 3:
                printf("\n\nEnter IP Address to delete: ");
                scanf("%s", ipAddress);
                if (isValidIp(ipAddress)) {
                    root = deleteNode(root, ipAddress);
                } else {
                    printf("Invalid IP Address.\n");
                }
                break;

            case 4:
                printf("\n\nIP Addresses in the tree:\n");
                inorderTraversal(root);
                break;

            case 5:
                printf("\n\nExiting program. Goodbye!\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}

