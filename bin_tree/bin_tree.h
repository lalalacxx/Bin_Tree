#pragma once

typedef char TreeDataType;

typedef struct TreeNode
{
    TreeDataType data;
    struct TreeNode *lchild;
    struct TreeNode *rchild;
}TreeNode;

//二叉树的初始化函数
void TreeInit(TreeNode **tRoot);
//二叉树的先序遍历函数
void TreePreOrder(TreeNode *root);
//二叉树的中序遍历函数
void TreeInOrder(TreeNode *root);
//二叉树的后序遍历函数
void TreePostOrder(TreeNode *root);
//二叉树的层序遍历函数
void TreeLevelOrder(TreeNode *root);
//二叉树的拷贝
TreeNode *TreeClone(TreeNode *root);
//用数组中的元素内容创建一个二叉树（该数组满足数的前序遍历且包含空节点）
TreeNode *CreateTree(TreeDataType arr[],int size,int *index,TreeDataType null_node);
//二叉树的销毁
void TreeDestroy(TreeNode **troot);
//求二叉树节点个数
int TreeSize(TreeNode *root);
//求叶子节点个数
int TreeLeafSize(TreeNode *root);
//求二叉树的第K层节点的个数
int TreeKLevelSize(TreeNode *root,int k);
//求树的高度
int TreeHeight(TreeNode *root);
//查找一个值，返回其指针
TreeNode *TreeFind(TreeNode *root,TreeDataType to_find);
//求一个节点的父节点
TreeNode *Parent(TreeNode *root,TreeNode *child);
//求一个节点的左孩子
TreeNode *LChild(TreeNode *node);
//求一个节点的右孩子
TreeNode *RChild(TreeNode *node);
