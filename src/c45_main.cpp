#include "c45.h"

int main(int argc, char* argv[]){
        string filename = "source.txt";
        DecisionTree dt ;
        int attr_node = 0;
        TreeNode* treeHead = nullptr;
        set<int> readLineNum;
        vector<int> readClumNum;
        int deep = 0;
        if (dt.get_dataset(filename, readLineNum, readClumNum) == 0)
        {
                dt.create_tree(treeHead, dt.get_state_tree(), dt.get_contents(), readLineNum, readClumNum, deep);
        }
        return 0;
}
