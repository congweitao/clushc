#include "c45.hpp"

int DecisionTree::get_dataset(string filename, set<int>& read_line_num, vector<int>& read_colum_num)
{
	ifstream read(filename.c_str());
	string itemline = "";
	getline(read, itemline);
	istringstream iss(itemline);
	string attr = "";
	while(iss >> attr)
	{
		attributes* s_attr = new attributes();
		s_attr->attribute_name = attr;
		// init attributes 
		state_tree.push_back(s_attr);
		// init attributes' mapping
		attribute_colum[attr] = attribute_num;
		attribute_num++;
		// init avaiable attributes
		read_colum_num.push_back(0);
		s_attr = nullptr;
	}

	int i  = 0;
	// add values
	while(true)
	{
		getline(read, itemline);
		if(itemline == "" || itemline.length() <= 1)
		{
			break;
		}
		vector<string> infoline;
		istringstream stream(itemline);
		string item = "";
		while(stream >> item)
		{
			infoline.push_back(item);
		}

		contents.push_back(infoline);
		read_line_num.insert(i);
		i++;
	}
	read.close();
	return 0;
}

int DecisionTree::get_data(vector<vector<string>>& contents, vector<attributes*>& state_tree, 
							set<int>& read_line, vector<int>& read_colum_num)
{
	// counts of yes
	int decision_num = 0;
	// statics of each line
	set<int>::iterator iter_end = read_line.end();
	for (set<int>::iterator line_iter = read_line.begin(); line_iter != iter_end; ++line_iter)
	{
		bool decision_line = false;
		if (contents[*line_iter][attribute_num - 1] == "yes")
		{
			decision_line = true;
			decision_num++; 	
		}
		
		for (int i = 0; i < attribute_num - 1; i++)
		{
			if (read_colum_num[i] == 0)
			{
				std::string tempitem = contents[*line_iter][i];
				auto map_iter = state_tree[i]->attributeItem.find(tempitem);
				// no found
				if (map_iter == (state_tree[i]->attributeItem).end())
				{
					// New
					attribute_item* attributeItem = new attribute_item();
					attributeItem->item_num.push_back(1);
					decision_line ? attributeItem->item_num.push_back(1) : attributeItem->item_num.push_back(0);
					attributeItem->item_line.insert(*line_iter);
					// create attribute name ->item
					(state_tree[i]->attributeItem)[tempitem] = attributeItem;
					attributeItem = nullptr;
				}
				else
				{
					(map_iter->second)->item_num[0]++;
					(map_iter->second)->item_line.insert(*line_iter);
					if(decision_line)
					{
						(map_iter->second)->item_num[1]++;
					}
				}
			}
		}
	}
	return decision_num;
}

