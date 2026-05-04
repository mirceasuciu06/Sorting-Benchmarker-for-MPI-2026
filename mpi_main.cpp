#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;
ifstream inputFile("custom_list.txt");
ofstream outputFile("sorting_times.csv", ios::app);

// Forward declarations of sorting functions
void bubble_sort(vector<int>& arr);
void insertion_sort(vector<int>& arr);
void selection_sort(vector<int>& arr);
void merge_sort(vector<int>& arr);
void heap_sort(vector<int>& arr);
void quick_sort(vector<int>& arr);
void cocktail_sort(vector<int>& arr);
void cycle_sort(vector<int>& arr);
void merge_sort_3way(vector<int>& arr);
void counting_sort(vector<int>& arr);
void radix_sort(vector<int>& arr);
void introsort(vector<int>& arr);
void timsort(vector<int>& arr);

vector<int> generateRandomNumbers(int minNumber, int maxNumber, int count) {
    std::vector<int> randomList;

    for(int i = 0;i < count; i++)
    {
        randomList.push_back(rand() % (maxNumber - minNumber + 1) + minNumber);
    }

    return randomList;
}

vector<int> loadCustomList() {
    std::vector<int> customList;
    std::ifstream file("custom_list.txt");
    
    if (!file.is_open()) {
        cout << "Error: Could not open custom_list.txt" << endl;
        return customList;
    }
    
    int num;
    while (file >> num) {
        customList.push_back(num);
    }
    
    file.close();
    
    if (customList.empty()) {
        cout << "Error: custom_list.txt is empty" << endl;
    } else {
        cout << "Loaded " << customList.size() << " elements from custom_list.txt" << endl;
    }
    
    return customList;
}

vector<vector<int>> loadAllCustomListsByLine() {
    vector<vector<int>> allLists;
    std::ifstream file("custom_list.txt");
    
    if (!file.is_open()) {
        cout << "Error: Could not open custom_list.txt" << endl;
        return allLists;
    }
    
    string line;
    int lineNum = 0;
    while (getline(file, line)) {
        if (line.empty()) continue;
        
        vector<int> currentList;
        istringstream iss(line);
        int num;
        while (iss >> num) {
            currentList.push_back(num);
        }
        
        if (!currentList.empty()) {
            allLists.push_back(currentList);
            lineNum++;
            cout << "Loaded custom list " << lineNum << " with " << currentList.size() << " elements" << endl;
        }
    }
    
    file.close();
    return allLists;
}

void saveUsedList(const vector<int>& list, const string& listType) {
    // Read existing content
    vector<string> lines;
    std::ifstream readFile("last_used_lists.txt");
    string line;
    while (getline(readFile, line)) {
        lines.push_back(line);
    }
    readFile.close();
    
    // Prepare new entry
    ostringstream newEntry;
    newEntry << "List Type: " << listType << " | Size: " << list.size() << " | Elements: ";
    for (int i = 0; i < list.size(); i++) {
        newEntry << list[i];
        if (i < list.size() - 1) newEntry << " ";
    }
    
    // Write back with new entry at the beginning
    std::ofstream writeFile("last_used_lists.txt");
    if (!writeFile.is_open()) {
        cout << "Error: Could not open last_used_lists.txt" << endl;
        return;
    }
    
    writeFile << newEntry.str() << endl;
    for (const auto& existingLine : lines) {
        writeFile << existingLine << endl;
    }
    
    writeFile.close();
}

