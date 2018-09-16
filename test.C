#include <iostream>
#include "SubSets.H"

size_t globalSum = 0;

// replace with function(vec) , for eg to calculate sum of path, tsp etc.
void print(const std::vector<std::reference_wrapper<std::string>>& vec){
    for(auto v : vec){
        globalSum += v.get().size();
    }
}

int main(){
    std::vector<std::string> vec = {"Bitset", "can", "be", "used", "to", "iterate", "over", "all", "possible", "subsets", "of", "elements", "in", "container.", "Change", "print", "function", "to", "something", "useful", "such", "as", "finding", "sum", "of", "all", "the", "strings", "in", "the", "subset"};
    SubSets<std::string> b(vec);
    size_t count = 0;
    std::cout<<vec.size() << std::endl;
    do{
        ++count;
        //if(count % 1000000 == 0)
          //  printf("%d\n", count);
        print(b.current());
        b.next();
    }while(!(b.isStart()));
    std::cout << count << std::endl;
    std::cout << globalSum << std::endl;
    return 0;
}
