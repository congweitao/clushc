<<<<<<< HEAD
#include "tree.hpp"
=======
#include "tree.h"
>>>>>>> ab146f55d50ec0d3d3e59807ea24af00d71b348f

TreeNode* CreateTreeNode(string value)
{
	TreeNode* pNode = new TreeNode();
	pNode->m_sAttribute = value;
	return pNode;
}

bool FindNode(TreeNode* pRoot, std::string& item)
{

    if(pRoot->m_sAttribute == item)
        return true;
 
    bool found = false;

    vector<TreeNode*>::iterator i = pRoot->m_vChildren.begin();
    while(!found && i < pRoot->m_vChildren.end())
    {
        found = FindNode(*i, item);
        ++i;
    }
 
    return found;
}

void ConnectTreeNodes(TreeNode* pParent, TreeNode* pChild)
{
	if(pParent != NULL)
	{
		pParent->m_vChildren.push_back(pChild);
	}
}

void PrintTreeNode(TreeNode* pNode)
{
	if(pNode != NULL)
	{
		cout<<"value of this node is:"<<pNode->m_sAttribute<<"\n"<<endl;
		cout<<"its children is as the following:\n"<<endl;
		std::vector<TreeNode*>::iterator i = pNode->m_vChildren.begin();
		while(i < pNode->m_vChildren.end())
		{
			if(*i != NULL)
				cout<<(*i)->m_sAttribute<<"\t";
			++i;
		}
		cout<<"\n"<<endl;
	}
	else
	{
		cout<<"this node is null.\n"<<endl;
	}

	cout<<"\n"<<endl;
}

void PrintTree(TreeNode* pRoot)
{
	PrintTreeNode(pRoot);

	if(pRoot != NULL)
	{
		std::vector<TreeNode*>::iterator i = pRoot->m_vChildren.begin();
		while(i < pRoot->m_vChildren.end())
		{
			PrintTree(*i);
			++i;
		}
	}
}

void DestroyTree(TreeNode* pRoot)
{
	if(pRoot != NULL)
	{
		std::vector<TreeNode*>::iterator i = pRoot->m_vChildren.begin();
		while(i < pRoot->m_vChildren.end())
		{
			DestroyTree(*i);
			++i;
		}
		delete pRoot;
	}
}
