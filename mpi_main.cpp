#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>
#include <cmath>

using namespace std;

vector<int> generateRandomNumbers(int maxNumber, int count) {
    std::vector<int> randomList;

    for(int i = 0;i < count; i++)
    {
        randomList.push_back(rand() % maxNumber + 1);
    }

    return randomList;
}
  
void bubble_sort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void insertion_sort(vector<int>& arr) {
    int n = arr.size();
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

void selection_sort(vector<int>& arr) {
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

void merge_sort(vector<int>& arr) {
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
void quick_sort(vector<int>& arr) {
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

void heap_sort(vector<int>& arr) {
    int n = arr.size();
    
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}
void cocktail_sort(vector<int>& arr) {
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
void cycle_sort(vector<int>& arr) {
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

void merge_sort_3way(vector<int>& arr) {
    merge_sort_3way_helper(arr, 0, arr.size() - 1);
}
void counting_sort(vector<int>& arr) {
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

void radix_sort(vector<int>& arr) {
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

void introsort(vector<int>& arr) {
    int depth_limit = 2 * log(arr.size());
    introsort_helper(arr, 0, arr.size() - 1, depth_limit);
}

void timsort(vector<int>& arr) {
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
void bogo_sort(vector<int>& arr) {
    while (!is_sorted(arr.begin(), arr.end())) {
        random_shuffle(arr.begin(), arr.end());
    }
}

void stalin_sort(vector<int>& arr) {
    vector<int> result;
    result.push_back(arr[0]);
    for (int i = 1; i < arr.size(); i++) {
        if (arr[i] >= result.back()) {
            result.push_back(arr[i]);
        }
    }
    arr = result;
}

void miracle_sort(vector<int>& arr) {
    while (!is_sorted(arr.begin(), arr.end())) {
        // Do nothing, just hope for a miracle
    }
}
int main(){
    srand(time(0));
    int x,y;
    cout<<"Enter the maximum number and the count of random numbers: ";
    cin>>x>>y;
    cout<<"Use meme sorting algorithms? !might not work properly! (y/n): ";
    char choice;
    cin>>choice;
    vector<int> randomList = generateRandomNumbers(x, y);
    
    vector<int> arr1 = randomList;
    auto start = std::chrono::steady_clock::now();
    bubble_sort(arr1);
    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::cout << "Bubble sort time: " << duration.count() << " nanoseconds, " <<duration.count() / 1000000.0 << " milliseconds, " << duration.count() / 1000000000.0 << " seconds" <<std::endl;
    
    vector<int> arr2 = randomList;
    start = std::chrono::steady_clock::now();
    insertion_sort(arr2);
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::cout << "Insertion sort time: " << duration.count() << " nanoseconds, " <<duration.count() / 1000000.0 << " milliseconds, " << duration.count() / 1000000000.0 << " seconds" << std::endl;
    
    vector<int> arr3 = randomList;
    start = std::chrono::steady_clock::now();
    selection_sort(arr3);
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::cout << "Selection sort time: " << duration.count() << " nanoseconds, " <<duration.count() / 1000000.0 << " milliseconds, " << duration.count() / 1000000000.0 << " seconds" << std::endl;

    vector<int> arr4 = randomList;
    start = std::chrono::steady_clock::now();
    merge_sort(arr4);
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::cout << "Merge sort time: " << duration.count() << " nanoseconds, " <<duration.count() / 1000000.0 << " milliseconds, " << duration.count() / 1000000000.0 << " seconds" << std::endl;

    vector<int> arr5 = randomList;
    start = std::chrono::steady_clock::now();
    heap_sort(arr5);
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::cout << "Heap sort time: " << duration.count() << " nanoseconds, " <<duration.count() / 1000000.0 << " milliseconds, " << duration.count() / 1000000000.0 << " seconds" << std::endl;

    vector<int> arr6 = randomList;
    start = std::chrono::steady_clock::now();
    quick_sort(arr6);
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::cout << "Quick sort time: " << duration.count() << " nanoseconds, " <<duration.count() / 1000000.0 << " milliseconds, " << duration.count() / 1000000000.0 << " seconds" << std::endl;

    vector<int> arr7 = randomList; 
    start = std::chrono::steady_clock::now();
    cocktail_sort(arr7);
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::cout << "Cocktail sort time: " << duration.count() << " nanoseconds, " <<duration.count() / 1000000.0 << " milliseconds, " << duration.count() / 1000000000.0 << " seconds" << std::endl;

    vector<int> arr8 = randomList;
    start = std::chrono::steady_clock::now();
    cycle_sort(arr8);
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::cout << "Cycle sort time: " << duration.count() << " nanoseconds, " <<duration.count() / 1000000.0 << " milliseconds, " << duration.count() / 1000000000.0 << " seconds" << std::endl;

    vector<int> arr9 = randomList;
    start = std::chrono::steady_clock::now();
    merge_sort_3way(arr9);
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::cout << "3-way Merge sort time: " << duration.count() << " nanoseconds, " <<duration.count() / 1000000.0 << " milliseconds, " << duration.count() / 1000000000.0 << " seconds" << std::endl;

    vector<int> arr10 = randomList;
    start = std::chrono::steady_clock::now();
    counting_sort(arr10);
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::cout << "Counting sort time: " << duration.count() << " nanoseconds, " <<duration.count() / 1000000.0 << " milliseconds, " << duration.count() / 1000000000.0 << " seconds" << std::endl;

    vector<int> arr11 = randomList;
    start = std::chrono::steady_clock::now();
    radix_sort(arr11);
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::cout << "Radix sort time: " << duration.count() << " nanoseconds, " <<duration.count() / 1000000.0 << " milliseconds, " << duration.count() / 1000000000.0 << " seconds" << std::endl; 

    vector<int> arr12 = randomList;
    start = std::chrono::steady_clock::now();
    introsort(arr12);
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::cout << "Introsort time: " << duration.count() << " nanoseconds, " <<duration.count() / 1000000.0 << " milliseconds, " << duration.count() / 1000000000.0 << " seconds" << std::endl;

    vector<int> arr13 = randomList;
    start = std::chrono::steady_clock::now();
    timsort(arr13);
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::cout << "Timsort time: " << duration.count() << " nanoseconds, " <<duration.count() / 1000000.0 << " milliseconds, " << duration.count() / 1000000000.0 << " seconds" << std::endl;
    
    if(choice == 'y' || choice == 'Y') {
        
    }
    return 0;
}
