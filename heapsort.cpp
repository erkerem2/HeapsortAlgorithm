//Author Kerem Er
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

using namespace std;

int get_data(string input) {
    size_t pos = input.find(';');
    if (pos != string::npos) {
        string numberString = input.substr(pos + 1);
        return stoi(numberString);
    }
    return -1;
}

void max_heapify(vector<string>& heap, int heapSize, int index) {
    //Relative indexes of the left and right child
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;

    //Assuming index is the largest element
    int largest = index;

    //Compares if the left child is bigger than heap[largest] which is index in this case
    if (leftChild < heapSize && get_data(heap[leftChild]) > get_data(heap[largest])) {
        largest = leftChild;
    }

    //Compares if the right child is bigger than heap[largest] which is index or left child in this case
    if (rightChild < heapSize && get_data(heap[rightChild]) > get_data(heap[largest])) {
        largest = rightChild;
    }

    //Checks if there were any change on the variable "largest"
    if (largest != index) {
        swap(heap[index], heap[largest]);

        //Recursively repeating untill the index is still
        max_heapify(heap, heapSize, largest);
    }
}

void build_max_heap(vector<string>& heap) {
    int heapSize = heap.size();

    //Heapifies the array number of leaves times
    for (int i = (heapSize / 2) - 1; i >= 0; --i) {
        max_heapify(heap, heapSize, i);
    }
}

void heapSort(vector<string>& arr) {
    int n = arr.size();

    //Makes max heap array
    build_max_heap(arr);

    //Removes elements from the max-heap one by one
    for (int i = n - 1; i > 0; --i) {
        //Swaps the maximum element with the last element
        swap(arr[0], arr[i]);

        // Reduce the heap size and heapify the root to maintain the max-heap property
        max_heapify(arr, i, 0);
    }
}

