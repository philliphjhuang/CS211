#include <stdlib.h>
#include <stdio.h>

// A program to perform a LEVEL ORDER (BREADTH-FIRST) TRAVERSAL of a binary search tree

// BINARY SEARCH TREE

typedef struct BSTNode BSTNode;
struct BSTNode {
    int key;
    struct BSTNode* l_child; // nodes with smaller key will be in left subtree
    struct BSTNode* r_child; // nodes with larger key will be in right subtree
};

// Add new data to the BST using recursion
/* ... */
struct BSTNode* insert(struct BSTNode* root, int key){
    if(root==NULL){
        struct BSTNode* temp = malloc(sizeof(struct BSTNode));
        temp->key = key;
        temp->l_child = NULL;
        temp->r_child = NULL;
        return temp;
    }

    if(root->key < key){
        root->r_child = insert(root->r_child, key);
    } else if(root->key > key) {
        root->l_child = insert(root->l_child, key);
    }
    return root;
}
// Delete the BST using recursion
/* ... */
void delete_bst ( BSTNode* root ) {
    if ( root->r_child!=NULL ) {
        delete_bst (root->r_child);
    }
    if ( root->l_child!=NULL ) {
        delete_bst (root->l_child);
    }
    free (root);
}

// LINKED LIST IMPLEMENTATION OF QUEUE
typedef struct QueueNode QueueNode;
struct QueueNode {
    struct BSTNode* data;
    struct QueueNode* next;
};
struct Queue {
    struct QueueNode* front;
    struct QueueNode* back;
};

typedef struct Queue Queue;

// queue needed for level order traversal

// Append a new QueueNode to the back of the Queue
void enqueue ( Queue* queue, BSTNode* data ) {
    QueueNode* queueNode = malloc(sizeof(QueueNode));
    queueNode -> data = data;
    queueNode -> next = NULL;

    if (queue->back==NULL) {
        queue->front = queueNode;
        queue->back = queueNode;
    } else {
        queue->back->next = queueNode;
        queue->back = queueNode;
    }
    return;
}

// Remove a QueueNode from the front of the Queue
struct BSTNode* dequeue ( Queue* queue ) {
    if (queue->front==NULL) {
        return NULL;
    } else {
        QueueNode* temp = queue->front;
        struct BSTNode* data = temp->data;
        queue->front = temp->next;
        if (queue->back==temp) {
            queue->back = NULL;
        }
        free(temp);
        return data;
    }
}

void depth_first ( struct BSTNode* root ) {
    if(root!=NULL){
        depth_first(root->r_child);
        printf(" %d ", root->key);
        depth_first(root->l_child);
    }
}

int main ( int argc, char* argv[] ) {

    // READ INPUT FILE TO CREATE BINARY SEARCH TREE
    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }
    BSTNode* root = NULL;
    int key;
    while ( fscanf(fp, "%d", &key)!=EOF ) {
        root = insert (root, key);
    }
    fclose(fp);

    // USE A QUEUE TO PERFORM LEVEL ORDER TRAVERSAL
    Queue queue = { .front=NULL, .back=NULL };
    BSTNode* currBSTNode = root;
    do {
        if(currBSTNode->l_child!=NULL){
            enqueue(&queue,currBSTNode->l_child);
        }
        if(currBSTNode->r_child!=NULL){
            enqueue(&queue,currBSTNode->r_child);
        }
        printf("%d ", currBSTNode->key);
        currBSTNode = dequeue(&queue);
    } while ( currBSTNode!=NULL );
    delete_bst(root);
    return EXIT_SUCCESS;
}
