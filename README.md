# cpp-binary-tree-construction-and-visualization
# 二叉树的构建和可视化

__CJLsysu__

[CSDN链接](https://blog.csdn.net/m0_73571517/article/details/128677617)

制作初衷：在leetcode刷二叉树题目时很难本地运行和调试

原因在于力扣平台实现了 二叉树的层序遍历字符串转二叉树的功能 和 二叉树可视化的功能 ，而本地编译器没有相关功能

在本地编译器添加这个头文件，可以实现二叉树的构建和可视化，这样可以方便力扣代码的本地运行和调试

使用方法：包含头文件`binary_tree.hpp`

## 二叉树构造函数

`bool readtree(treenode*& root, string read)`

将力扣风格的二叉树层序遍历字符串转化为二叉树

力扣风格的层序遍历字符串格式：`"[3,9,20,null,null,15,7]"`

起始和结尾需要中括号，用null代替空节点

参数1：`treenode*& root`为二叉树头节点，新生成的二叉树会以root为头节点

参数2：`string read`为力扣风格的层序遍历字符串

生成成功则返回true,否则返回false


## 二叉树打印函数

`void printtree(treenode* root)`

在控制台上打印出二叉树

参数1：`treenode* root`  待打印二叉树的头节点

## 使用示例

```cpp
#include"binary_tree.hpp"
int main()
{
	string read = "[3,1,8,null,9,4,5,9,2,0,12,null,null,4]";
	treenode* root;
	if (readtree(root, read))
	{
		cout << "二叉树生成成功" << endl;
		printtree(root);
	}
	else
		cout << "二叉树生成失败" << endl;
}
```

控制台:

```
二叉树生成成功
***************
                                NULL
                        NULL
                                NULL
                5               NULL
                        NULL
                                NULL
        8                       NULL
                        12
                                NULL
                4               NULL
                        0
                                NULL
3                               NULL
                        2
                9               NULL
                                NULL
                        9
        1                       4
                                NULL
                        NULL
                NULL            NULL
                                NULL
                        NULL
                                NULL
***************
```