void runAllSortingAlgorithms(const vector<int>& originalList, const string& listLabel) {
    cout << "\n=== Running sorting algorithms for: " << listLabel << " ==="  << endl;
    saveUsedList(originalList, listLabel);
    
    vector<int> arr1 = originalList;
    auto start = std::chrono::steady_clock::now();
    bubble_sort(arr1);
    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    cout << "Bubble sort time: " << duration.count() << " nanoseconds, " <<duration.count() / 1000000.0 << " milliseconds, " << duration.count() / 1000000000.0 << " seconds" <<std::endl;
    outputFile << "Bubble Sort," << duration.count() << " nanoseconds," << duration.count() / 1000000.0 << " milliseconds," << duration.count() / 1000000000.0 << " seconds" << std::endl;

    vector<int> arr2 = originalList;
    start = std::chrono::steady_clock::now();
    insertion_sort(arr2);
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    cout << "Insertion sort time: " << duration.count() << " nanoseconds, " <<duration.count() / 1000000.0 << " milliseconds, " << duration.count() / 1000000000.0 << " seconds" << std::endl;
    outputFile << "Insertion Sort," << duration.count() << " nanoseconds," << duration.count() / 1000000.0 << " milliseconds," << duration.count() / 1000000000.0 << " seconds" << std::endl;

    vector<int> arr3 = originalList;
    start = std::chrono::steady_clock::now();
    selection_sort(arr3);
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    cout << "Selection sort time: " << duration.count() << " nanoseconds, " <<duration.count() / 1000000.0 << " milliseconds, " << duration.count() / 1000000000.0 << " seconds" << std::endl;
    outputFile << "Selection Sort," << duration.count() << " nanoseconds," << duration.count() / 1000000.0 << " milliseconds," << duration.count() / 1000000000.0 << " seconds" << std::endl;

    vector<int> arr4 = originalList;
    start = std::chrono::steady_clock::now();
    merge_sort(arr4);
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    cout << "Merge sort time: " << duration.count() << " nanoseconds, " <<duration.count() / 1000000.0 << " milliseconds, " << duration.count() / 1000000000.0 << " seconds" << std::endl;
    outputFile << "Merge Sort," << duration.count() << " nanoseconds," << duration.count() / 1000000.0 << " milliseconds," << duration.count() / 1000000000.0 << " seconds" << std::endl;

    vector<int> arr5 = originalList;
    start = std::chrono::steady_clock::now();
    heap_sort(arr5);
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    cout << "Heap sort time: " << duration.count() << " nanoseconds, " <<duration.count() / 1000000.0 << " milliseconds, " << duration.count() / 1000000000.0 << " seconds" << std::endl;
    outputFile << "Heap Sort," << duration.count() << " nanoseconds," << duration.count() / 1000000.0 << " milliseconds," << duration.count() / 1000000000.0 << " seconds" << std::endl;

    vector<int> arr6 = originalList;
    start = std::chrono::steady_clock::now();
    quick_sort(arr6);
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    cout << "Quick sort time: " << duration.count() << " nanoseconds, " <<duration.count() / 1000000.0 << " milliseconds, " << duration.count() / 1000000000.0 << " seconds" << std::endl;
    outputFile << "Quick Sort," << duration.count() << " nanoseconds," << duration.count() / 1000000.0 << " milliseconds," << duration.count() / 1000000000.0 << " seconds" << std::endl;

    vector<int> arr7 = originalList; 
    start = std::chrono::steady_clock::now();
    cocktail_sort(arr7);
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    cout << "Cocktail sort time: " << duration.count() << " nanoseconds, " <<duration.count() / 1000000.0 << " milliseconds, " << duration.count() / 1000000000.0 << " seconds" << std::endl;

    vector<int> arr8 = originalList;
    start = std::chrono::steady_clock::now();
    cycle_sort(arr8);
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    cout << "Cycle sort time: " << duration.count() << " nanoseconds, " <<duration.count() / 1000000.0 << " milliseconds, " << duration.count() / 1000000000.0 << " seconds" << std::endl;
    outputFile << "Cycle Sort," << duration.count() << " nanoseconds," << duration.count() / 1000000.0 << " milliseconds," << duration.count() / 1000000000.0 << " seconds" << std::endl;

    vector<int> arr9 = originalList;
    start = std::chrono::steady_clock::now();
    merge_sort_3way(arr9);
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    cout << "3-way Merge sort time: " << duration.count() << " nanoseconds, " <<duration.count() / 1000000.0 << " milliseconds, " << duration.count() / 1000000000.0 << " seconds" << std::endl;
    outputFile << "3-way Merge Sort," << duration.count() << " nanoseconds," << duration.count() / 1000000.0 << " milliseconds," << duration.count() / 1000000000.0 << " seconds" << std::endl;
    
    vector<int> arr10 = originalList;
    start = std::chrono::steady_clock::now();
    counting_sort(arr10);
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    cout << "Counting sort time: " << duration.count() << " nanoseconds, " <<duration.count() / 1000000.0 << " milliseconds, " << duration.count() / 1000000000.0 << " seconds" << std::endl;
    outputFile << "Counting Sort," << duration.count() << " nanoseconds," << duration.count() / 1000000.0 << " milliseconds," << duration.count() / 1000000000.0 << " seconds" << std::endl;

    vector<int> arr11 = originalList;
    start = std::chrono::steady_clock::now();
    radix_sort(arr11);
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    cout << "Radix sort time: " << duration.count() << " nanoseconds, " <<duration.count() / 1000000.0 << " milliseconds, " << duration.count() / 1000000000.0 << " seconds" << std::endl; 
    outputFile << "Radix Sort," << duration.count() << " nanoseconds," << duration.count() / 1000000.0 << " milliseconds," << duration.count() / 1000000000.0 << " seconds" << std::endl;

    vector<int> arr12 = originalList;
    start = std::chrono::steady_clock::now();
    introsort(arr12);
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    cout << "Introsort time: " << duration.count() << " nanoseconds, " <<duration.count() / 1000000.0 << " milliseconds, " << duration.count() / 1000000000.0 << " seconds" << std::endl;
    outputFile << "Introsort," << duration.count() << " nanoseconds," << duration.count() / 1000000.0 << " milliseconds," << duration.count() / 1000000000.0 << " seconds" << std::endl;

    vector<int> arr13 = originalList;
    start = std::chrono::steady_clock::now();
    timsort(arr13);
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    cout << "Timsort time: " << duration.count() << " nanoseconds, " <<duration.count() / 1000000.0 << " milliseconds, " << duration.count() / 1000000000.0 << " seconds" << std::endl;
    outputFile << "Timsort," << duration.count() << " nanoseconds," << duration.count() / 1000000.0 << " milliseconds," << duration.count() / 1000000000.0 << " seconds" << std::endl;
    outputFile << endl;
}
  
