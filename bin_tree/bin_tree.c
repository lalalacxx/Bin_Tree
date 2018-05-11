#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"bin_tree.h"
#include"queue.h"
#include"stack.h"

#define Test_Header printf("\n==========%s=========\n",__FUNCTION__);

//创建新节点的函数
TreeNode *CreateNode(TreeDataType value)
{
    TreeNode *new_node =(TreeNode*)malloc(sizeof(TreeNode));
    new_node->data = value;
    new_node->lchild = NULL;
    new_node->rchild = NULL;
    return new_node;
}
//销毁节点的函数
void DestroyNode(TreeNode *node)
{
    free(node);
    return;
}
//二叉树的初始化函数
void TreeInit(TreeNode **tRoot)
{
    if(tRoot == NULL)
    {
        //非法输入
        return;
    }
    *tRoot = NULL;
}
//二叉树的先序遍历函数
void TreePreOrder(TreeNode *root)
{
    if(root == NULL)
    {
        //空树
        return;
    }
    //先访问根节点
    printf("%c ",root->data);
    //在递归的遍历访问左子树
    TreePreOrder(root->lchild);
    //在递归的遍历访问右子树
    TreePreOrder(root->rchild);
}
//二叉树的中序遍历函数
void TreeInOrder(TreeNode *root)
{
    if(root == NULL)
    {
        //空树
        return;
    }
    //先递归的遍历访问左子树
    TreeInOrder(root->lchild);
    //再访问根节点
    printf("%c ",root->data);
    //在递归的遍历访问右子树
    TreeInOrder(root->rchild);
}
//二叉树的后序遍历函数
void TreePostOrder(TreeNode *root)
{

    if(root == NULL)
    {
        //空树
        return;
    }
    //先递归的遍历访问左子树
    TreePostOrder(root->lchild);
    //在递归的遍历访问右子树
    TreePostOrder(root->rchild);
    //再访问根节点
    printf("%c ",root->data);
}
//二叉树的层序遍历函数
void TreeLevelOrder(TreeNode *root)
{
    if(root == NULL)
    {
        //空树
        return;
    }
    Queue queue;
    //初始化队列
    QueueInit(&queue);
    //将根节点入队列
    QueuePush(&queue,root);
    TreeNode* cur = NULL;
    while(1)
    {
        //取队首元素
        int ret =  QueueGetTop(&queue,&cur);
        if(ret == 0)
        {
            //此时说明队列空了
            //也就说明树遍历结束
            break;
        }
        //访 问树中的元素，打印当前值
        printf("%c ",cur->data);
        //将当前队首元素出队列
        QueuePop(&queue);
        //将当前元素的左子树入队列
        if(cur->lchild != NULL)
        {
            QueuePush(&queue,cur->lchild);
        }
        //将当前元素的右子树入队列
        if(cur->rchild != NULL)
        {
            QueuePush(&queue,cur->rchild);
        }
    }
    printf("\n");
    return;
}
//二叉树的拷贝
TreeNode *TreeClone(TreeNode *root)
{
    if(root == NULL)
    {
        //空树
        return NULL;
    }
    //按照先序方式遍历
    TreeNode *new_node = CreateNode(root->data);
    new_node->lchild = TreeClone(root->lchild);
    new_node->rchild = TreeClone(root->rchild);
    return new_node;
}
//用数组中的元素内容创建一个二叉树（该数组满足数的前序遍历且包含空节点）
TreeNode *CreateTree(TreeDataType arr[],int size,int *index,TreeDataType null_node)
{
    if(index == NULL)
    {
        //非法输入
        return NULL;
    }
    if(*index >= size)
    {
        return NULL;
    }
    if(arr[*index] == null_node)
    {
        return NULL;
    }
    TreeNode *new_node = CreateNode(arr[*index]);
    ++(*index);
    new_node->lchild = CreateTree(arr,size,index,null_node);
    ++(*index);
    new_node->rchild = CreateTree(arr,size,index,null_node);
    return new_node;
}
TreeNode *_CreateTree(TreeDataType arr[],int size,TreeDataType null_node)
{
    int index = 0;
    return CreateTree(arr,size,&index,null_node);
}
//二叉树的销毁
void TreeDestroy(TreeNode **troot)
{
    if(troot == NULL)
    {
        //非法输入
        return;
    }
    if(*troot == NULL){
        //空树
        return;
    }
    //方法1：采用后续遍历的方法依次销毁树的节点
//    TreeDestroy(&(*troot)->lchild);
//    TreeDestroy(&(*troot)->rchild);
//    DestroyNode(*troot);
//    *troot = NULL;
    //方法2：采用前序遍历的方法依次销毁树的节点
   TreeNode *lchild = (*troot)->lchild;
   TreeNode *rchild = (*troot)->rchild;
   DestroyNode(*troot);
   *troot = NULL;
   TreeDestroy(&lchild);
   TreeDestroy(&rchild);
}
void _TreeSize(TreeNode* root,int* size){
    if(root == NULL || *size < 1)
        return;

    ++(*size);
    _TreeSize(root->lchild,size);
    _TreeSize(root->rchild,size);
}
//求二叉树节点个数
int TreeSize(TreeNode *root)
{
    if(root == NULL)
    {
        //空树
        return 0;
    }
    //方法1：递归
   // if(root->lchild == NULL && root->rchild == NULL)
  //  {
        //此时的树只有一个根节点
 //       return 1;
 //   }
    //此时树的节点不只有根节点
    //所以节点个数就等于根节点的个数1加上左子树的节点个数
    //再加上右子树的节点个数
    //return 1 + TreeSize(root->lchild) + TreeSize(root->rchild);
    //方法2：前序遍历，此时的访问相当于计数+1
    int size = 0;
    size++;
    _TreeSize(root->lchild,&size);
    _TreeSize(root->rchild,&size);
    return size;
}

