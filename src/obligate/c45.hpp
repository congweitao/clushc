#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

#include "tree.hpp"
using namespace std;


class DecisionTree {
private:

	struct attribute_item 
	{
	    vector<int> item_num;
	    set<int>    item_line; 
	};

       struct attributes
        {
                string attribute_name;
                vector<double> state_result;
                map<string, attribute_item*> attributeItem;
        };

        vector<attributes*> state_tree;
        int attribute_num;
        vector< vector<string> > contents;
        map<string, int> attribute_colum;

public:

	DecisionTree(){
                attribute_num = 0;
        }
        vector< vector<string> >& get_contents()
        {
                return contents;
        }
        vector<attributes*>& get_state_tree()
        {
                return state_tree;
        }
        int get_dataset(string filename, set<int>& read_line_num, vector<int>& read_colum_num);
        int get_data(vector <vector <string> >& contents, vector<attributes*>& state_tree,
                                        set<int>& read_line, vector<int>& read_colum_num);	
         
	double compute_entropy_S(int descision_num, int sum);
	void   reset_state_tree(vector<attributes*>& state_tree, vector<int>& read_coloum_num);
	double compute_entropy_A(map<string, attribute_item*>& attribute_item, double& split_info, int line_num);
	int    compute_c45(vector<attributes*>& state_tree, int decision_num, int line_num, vector<int>& read_colum_num);
	void   create_tree(TreeNode* tree_head, vector<attributes*>& state_tree, vector< vector<string> >& contents,
                                  set<int>& read_line, vector<int>& read_colum_num, int deep);
};