void bubble_sort(vector<int>& arr) { //swaps adjacent out-of-order elements until the array is fully sorted O(n^2)
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void insertion_sort(vector<int>& arr) { //builds a sorted subarray by picking each element and 
    int n = arr.size();                 //shifting larger elements right until the correct position is found O(n^2)
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void selection_sort(vector<int>& arr) { //repeatedly finds the minimum element in the unsorted region and swaps it into its correct position O(n^2)
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        swap(arr[i], arr[min_idx]);
    }
}
void merge(vector<int>& arr, int left, int mid, int right) { 
    vector<int> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;
    
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }
    
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];
    
    for (int i = left, k = 0; i <= right; i++, k++) {
        arr[i] = temp[k];
    }
}

void merge_sort_helper(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort_helper(arr, left, mid);
        merge_sort_helper(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void merge_sort(vector<int>& arr) { //recursively splits the array in half, sorts each half, then merges them back together in sorted order O(n log n)
    merge_sort_helper(arr, 0, arr.size() - 1);
}
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quick_sort_helper(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick_sort_helper(arr, low, pi - 1);
        quick_sort_helper(arr, pi + 1, high);
    }
}
void quick_sort(vector<int>& arr) { //partitions the array around a pivot element, then recursively sorts the two resulting sub-arrays O(n log n) on average, O(n^2) in worst case
    quick_sort_helper(arr, 0, arr.size() - 1);
}

void heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < n && arr[left] > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;
    
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heap_sort(vector<int>& arr) { //builds a max-heap from the array, then repeatedly extracts the largest element to produce a sorted result O(n log n)
    int n = arr.size();
    
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}
void cocktail_sort(vector<int>& arr) { //is a bidirectional Bubble Sort that alternates between forward and backward passes to move elements toward their correct positions O(n^2)
    bool swapped = true;
    int start = 0;
    int end = arr.size() - 1;

    while (swapped) {
        swapped = false;

        for (int i = start; i < end; i++) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }

        if (!swapped) break;

        swapped = false;
        end--;

        for (int i = end; i >= start; i--) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        start++;
    }
}
void cycle_sort(vector<int>& arr) { //minimizes the number of writes by placing each element directly into its correct position in cycles O(n^2)
    int n = arr.size();
    for (int cycle_start = 0; cycle_start < n - 1; cycle_start++) {
        int item = arr[cycle_start];
        int pos = cycle_start;
        
        for (int i = cycle_start + 1; i < n; i++) {
            if (arr[i] < item) pos++;
        }
        
        if (pos == cycle_start) continue;
        
        while (item == arr[pos]) pos++;
        swap(item, arr[pos]);
        
        while (pos != cycle_start) {
            pos = cycle_start;
            for (int i = cycle_start + 1; i < n; i++) {
                if (arr[i] < item) pos++;
            }
            while (item == arr[pos]) pos++;
            swap(item, arr[pos]);
        }
    }
}
void merge_3way(vector<int>& arr, int left, int mid1, int mid2, int right) { 
    vector<int> temp(right - left + 1);
    int i = left, j = mid1 + 1, k = mid2 + 1, index = 0;
    
    while (i <= mid1 && j <= mid2 && k <= right) {
        if (arr[i] <= arr[j] && arr[i] <= arr[k]) {
            temp[index++] = arr[i++];
        } else if (arr[j] <= arr[i] && arr[j] <= arr[k]) {
            temp[index++] = arr[j++];
        } else {
            temp[index++] = arr[k++];
        }
    }
    
    while (i <= mid1 && j <= mid2) {
        temp[index++] = (arr[i] <= arr[j]) ? arr[i++] : arr[j++];
    }
    while (i <= mid1 && k <= right) {
        temp[index++] = (arr[i] <= arr[k]) ? arr[i++] : arr[k++];
    }
    while (j <= mid2 && k <= right) {
        temp[index++] = (arr[j] <= arr[k]) ? arr[j++] : arr[k++];
    }
    
    while (i <= mid1) temp[index++] = arr[i++];
    while (j <= mid2) temp[index++] = arr[j++];
    while (k <= right) temp[index++] = arr[k++];
    
    for (int i = left, index = 0; i <= right; i++, index++) {
        arr[i] = temp[index];
    }
}

