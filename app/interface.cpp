#include"interface.hpp"

// constructer as you see. command has three and a new empty hash map use the default hash method. 
Interface::Interface()
    :command{new std::string[3]}
{
    hashTable = new HashMap();
}

// Since this class have two pointer. 
// It need a destrcter. 
Interface::~Interface()
{
    delete hashTable;
    delete[] command;
}

// first check for existence . then call the add fucntion in the HashMap class. 
bool Interface::create(const std::string& key, const std::string& value)
{
    if (hashTable->contains(key))
    {
        std::cout<<"EXISTS"<<std::endl;
        return false;
    }
    // std::cout<<hashTable->contains(key)<<std::endl;
    hashTable->add(key,value);
    // std::cout<<hashTable->contains(key)<<std::endl;
    std::cout<<"CREATED"<<std::endl;
    return true;
}   

// check the key value pair. does it correct with the key value pair stored in the Hashtable. 
bool Interface::login(const std::string& key, const std::string& value)
{
    if(hashTable->value(key)==value)
    {
        std::cout<<"SUCCEED"<<std::endl;
        return true;
    }
    std::cout<<"FAILED"<<std::endl;
    return false;
}

// delete the key value pair
// since hte remove funciton can check for whether it exist or not. 
// this fucntion will not check for contains. 
void Interface::remove(const std::string& key)
{
    if(hashTable->remove(key))
    {
        std::cout<<"REMOVED"<<std::endl;
        return;
    }
    std::cout<<"NONEXISTENT"<<std::endl;

}

// make my hashmap pointer point to a new one and delete the old one.
void Interface::clear()
{
    delete hashTable;
    hashTable = new HashMap();
    
    std::cout<<"CLEARED"<<std::endl;
}

//quite detail introduce inteh hpp file. 
void Interface::split(const std::string& input)
{   
    // do not delete this "seem to be useless thing.".
    // this is useful for the second run and latter. 
    // SInce in the second run, these command still keep the value in
    // the last run. Thus, I need to reset these values. 
    command[0]="";
    command[1]="";
    command[2]="";
    
    // this index value is for appoint the command index. 
    int index = 0;
    int len = input.length();
    // last check is for remember the last char is space or other. 
    // set to be true by default. Since, the first time, I read might be space. 
    // and the thing I want to keep is anything other than space. 
    bool lastcheck = true;
    // loop over the input string for each char.
    for(int i = 0; i <len;i++)
    {
        if(input[i] == ' ')
        {
            // if the last check from change from not space to space, 
            // then this part of command finish. and ready to keep the next part. 
            if(!lastcheck)
            {
                lastcheck = true;
                index++;
                // if the command has larger than three part. then that input is definiely invaild. 
                // to set it to be invalid, the most easy thing is to set the first command be empty. 
                
            }
        }
        else
        {
            if (index == 3)
                {
                    command[0]="";
                    // for any invalid command , no need to keep produce.
                    return;
                }
            command[index] = command[index]+input[i];
            // if it is not space. then the last check become false. 
            lastcheck = false;
        }
    }

}

// problem handle.
void Interface::invalid()
{
    std::cout<<"INVALID"<<std::endl;
}

// call the hashMap class check the size function in hashmap for detail.
void Interface::loginCount()
{
    std::cout<<hashTable->size()<<std::endl;
}

// check the bucketcount funciton in hashmap for detail 
void Interface::bucketCount()
{
    std::cout<<hashTable->bucketCount()<<std::endl;
}

// check the laod factior funciton in hashmap for detail. 
void Interface::loadFactor()
{
    std::cout<<hashTable->loadFactor()<<std::endl;
}

// check the maxbucketsize funciton in hashmap for detial.
void Interface::maxBucketSize()
{
    std::cout<<hashTable->maxBucketSize()<<std::endl;
}
