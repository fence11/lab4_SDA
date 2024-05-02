#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct BinaryTreeNode
{
    int id;
    char track_name[100];
    int duration;
    struct BinaryTreeNode *left;
    struct BinaryTreeNode *right;
} BinaryTreeNode;

typedef struct BinaryTree
{
    BinaryTreeNode *root;
} BinaryTree;

BinaryTreeNode *create_binary_tree_node(int id, const char *track_name, int duration)
{
    BinaryTreeNode *tree_node = calloc(sizeof(BinaryTreeNode), 1);
    tree_node->id = id;
    strncpy(tree_node->track_name, track_name, sizeof(tree_node->track_name) - 1);
    tree_node->duration = duration;
    tree_node->left = tree_node->right = NULL;
    return tree_node;
}

BinaryTree *create_binary_tree()
{
    BinaryTree *local = calloc(sizeof(BinaryTree), 1);
    return local;
}

void delete_all_tree_nodes_from_node(BinaryTreeNode *current_node)
{
    if (current_node)
    {
        delete_all_tree_nodes_from_node(current_node->left);
        delete_all_tree_nodes_from_node(current_node->right);
        free(current_node);
    }
}

void clear_binary_tree(BinaryTree *tree)
{
    if (tree)
    {
        if (tree->root)
        {
            delete_all_tree_nodes_from_node(tree->root);
            tree->root = NULL;
        }
    }
}

void delete_binary_tree(BinaryTree *tree)
{
    if (tree)
    {
        clear_binary_tree(tree);
        free(tree);
    }
}

void insert_new_node_in_binary_tree(BinaryTreeNode *current_node, BinaryTreeNode *new_node)
{
    if (current_node)
    {
        if (current_node->id > new_node->id)
        {
            if (current_node->left)
            {
                insert_new_node_in_binary_tree(current_node->left, new_node);
            }
            else
            {
                current_node->left = new_node;
            }
        }
        else
        {
            if (current_node->right)
            {
                insert_new_node_in_binary_tree(current_node->right, new_node);
            }
            else
            {
                current_node->right = new_node;
            }
        }
    }
}

void insert_data_in_binary_tree(BinaryTree *tree, int id, const char *track_name, int duration)
{
    if (tree)
    {
        BinaryTreeNode *new_node = create_binary_tree_node(id, track_name, duration);
        if (tree->root)
        {
            insert_new_node_in_binary_tree(tree->root, new_node);
        }
        else
        {
            tree->root = new_node;
        }
    }
}

void print_binary_tree_node(BinaryTreeNode *node)
{
    if (node)
    {
        printf("ID: %3d, Track Name: %10s, Duration: %4d\n", node->id, node->track_name, node->duration);
    }
}

void print_binary_tree_inorder(BinaryTreeNode *root)
{
    if (root)
    {
        print_binary_tree_inorder(root->left);
        print_binary_tree_node(root);
        print_binary_tree_inorder(root->right);
    }
}

void print_binary_tree(BinaryTree *tree)
{
    if (tree && tree->root)
    {
        printf("Binary Tree (Inorder traversal):\n");
        print_binary_tree_inorder(tree->root);
        printf("\n");
    }
    else
    {
        printf("Binary Tree is empty.\n");
    }
}

BinaryTreeNode *search_node_by_id(BinaryTreeNode *root, int target_id)
{
    if (root == NULL || root->id == target_id)
    {
        return root;
    }

    if (target_id < root->id)
    {
        return search_node_by_id(root->left, target_id);
    }
    else
    {
        return search_node_by_id(root->right, target_id);
    }
}

void input_node(BinaryTree *tree)
{
    int id, duration;
    char track_name[100];

    scanf("%d %s %d", &id, track_name, &duration);
    insert_data_in_binary_tree(tree, id, track_name, duration);
}

void inorder_traversal_of_tree(BinaryTreeNode *node)
{
    if (node == NULL)
        return;
    inorder_traversal_of_tree(node->left);
    printf("%d ", node->id); // instead of print node->id | print all data from node \n FUNCTION: display_node
    inorder_traversal_of_tree(node->right);
}

void preorder_traversal_of_tree(BinaryTreeNode *node)
{
    if (node == NULL)
        return;
    printf("%d ", node->id); // instead of print node->id | print all data from node \n FUNCTION: display_node
    inorder_traversal_of_tree(node->left);
    inorder_traversal_of_tree(node->right);
}