//Key should be in k_name;integer form
void max_heap_insert(vector<string>& heap, string key) {
    build_max_heap(heap);
    // Insert the new element at the end of the heap
    heap.push_back(key);

    int index = heap.size() - 1;

    // Heapify the heap upwards to maintain the max-heap property
    while (index > 0 && get_data(heap[(index - 1) / 2]) < get_data(heap[index])) {
        swap(heap[index], heap[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}
//-------------------------------------------------------------------------------------------------
int heap_extract_max(vector<string>& heap) {
    build_max_heap(heap);
    if (heap.empty()){
        return -1;
    }

    int maxElement = get_data(heap[0]);
    heap[0] = heap.back();
    heap.pop_back();

    //Heapify the heap downwards to keep it as a max heap
    max_heapify(heap, heap.size(), 0);

    return maxElement;
}

void heap_increase_key(vector<string>& heap, int index, int newKey) {
    build_max_heap(heap);
    index--; //Heap root starts with index 1 so when input is 1 it will make it 0 to take the root
    if (newKey < get_data(heap[index])) {
        return;
    }

    string cityName;
    size_t semicolonPos = heap[index].find(';');
    if (semicolonPos != string::npos) {
        cityName = heap[index].substr(0, semicolonPos);
    } else {
        return;
    }

    // Update the heap with the new key
    heap[index] = cityName + ";" + to_string(newKey);

    // Heapify the heap upwards to keep it as a max heap
    while (index > 0 && get_data(heap[(index - 1) / 2]) < get_data(heap[index])) {
        swap(heap[index], heap[(index - 1) / 2]);
        index = (index - 1) / 2;
    }

}


string heap_maximum(vector<string>& heap) {
    build_max_heap(heap);
    if (!heap.empty()) {
        //Returns the root of the heap
        return heap[0];
    } else {
        return "";
    }
}

//--------Implementation of d-ary Heap Operations--------------
int dary_calculate_height(int n, int d){
    //Height formula for a d-ary heap: ceil(log_d(n + 1) - 1)
    return static_cast<int>(ceil(log(n + 1) / log(d))) - 1;
}

void dary_max_heapify(vector<string>& heap, int heapSize, int index, int d) {
    int largest = index;
    int childStart = d * index + 1;

    for (int i = 0; i < d; ++i) {
        int childIndex = childStart + i;

        if (childIndex < heapSize && get_data(heap[childIndex]) > get_data(heap[largest])) {
            largest = childIndex;
        }
    }

    if (largest != index) {
        swap(heap[index], heap[largest]);
        dary_max_heapify(heap, heapSize, largest, d);
    }
}

void dary_build_max_heap(vector<string>& heap, int d) {
    int heapSize = heap.size();

    //Starting from the last non-leaf node and repeating it untill the root
    for (int i = (heapSize - 2) / d; i >= 0; --i) {
        dary_max_heapify(heap, heapSize, i, d);
    }
}

int dary_extract_max(vector<string>& heap, int& heapSize, int d) {
    dary_build_max_heap(heap, d);
    if (heapSize == 0) {
        return -1;
    }

    //
    int maxElement = get_data(heap[0]);
    heap[0] = heap.back();
    heap.pop_back();
    heapSize--;

    //Heapifyint the heap downwards to maintain max heap structure
    dary_max_heapify(heap, heapSize, 0, d);

    return maxElement;
}

//Key input should be in "k_name;integer" structure
void dary_insert_element(vector<string>& heap, int& heapSize, string key, int d) {
    heap.push_back(key);
    heapSize++;

    int index = heapSize - 1;

    //Heapifyint the heap upwords to maintain max heap structure
    while (index > 0 && get_data(heap[(index - 1) / d]) < get_data(heap[index])) {
        swap(heap[index], heap[(index - 1) / d]);
        index = (index - 1) / d;
    }
}

void dary_increase_key(vector<string>& heap, int index, int newKey, int d) {
    dary_build_max_heap(heap, d);
    index--; //Since the root of a heap is indexed as 1 when the user enters 1 it will decrement it to 0 to work correctly as a vector
    if (newKey < get_data(heap[index])) {
        return;
    }

        string cityName;
    size_t semicolonPos = heap[index].find(';');
    if (semicolonPos != string::npos) {
        cityName = heap[index].substr(0, semicolonPos);
    } else {
        return;
    }

    // Update the heap with the new key
    heap[index] = cityName + ";" + to_string(newKey);

    //Heapifyint the heap downwards to maintain max heap structure
    while (index > 0 && get_data(heap[(index - 1) / d]) < get_data(heap[index])) {
        swap(heap[index], heap[(index - 1) / d]);
        index = (index - 1) / d;
    }
}

//----------File Read------------//
vector<string> Read(const string& filename) {
    vector<std::string> lines;
    ifstream file(filename);

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            lines.push_back(line);
        }
        file.close();
    } else {
        cerr << "Wrong file name: " << filename << endl;
    }

    return lines;
}

//----------File Write------------//
void Write(const string& fullFileName, const vector<string>& lines) {
    ofstream outputFile(fullFileName);

    if (!outputFile.is_open()) {
        cerr << "Error: Could not open file " << fullFileName << " for writing." << endl;
        return;
    }

    for (const string& line : lines) {
        outputFile << line << endl;
    }

    outputFile.close();
}
//---------------------------------------------------------------
//Determining the type of input and getting the data
void categorize(const string& input, int &index, int &key, int &dary, string &key2) {
    try {
        int value = stoi(input.substr(1)); // Convert the substring (excluding the first character) to an integer

        if(input[0] == 'i') {
            index = value;
        } else if(input[0] == 'k') {
            key = value;
        } else if(input[0] == 'd') {
            dary = value;
        } else {
            // Handle invalid input character
        }
    } catch (const std::invalid_argument& e) {
        if(input[0] == 'k'){
            key2 = input.substr(2);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        cerr << "Usage: " << argv[0] << " <input_file> <function_name> <output_file> [optional_args]" << endl;
        return 1;
    }

    string inputFileName = argv[1];
    string functionName = argv[2];
    string outputFileName = argv[3];
    int index = 0;
    int key = 0;
    int dary = 0;
    string key2 = "";

    //Catagorizing inputs
    if(argc > 4){
        categorize(argv[4], index, key, dary, key2);
    }
    if(argc > 5){
        categorize(argv[5], index, key, dary, key2);
    }
    if(argc > 6){
        categorize(argv[6], index, key, dary, key2);
    }


    vector<string> heapData = Read(inputFileName);
    int size = heapData.size();

    if (functionName == "max_heapify") {
        
        max_heapify(heapData, size, index);

    } else if (functionName == "build_max_heap") {
        build_max_heap(heapData);

    } else if (functionName == "heapsort") {
        heapSort(heapData);

    } else if (functionName == "max_heap_insert") {
        
        max_heap_insert(heapData, key2);

    } else if (functionName == "heap_extract_max") {
        cout << heap_extract_max(heapData) << endl; 

    } else if (functionName == "heap_increase_key") {
        
        heap_increase_key(heapData, index, key);

    } else if (functionName == "heap_maximum") {
        cout << heap_maximum(heapData) << endl;

    } else if (functionName == "dary_calculate_height"){

        cout << dary_calculate_height(size,dary) << endl;

    } else if (functionName == "dary_extract_max"){

        cout << dary_extract_max(heapData, size, dary) << endl;

    } else if (functionName == "dary_insert_element") {

        dary_insert_element(heapData, size, key2, dary);

    } else if (functionName == "dary_increase_key"){

        dary_increase_key(heapData, index, key, dary);

    }
    else {
        cerr << "Invalid function name: " << functionName << endl;
        return 1;
    }

    Write(outputFileName, heapData);

    return 0;
}
