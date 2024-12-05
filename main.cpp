#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <filesystem>
#include <random>
#include <unordered_set>
#include "sorts.h"

//leonardo Starfire
using namespace std;

//Supported sorting algorithms and their completion times
map<string, long long> sortingAlgorithms = {
        {"bubble", 0},
        {"quick", 0},
        {"merge", 0},
        {"insertion", 0},
        {"selection", 0},
        {"heap", 0}
};

string resolveFilePath(const string& filename);
bool isValidFile(const string& filename);
vector<int> loadDataFromFile(const string& filename);
vector<int> generateRandomData(size_t size, int min, int max);
vector<int> generateRandomDataInput();
vector<int> getFileData();
vector<int> getDataChoice();
void performSorting(const string& sortName, vector<int>& data);
void displaySortedData(const vector<int>& data);
void displaySortingTimes();
bool isNumber(const string& str);

int main() {
    vector<int> data;

    //Keep asking for valid input until successful
    data = getDataChoice();

    vector<int> dataCopy = data; //Copy for later comparison

    //Run every sorting algorithm
    for (auto& sort : sortingAlgorithms) {
        vector<int> tempData = data; //Copy the original data for each sort
        performSorting(sort.first, tempData);
    }

    //Display sorted data (based on a single algorithm, as all should produce the same result)
    //sort(dataCopy.begin(), dataCopy.end()); //Sort once using std::sort to generate the final sorted data
    //displaySortedData(dataCopy);

    //Display sorting algorithm times
    displaySortingTimes();

    return 0;
}

//Resolve relative paths from main assuming main is 1 level above the build folder, or works with absolute path
string resolveFilePath(const string& filename) {
    //Check if the filename is already an absolute path
    if (std::filesystem::path(filename).is_absolute()) {
        return filename; //Use the absolute path directly
    }

    //If it's a relative path, resolve it to the source directory
    string currentPath = std::filesystem::current_path().string();
    string basePath = currentPath + "/../";
    return std::filesystem::absolute(basePath + filename).string();
}

//Validate if a file exists
bool isValidFile(const string& filename) {
    string fullPath = resolveFilePath(filename);

    ifstream file(fullPath);
    if (!file.is_open()) {
        return false;
    }
    return true;
}

//Load data from file (supports both CSV and plain text)
vector<int> loadDataFromFile(const string& filename) {
    vector<int> data;
    string fullPath = resolveFilePath(filename);
    ifstream file(fullPath);

    if (!file.is_open()) {
        cout << "Error: Cannot open file." << endl << endl;
        return {};
    }

    string line;
    while (getline(file, line)) {  //Read the file line by line
        stringstream ss(line);
        string value;

        //Detect whether the line is CSV or plain text
        if (line.find(',') != string::npos) {
            //Process as CSV
            while (getline(ss, value, ',')) {
                try {
                    data.push_back(stoi(value)); //Convert and store the number
                } catch (invalid_argument& e) {
                    cout << "Error: Invalid number in file: " << value << endl << endl;
                    return {};
                }
            }
        } else {
            //Process as plain text
            int num;
            while (ss >> num) {
                data.push_back(num);
            }
        }
    }
    return data;
}

//Generate random data
vector<int> generateRandomData(size_t size, int min, int max, unsigned int seed){
    if(seed == 0){
        seed = random_device{}();
    }
    mt19937 gen(seed);
    uniform_int_distribution<> dis(min, max);
    unordered_set<int> numsUnique;
    vector<int> data;
    while(numsUnique.size() < size){
        int num = dis(gen);
        if(numsUnique.insert(num).second){
            data.push_back(num);
        }
    }
    return data;
}

//Check if a string represents a valid positive integer
bool isNumber(const string& str) {
    if (str.empty()) return false; //Empty string is not a number
    for (char c : str) {
        if (!isdigit(c)) return false; //Non-digit character found
    }
    return true;
}

