//
//  Source: tree_bst.h written by Jung,JaeJoon at the www.kernel.bz
//  Compiler: Standard C
//  Copyright(C): 2010, Jung,JaeJoon(rgbi3307@nate.com)
//
//  rsum:
//		2010-03-28 Binary Serach Tree ������� ����
//		yyyy-mm-dd ...
//

//boolean ������ Ÿ��(gcc: #include <stdbool.h>) ------------------------------
typedef enum {
    true = 1, 
    TRUE = 1, 
    false = 0, 
    FALSE = 0 
} bool;

//�ܾ� ����ü ���� ------------------------------------------------------------
typedef struct
{
	int		key;
	char	*word;
} KEY_WORD;

//���� Ʈ����� ���� ----------------------------------------------------------
typedef struct node3
{
	struct node3*	left;
	void*			data;	
	struct node3*	right;
} NODE3;

//���� ���� ����ü ���� -------------------------------------------------------
typedef struct 
{
	int		count;  //����
	int		(*compare) (void* argu1, void* argu2);
	NODE3*	root;
} TREE_BST;

//���� Ž�� Ʈ�� �Լ� ���� ----------------------------------------------------
TREE_BST* bst_create (int (*compare) (void* argu1, void* argu2));
TREE_BST* bst_destroy (TREE_BST* tree);

bool bst_insert (TREE_BST* tree, void* data_in);
bool bst_delete (TREE_BST* tree, void* data_key);
void* bst_retrieve (TREE_BST* tree, void* data);
void bst_traverse (TREE_BST* tree, void (*process)(void* data));

bool bst_empty (TREE_BST* tree);
bool bst_full (TREE_BST* tree);
int  bst_count (TREE_BST* tree);

static NODE3* _insert (TREE_BST* tree, NODE3* root, NODE3* node_new);
static NODE3* _delete (TREE_BST* tree, NODE3* root, void* data_key, bool* success);
static void* _retrieve (TREE_BST* tree, void* data, NODE3* root);
static void _traverse (NODE3* root, void (*process) (void* data));
static void _destroy (NODE3* root);