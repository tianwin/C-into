#ifndef INTERFACE_CPP
#define INTERFACE_CPP


#include"HashMap.hpp"
#include<iostream>
#include<string>

// this is the interface process and make maniputlate to the value stored. 
// the interface create a hashmap local variable. and manipulate these value. 
// there are several fucniton supported in this interface class. 
// CREATE LOGIN REMOVE CLEAR SPLIT INVALID COUT LOADFACTOR MAXBUCKETSIZE.
// also another public variable. 
class Interface
{

public:
    //constructer to initialize the command and the hashtable. 
    Interface();
    // the reason I did not writ all the big three is because, What i need is only the dealocator. 
    ~Interface();
    
    //all the follow description are from the assignment material. Since what I wrtite down 
    // is just to fulfill the requirment. anything specific or different, I will write it in seperate lines. 
    // please pay more attention on these thing when you use this class. 

    //Create a new username/password combination and stores it in the program's collection. If successful, the output is CREATED. If the username is already stored in the collection, no change is made and the output is EXISTS. (One key consequence is that the same username cannot appear in the collection more than once.)
    bool create(const std::string& key, const std::string& value);
    //Checks a username/password combination to see if it is valid. A username/password combination is valid if it exists (i.e., the username is in the collection and is associated with the password), in which case the output is SUCCEEDED. If the username/password combination does not exist, the output is FAILED. (Note that there is no distinction between the username not existing and the password being incorrect; either situation would output FAILED. This is fairly standard — and wise — behavior for an authentication service; if you return different error messages when a username does not exist and when a password is wrong, you're letting an attacker know a useful piece of information: whether a username is valid.)
    bool login(const std::string& key, const std::string& value);
    //Removes the username/password combination with the given username, if it exists. If so, the output is REMOVED. If no username/password combination with the given username exists, the output is NONEXISTENT.
    void remove(const std::string& key);
    //	Removes all username/password combinations from the service. The output is CLEARED (even if there were no username/password combinations at the time).
    void clear();
    
    // WOW, you find something different!!!
    // this fucntion is for split the raw input. and it is pretty complicated  in detail 
    // I mean not compliated . it is easy but really really long. 
    // SInce write it in python do not need thse things . it was just need to write down the powerful split. 
    // all in all, let's talk about this thing in detail. 
    // THis fucniton split the command by space. and split into three parts. 
    // any command longer than three will cause to stop reading.
    // and set the first command to be empty. 
    void split(const std::string& input);
    
    //WOW, this is also soemthing write down by my self. 
    // THis is a typical error handle. 
    // any thing that are invalid will go through this funciton. 
    // the thing that you see print out "INVALID" is produced by this funciton. 
    void invalid();
    //The output is the number of username/password combinations currently being stored.
    void loginCount();
    //	The output is the number of buckets in the hash table at present.
    void bucketCount();
    //The output is the load factor of the hash table at present. There is no specific requirement here about the number of decimal places to include in the output; whatever emerges by default if you write a double to std::cout is best.
    void loadFactor();
    //The output is the length of the largest bucket (i.e., the one whose linked list contains the largest number of elements) in the hash table.
    void maxBucketSize();

    // The reason I keep it here is to more easier to deallocate the memory. 
    // When I keep it in the main fucniton. Since it is created. here. Thus I wish to deallocat it here. 
    std::string* command;
private:
    // store the username and password pair. check detatil in the HashMap class. 
    HashMap* hashTable;
};

#endif