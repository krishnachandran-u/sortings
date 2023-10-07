#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <utility>

std::vector<int> v;
int threshold = 10;

void qksort(int begin, int end);
int split(int begin, int end);
void insertion_sort(int begin, int end);
void optimal_sort(int begin, int end);

int main(){
    int n; 
    std::cin >> n;

    v.resize(n);
    for(int &i: v)
        std::cin >> i;

    std::srand(static_cast<int>(std::time(0)));  

    optimal_sort(0, n - 1);

    std::cout << "sorted: " << "\n";
    for(int &i: v)
        std::cout << i << " ";
    std::cout << "\n";

    return 0;
}

void qksort(int begin, int end){
    int p = split(begin, end); 

    int q = split(p + 1, end);

    optimal_sort(begin, p - 1);

    optimal_sort(p + 1, q - 1);

    optimal_sort(q + 1, end);
}

int split(int begin, int end){
    if(begin >= end) return end + 1;

    int size = end - begin + 1;

    int random_index = std::rand() % size + begin;
    std::swap(v[begin], v[random_index]);

    int cnt = 0;
    for(int i = begin + 1; i <= end; i++)
        cnt += (v[i] <= v[begin]);

    int p = begin + cnt;
    std::swap(v[begin], v[p]);

    int I = begin, J = end;
    while(I < p && p < J){
        while(I < p && v[I] <= v[p])
            I++;
        while(p < J && v[J] > v[p])
            J--;
        if(I < p && p < J)
            std::swap(v[I++], v[J--]);
    }

    return p;
}

void insertion_sort(int begin, int end){
    for(int i = begin + 1, j; i <= end; i++){
        int k = v[i];
        j = i - 1;

        while(j >= 0 && v[j] > k){
            v[j + 1] = v[j];
            j--;
        }

        v[j + 1] = k;
    }

    return;
}

void optimal_sort(int begin, int end){
    if(begin >= end) return;

    int size = end - begin + 1;
    if(size > threshold)
        qksort(begin, end);
    else
        insertion_sort(begin, end);
}
