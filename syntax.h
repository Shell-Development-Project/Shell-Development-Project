#ifndef SYNTAX_H_INCLUDED
#define SYNTAX_H_INCLUDED

#include <iostream>
#include <utility>
#include <exception>
#include <unordered_map>
// #include <functional>

typedef std::pair <int, std::string> key;
typedef std::pair <int, char> value;

// typedef std::unordered_map <key, value> table;

// For detailed knowledge on the unordered_maps, go to the following link:
// http://marknelson.us/2011/09/03/hash-functions-for-c-unordered-containers/


/*
->We’re used to seeing unordered_map declared with two template parameters: for ex- unordered_map<key,value> Name;
But a look at the help page shows that IT ACTUALLY TAKES FIVE – the last three usually accept DEFAULT values: 
________________________________________________________________

template<class Key,
    class Ty,
    class Hash = std::hash<Key>,
    class Pred = std::equal_to<Key>,
    class Alloc = std::allocator<std::pair<const Key, Ty> > >
    class unordered_map;
________________________________________________________________

The THIRD PARAMETER to the definition is a function object type that is used by the class to convert a key into a hash code. 
By default it is set to std::hash.
Internally the unordered_map class calls operator() on an object of that type in order to get a hash code for a given key.

Although unordered maps have a pre-defined hash function for the fundamental data types (int, char, std::string, etc.), but 
An unordered_map doesn’t know how to create a hash for the given key type of std::pair, because it's a user-defined data type.

As a general rule of thumb, if I have two hashes for independent variables, and I combine them using XOR, I can expect that the resulting hash 
is probably just as good as the input hashes. Therefore, i can define the hash function as follows:

size_t name_hash( const Name & name )
{
    return hash<string>()(name.first) ^ hash<string>()(name.second);
}

->Also,The standard defines a constructor that takes an initial number of buckets and a hashing object as inputs. 
So the first step is to modify the declaration code to look like this:

________________________________________________

unordered_map<Name,int> ids(100, name_hash ); 
________________________________________________

But,  The default implementation of unordered_map expects to be using a function object of type std::hash to calculate hashes, 
and that is not what we are passing into the constructor. Thus, we'll have to convert our defined hash function to std::hash
Methods:
1) By using the: decltype keyword
	unordered_map<Name,int,decltype(&name_hash)> ids(100, name_hash );
2) Specializing std::hash
	use the name hash for your object, and define it as a specialization of that template class, 
	and finally, we have to hoist the whole thing into the std namespace.
	Something like the one used in this file.
*/
namespace std					
{
	template<>
	class hash<key>
	{
	public:
		size_t operator()(const key &key) const 
		{								//^^^^^^ this const shows that the function doesnot change 
										// the state of the object. i.e. the method does not change any member variables.
			
			return hash<int>()(key.first) ^ hash<std::string>()(key.second);
		}
	};
};
// class MyException:public exception
// {
// public:
// 	MyException(const std::string m = "Syntax Error"):msg(m){}
// 	~MyException(void);
// 	const char* what()
// 	{
// 		return msg.c_str();
// 	}
// private:
// 	std::string msg;
// };
void constructTable(std::unordered_map <key,value>& table);
int parser(std::unordered_map <key, value>& table, std::vector <std::string>& tokenStream);
int reduceMove(int productionNo, std::unordered_map <key, value>& table);
#endif // SYNTAX_H_INCLUDED