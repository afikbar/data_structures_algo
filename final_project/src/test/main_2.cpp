#include <iostream>
#include <string>
#include <climits>
#include <cstdlib>
#include "BalancedTreeK.h"

#define MAX_KEY 3.0
#define MIN_KEY -1.0

#define CHECK_SIZE 113
#define INITIAL_INSERT_NUM 70
#define INITIAL_DELETED_SIZE 50
#define OPERATIONS_SIZE 150
#define VALUES_LENGTH 10
#define SEED 22568

#define NUM_OF_OPERATIONS 6
#define INSERT 1
#define DELETE 2
#define SEARCH 3
#define RANK 4
#define SELECT 5
#define GETMAXVALUE 6


using namespace std;

class MyKey :public Key
{
public:
	MyKey(double k) : key(k) {}
	MyKey(MyKey const &mk) :key(mk.key) {}
	~MyKey() {}
	MyKey* clone() const
	{
		return new MyKey(*this);
	}
	bool operator<(const Key &rhs) const { return key <((MyKey&)rhs).key; }
	void print() const { cout << key; }
private:
	double key;
};


class MyValue : public Value
{
public:
	MyValue(string val) : value(val) {}
	MyValue(MyValue const &v) { value = v.value; }
	~MyValue() {}
	MyValue* clone() const
	{
		return new MyValue(*this);
	}
	bool operator<(const Value &rhs) const { return value <((MyValue&)rhs).value; }
	void print() const { cout << value; }
private:
	string value;
};

string generate_random_string(const unsigned len)
/*returns a random string of length len*/
{
	const char alphanum[] ="abcdefghijklmnopqrstuvwxyz";
	string s;
	for (int i = 0; i < len; ++i) {
		s =s+alphanum[rand() % (sizeof(alphanum) - 1)];
	}
	return s;
}

unsigned generate_random_index(const unsigned max_ind)
/*generate random number in range [0,max_ind-1]*/
{
	return rand() % max_ind;
}

void operation_execution(unsigned operation, MyKey* my_keys_array[], MyValue* my_values_array[], bool inserted_keys[], BalancedTreeK* T)
{
	MyValue* val = NULL;
	MyKey* key = NULL;
	MyKey* key1 = NULL;
	unsigned rank;
	unsigned index;
	double new_key;
	bool delete_keys=false;

	switch (operation)
	{
	case INSERT:
		index = generate_random_index(CHECK_SIZE);
		if (inserted_keys[index]==false)
		{
			T->Insert(my_keys_array[index], my_values_array[index]);
			inserted_keys[index]=true;
		}
		break;
	case DELETE:
		index = generate_random_index(CHECK_SIZE);
		T->Delete(my_keys_array[index]);
		inserted_keys[index] = false;
		break;
	case SEARCH:
		index = generate_random_index(CHECK_SIZE);
		key = my_keys_array[index];
		val = (MyValue*)T->Search(key);
		cout << "Search for key: ";
		key->print();
		cout << ", resulted in value: ";
		if (val != NULL)
		{
			val->print();
		}
		else
		{
			cout << "NULL";
		}
		cout << "\n";
		break;
	case RANK:
		index = generate_random_index(CHECK_SIZE);
		key = my_keys_array[index];
		rank = T->Rank(key);
		cout << "Rank for key: ";
		key->print();
		cout << ", resulted in: ";
		cout << rank << "\n";
		break;
	case SELECT:
		index = generate_random_index(CHECK_SIZE);
		key = (MyKey*)T->Select(index);
		cout << "Select for index: " << index;
		cout << ", resulted in key: ";
		if (key != NULL)
		{
			key->print();
		}
		else
		{
			cout << "NULL";
		}
		cout << "\n";
		break;
	case GETMAXVALUE:
		index = generate_random_index(2);
		if (index == 0)
		{
			key = my_keys_array[generate_random_index(CHECK_SIZE)];
			key1 = my_keys_array[generate_random_index(CHECK_SIZE)];
		}
		else
		{
			new_key = (double) rand() / RAND_MAX;
			key = new MyKey(new_key);
			key1 = new MyKey(new_key + (double) rand() / RAND_MAX);
			delete_keys = true;
		}
		val = (MyValue*)T->GetMaxValue(key, key1);
		cout << "GetMaxValue for interval [";
		key->print();
		cout << ",";
		key1->print();
		cout << "]";
		cout << ", resulted in value: ";
		if (val != NULL)
		{
			val->print();
		}
		else
		{
			cout << "NULL";
		}
		cout << "\n";
		if (delete_keys)
		{
			delete key;
			delete key1;
			delete_keys = false;
		}
		break;
	}
}