void postorder_traversal_of_tree(BinaryTreeNode *node)
{
    if (node == NULL)
        return;
    inorder_traversal_of_tree(node->left);
    inorder_traversal_of_tree(node->right);
    printf("%d ", node->id); // instead of print node->id | print all data from node \n FUNCTION: display_node
}

void mirror_binary_tree(BinaryTreeNode * node)
{
    if (node == NULL)
        return;

    BinaryTreeNode *temp; 

    mirror_binary_tree(node->left);
    mirror_binary_tree(node->right);

    temp = node->left;
    node->left = node->right;
    node->right = temp;
}

void clear_tree(BinaryTree *tree)
{
    if (tree && tree->root)
    {
        delete_all_tree_nodes_from_node(tree->root);
        tree->root = NULL;
    }
}

void free_binary_tree(BinaryTreeNode * node){
    if (node == NULL)
        return;
    
    free_binary_tree(node->left);
    free_binary_tree(node->right);

    free(node);
} 

int main()
{
    BinaryTree *tree = create_binary_tree();

    int menu_option = 0;
    do
    {
        printf("\n1  | Print binary tree\n");
        printf("2  | Insert nodes\n");
        printf("4  | Search for node by ID\n");
        printf("5  | Print inorder\n");
        printf("6  | Print preorder\n");
        printf("7  | Print postorder\n");
        printf("8  | --- DFS\n");
        printf("9  | --- BFS\n");
        printf("10 | --- Balance tree\n");
        printf("11 | Mirror tree\n");
        printf("12 | Clear tree\n");
        printf("13 | --- Free tree\n");
        printf("0  | Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &menu_option);
        switch (menu_option)
        {
        case 1:
            print_binary_tree(tree);
            break;
        case 2:
        {
            char choice;
            printf("Enter elements to insert into the binary tree (ID Track_Name Duration, separated by spaces):\n");
            do
            {
                input_node(tree);
                printf("Insert more elements (y/n): ");
                scanf(" %c", &choice);
            } while (choice == 'y' || choice == 'Y');
        }
        break;
        case 4:
        {
            int target_id = -1;
            printf("Insert search target ID:\n");
            scanf(" %d", &target_id);
            BinaryTreeNode *result_node = search_node_by_id(tree->root, target_id);
            if (result_node != NULL)
            {
                // instead of this, place found node ... Node * node
                printf("Found node with ID %d: %s\n", result_node->id, result_node->track_name);
            }
            else
            {
                printf("Node with ID %d not found.\n", target_id);
            }
            break;
        }
        case 5:
            printf("\nInorder traversal:\n");
            inorder_traversal_of_tree(tree->root);
            printf("\n");
            break;
        case 6:
            printf("\nInorder traversal:\n");
            preorder_traversal_of_tree(tree->root);
            printf("\n");
            break;
        case 7:
            printf("\nInorder traversal:\n");
            postorder_traversal_of_tree(tree->root);
            printf("\n");
            break;
        case 11:
            printf("\nMirroring tree...\n");
            mirror_binary_tree(tree->root);
            break;
        case 12:
            printf("\nClearing tree...\n");
            clear_binary_tree(tree);
            break;
        case 13:
            printf("\nFreeing tree...\n");
            free_binary_tree(tree->root);
            break;
        case 0:
            printf("==============\n||   EXIT   ||\n==============\n");
            break;
        default:
            printf("Invalid choice");
            break;
        }
    } while (menu_option != 0);

    delete_binary_tree(tree);

    return 0;
}

/*
\	căutarea unui nod în baza cîmpului cheie și afișarea cîmpurilor nodului găsit;
?	parcurgerea arborelui în adîncime( DFS); <--- already done when printing inorder, postorder, preorder
-	parcurgerea arborelui în lărgime ( BFS);
X	balansarea arborelui (în imaginea de mai jos este redat un arbore balansat și unul nebalansat );
\	oglindirea arborelui (orice nod copil drept, devine un nod copil stîng și analog orice nod copil stîng devine
    un nod copil drept), ține cont că după oglindirea arborelui binar de căutare proprietatea între nod și copii
    se va schimba, prin urmare și căutarea deja se va face în altă ordine;
\	eliberarea memoriei arborelui.
*/