void merge_sort_3way_helper(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid1 = left + (right - left) / 3;
        int mid2 = left + 2 * (right - left) / 3;
        merge_sort_3way_helper(arr, left, mid1);
        merge_sort_3way_helper(arr, mid1 + 1, mid2);
        merge_sort_3way_helper(arr, mid2 + 1, right);
        merge_3way(arr, left, mid1, mid2, right);
    }
}

void merge_sort_3way(vector<int>& arr) { //splits the array into three parts recursively, then merges all three sorted parts back together O(n log n)
    merge_sort_3way_helper(arr, 0, arr.size() - 1);
}
void counting_sort(vector<int>& arr) { //counts the occurrences of each element and uses those counts to place elements directly into their sorted positions O(n + k) where k is the range of input values
    if (arr.empty()) return;
    
    int maxVal = *max_element(arr.begin(), arr.end());
    int minVal = *min_element(arr.begin(), arr.end());
    int range = maxVal - minVal + 1;
    
    vector<int> count(range, 0);
    vector<int> output(arr.size());
    
    for (int i = 0; i < arr.size(); i++) {
        count[arr[i] - minVal]++;
    }
    
    for (int i = 1; i < range; i++) {
        count[i] += count[i - 1];
    }
    
    for (int i = arr.size() - 1; i >= 0; i--) {
        output[count[arr[i] - minVal] - 1] = arr[i];
        count[arr[i] - minVal]--;
    }
    
    for (int i = 0; i < arr.size(); i++) {
        arr[i] = output[i];
    }
}

void radix_sort_helper(vector<int>& arr, int exp) {
    vector<int> output(arr.size());
    vector<int> count(10, 0);
    
    for (int i = 0; i < arr.size(); i++) {
        count[(arr[i] / exp) % 10]++;
    }
    
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }
    
    for (int i = arr.size() - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    
    for (int i = 0; i < arr.size(); i++) {
        arr[i] = output[i];
    }
}

void radix_sort(vector<int>& arr) { //sorts elements digit by digit from least to most significant, using a stable sort at each digit level O(d * (n + k)) where d is the number of digits and k is the range of digit values (10 for decimal)
    if (arr.empty()) return;
    
    int maxVal = *max_element(arr.begin(), arr.end());
    
    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        radix_sort_helper(arr, exp);
    }
}

void introsort_helper(vector<int>& arr, int left, int right, int depth_limit) {
    while (right > left) {
        if (depth_limit == 0) {
            vector<int> temp(arr.begin() + left, arr.begin() + right + 1);
            heap_sort(temp);
            for (int i = left, j = 0; i <= right; i++, j++) {
                arr[i] = temp[j];
            }
            return;
        }
        int pi = partition(arr, left, right);
        if (pi - left < right - pi) {
            introsort_helper(arr, left, pi - 1, depth_limit - 1);
            left = pi + 1;
        } else {
            introsort_helper(arr, pi + 1, right, depth_limit - 1);
            right = pi - 1;
        }
        depth_limit--;
    }
}

void introsort(vector<int>& arr) { //combines Quick Sort, Heap Sort, and Insertion Sort, switching between them based on recursion depth and array size to guarantee optimal performance O(n log n) in worst case, O(n) for nearly sorted data
    int depth_limit = 2 * log(arr.size());
    introsort_helper(arr, 0, arr.size() - 1, depth_limit);
}

