#include <iostream>
#include <fstream>
#include <sstream>
#include "random_forest.h"

using namespace std;

vector<DecisionTree*> alltrees;

vector<TupleData> trainAll,
	          train,			
		  test;			

vector<int>   attributes;	
ifstream      fin;
			
int trainAllNum=0;														
int testAllNum=0;								
int MaxAttr;														
int *ArrtNum;
unsigned int F;
int tree_num=100;
const int leafattrnum=-1;
int TP=0,
	FN=0,
	FP=0,
	TN=0,
	TestP=0,
	TestN=0;

void init(char * trainname, char * testname)
{
	trainAllNum=read_data(trainAll, trainname);
	testAllNum=read_data(test, testname);
	calculate_attributes();
	double temp=(double)trainAllNum;
	temp=log(temp)/log(2.0);
	F=round(temp)+1;
	if(F>MaxAttr) F=MaxAttr;
	//cout<<"f="<<F<<endl;
}

void sub_init()
{
	random_select_data(trainAll, train);
	calculate_arrt_num();
}


int read_data(vector<TupleData> &data, const char* fileName)
{
	fin.open(fileName);
	string line;
	
	int datanum=0;
	
	while(getline(fin,line))
	{
		TupleData d;
        istringstream stream(line);
        string str;
		while(stream>>str)
		{
			if(str.find('+')==0)
			{
				d.label='+';
			}
			else if(str.find('-')==0)
			{
				 d.label='-';
			}
			else
			{
				int j=string_to_int(str);
				d.A.push_back(j);
			}
		}
		
		data.push_back(d);	
		datanum++;
	}
	
	fin.close();
	return datanum;
}

void random_select_data(vector<TupleData> &data, vector<TupleData> &subdata)
{
	int index;
	subdata.clear();
	int d=0;
	while (d < trainAllNum)
	{
		index = rand() % trainAllNum;
		subdata.push_back(data.at(index));
		d++;
	}
}

void calculate_attributes()
{
	TupleData d=trainAll.at(0);
	MaxAttr=d.A.size();
	attributes.clear();
	
	for (int i = 0; i < MaxAttr; i++)
	{
		attributes.push_back(i);
	}
	
	ArrtNum=new int[MaxAttr];
}
	

int string_to_int(string s)
{
	int sum=0;
	for(int i=0; s[i]!='\0';i++)
	{
		int j=int(s[i])-48;
		sum=sum*10+j;
	}
	return sum;
}

void calculate_arrt_num()
{
	for(int i=0; i<MaxAttr;i++) ArrtNum[i]=0;
	for (vector<TupleData>::const_iterator it = train.begin(); it != train.end(); it++)	
	{
		int i=0;
		for (vector<int>::const_iterator intt=(*it).A.begin(); intt!=(*it).A.end();intt++)
		{
			int valuemax=(*intt)+1;   //(*it).A.at(i)???
			if(valuemax>ArrtNum[i]) ArrtNum[i]=valuemax;
			i++;
		}
	}
}


double compute_entropy(double p, double s)
{
	double n = s - p;
	double result = 0;
	if (n != 0)
		result += - double(n) / s * log(double(n) / s) / log(2.0);
	if (p != 0)
		result += double(-p) / s * log(double(p) / s) / log(2.0);
	return result;
}

int create_classifier(DecisionTree *&p, const vector<TupleData> &samples, vector<int> &attributes)
{
	if (p == NULL)
		p = new DecisionTree();
	if (all_the_same(samples, '+'))
	{
		p->node.label = '+';
		p->node.attrNum = leafattrnum;
		p->childs.clear();
		return 1;
	}
	if (all_the_same(samples, '-'))
	{
		p->node.label = '-';
		p->node.attrNum = leafattrnum;
		p->childs.clear();
		return 1;
	}
	if (attributes.size() == 0)
	{
		p->node.label = majority_class(samples);
		p->node.attrNum = leafattrnum;
		p->childs.clear();
		return 1;
	}
	p->node.attrNum = best_gain_arrt(samples, attributes);

	p->node.label = ' ';
	
	vector<int> newAttributes;
	for (vector<int>::iterator it = attributes.begin(); it != attributes.end(); it++)
		if ((*it) != p->node.attrNum)
			newAttributes.push_back((*it));

	int maxvalue=ArrtNum[p->node.attrNum];
	vector<TupleData> subSamples[maxvalue];
	for (int i = 0; i < maxvalue; i++)
		subSamples[i].clear();

	for (vector<TupleData>::const_iterator it = samples.begin(); it != samples.end(); it++)
	{
		subSamples[(*it).A.at(p->node.attrNum)].push_back((*it));
	}

	DecisionTree *child;
	for (int i = 0; i < maxvalue; i++)
	{
		child = new DecisionTree;
		child->node.attr = i;
		if (subSamples[i].size() == 0)
			child->node.label = majority_class(samples);
		else
			create_classifier(child, subSamples[i], newAttributes);
		p->childs.push_back(child);
	}
	return 0;
}