//Handle user input for generating random data
vector<int> generateRandomDataInput() {
    while (true) {
        string sizeStr, minStr, maxStr, seedStr;
        size_t size;
        int min, max;
        unsigned int seed;

        cout << "Enter the number of elements to generate:" << endl;
        cin >> sizeStr;

        if (!isNumber(sizeStr)) {
            cout << "Error: Invalid input. Please enter a valid number." << endl << endl;
            continue;
        }

        size = stoi(sizeStr);
        if (size <= 0) {
            cout << "Error: Size must be greater than 0." << endl << endl;
            continue;
        }

        cout << "Enter the minimum value:" << endl;
        cin >> minStr;

        if (!isNumber(minStr)) {
            cout << "Error: Invalid input. Please enter a valid number." << endl << endl;
            continue;
        }

        min = stoi(minStr);

        cout << "Enter the maximum value:" << endl;
        cin >> maxStr;

        if (!isNumber(maxStr)) {
            cout << "Error: Invalid input. Please enter a valid number." << endl << endl;
            continue;
        }

        max = stoi(maxStr);

        if (min > max) {
            cout << "Error: Minimum value cannot be greater than maximum value." << endl << endl;
            continue;
        }

        cout << "Enter a seed (or 0 for a random seed):" << endl;
        cin >> seedStr;

        if(!isNumber(seedStr)){
            cout << "Error: Invalid input. Please enter a valid number." << endl << endl;
            continue;
        }
        seed = stoi(seedStr);
        return generateRandomData(size, min, max, seed);
    }
}

//Handle file input with error checking
vector<int> getFileData() {
    string dataFile;
    cin.ignore(); //Clear the input buffer
    while (true) {  //Loop until a valid file is provided
        cout << "Enter the data file name (relative to the program's source directory) or type 'exit' to quit:" << endl;
        getline(cin, dataFile); //Use getline to read the entire path, including spaces

        if (dataFile.empty()) {
            cout << "Error: File name cannot be empty. Please try again." << endl << endl;
            continue;
        }

        if (dataFile == "exit") {
            exit(0); //Exit the program
        }

        if (!isValidFile(dataFile)) {
            cout << "Error: Cannot open file. Please try again." << endl << endl;
        } else {
            return loadDataFromFile(dataFile);
        }
    }
}

//Get user choice for data source
vector<int> getDataChoice() {
    string choice;

    cout << "Do you want to load data from a file or generate random data? (f for file, r for random):" << endl;
    cin >> choice;

    if (choice == "f") {
        return getFileData();
    } else if (choice == "r") {
        return generateRandomDataInput();
    } else {
        cout << "Error: Invalid choice. Please enter 'f' or 'r'." << endl << endl;
        return getDataChoice(); //Retry until valid input is given
    }
}

//Perform sorting based on the chosen algorithm (placeholder for integration)
void performSorting(const string& sortName, vector<int>& data) {
    cout << "Sorting using " << sortName << " algorithm..." << endl;

    auto start = chrono::high_resolution_clock::now();

    //Placeholder: Replace this with actual sorting logic
    if (sortName == "bubble") {
        Sorts::bubbleSort(data);
    } else if (sortName == "quick") {
        Sorts::quickSort(data);
    } else if (sortName == "merge") {
        Sorts::mergeSort(data);
    } else if (sortName == "insertion") {
        Sorts::insertionSort(data);
    } else if (sortName == "selection") {
        Sorts::selectionSort(data);
    } else if (sortName == "heap") {
        Sorts::heapSort(data);
    }

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    //Update sorting time in the map
    sortingAlgorithms[sortName] = duration;

    cout << sortName << " sort completed in " << duration << " ms." << endl << endl;
}

//Display the sorted data
void displaySortedData(const vector<int>& data) {
    cout << "Final Sorted Data:" << endl;
    for (const int& num : data) {
        cout << num << " ";
    }
    cout << endl;
}

//Display the sorting times for each algorithm
void displaySortingTimes() {
    cout << "\nSorting Times (in milliseconds):" << endl;
    for (const auto& sort : sortingAlgorithms) {
        cout << sort.first << ": " << sort.second << " ms" << endl;
    }
}