void DecisionTree::create_tree(TreeNode* tree_head, vector<attributes*>& state_tree, vector<vector<string>>& contents, 
							 set<int>& read_line, vector<int>& read_colum_num, int deep)
{
	if (read_line.size() != 0)
	{
		string tree_line = "";
		for (int i = 0; i < deep; i++)
		{
			tree_line += "--";
		}
		reset_state_tree(state_tree, read_colum_num);
		int decision_num = get_data(get_contents(), state_tree, read_line, read_colum_num);
		int line_num = read_line.size();
		int attribute_node = compute_c45(state_tree, decision_num, line_num, read_colum_num);
		read_colum_num[attribute_node] = 1;
		TreeNode* root = new TreeNode();
		root->m_sAttribute = state_tree[attribute_node]->attribute_name;
		root->m_iDeciNum = decision_num;
		root->m_iUnDecinum = line_num - decision_num;
		if (tree_head == nullptr)
		{
			tree_head = root; 
		}
		else
		{
			tree_head->m_vChildren.push_back(root);
		}
		cout << "节点-"<< tree_line << ">" << state_tree[attribute_node]->attribute_name << " " << decision_num << " " << line_num - decision_num << endl;
		
		for(map<string, attribute_item*>::iterator map_iterator = state_tree[attribute_node]->attributeItem.begin();
			map_iterator != state_tree[attribute_node]->attributeItem.end(); ++map_iterator)
		{
			int sum = map_iterator->second->item_num[0];
			int decision_num = map_iterator->second->item_num[1];
			cout << "分支--"<< tree_line << ">" << map_iterator->first << endl;
			if (decision_num != 0 && sum != decision_num )
			{
				set<int> newReadLineNum = map_iterator->second->item_line;
				create_tree(root, state_tree, contents, newReadLineNum, read_colum_num, deep + 1);
			}
			else
			{
				TreeNode* child = new TreeNode();
				child->m_sAttribute = state_tree[attribute_node]->attribute_name;
				child->m_iDeciNum = decision_num;
				child->m_iUnDecinum = sum - decision_num;
				root->m_vChildren.push_back(child);
				if (decision_num == 0)
				{
					cout << "叶子---"<< tree_line << ">no" << " " << sum << endl;
				}
				else
				{
					cout << "叶子---"<< tree_line << ">yes" << " " << decision_num <<endl;
				}
			}
		}
		read_colum_num[attribute_node] = 0;
	}
}

int DecisionTree::compute_c45(vector<attributes*>& stat_tree, int decision_num, int line_num, vector<int>& read_colum_num)
{
	double max_temp = 0;
	int max_attribute = 0;
	
	double entropy_S = compute_entropy_S(decision_num, line_num);
	for (int i = 0; i < attribute_num - 1; i++)
	{
		if (read_colum_num[i] == 0)
		{
			double split_info = 0.0;
			//info
			double info_temp = compute_entropy_A(stat_tree[i]->attributeItem, split_info, line_num);
			state_tree[i]->state_result.push_back(info_temp);
			//gain
			double gain_temp = entropy_S - info_temp;
			state_tree[i]->state_result.push_back(gain_temp);
			//split_info
			state_tree[i]->state_result.push_back(split_info);
			//gain_info
			double temp = gain_temp / split_info;
			state_tree[i]->state_result.push_back(temp);
			if (temp > max_temp)
			{
				max_temp = temp;
				max_attribute = i;
			}
		}
	}
	return max_attribute;
}

double DecisionTree::compute_entropy_S(int decision_num, int sum)
{
	double pi = (double)decision_num / (double)sum;
	double result = 0.0;
	if (pi == 1.0 || pi == 0.0)
	{
		return result;
	}
	result = pi * (log(pi) / log((double)2)) + (1 - pi)*(log(1 - pi)/log((double)2));
	return -result;
}

double DecisionTree::compute_entropy_A(map<string, attribute_item*>& attributeItem, double& split_info, int line_num)
{
	double result = 0.0;
	for (map<string, attribute_item*>::iterator item = attributeItem.begin();
		 item != attributeItem.end();
		 ++item
		)
	{
		 double pi = (double)(item->second->item_num[0]) / (double)line_num;
		 split_info += pi * (log(pi) / log((double)2));
		 double sub_attr = compute_entropy_S(item->second->item_num[1], item->second->item_num[0]);
		 result += pi * sub_attr;
	}
	split_info = -split_info;
	return result;
}

void DecisionTree::reset_state_tree(vector<attributes*>& state_tree, vector<int>& read_colum_num)
{
	for (int i = 0; i < read_colum_num.size() - 1; i++)
	{
		if (read_colum_num[i] == 0)
		{
			map<string, attribute_item*>::iterator it_end = state_tree[i]->attributeItem.end();
			for (map<string, attribute_item*>::iterator it = state_tree[i]->attributeItem.begin();
				it != it_end; it++)
			{
				delete it->second;
			}
			state_tree[i]->attributeItem.clear();
			state_tree[i]->state_result.clear();
		}
	}
}
