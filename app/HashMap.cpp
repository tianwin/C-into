#include"HashMap.hpp"
#include<string>
#include<iostream>

// this name space contain the default hash fucntion 
// in the situation of no hash funciton provided. 
namespace
{
    // this hashfucniton uses two prime number. 
    // take the typical form of ax+b. 
    unsigned int DefaultHashFunction(const std::string& key)
    {
        //any ideal prime number. 
        int prime1 = 13;
        int prime2 = 23;
        int sum = 0;
        // loop over the stirng. 
        for(const char i:key)
        {
            sum = sum+((int)i)*prime1+prime2;
        }
        return sum;
    }
}

// as we see in the header file. the hashfunciton can not fit perfectly to what we want. 
// thus this fit hashfunciton funciton can modify the value that can be set into the class. 
unsigned int HashMap::fithashfunction(const std::string& key) const
{
    return hashFunction(key)%bucketTotal;
}

// constructer with all initial value. 
HashMap::HashMap()
    :
    hashFunction{DefaultHashFunction},
    
    bucket{0},
    buckets{new Node[INITIAL_BUCKET_COUNT]},
    sizecount{0}
    
{   
    bucketTotal = INITIAL_BUCKET_COUNT;
}

// construcet with given hashfucntion.
HashMap::HashMap(HashFunction hashfunction)
    :
    bucketTotal{INITIAL_BUCKET_COUNT},
    bucket{0},
    buckets{new Node[INITIAL_BUCKET_COUNT]},
    sizecount{0}
{
    this->hashFunction=hashfunction;
}

// construct from another hashmap to initiate.
HashMap::HashMap(const HashMap& hm)
    :hashFunction{hm.hashFunction},
    bucket{0},
    buckets{new Node[hm.bucketTotal]},
    sizecount{hm.sizecount}
{
    bucketTotal = hm.bucketTotal;
    // all these folow thing is to copy the hashtable infor. 
    for(int i = 0;i<hm.bucketTotal;i++)
    {
        Node* nextnode=buckets[i].next;
        Node* currentnode = &buckets[i];

        Node* hmnextnode=hm.buckets[i].next;
        Node* hmcurrentnode = &hm.buckets[i];
        
        currentnode->key=hmcurrentnode->key;
        currentnode->next = hmcurrentnode->next;
        currentnode->value = hmcurrentnode->value;
        
        while(currentnode->value!="")
        {
            currentnode = nextnode;
            nextnode = nextnode->next;
            hmcurrentnode = hmnextnode;
            hmnextnode = hmnextnode->next;
            currentnode->key=hmcurrentnode->key;
            currentnode->next = hmcurrentnode->next;
            currentnode->value = hmcurrentnode->value;
        }
        
    }
}

// since there are several pointer in this calss. thus  a destructer is needed.
void HashMap::deleteNodes()
{
    // these step is to delete all these deeper nodes. 
    // this is achieved by step over and check. 
    for(int i = 0;i<bucketTotal;i++)
    {
        Node* currentnode;
        Node* nextnode;
        // Node* abundent;
        if (buckets[i].value!="")
        {
            currentnode = &buckets[i];
            nextnode = buckets[i].next;
            while(currentnode->value!="")
            {
                // this additional check is for aoviding the "access to unitinial pointer."
                if(nextnode->value!="")
                {
                    currentnode->next=nextnode->next;
                    delete nextnode;
                    nextnode = currentnode->next;
                }
                else
                {
                    delete nextnode;
                    currentnode->next=NULL;
                    break;
                }
            }
        }
    }
}

// I write a seperate destruct funciton for help. 
// this is just to delete the baisc initial value or i mean pointer.
HashMap::~HashMap()
{
    deleteNodes();
    delete[] buckets;
}


// for this copy hash operator. 
// what i understand is jsut copy the hash table. 
// THus I keep the hash fcuntion not change. 
// and delete all the original hashtable. 
HashMap& HashMap::operator=(const HashMap& hm)
{
    // copy some basic thing.
    bucketTotal=hm.bucketTotal;
    bucket=0;
    // since the original buckets is no longer needed. thus delet all recursive nodes. 
    deleteNodes();
    // sicce I build a new one, I need to record the old one and delete it. 
    Node* tempptr= buckets;
    buckets=new Node[hm.bucketTotal];
    delete[] tempptr;

    // i believ you have see this for loop for seveal time in my also may in other studnets's assignment.
    // this is kind of boring and take a lot of work. but it's job is sumple
    // just loop over and copy all values. 
    for(int i = 0;i<hm.bucketTotal;i++)
    {
        Node* nextnode=buckets[i].next;
        Node* currentnode = &buckets[i];

        Node* hmnextnode=hm.buckets[i].next;
        Node* hmcurrentnode = &hm.buckets[i];
        
        currentnode->key=hmcurrentnode->key;
        currentnode->value = hmcurrentnode->value;
        
        while(currentnode->value!="")
        {
            currentnode = nextnode;
            nextnode = nextnode->next;
            hmcurrentnode = hmnextnode;
            hmnextnode = hmnextnode->next;
            currentnode->key=hmcurrentnode->key;
            // once find cursive node. 
            // construct a new one for this. 
            currentnode->next = new Node;
            currentnode->value = hmcurrentnode->value;
        }
        
    }
    return *this;
}

