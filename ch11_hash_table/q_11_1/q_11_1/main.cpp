/*
 Q 11.1.4
 We wish to implement a dictionary by using direct addressing on a huge array. At
 the start, the array entries may contain garbage, and initializing the entire array
 is impractical because of its size. Describe a scheme for implementing a directaddress
 dictionary on a huge array. Each stored object should use O.1/ space;
 the operations SEARCH, INSERT, and DELETE should take O.1/ time each; and
 initializing the data structure should take O.1/ time. (Hint: Use an additional array,
 treated somewhat like a stack whose size is the number of keys actually stored in
 the dictionary, to help determine whether a given entry in the huge array is valid or
 not.)
------------------------------------------------------------*/

#include "iostream"
using namespace std;

#define MAIN_ARRAY_SIZE (10*1000*1000)
#define ASIS_ARRAY_SIZE 1000

class Strange_Array
{
public:
	Strange_Array() { top = 0; };
	bool INSERT(int key, int v);
	bool SEARCH(int key, int &v);
	bool DELETE(int key);

private:
	int top;
	int main_ary[MAIN_ARRAY_SIZE];
	int asis_ary_1[ASIS_ARRAY_SIZE];
	int asis_ary_2[ASIS_ARRAY_SIZE];
};

bool Strange_Array::INSERT(int key, int v)
{
	if (key >= 0 && key < MAIN_ARRAY_SIZE)
	{
		if (top < ASIS_ARRAY_SIZE)
		{
			asis_ary_1[top] = key;
			asis_ary_2[top] = v;
			main_ary[key] = top;
			top++;
		}
		else
		{
			cout << "No enough memeory in assistant array" << endl;
		}

		return true;
	}
	else
	{
		cout << "key=" << key << " exceed range " << MAIN_ARRAY_SIZE << endl;
		return false;
	}
}

bool Strange_Array::SEARCH(int key, int &v)
{
	if (key >= 0 && key < MAIN_ARRAY_SIZE)
	{
		if (main_ary[key] > 0 && main_ary[key] < top)
		{
			int cur_top = main_ary[key];

			if (asis_ary_1[cur_top] == key)
			{
				v = asis_ary_2[cur_top];
				return true;
			}
			else
			{
				cout << "No valid data found" << endl;
				return false;
			}
		}
		else
		{
			cout << "No valid data found" << endl;
			return false;
		}
	}
	else
	{
		cout << "key=" << key << " exceed range " << MAIN_ARRAY_SIZE << endl;
		return false;
	}
}

bool Strange_Array::DELETE(int key)
{
	if (key >= 0 && key < MAIN_ARRAY_SIZE)
	{
		if (main_ary[key] > 0 && main_ary[key] < top)
		{
			int cur_top = main_ary[key];

			if (asis_ary_1[cur_top] == key)
			{
				int global_top = top - 1;

				asis_ary_1[cur_top] = asis_ary_1[global_top];
				asis_ary_2[cur_top] = asis_ary_2[global_top];
				main_ary[key] = global_top;

				top = global_top;

				return true;
			}
			else
			{
				cout << "No valid data found" << endl;
				return false;
			}
		}
		else
		{
			cout << "No valid data found" << endl;
			return false;
		}
	}
	else
	{
		cout << "key=" << key << " exceed range " << MAIN_ARRAY_SIZE << endl;
		return false;
	}
}

int main()
{
	Strange_Array* a = new Strange_Array;

	for (int i = 0; i < 100; i++)
	{
		unsigned int d = rand();
		unsigned int k = d % MAIN_ARRAY_SIZE;
		unsigned int v = d;

		a->INSERT(k, v);
	}

	return 0;
}