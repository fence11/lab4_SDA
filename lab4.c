#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct BinaryTreeNode
{
    int id; // id -> key
    char track_name[50];
    char composer_name[50];
    char media_type[5];
    int duration;
    struct BinaryTreeNode *left;
    struct BinaryTreeNode *right;
} BinaryTreeNode;

typedef struct BinaryTree
{
    BinaryTreeNode *root;
} BinaryTree;

BinaryTreeNode *create_binary_tree_node(int id, const char *track_name, const char *composer_name, const char *media_type, int duration)
{
    BinaryTreeNode *tree_node = calloc(sizeof(BinaryTreeNode), 1);
    tree_node->id = id;
    strncpy(tree_node->track_name, track_name, sizeof(tree_node->track_name) - 1);
    strncpy(tree_node->composer_name, composer_name, sizeof(tree_node->composer_name) - 1);
    strncpy(tree_node->media_type, media_type, sizeof(tree_node->media_type) - 1);
    tree_node->duration = duration;
    tree_node->left = tree_node->right = NULL;
    return tree_node;
}

BinaryTree *create_binary_tree()
{
    BinaryTree *local = calloc(sizeof(BinaryTree), 1);
    return local;
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

void insert_data_in_binary_tree(BinaryTree *tree, BinaryTreeNode *new_node)
{
    if (tree && new_node)
    {
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
        printf("ID: %3d, Track Name: %8s, Composer: %8s, Media: %4s, Duration: %4d\n", node->id, node->track_name, node->composer_name, node->media_type, node->duration);
    }
}

void inorder_traversal_for_printing(BinaryTreeNode *node)
{
    if (node == NULL)
        return;
    inorder_traversal_for_printing(node->left);
    print_binary_tree_node(node);
    inorder_traversal_for_printing(node->right);
}

void print_binary_tree(BinaryTree *tree)
{
    if (tree && tree->root)
    {
        printf("Binary Tree (Inorder traversal):\n");
        inorder_traversal_for_printing(tree->root);
        printf("\n");
    }
    else
    {
        printf("Binary Tree is empty.\n");
    }
}

BinaryTreeNode *search_node_by_id(BinaryTreeNode *root, int target_id, int is_mirrored)
{
    if (root == NULL || root->id == target_id)
    {
        return root;
    }

    if (is_mirrored)
    {
        if (target_id > root->id)
        {
            return search_node_by_id(root->left, target_id, is_mirrored);
        }
        else
        {
            return search_node_by_id(root->right, target_id, is_mirrored);
        }
    }
    else
    {
        if (target_id < root->id)
        {
            return search_node_by_id(root->left, target_id, is_mirrored);
        }
        else
        {
            return search_node_by_id(root->right, target_id, is_mirrored);
        }
    }
}

void input_nodes(BinaryTree *tree, int num_nodes)
{
    int id, duration;
    char track_name[50], composer_name[50], media_type[5] = "mp3";

    srand(time(NULL));
    int used_ids[100] = {0};

    for (int i = 0; i < num_nodes; i++)
    {
        // printf("Node %d ID: ", i);
        // scanf("%d", &id);
        do
        {
            id = rand() % 100 + 1;
        } while (used_ids[id - 1] == 1);

        used_ids[id - 1] = 1;

        sprintf(track_name, "track_%d", id);
        sprintf(composer_name, "composer_%d", id);
        duration = rand() % 301 + 100;

        BinaryTreeNode *new_node = create_binary_tree_node(id, track_name, composer_name, media_type, duration);
        insert_data_in_binary_tree(tree, new_node);
    }
}

void inorder_traversal_of_tree(BinaryTreeNode *node)
{
    if (node == NULL)
        return;
    inorder_traversal_of_tree(node->left);
    // print_binary_tree_node(node);
    printf("%d ", node->id);
    inorder_traversal_of_tree(node->right);
}

void preorder_traversal_of_tree(BinaryTreeNode *node)
{
    if (node == NULL)
        return;
    // print_binary_tree_node(node);
    printf("%d ", node->id);
    inorder_traversal_of_tree(node->left);
    inorder_traversal_of_tree(node->right);
}

void postorder_traversal_of_tree(BinaryTreeNode *node)
{
    if (node == NULL)
        return;
    inorder_traversal_of_tree(node->left);
    inorder_traversal_of_tree(node->right);
    // print_binary_tree_node(node);
    printf("%d ", node->id);
}

int mirror_binary_tree(BinaryTreeNode *node)
{
    if (node == NULL)
        return 1;

    int left_result = mirror_binary_tree(node->left);
    int right_result = mirror_binary_tree(node->right);

    BinaryTreeNode *temp = node->left;
    node->left = node->right;
    node->right = temp;

    return left_result && right_result;
}

void clear_binary_tree_nodes(BinaryTreeNode *node)
{
    if (node == NULL)
        return;

    clear_binary_tree_nodes(node->left);
    clear_binary_tree_nodes(node->right);

    free(node);
}

void clear_binary_tree(BinaryTree *tree)
{
    if (tree == NULL)
        return;

    clear_binary_tree_nodes(tree->root);
    tree->root = NULL;
}

void delete_binary_tree(BinaryTree **tree_ptr)
{
    if (tree_ptr == NULL || *tree_ptr == NULL)
        return;

    clear_binary_tree(*tree_ptr);
    free(*tree_ptr);
    *tree_ptr = NULL;
}

int main()
{
    BinaryTree *tree = create_binary_tree();

    int menu_option = -1, is_mirrored = 0;
    do
    {
        printf("\n1  | Print binary tree\n");
        printf("2  | Insert nodes\n");
        printf("3  | Search for node by ID\n");
        printf("4  | Print inorder\n");
        printf("5  | Print preorder\n");
        printf("6  | Print postorder\n");
        printf("7  | Mirror tree\n");
        printf("8  | Clear tree\n");
        printf("9  | Free tree\n");
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
            int num_nodes;
            printf("Number of nodes to insert: ");
            scanf("%d", &num_nodes);

            input_nodes(tree, num_nodes);
        }
        break;
        case 3:
        {
            int target_id = -1;
            printf("Insert search target ID:\n");
            scanf(" %d", &target_id);
            BinaryTreeNode *result_node = search_node_by_id(tree->root, target_id, is_mirrored);
            if (result_node != NULL)
            {
                printf("Found node with ID %d:\n", result_node->id);
                print_binary_tree_node(result_node);
            }
            else
            {
                printf("Node with ID %d not found.\n", target_id);
            }
            break;
        }
        case 4:
            printf("\nInorder traversal:\n");
            inorder_traversal_of_tree(tree->root);
            printf("\n");
            break;
        case 5:
            printf("\nPreorder traversal:\n");
            preorder_traversal_of_tree(tree->root);
            printf("\n");
            break;
        case 6:
            printf("\nPostorder traversal:\n");
            postorder_traversal_of_tree(tree->root);
            printf("\n");
            break;
        case 7:
            printf("\nMirroring tree...\n");
            if (mirror_binary_tree(tree->root))
            {
                printf("Tree mirrored\n");
                is_mirrored = !is_mirrored;
            }
            else
            {
                printf("Failed to mirror tree\n");
            }
            break;

        case 8:
            printf("\nClearing tree...\n");
            clear_binary_tree(tree);
            break;
        case 9:
            printf("\nFreeing tree...\n");
            delete_binary_tree(&tree);
            break;
        case 0:
            printf("==============\n||   EXIT   ||\n==============\n");
            break;
        default:
            printf("Invalid choice");
            break;
        }
    } while (menu_option != 0);

    delete_binary_tree(&tree);

    return 0;
}