void timsort(vector<int>& arr) { //combines Merge Sort and Insertion Sort by exploiting naturally occurring sorted runs in the data to minimize comparisons O(n log n) in worst case, O(n) for nearly sorted data
    const int min_run = 32;
    int n = arr.size();
    
    for (int start = 0; start < n; start += min_run) {
        int end = min(start + min_run, n);
        vector<int> temp(arr.begin() + start, arr.begin() + end);
        insertion_sort(temp);
        for (int i = start, j = 0; i < end; i++, j++) {
            arr[i] = temp[j];
        }
    }
    
    int size = min_run;
    while (size < n) {
        for (int start = 0; start < n; start += size * 2) {
            int mid = start + size;
            int end = min(start + size * 2, n);
            if (mid < end) {
                merge(arr, start, mid - 1, end - 1);
            }
        }
        size *= 2;
    }
}

int main(){
    srand(time(0));
    
    int mode;
    cout << "=== Sorting Algorithm Benchmarker ===" << endl;
    cout << "Select mode:" << endl;
    cout << "1. Single use" << endl;
    cout << "2. Multiple runs" << endl;
    cout << "Enter your choice (1 or 2): ";
    cin >> mode;
    
    if (mode == 1) {
        // SINGLE USE MODE
        int choice;
        vector<int> randomList;
        
        cout << "\nSelect list type:" << endl;
        cout << "1. Random list" << endl;
        cout << "2. Custom list (from custom_list.txt)" << endl;
        cout << "Enter your choice (1 or 2): ";
        cin >> choice;
        
        if (choice == 2) {
            randomList = loadCustomList();
            if (randomList.empty()) {
                cout << "Falling back to random list..." << endl;
                int minNum, maxNum, cnt;
                cout << "Enter the minimum number, maximum number, and the count of random numbers: ";
                cin >> minNum >> maxNum >> cnt;
                randomList = generateRandomNumbers(minNum, maxNum, cnt);
                runAllSortingAlgorithms(randomList, "Random (fallback)");
            } else {
                runAllSortingAlgorithms(randomList, "Custom (Single)");
            }
        } else {
            int minNum, maxNum, cnt;
            cout << "Enter the minimum number, maximum number, and the count of random numbers: ";
            cin >> minNum >> maxNum >> cnt;
            randomList = generateRandomNumbers(minNum, maxNum, cnt);
            runAllSortingAlgorithms(randomList, "Random (Single)");
        }
    } else {
        // MULTIPLE USE MODE
        vector<vector<int>> allLists;
        
        // Load custom lists from custom_list.txt
        cout << "\nLoading custom lists from custom_list.txt..." << endl;
        vector<vector<int>> customLists = loadAllCustomListsByLine();
        for (const auto& customList : customLists) {
            allLists.push_back(customList);
        }
        
        // Ask for random lists parameters
        int totalRandomGenerated = 0;
        bool generateMore = true;
        
        while (generateMore) {
            int minNumber, maxNumber, count, numRandomRuns;
            
            cout << "\nEnter the minimum number and maximum number for the random lists: ";
            cin >> minNumber >> maxNumber;
            cout << "Enter the count of elements per random list: ";
            cin >> count;
            cout << "How many random lists do you want to generate with these parameters? ";
            cin >> numRandomRuns;
            
            // Generate random lists
            for (int i = 0; i < numRandomRuns; i++) {
                vector<int> randomList = generateRandomNumbers(minNumber, maxNumber, count);
                allLists.push_back(randomList);
                totalRandomGenerated++;
            }
            
            cout << "\nGenerated " << numRandomRuns << " random lists." << endl;
            
            // Ask if they want to generate more
            char choice;
            cout << "Do you want to generate more random lists with different parameters? (y/n): ";
            cin >> choice;
            generateMore = (choice == 'y' || choice == 'Y');
        }
        
        cout << "\n" << string(50, '=') << endl;
        cout << "Total lists to process: " << allLists.size() << " (";
        cout << customLists.size() << " custom + " << totalRandomGenerated << " random)" << endl;
        cout << string(50, '=') << endl;
        
        // Run all sorting algorithms for each list
        for (int i = 0; i < allLists.size(); i++) {
            string label;
            if (i < customLists.size()) {
                label = "Custom List " + to_string(i + 1);
            } else {
                label = "Random List " + to_string(i - customLists.size() + 1);
            }
            runAllSortingAlgorithms(allLists[i], label);
        }
        
        cout << "\n" << string(50, '=') << endl;
        cout << "All " << allLists.size() << " lists have been processed!" << endl;
        cout << string(50, '=') << endl;
    }
    
    return 0;
}
