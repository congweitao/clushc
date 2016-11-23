#pragma once
#ifndef _DECISION_TREE_H_
#define _DECISION_TREE_H_
#include <string>
#include <vector>
#include <set>
#include <ctime> 
#include <algorithm>
#include <cmath>

using namespace std;

//the data structure for a tuple
struct TupleData
{
	vector<int> A;
	char label;
};

struct TreeNode
{
	int attrNum;	
	int attr;	
	char label;
};

struct DecisionTree
{
	TreeNode node;
	vector<DecisionTree*> childs;
};

void init(char * trainname, char * testname);
int read_data(vector<TupleData> &data, const char* fileName);
int string_to_int(string s);
void sub_init();
void calculate_arrt_num();
void calculate_attributes();
void random_select_data(vector<TupleData> &data, vector<TupleData> &subdata);
double compute_entropy(double p, double s);
int create_classifier(DecisionTree *&p, const vector<TupleData> &samples, vector<int> &attributes);
int best_gain_arrt(const vector<TupleData> &samples, vector<int> &attributes);
bool all_the_same(const vector<TupleData> &samples, char ch);
char majority_class(const vector<TupleData> &samples);
void random_select_attr(vector<int> &data, vector<int> &subdata);
char test_classifier(DecisionTree *p, TupleData d);
void test_data();
void free_classifier(DecisionTree *p);
void free_arrt_num();
void show_result();

#endif //_RANDOM_FOREST_H_
