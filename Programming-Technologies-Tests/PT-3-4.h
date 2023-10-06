#pragma once

#include <vector>

#include "PT-1-4.h"

using namespace TASK_1_4;

namespace TASK_3_4
{

	struct TreeNode
	{
		int value;
		int pathsUp;
		int pathsDown;
		TreeNode* left;
		TreeNode* right;

		TreeNode(int value) : 
			left(nullptr), right(nullptr),
			pathsDown(0), pathsUp(0)
		{
			this->value = value;
		}
	};

	class Tree
	{
	public:
		Tree() : _root(nullptr)
		{
		}
		~Tree()
		{
			clear_tree(_root);
		}

		TreeNode* get_root() { return _root; }

		void add(int value)
		{
			TreeNode* newNode = new TreeNode(value);
			if (_root == nullptr)
			{
				_root = newNode;
				return;
			}

			insert_node(_root, newNode);
		}


	private:
		void insert_node(TreeNode* root, TreeNode* node)
		{
			if (root->right == nullptr && root->left == nullptr)
			{
				if (node->value > root->value)
				{
					root->right = node;
				}
				else
				{
					root->left = node;
				}
				return;
			}

			if (node->value > root->value)
			{
				if (root->right == nullptr)
				{
					root->right = node;
					return;
				}
				else
				{
					insert_node(root->right, node);
				}
			}
			else
			{
				if (root->left == nullptr)
				{
					root->left = node;
					return;
				}
				else
				{
					insert_node(root->left, node);
				}
			}
		}

		void clear_tree(TreeNode* node)
		{
			if (node == nullptr)
				return;

			clear_tree(node->right);
			clear_tree(node->left);
			delete node;
		}

		TreeNode* _root;
	};

	TreeNode* MAX_PATH_ROOT = nullptr;
	int MAX_PATH_LENGTH = 0;
	List MAX_TREE_PATH;

	TreeNode* count_path(TreeNode* root)
	{
		if (root->right == nullptr && root->left == nullptr)
		{
			return root;
		}

		if (root->right)
		{
			if (root->value > root->right->value)
			{
				root->pathsUp = count_path(root->right)->pathsUp + 1;
			}
			else
			{
				root->pathsDown = count_path(root->right)->pathsDown + 1;
			}
		}

		if (root->left)
		{
			if (root->value > root->left->value)
			{
				root->pathsUp = max(root->pathsUp, count_path(root->left)->pathsUp + 1);
			}
			else
			{
				root->pathsDown = max(root->pathsDown, count_path(root->left)->pathsDown + 1);
			}
		}

		int currentPathLength = root->pathsUp + 1 + root->pathsDown;
		
		if (currentPathLength > MAX_PATH_LENGTH)
		{
			MAX_PATH_LENGTH = currentPathLength;
			MAX_PATH_ROOT = root;
		}
		
		return root;
	}

	void get_path_down(TreeNode* root)
	{
		MAX_TREE_PATH.push_back(root->value);
		if (root->pathsDown == 0)
		{
			return;
		}

		if (root->left && root->right)
		{
			if (root->left->value > root->value && root->right->value > root->value)
			{
				if (root->left->pathsDown > root->right->pathsDown)
				{
					get_path_down(root->left);
					return;
				}
				else
				{
					get_path_down(root->right);
					return;
				}
			}
			else if (root->left->value > root->value)
			{
				get_path_down(root->left);
				return;
			}
			else
			{
				get_path_down(root->right);
				return;
			}
		}

		if (root->right)
		{
			get_path_down(root->right);
			return;
		}

		if (root->left)
		{
			get_path_down(root->left);
			return;
		}
	}

	void get_path_up(TreeNode* root)
	{
		if (root->pathsUp == 0)
		{
			MAX_TREE_PATH.push_back(root->value);
			return;
		}

		if (root->left && root->right)
		{
			if (root->left->value < root->value && root->right->value < root->value)
			{
				if (root->left->pathsUp > root->right->pathsUp)
				{
					get_path_up(root->left);
					MAX_TREE_PATH.push_back(root->value);
					return;
				}
				else
				{
					get_path_up(root->right);
					MAX_TREE_PATH.push_back(root->value);
					return;
				}
			}
			else if (root->left->value < root->value)
			{
				get_path_up(root->left);
				MAX_TREE_PATH.push_back(root->value);
				return;
			}
			else
			{
				get_path_up(root->right);
				MAX_TREE_PATH.push_back(root->value);
				return;
			}
		}

		if (root->right)
		{
			get_path_up(root->right);
			MAX_TREE_PATH.push_back(root->value);
			return;
		}

		if (root->left)
		{
			get_path_up(root->left);
			MAX_TREE_PATH.push_back(root->value);
			return;
		}
	}

	void get_path(TreeNode* root)
	{
		get_path_up(MAX_PATH_ROOT);
		MAX_TREE_PATH.pop_back();
		get_path_down(MAX_PATH_ROOT);
	}

	void test()
	{
		Tree tree;

		tree.add(7);
		tree.add(17);
		tree.add(30);
		tree.add(28);
		tree.add(40);
		tree.add(5);
		tree.add(1);
		tree.add(16);
	}

	vector<int> get_path(vector<int> input)
	{
		Tree tree;
		for (int value : input)
		{
			tree.add(value);
		}

		count_path(tree.get_root());
		get_path(tree.get_root());

		return list_to_vector(MAX_TREE_PATH);
	}
}