// with the benefit of sizecount 
// just one line funciton.
unsigned int HashMap::size() const
{
    return sizecount;
}

// easy one line funciton
double HashMap::loadFactor() const
{
    return (double)sizecount/(double)bucketTotal;
}

// this is a simple add fucniton with no complcated. 
void  HashMap::justadd(const std::string& key, const std::string& value)
{
    bucket = fithashfunction(key);
    Node* currentNode = &buckets[bucket];
    // keep searching, till find a empty node. 
    while(currentNode->value!="")
    {
        currentNode = currentNode->next;
    }
    currentNode->key = key;
    currentNode->value = value;
    // once the node is setted, build a new empty node. 
    currentNode->next = new Node;
}

// after the size overwellm, then the fucniton reqest to reset all value to a larger buckets. 
void HashMap::resetHastTable(const int newbucketTotal)
{
    
    // first store all old values in a array.
    std::string* keys = new std::string[sizecount];
    std::string* values = new std::string[sizecount];
    int index = 0;
    Node* currentnode;
    for(int i = 0;i<bucketTotal;i++)
    {
        currentnode = &buckets[i];
        while(currentnode->value!="")
        {
            keys[index] = currentnode->key;
            values[index] = currentnode->value;
            currentnode = currentnode->next;
            index++;
        }
    }
    // after done copy, reset all value to new position. and abudnetn old buckets. 
    bucketTotal = newbucketTotal;
    delete[] buckets;
    buckets = new Node [newbucketTotal];
    for (int i = 0; i < sizecount; i++)
    {
        justadd(keys[i],values[i]);
    }
    


}

// just add funciton see it call jsut add and just whether or not overwellm. 
// if it is almost full, then call reset all to a larger buckets. 
void HashMap::add(const std::string& key, const std::string& value)
{
    justadd(key,value);
    sizecount++;
    if(loadFactor()>0.8)
    {
        resetHastTable(bucketTotal*2+1);
    }
}

// check if the key in teh hashtable. 
bool HashMap::contains(const std::string& key) const
    {
        const int index = fithashfunction(key);
        Node* currentnode = &buckets[index];
        while(currentnode->value!="")
        {
            if(key == currentnode->key)
            {
                return true;
            }
            currentnode = currentnode->next;
        }
        
        return false;
    }

// this remove funciton, i write it in a simple way of jsut set the key to be empyt. 
bool HashMap::remove(const std::string& key)
    {
        // make the pointer point to the value that we want to manipulate. 
        Node* currentnode= &buckets[fithashfunction(key)];
        // std::cout<<fithashfunction(key)<<std::endl;
        while(currentnode->value!="")
        {
            if(key == currentnode->key)
            {
                currentnode->key="";
                sizecount--;
                return true;
                
            }
            currentnode = currentnode->next;
        }
        
        
        return false;
    }

// search by key and find the coorespond value. 
// it will also check the contain.
std::string HashMap::value(const std::string& key) const
{
    if(!contains(key))
    {
        return "";
    }
    Node* currentnode = &buckets[fithashfunction(key)];
    while(currentnode->key!=key)
    {
        currentnode = currentnode->next;
    }
    return currentnode->value;
}


// simple one line function 
//bucketCount() returns the number of buckets currently allocated in
    // this HashMap.
unsigned int HashMap::bucketCount() const
{
    return bucketTotal;
}


//the max bucket size is a heavy one. do not easily use it to check and it does not mean a lot for me. I hate this and I am tired. 
// maxBucketSize() returns the number of key/value pairs stored in this
// HashMap's largest bucket.
unsigned int HashMap::maxBucketSize() const
{
    unsigned int max = 0;
    for(int i = 0;i<bucketTotal;i++)
    {   
        int currentmax = 0;
        Node* currentnode= &buckets[i];
        while (currentnode->value!="")
        {
            if(currentnode->key!="")
            {
                currentmax++;
            }
            currentnode = currentnode->next;
        }
        if (currentmax>max)
        {
            max = currentmax;
        }
    }  
    return max;
}