//Jacob Ford
//11/19/2025
//Implementation of the Bankers algorithm, Data in file input.txt

#include <iostream>
#include <fstream>
#include <vector>

using std::vector; using std::cout; using std::endl;

/* Note: this program relies on the 
information being provided in the input document to 
be of the correct format, specificaly regaring spacing, the correct number
of values provided for the resource count, the format of the first two lines,
and the '|' character seperating each catigory of data. 
In addition, it is expected that the input file be located in the same folder
as this file, though you can change the desired input file on line 39 so long
as the new file is also in the correct format.
Finaly, you must have at least one resource and at least two processes. 
*/
int main(){ 
    //matrix[i][j] will always be resource value j for process i
    vector<vector<int>> allocation;
    vector<vector<int>> max;
    vector<vector<int>> need;

    int numOfResources = 0;
    vector<int> avalible; //always one for each resource

    bool finished[max.size()]; //if true value has been added to the stack
    vector<int> sequence;
    bool isSafe = true;
    
    //blank vector for matnence
    vector<int> empty;


    //verify file opens properly
    std::ifstream input("input3.txt");
    if(input.fail()){
        cout << "cannot open file" << endl;
        exit(1); 
    }


    //collect numOfResources
    char charInput;
    int  intInput;
    input >> charInput;
    while(charInput != ':') input >> charInput;

    input >> numOfResources;
    if (numOfResources == 0){
        cout << "must be tested with at least one resource" << endl;
        exit(1); 
    }


    //collect the first line of data
    allocation.push_back(empty);
    charInput = '.';
    while(charInput != '|') input >> charInput;
    for(int i = 0; i < numOfResources; ++i){
        input >> intInput;
        allocation[0].push_back(intInput);
    }

    
    max.push_back(empty);
    charInput = '.';
    while(charInput != '|') input >> charInput;
    for(int i = 0; i < numOfResources; ++i){
        input >> intInput;
        max[0].push_back(intInput);
    }

    charInput = '.';
    while(charInput != '|') input >> charInput;
    for(int i = 0; i < numOfResources; ++i){
        input >> intInput;
        avalible.push_back(intInput);
    }


    //continues looping through till all information is gathered
    int iterationNum = 0;
    charInput = '.';
    while(charInput != '|') input >> charInput;
    while(!input.eof()){
        ++iterationNum;

        allocation.push_back(empty);
        for(int i = 0; i < numOfResources; ++i){
            input >> intInput;
            allocation[iterationNum].push_back(intInput);
        }

        max.push_back(empty);
        charInput = '.';
        while(charInput != '|') input >> charInput;
        for(int i = 0; i < numOfResources; ++i){
            input >> intInput;
            max[iterationNum].push_back(intInput);
        }

        charInput = '.';
        while(charInput != '|') input >> charInput;

        //set up start of next line, or find end of file
        charInput = '.';
        while(charInput != '|' && !input.eof()) {input >> charInput;}
    }

    input.close();




    //set up need

    for(int i = 0; i < max.size(); ++i){
        need.push_back(empty);
        for(int j = 0; j < numOfResources; ++j){
            need[i].push_back((max[i][j] - allocation[i][j]));
            if (need[i][j] < 0) isSafe = false;
        }
    }




    //testing that everything is read in properly
    cout << "Amount of resources: " << numOfResources << endl << endl;
    cout << "Avalible: " << endl;
    for(auto e:avalible){
        cout << e;
        cout << " ";
    }
    cout << endl << endl;

    cout << "Allocated: " << endl;
    for(auto e:allocation){
        for(auto e2:e){
            cout << e2;
            cout << " ";
        }
        cout << endl;
    }
    cout << endl << endl;

    cout << "Max: " << endl;
    for(auto e:max){
        for(auto e2:e){
            cout << e2;
            cout << " ";
        }
        cout << endl;
    }
    cout << endl << endl;

    cout << "Need: " << endl;
    for(auto e:need){
        for(auto e2:e){
            cout << e2;
            cout << " ";
        }
        cout << endl;
    }
    cout << endl << endl;


    //the bankers algorithm


    
    for(int done = 0; done < max.size(); ++done){  //will iterate once for each process, or untill declared unsafe
        for(int i = 0; i < max.size(); ++i){  //checks from process 0 to final process for one that needs done and needs less than avalible
            if(!finished[i]){
                bool isLessNeed = true;
                for(int j = 0; j < numOfResources; ++j){
                    if(avalible[j] < need[i][j]) isLessNeed = false;
                }

                if(isLessNeed){  //if next in sequence is found, take back allocated resources and mark process as done
                    sequence.push_back(i);
                    finished[i] = true;
                    for(int j = 0; j < numOfResources; ++j){
                        avalible[j] += allocation[i][j];
                    }
                    break;
                }
            }

            if(i == max.size()-1){isSafe = false;}  //if it checks all processes and make it to this command, system is not safe
        }

        if(!isSafe){break;}
    }


    if(isSafe){
        cout << "This is a safe system." << endl;
        cout << "A safe sequence is: ";
        for(auto e:sequence){
            cout << "P" << e << " ";
        }
        cout << endl << endl;
    }else{
        cout << "This is not a safe system" << endl;
    }

    

}