//求叶子节点个数
int TreeLeafSize(TreeNode *root)
{
    if(root == NULL)
    {
        //空树
        return 0;
    }
    if(root->lchild == NULL && root->rchild == NULL)
    {
        //此时只有一个根节点，该根节点也是一个叶子节点
        return 1;
    }
    //此时不只有一个根节点
    //叶子节点的个数等于根节点的左子树的叶子节点的个数
    //再加上右子树的叶子节点的个数
    return TreeLeafSize(root->lchild) + TreeLeafSize(root->rchild);
}
//求二叉树的第K层节点的个数
int TreeKLevelSize(TreeNode *root,int k)
{
    if(root == NULL || k < 1)
    {
        //空树
        return 0;
    }
    if(k == 1)
    {
        return 1;
    }
    return TreeKLevelSize(root->lchild,k-1) + TreeKLevelSize(root->rchild,k-1);
}
//求树的高度
int TreeHeight(TreeNode *root)
{
    if(root == NULL)
    {
        return 0;
    }    
    if(root->lchild == NULL && root->rchild == NULL)
    {
        //此时只有一个根节点
        return 1;
    }
    int lresult = TreeHeight(root->lchild);
    int rresult = TreeHeight(root->rchild);
    return 1+(lresult > rresult ? lresult : rresult);
}
//查找一个值，返回其指针
TreeNode *TreeFind(TreeNode *root,TreeDataType to_find)
{
    if(root == NULL)
    {
        //空树
        return NULL;
    }
    //以前序遍历的顺序查找
    //先判断根节点的值是否为我们要查找的值
    if(root->data == to_find)
    {
        //此时满足条件说明根节点就是我们需要查找的
        return root;
    }
    //再递归的以根节点的左右子树递归的调用该函数
    TreeNode *lresult = TreeFind(root->lchild,to_find);
    TreeNode *rresult = TreeFind(root->rchild,to_find);
    return lresult != NULL ? lresult : rresult;
}
//求一个节点的父节点
TreeNode *Parent(TreeNode *root,TreeNode *child)
{
    if(root == NULL)
    {
        //空树
        return NULL;
    }
    if(root->lchild == child || root->rchild == child)
    {
        //判断根节点是否为其父节点
        return root;
    }
    //递归的以根节点的额左右子树调用该函数
    TreeNode *lresult = Parent(root->lchild,child);
    TreeNode *rresult = Parent(root->rchild,child);
    return lresult != NULL ? lresult : rresult;
}
//求一个节点的左孩子
TreeNode *LChild(TreeNode *node)
{ 
    if(node == NULL)
    {
        return NULL;
    }
    return node->lchild;
}
//求一个节点的右孩子
TreeNode *RChild(TreeNode *node)
{
    if(node == NULL)
    {
        return NULL;
    }
    return node->rchild;
}
//非递归前序遍历二叉树
void TreePreOrderByLoop(TreeNode *root)
{
    if(root == NULL)
    {
        //空树
        return;
    }
    Stack stack;
    StackInit(&stack);
    //根节点入栈
    StackPush(&stack,root);
    TreeNode *cur = NULL;
    //循环的去栈顶元素对其操作，栈为空时结束循环
    while(StackGetTop(&stack,&cur))
    {
        //出栈
        StackPop(&stack);
        //访问当前栈顶元素
        printf("%c ",cur->data);
        //将当前元素的右子树入栈
        if(cur->rchild != NULL)
        {
            StackPush(&stack,cur->rchild);
        }
        //再将当前元素的左子树入栈（一定是先右在左）
        if(cur->lchild != NULL)
        {
            StackPush(&stack,cur->lchild);
        }
    }
    return;
}
//非递归中序遍历二叉树
void TreeInOrderByLoop(TreeNode *root)
{
    if(root == NULL)
    {
        //空树
        return;
    }
    Stack stack;
    StackInit(&stack);
    TreeNode *cur = root;
    while(1)
    {
        //该循环结束cur就到了一个空节点处
        //他的前一个指向的节点就是当前树的最左的节点
        while(cur != NULL)
        {
            StackPush(&stack,cur);
            cur = cur->lchild;
        }
        //此时cur为空
        //取栈顶元素
        TreeNode *tmp = NULL;
        int ret = StackGetTop(&stack,&tmp);
        if(ret == 0)
        {
            //取栈顶元素失败，说明栈空了
            //也就说明遍历完成
            return;
        }
        //访问
        printf("%c ",tmp->data);
        //出栈
        StackPop(&stack);
        if(tmp->rchild != NULL)
        {
            cur = tmp->rchild;
        }
    }
    return; 
}
//非递归后序遍历二叉树
void TreePostOrderByLoop(TreeNode *root)
{
    if(root == NULL)
    {
        //空树
        return;
    }
    Stack stack;
    StackInit(&stack);
    //定义cur指针指向根节点
    TreeNode *cur = root;
    //定义一个指针保存我们最新访问过的最后一个元素
    TreeNode *pre = NULL;
    //该循环结束cur就到了一个空节点处
    //他的前一个指向的节点就是当前树的最左的节点
    while(1)
    {
        while(cur != NULL)
        {
            StackPush(&stack,cur);
            cur = cur->lchild;
        }
        //此时cur为空
        //取栈顶元素
        TreeNode *tmp = NULL;
        int ret = StackGetTop(&stack,&tmp);
        if(ret == 0)
        {
            //取栈顶元素失败，说明栈空了
            //也就说明遍历完成
            return;
        }
        //对当前栈顶元素进行判定
        //1、如果当前栈顶元素的右子树为空
        //2、或者右子树已经访问过（和访问的上一个元素是同一个元素）
        //此时才能够对该栈顶元素进行访问，然后出栈
        if(tmp->rchild == NULL || tmp->rchild == pre)
        {
            printf("%c ",tmp->data);
            StackPop(&stack);
            //更新pre的指向，用于下一次的栈顶元素的判断
            pre = tmp;
        }
        //如果都不满足，则就让cur指向该栈顶元素的右子树
        //重复之前的动作
        else
        {
            cur = tmp->rchild;
        } 
    }
}
void swap(TreeNode **a,TreeNode **b)
{
    if(a == NULL || b == NULL)
    {
        return;
    }
    TreeNode *tmp = *a;
    *a = *b;
    *b = tmp;
    return;
}
//求二叉树的镜像(递归)
void TreeMirror(TreeNode *root)
{
    if(root == NULL)
    {
        //空树
        return;
    }
    swap(&root->lchild,&root->rchild);
    TreeMirror(root->lchild);
    TreeMirror(root->rchild);
}
//求二叉树的镜像(非递归)
void TreeMirror2(TreeNode *root)
{
    if(root == NULL)
    {
        //空树
        return;
    }
    //定义一个队列并且初始化
    Queue queue;
    QueueInit(&queue);
    //将根节点入队列
    QueuePush(&queue,root);
    TreeNode *top = NULL;
    //循环的取队首元素
    while(QueueGetTop(&queue,&top))
    {
        //交换左右子树
        swap(&top->lchild,&top->rchild);
        //将当前栈顶元素出栈
        QueuePop(&queue);
        //将当前栈顶元素的左右子树入队列
        if(top->lchild != NULL)
        {
            QueuePush(&queue,top->lchild);
        }
        if(top->rchild != NULL)
        {
            QueuePush(&queue,top->rchild);
        }
    }
    return;
}
//判断是否为完全二叉树
int IsCompleteTree(TreeNode *root)
{
    if(root == NULL)
    {
        //空树
        return 0;
    }
    //定义一个队列并且初始化
    Queue queue;
    QueueInit(&queue);
    //将根节点初始化
    QueuePush(&queue,root);
    //定义一个变量用来表示是否进入第二阶段
    int Is_start_step_two = 0;
    TreeNode *top = NULL;
    //循环取队首元素
    while(QueueGetTop(&queue,&top))
    {
        //将当前队首元素出栈
        QueuePop(&queue);
        //第一阶段的判定
        if(Is_start_step_two == 0)
        {
            if(top->lchild != NULL && top->rchild != NULL)
            {
                QueuePush(&queue,top->lchild);
                QueuePush(&queue,top->rchild);
            }
            else if(top->lchild == NULL && top->rchild != NULL)
            {
                //此时没有左子树，只有右子树，那么一定不是完全二叉树
                return 0;
            }
            else if(top->lchild != NULL && top->rchild == NULL)
            {
                //此时只有左子树没有右子树，就需要进入下一个阶段再进行判断
                Is_start_step_two = 1;
                QueuePush(&queue,top->lchild);
            }
            else
            {
                //此时左右子树都没有，需要进入下一阶段在进行判断
                Is_start_step_two = 1;
            }
        }
        //第二阶段的判定
        else
        {
            //节点没有子树
            if(top->lchild == NULL && top->rchild == NULL)
            {
                ;
            }
            else
            {
                //节点有任意一棵子树，或者两棵子树都有，一定不是完全二叉树
                return 0;
            }
        }
    }//此处循环结束
    //所有的节点都遍历完了，而又没有return 0从而走到这一步
    //说明该树一定是完全二叉树
    return 1;
}
//由前序和中序结果创建树
int Find(TreeDataType to_find,TreeDataType in_order[],int left,int right)
{
    int i = left;
    for(;i < right;i++)
    {
        if(to_find == in_order[i])
        {
            return i;
        }
    }
    return -1;
}
TreeNode *_TreeRebuild(TreeDataType pre_order[],int *pre_order_index,int size,\
                       TreeDataType in_order[],int left,int right)
{
    if(left >= right)
    {
        //区间无效，说明为一棵空树
        return NULL;
    }
    if(pre_order_index == NULL)
    {
        //非法输入
        return NULL;
    }
    if(*pre_order_index >= size)
    {
        //遍历结束
        return NULL;
    }
    //以先序结果取当前值构建一个新节点
    //相当于当前子树的根节点
    TreeNode *new_node = CreateNode(pre_order[*pre_order_index]);
    //找到当前节点在中序遍历结果中的位置
    int cur_root_in_order_index = Find(new_node->data,in_order,left,right);
    assert(cur_root_in_order_index != -1);
    ++(*pre_order_index);
    //左子树区间[left,cur_root_in_order_index)
    new_node->lchild =  _TreeRebuild(pre_order,pre_order_index,size,in_order,left,cur_root_in_order_index);
    //右子树区间[cur_root_in_order_index+1,right)
    new_node->rchild =  _TreeRebuild(pre_order,pre_order_index,size,in_order,cur_root_in_order_index+1,right);
    return new_node;
}
TreeNode *TreeRebuild(TreeDataType pre_order[],TreeDataType in_order[],int size)
{
    int pre_order_index = 0;
    int in_order_left = 0;
    int in_order_right = size;
    return _TreeRebuild(pre_order,&pre_order_index,size,in_order,in_order_left,in_order_right);
}
//由前序和中序结果创建树的函数测试
void TestRebuild()
{
    Test_Header;
    TreeDataType pre_order[] = "abdegcf";
    TreeDataType in_order[] = "dbgeacf";
    TreeNode *new_node = TreeRebuild(pre_order,in_order,7);
    printf("递归先序遍历结果：");
    TreePreOrder(new_node);
    printf("非递归先序遍历结果：");
    TreePreOrderByLoop(new_node);
    printf("\n");
    printf("递归中序遍历结果：");
    TreeInOrder(new_node);
    printf("非递归中序遍历结果：");
    TreeInOrderByLoop(new_node);
    printf("\n");
    printf("递归后序遍历结果：");
    TreePostOrder(new_node);
    printf("非递归后序遍历结果：");
    TreePostOrderByLoop(new_node);
    printf("\n");
}
//判断是否为完全二叉树函数测试                     
 void TestIsCompleteTree()                
 {                                  
     Test_Header;                   
     TreeNode *a = CreateNode('a'); 
     TreeNode *b = CreateNode('b'); 
     TreeNode *c = CreateNode('c'); 
     TreeNode *d = CreateNode('d'); 
     TreeNode *e = CreateNode('e'); 
     TreeNode *f = CreateNode('f'); 
     TreeNode *g = CreateNode('g'); 
     a->lchild = b;                 
     a->rchild = c;                 
     c->rchild = f;                 
     b->lchild = d;                 
     b->rchild = e;                 
     e->lchild = g;                
     //对一棵非完全二叉树进行判断测试
     int ret = IsCompleteTree(a);   
     printf("expected ret = 0,actual ret = %d\n",ret);
     //将树修改为完全二叉树再次测试
     c->rchild = NULL;
     e->lchild = NULL;
     ret = IsCompleteTree(a);
     printf("expected ret = 1,actual ret = %d\n",ret);

 }
