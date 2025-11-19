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
as this file, though you can change the desired input file on line 27 so long
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
    
    //blank vector for matnence
    vector<int> empty;


    //verify file opens properly
    std::ifstream input("input.txt");
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


    //testing that everything is read in properly
    cout << "resources: " << numOfResources << endl << endl;
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

}