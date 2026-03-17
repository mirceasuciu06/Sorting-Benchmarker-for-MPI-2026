#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;

vector<int> generateRandomNumbers(int maxNumber, int count) {

    srand(time(0));
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
int main(){
    vector<int> randomList = generateRandomNumbers(100, 10);
    auto start = std::chrono::steady_clock::now();
    bubble_sort(randomList);
    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::cout << "Sorting time: " << duration.count() << " nanoseconds" << std::endl;
}