void TestInit()
{
    Test_Header;
    TreeNode *tRoot;
    TreeInit(&tRoot);
    printf("expected NULL,actual %p\n",tRoot);
}
//遍历函数测试
void TestTraverse()
{
    Test_Header;
    TreeNode *a = CreateNode('a');
    TreeNode *b = CreateNode('b');
    TreeNode *c = CreateNode('c');
    TreeNode *d = CreateNode('d');
    TreeNode *e = CreateNode('e');
    TreeNode *f = CreateNode('f');
    TreeNode *g = CreateNode('g');
    a->lchild = b;
    a->rchild = c;
    c->rchild = f;
    b->lchild = d;
    b->rchild = e;
    e->lchild = g;
    printf("递归先序遍历结果：");
    TreePreOrder(a);
    printf("非递归先序遍历结果：");
    TreePreOrderByLoop(a);
    printf("\n");
    printf("递归中序遍历结果：");
    TreeInOrder(a);
    printf("非递归中序遍历结果：");
    TreeInOrderByLoop(a);
    printf("\n");
    printf("递归后序遍历结果：");
    TreePostOrder(a);
    printf("非递归后序遍历结果：");
    TreePostOrderByLoop(a);
    printf("\n");
    printf("层序遍历结果：");
    TreeLevelOrder(a);
    printf("\n");
}
void TestTreeCreateAndClone()
{
    Test_Header;

    printf("[创建树的测试]\n");
    TreeDataType arr[] = "abd**eg***c*f**";
    TreeNode *root = _CreateTree(arr,sizeof(arr)/sizeof(arr[0]),'*');
    printf("先序遍历结果：");
    TreePreOrder(root);
    printf("\n");
    printf("中序遍历结果：");
    TreeInOrder(root);
    printf("\n");
    printf("后序遍历结果：");
    TreePostOrder(root);
    printf("\n");
    printf("层序遍历结果：");
    TreeLevelOrder(root);

    printf("[克隆树的测试]\n");
    TreeNode *new_root = TreeClone(root);
    printf("先序遍历结果：");
    TreePreOrder(new_root);
    printf("\n");
    printf("中序遍历结果：");
    TreeInOrder(new_root);
    printf("\n");
    printf("后序遍历结果：");
    TreePostOrder(new_root);
    printf("\n");
    printf("层序遍历结果：");
    TreeLevelOrder(new_root);
}
void TestDestroy()
{
    Test_Header;
    //创建一棵树
    TreeDataType arr[] = "abd**eg***c*f**";
    TreeNode *troot = _CreateTree(arr,sizeof(arr)/sizeof(arr[0]),'*');
    TreeDestroy(&troot); 
    printf("expected troot = null,actual troot = %p\n",troot);
}
void TestNodeNumAndHeight()
{
    Test_Header;
    //创建一棵树
    TreeDataType arr[] = "abd**eg***c*f**";
    TreeNode *root = _CreateTree(arr,sizeof(arr)/sizeof(arr[0]),'*');
    printf("树的节点个数函数测试：");
    int ret0 = TreeSize(root);
    printf("expected ret0 = 7,actual ret0 = %d\n",ret0);
    printf("树的叶子节点个数函数测试：");
    int ret1 = TreeLeafSize(root);
    printf("expected ret1 = 3,actual ret1 = %d\n",ret1);
    printf("树的第k层节点个数函数测试：");
    int ret2 = TreeKLevelSize(root,3);
    printf("expected ret2 = 3,actual ret2 = %d\n",ret2);
    printf("树的高度函数测试：");
    int ret3 = TreeHeight(root);
    printf("expected ret3 = 4,actual ret3 = %d\n",ret3);
}
void TestFind()
{
    Test_Header;
    //创建一棵树
    TreeDataType arr[] = "abd**eg***c*f**";
    TreeNode *root = _CreateTree(arr,sizeof(arr)/sizeof(arr[0]),'*');
    TreeDataType to_find1 = 'b';
    TreeDataType to_find2 = 'x';
    TreeNode *R1 = TreeFind(root,to_find1);
    printf("rexpected R1 = %p.actual R1 = %p\n",root->lchild,R1);
    TreeNode *R2 = TreeFind(root,to_find2);
    printf("rexpected R2 = NULL,actual R2 = %p\n",R2);
}
void TestParent()
{
    Test_Header;
    TreeNode *a = CreateNode('a');
    TreeNode *b = CreateNode('b');
    TreeNode *c = CreateNode('c');
    TreeNode *d = CreateNode('d');
    TreeNode *e = CreateNode('e');
    TreeNode *f = CreateNode('f');
    TreeNode *g = CreateNode('g');
    a->lchild = b;
    a->rchild = c;
    c->rchild = f;
    b->lchild = d;
    b->rchild = e;
    e->lchild = g;
    TreeNode *R1 = Parent(a,e);
    printf("rexpected R1 = %p,actual R1 = %p\n",b,R1);
    TreeNode *q = CreateNode('q');
    TreeNode *R2 = Parent(a,q);
    printf("expected R2 = NULL,actual R2 = %p\n",R2);
    printf("找到节点的左右孩子：\n");
    TreeNode *R3 = LChild(c);
    printf("expected R3 = NULL,actual R3 = %p\n",R3);
    TreeNode *R4 = RChild(c);
    printf("expected R4 = %p,actual R4 = %p\n",f,R4);
}
//镜像测试
void TestTreeMirror()
{
    Test_Header;
    //创建一棵树
    TreeDataType arr[] = "abd**eg***c*f**";
    TreeNode *root = _CreateTree(arr,sizeof(arr)/sizeof(arr[0]),'*');
    printf("先序遍历结果：");
    TreePreOrder(root);
    printf("中序遍历结果：");
    TreeInOrder(root);
    printf("后序遍历结果：");
    TreePostOrder(root);
    printf("\n");
    TreeMirror(root);
    //TreeMirror2(root);
    printf("调用求镜像函数之后的遍历结果：\n");

    printf("先序遍历结果：");
    TreePreOrder(root);
    printf("中序遍历结果：");
    TreeInOrder(root);
    printf("后序遍历结果：");
    TreePostOrder(root);
    printf("\n");
}
int main()
{
    TestInit();
    TestTraverse();
    TestRebuild();
    TestTreeCreateAndClone();
    TestDestroy();
    TestNodeNumAndHeight();
    TestFind();
    TestParent();
    TestIsCompleteTree();
    TestTreeMirror();
    return 0;
}
