//
// binary_tree.h
//
//      Copyright (c) CJL_sysu. All rights reserved.
//
// A C++ binary tree header.
//
#pragma once
#include<iostream>
#include<vector>
#include<cstring>
#include<string>
#include<queue>
#include<unordered_map>
using namespace std;
#define nulptr 0x80000000
//Definition for a binary tree node.(From Leetcode)
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};
typedef struct TreeNode treenode;
typedef struct TreeNode TreeNode;
//二叉树构造
bool treemake(vector<int> letra, treenode*& root)
{
	root = NULL;
	if (letra.size() == 0)
		return true;
	queue<treenode*> que;
	vector<int>::iterator it = letra.begin();
	if (*it == nulptr)
	{
		if (letra.size() >= 2)
			return false;
		else
			return true;
	}
	root = new treenode;
	root->val = *it;
	que.push(root);
	while (!que.empty())
	{
		int if_stop = 0;
		treenode* cur = que.front();
		que.pop();
		for (int i = 0; i < 2; i++)
		{
			it++;
			if (it == letra.end())
			{
				if_stop = 1;
				break;
			}
			else
			{
				treenode* tnode;
				if (*it != nulptr)
				{
					tnode = new treenode;
					tnode->val = *it;
					que.push(tnode);
				}
				else
					tnode = NULL;
				if (i == 0)
					cur->left = tnode;
				else
					cur->right = tnode;
			}
		}
		if (if_stop)
			break;
	}
	if (!que.empty())
		return true;
	else
	{
		if (it != letra.end())
			it++;
		for (; it != letra.end(); it++)
		{
			if (*it != nulptr)
				return false;
		}
		return true;
	}
}
//将力扣风格的二叉树层序遍历字符串转化为二叉树
//力扣风格的层序遍历字符串格式："[3,9,20,null,null,15,7]"
//起始和结尾需要中括号，用null代替空节点
//参数1：treenode*& root为二叉树头节点，新生成的二叉树会以root为头节点
//参数2：string read为力扣风格的层序遍历字符串
//生成成功则返回true,否则返回false
bool readtree(treenode*& root, string read)
{
	int slen = read.size();
	if (read[0] != '[' || read[slen - 1] != ']')
		return false;
	string temp = "";
	vector<int> letra;
	for (int i = 1; i < slen; i++)
	{
		if (read[i] != ',' && read[i] != ']')
		{
			temp += read[i];
		}
		else
		{
			if (temp == "null")
			{
				letra.emplace_back(nulptr);
			}
			else if (temp.size() != 0)
			{
				int num = stoi(temp);
				letra.emplace_back(num);
			}
			temp = "";
		}
	}
	return treemake(letra, root);
}
//此处分开
//二叉树打印
int tree_depth;
void count_tree_depth(treenode* node, int deep)
{
	tree_depth = deep > tree_depth ? deep : tree_depth;
	if (node->left != NULL)
		count_tree_depth(node->left, deep + 1);
	if (node->right != NULL)
		count_tree_depth(node->right, deep + 1);
}
//在控制台上打印出二叉树
//参数1：treenode* root  待打印二叉树的头节点
void printtree(treenode* root)
{
	//确定二叉树深度
	tree_depth = -1;
	if (root != NULL)
		count_tree_depth(root, tree_depth + 1);
	else
	{
		cout << "****" << endl << "NULL" << endl << "****" << endl;
		return;
	}
	//层序遍历二叉树
	vector<vector<pair<int, int>>> node;
	node.resize(tree_depth + 1);
	queue<pair<treenode*, int>> lque;
	lque.push(make_pair(root, 0));
	treenode* Nuptr = NULL;
	while (1)
	{
		treenode* cur = lque.front().first;
		int floor = lque.front().second;
		if (floor == tree_depth + 1)
			break;
		lque.pop();
		if (cur == NULL)
		{
			lque.push(make_pair(Nuptr, floor + 1));
			lque.push(make_pair(Nuptr, floor + 1));
			node[floor].emplace_back(make_pair(nulptr, 0));
			continue;
		}
		if (cur->left != NULL)
			lque.push(make_pair(cur->left, floor + 1));
		else
			lque.push(make_pair(Nuptr, floor + 1));
		if (cur->right != NULL)
			lque.push(make_pair(cur->right, floor + 1));
		else
			lque.push(make_pair(Nuptr, floor + 1));
		node[floor].emplace_back(make_pair(cur->val, 0));
	}
	//构造最后一列
	unordered_map<int, vector< pair<int, int>>> hash;
	vector<pair<int, int>>::iterator it1;
	for (it1 = node[tree_depth].begin(); it1 != node[tree_depth].end(); it1++)
	{
		int num1 = it1 - node[tree_depth].begin() + 1;
		if (num1 % 2 == 1)
		{
			hash[(3 * num1 - 1) / 2].emplace_back(make_pair((*it1).first, tree_depth));
			(*it1).second = (3 * num1 - 1) / 2;
		}
		else
		{
			hash[(3 * num1) / 2].emplace_back(make_pair((*it1).first, tree_depth));
			(*it1).second = (3 * num1) / 2;
		}
	}
	it1--;
	int maxline = (*it1).second;
	//构造其余列
	vector<pair<int, int>>::iterator it2;
	for (int i = tree_depth - 1; i >= 0; i--)
	{
		it1 = node[i + 1].begin();
		it2 = node[i].begin();
		while (it1 != node[i + 1].end())
		{
			int line1 = (*it1).second;
			it1++;
			int line2 = (*it1).second;
			it1++;
			if (it2 - node[i].begin() < node[i].size() / 2)//向上取整
				(*it2).second = (line1 + line2 + 1) / 2;
			else//向下取整
				(*it2).second = (line1 + line2) / 2;
			hash[(*it2).second].emplace_back(make_pair((*it2).first, i));
			it2++;
		}
	}
	cout << "***************" << endl;
	for (int i = maxline; i >= 1; i--)
	{
		vector<pair<int, int>> vep = hash[i];
		int col = 0;
		int vsize = vep.size();
		for (int k = vsize - 1; k >= 0; k--)
		{
			for (; col < vep[k].second; col++)
				cout << "\t";
			if (vep[k].first != nulptr)
				cout << vep[k].first;
			else
				cout << "NULL";
		}
		cout << endl;
	}
	cout << "***************" << endl;
}
