#include "decision_tree.h"

int main(int argc, char* argv[]){
        string filename = "source.txt";
        DecisionTree dt ;
        int attr_node = 0;
        TreeNode* treeHead = nullptr;
        set<int> readLineNum;
        vector<int> readClumNum;
        int deep = 0;
        if (dt.pretreatment(filename, readLineNum, readClumNum) == 0)
        {
                dt.CreatTree(treeHead, dt.getStatTree(), dt.getInfos(), readLineNum, readClumNum, deep);
        }
        return 0;
}