int best_gain_arrt(const vector<TupleData> &samples, vector<int> &attributes)
{
	int attr, 
		bestAttr = 0,
		p = 0,
		s = (int)samples.size();
		
	for (vector<TupleData>::const_iterator it = samples.begin(); it != samples.end(); it++)
	{
		if ((*it).label == '+')
			p++;
	}
	
	double infoD;
	double bestResult = 0;
	infoD=compute_entropy(p, s);
	
	vector<int> m_attributes;
	random_select_attr(attributes, m_attributes);
	
	for (vector<int>::iterator it = m_attributes.begin(); it != m_attributes.end(); it++)
	{
		attr = (*it);
		double result = infoD;
		
		int maxvalue=ArrtNum[attr];
		int subN[maxvalue], subP[maxvalue], sub[maxvalue];
		for (int i = 0; i < maxvalue; i++)
		{
			subN[i] = 0;
			subP[i] = 0;
			sub[i]=0;
		}
		for (vector<TupleData>::const_iterator jt = samples.begin(); jt != samples.end(); jt++)
		{
			if ((*jt).label == '+')
				subP[(*jt).A.at(attr)] ++;
			else
				subN[(*jt).A.at(attr)] ++;
			sub[(*jt).A.at(attr)]++;
		}
		
		double SplitInfo=0;
		for(int i=0; i<maxvalue; i++)
		{
			double partsplitinfo;
			partsplitinfo=-double(sub[i])/s*log(double(sub[i])/s)/log(2.0);
			SplitInfo=SplitInfo+partsplitinfo;
		}
		
		double infoattr=0;
		for (int i = 0; i < maxvalue; i++)
		{
			double partentropy;
			partentropy=compute_entropy(subP[i], subP[i] + subN[i]);
			infoattr=infoattr+((double)(subP[i] + subN[i])/(double)(s))*partentropy;
		}
		result=result-infoattr;
		result=result/SplitInfo;
		
		if (result > bestResult)
		{
			bestResult = result;
			bestAttr = attr;
		}
	}

	if (bestResult == 0)
	{
		bestAttr=attributes.at(0);
	}
	return bestAttr;
}

void random_select_attr(vector<int> &data, vector<int> &subdata)
{
	int index;
	unsigned int dataNum=data.size();
	subdata.clear();
	if(dataNum<=F)
	{
		for (vector<int>::iterator it = data.begin(); it != data.end(); it++)
		{
			int attr = (*it);
			subdata.push_back(attr);
		}
	}
	else
	{
		set<int> AttrSet;
		AttrSet.clear();
		while (AttrSet.size() < F)
		{
			index = rand() % dataNum;
			if (AttrSet.count(index) == 0)
			{
				AttrSet.insert(index);
				subdata.push_back(data.at(index));
			}
		}
	}
}

bool all_the_same(const vector<TupleData> &samples, char ch)
{
	for (vector<TupleData>::const_iterator it = samples.begin(); it != samples.end(); it++)
		if ((*it).label != ch)
			return false;
	return true;
}

char majority_class(const vector<TupleData> &samples)
{
	int p = 0, n = 0;
	for (vector<TupleData>::const_iterator it = samples.begin(); it != samples.end(); it++)
		if ((*it).label == '+')
			p++;
		else
			n++;
	if (p >= n)
		return '+';
	else
		return '-';
}

char test_classifier(DecisionTree *p, TupleData d)
{
	if (p->node.label != ' ')
		return p->node.label;
	int attrNum = p->node.attrNum;
	if (d.A.at(attrNum) < 0)
		return ' ';
	return test_classifier(p->childs.at(d.A.at(attrNum)), d);
}

void test_data()
{
	for (vector<TupleData>::iterator it = test.begin(); it != test.end(); it++)
	{
		if((*it).label=='+') TestP++;
		else TestN++;
		
		int p=0, n=0;
		for(int i=0;i<tree_num;i++)
		{
			if(test_classifier(alltrees.at(i), (*it))=='+')  p++;
			else n++;
		}
		
		if(p>n)
		{
			if((*it).label=='+') TP++;
			else FP++;
		}
		else
		{
			if((*it).label=='+') FN++;
			else TN++;
		}
	}
}


void free_classifier(DecisionTree *p)
{
	if (p == NULL)
		return;
	for (vector<DecisionTree*>::iterator it = p->childs.begin(); it != p->childs.end(); it++)
	{
		free_classifier(*it);
	}
	delete p;
}

void free_arrt_num()
{
	delete[] ArrtNum;
}

void show_result()
{
	cout<<"Train size:	"<< trainAllNum<<endl;
	cout<<"Test size:	"<<testAllNum<<endl;														
	cout << "True positive:	" << TP << endl;
	cout << "False negative:	"<< FN<<endl;
	cout << "False positive:	"<<FP<<endl;
	cout << "True negative:	"<<TN<<endl;
}

int main(int argc, char **argv)
{
	char * trainfile=argv[1];
	char * testfile=argv[2];
	
	//cout<<"input the F and tree_num"<<endl;
	//cin>>F>>tree_num;
	
	srand((unsigned)time(NULL)); 
	
	init(trainfile, testfile);
	
	for(int i=0; i<tree_num; i++)
	{
		sub_init();
		DecisionTree * root=NULL;
		create_classifier(root, train, attributes);
		alltrees.push_back(root);
	}

	test_data();
	
	for (vector<DecisionTree *>::const_iterator it = alltrees.begin(); it != alltrees.end(); it++)
	{
		free_classifier((*it));
	}
		
	free_arrt_num();
	
	show_result();
	return 0;
}
