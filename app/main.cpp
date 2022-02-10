#include<iostream>
#include<string>
#include"interface.hpp"


// this is the hello screen. all this thing do is do the initial process of split all command to different threads. 
// it will ask you for specific command in order. plase write the exact thing that the machine can read. any other thing will retrun invalid. 
// here is a brief list for command that are allowed. 
// CREATE LOGIN REMOVE CLEAR QUIT DEBUG LOGIN BUCKET LOAD MAX. 
// !!! only exact command and format that follow the order will result proper out put. 
// any other thing will result Invalid. 
// If you want to end the program properly, rather than shut down or kill the thread in manager level. 
// Please type in "QUIT"
// even this kind of hello screen can even write in the interface class. I prefer to leave some thing in the 
// main function. Thus I could debug more properly for the interface detail class. 
int main()
{
    //variable that needed in the program. Input will be reset after each line of input. 
    std::string input;
    // when debug on you could do somehing majic. it is set to be off by default. 
    bool debug = false;
    // initialize the interface class. Pleace check interface.hpp for detail. 
    Interface initiate;
    
    while(true)
    {
        // this pleas is for test
        // i know the gtest is good 
        // but gtest does not provide me enough information to debug

        // std::string* keys = new std::string [10];
        // std::string* values = new std::string [10];
        // std::string temp = "a";
        // for(int i = 0;i <10;i++)
        // {
        //     temp += "a";
        //     keys[i] = temp;
        //     values[i] = temp;
        // }

        // for(int i = 0;i<10;i++)
        // {
        //     initiate.create(keys[i],values[i]);
        // }
        // delete[] keys;
        // delete[] values;

        input = "";
        // read one line in each term. 
        std::getline(std::cin,input);
        // procedure the input and store the produced value in interface calss.
        initiate.split(input);
        // the line below is for check the command whether or not it split properly.  
        // you can un comment is to see if the value you type in exactly follw the order. 
        // anything you type in loger than three words will cause the stop spliting and empty the first command.
        // 
        // std::cout<<initiate.command[0]<<"|"<<initiate.command[1]<<"|"<<initiate.command[2]<<"|"<<std::endl;
        
        // I kind of hate this long redudent thing, may be the switch fucntion could be easier. Or I might even need to write it in a hashmasp LOL.
        if (input == "QUIT")
        {
            break;
        }
        else if (initiate.command[0] == "CREATE" && initiate.command[1]!="" && initiate.command[2]!="")
        {
            initiate.create(initiate.command[1],initiate.command[2]);
        }
        else if (initiate.command[0] == "LOGIN" && initiate.command [1]!="" && initiate.command[2]!="")
        {
            initiate.login(initiate.command[1],initiate.command[2]);
        }
        else if (initiate.command[0] == "REMOVE" && initiate.command[1]!="" && initiate.command[2]=="")
        {
            initiate.remove(initiate.command[1]);
        }
        else if (initiate.command[0] == "CLEAR" && initiate.command[1] == "" && initiate.command[2]=="")
        {
            initiate.clear();
        }
        else if (initiate.command[0] == "DEBUG" && initiate.command[1] != "" && initiate.command[2]=="")
        {
            if(initiate.command[1]=="ON")
            {
                // the only output in the main funciton. most of the respone, I wirte in the interface class. 
                // Since this thing is kind of too short. And it did not manipulate anything in the interface clss. 
                // Thus I keep it here. 
                // Makes the other debug commands available. Before issuing this command, all other debug commands (except DEBUG ON and DEBUG OFF) should be considered invalid. If debug commands were not already on, the output is ON NOW; if they were, the output is ON ALREADY. While in debug mode, all of the user-facing commands remain available.
                if (debug)
                {
                    std::cout<<"ON ALREADY"<<std::endl;
                }
                else
                {
                    std::cout<<"ON NOW"<<std::endl;
                }
                debug = true;
                
            }
            else if (initiate.command[1]=="OFF")
            {
                //Makes the other debug commands unavailable. After issuing this command, all debug commands should be considered invalid except for DEBUG ON and DEBUG OFF. If debug commands were already on, the output is OFF NOW; if they weren't already on, the output is OFF ALREADY.
                if (debug)
                {
                    std::cout<<"OFF NOW"<<std::endl;
                }
                else
                {
                    std::cout<<"OFF ALREADY"<<std::endl;
                }
                debug = false;
            }
            else
            {
                initiate.invalid();
            }
        }

        // if the debug is on. THen I could have several other funciton that could run. 
        // Thus, need to keep test whether the input follow what we allowed. 
        else if (debug)
        {
            if (initiate.command[0] == "LOGIN" && initiate.command[1] == "COUNT" && initiate.command[2]=="")
            {
                initiate.loginCount();
            }
            else if (initiate.command[0] == "BUCKET" && initiate.command[1] == "COUNT" && initiate.command[2]=="")
            {
                initiate.bucketCount();
            }
            else if (initiate.command[0] == "LOAD" && initiate.command[1] == "FACTOR" && initiate.command[2]=="")
            {
                initiate.loadFactor();
            }
            else if (initiate.command[0] == "MAX" && initiate.command[1] == "BUCKET" && initiate.command[2]=="SIZE")
            {
                initiate.maxBucketSize();
            }
            else
            {
                initiate.invalid();
            }
        }
        else
        {
            initiate.invalid();
        }
    }

    //"BYE BYE"
    std::cout<<"GOODBYE"<<std::endl;
    return 0;
}