int main()
{
	srand(SEED);
	MyKey* max_key = new MyKey(MAX_KEY);
	MyKey* min_key = new MyKey(MIN_KEY);
	bool inserted_keys[CHECK_SIZE];
	BalancedTreeK* T = new BalancedTreeK(min_key,max_key);

	double keys_array[CHECK_SIZE];
	string values_array[CHECK_SIZE];

	MyKey* my_keys_array[CHECK_SIZE];
	MyValue* my_values_array[CHECK_SIZE];
	
	for (unsigned i = 0;i < CHECK_SIZE;i++)
	{
		inserted_keys[i] = false;
		keys_array[i] = (double) rand()/RAND_MAX;
		values_array[i] = generate_random_string(VALUES_LENGTH);
		my_keys_array[i] = new MyKey(keys_array[i]);
		my_values_array[i] = new MyValue(values_array[i]);
	}

	operation_execution(DELETE, my_keys_array, my_values_array, inserted_keys, T);
	operation_execution(SEARCH, my_keys_array, my_values_array, inserted_keys, T);
	operation_execution(RANK, my_keys_array, my_values_array, inserted_keys, T);
	operation_execution(SELECT, my_keys_array, my_values_array, inserted_keys, T);
	operation_execution(GETMAXVALUE, my_keys_array, my_values_array, inserted_keys, T);

	for (unsigned i = 0;i < CHECK_SIZE;i++)
	{
		T->Insert(my_keys_array[i], my_values_array[i]);
		inserted_keys[i] = true;
	}

	operation_execution(INSERT, my_keys_array, my_values_array, inserted_keys, T);
	operation_execution(DELETE, my_keys_array, my_values_array, inserted_keys, T);
	operation_execution(SEARCH, my_keys_array, my_values_array, inserted_keys, T);
	operation_execution(RANK, my_keys_array, my_values_array, inserted_keys, T);
	operation_execution(SELECT, my_keys_array, my_values_array, inserted_keys, T);
	operation_execution(GETMAXVALUE, my_keys_array, my_values_array, inserted_keys, T);

	unsigned del_index;

	for (unsigned i = 0;i < INITIAL_DELETED_SIZE;i++)
	{
		del_index = generate_random_index(CHECK_SIZE);
		T->Delete(my_keys_array[del_index]);
		inserted_keys[i] = false;
	}

	operation_execution(INSERT, my_keys_array, my_values_array, inserted_keys, T);
	operation_execution(DELETE, my_keys_array, my_values_array, inserted_keys, T);
	operation_execution(SEARCH, my_keys_array, my_values_array, inserted_keys, T);
	operation_execution(RANK, my_keys_array, my_values_array, inserted_keys, T);
	operation_execution(SELECT, my_keys_array, my_values_array, inserted_keys, T);
	operation_execution(GETMAXVALUE, my_keys_array, my_values_array, inserted_keys, T);

	delete T;

	T = new BalancedTreeK(min_key,max_key);

	delete max_key;
	delete min_key;

	for (unsigned i = 0;i < CHECK_SIZE;i++)
	{
		inserted_keys[i] = false;
	}

	unsigned index;
	for (unsigned i = 0;i < CHECK_SIZE;i++)
	{
		index = generate_random_index(CHECK_SIZE);
		if (inserted_keys[index]==false)
		{
			T->Insert(my_keys_array[index], my_values_array[index]);
			inserted_keys[index] = true;
		}
	}

	unsigned operations_array[OPERATIONS_SIZE];
	for (unsigned i = 0;i < OPERATIONS_SIZE;i++)
	{
		operations_array[i] = generate_random_index(NUM_OF_OPERATIONS) + 1;
	}

	for (unsigned i = 0;i < OPERATIONS_SIZE;i++)
	{
		operation_execution(operations_array[i], my_keys_array, my_values_array, inserted_keys, T);
	}

	for (unsigned i = 0;i < CHECK_SIZE;i++)
	{
		T->Delete(my_keys_array[i]);
		inserted_keys[i] = false;
	}

	operation_execution(INSERT, my_keys_array, my_values_array, inserted_keys, T);
	operation_execution(DELETE, my_keys_array, my_values_array, inserted_keys, T);
	operation_execution(SEARCH, my_keys_array, my_values_array, inserted_keys, T);
	operation_execution(RANK, my_keys_array, my_values_array, inserted_keys, T);
	operation_execution(SELECT, my_keys_array, my_values_array, inserted_keys, T);
	operation_execution(GETMAXVALUE, my_keys_array, my_values_array, inserted_keys, T);

	for (unsigned i = 0;i < CHECK_SIZE;i++)
	{
		delete my_keys_array[i];
		delete my_values_array[i];
	}
	delete T;
}