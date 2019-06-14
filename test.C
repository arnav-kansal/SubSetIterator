#include <iostream>
#include <vector>

#ifdef TEST
    #include "simpleSubSetIterator.H"
#else
    #include "fastSubSetIterator.H"
#endif

size_t globalSum = 0;

// replace with function(vec) , for eg to calculate sum of path, tsp etc.
void print(const std::vector<std::reference_wrapper<std::string>>& vec){
    for(auto v : vec){
        globalSum += v.get().size();
    }
}

int main(){
    std::vector<std::string> vec = {"Bitset", "can", "be", "used", "to", "iterate", "over", "all", "possible", "subsets", "of", "elements", "in", "container.", "Change", "print", "function", "to", "something", "useful", "such", "as", "finding", "sum", "of", "all", "the"};//, "strings", "in", "the", "subset"};
    SubSets<std::string> b(vec);
    size_t count = 0;
    std::cout<< "size of original set: " << vec.size() << '\n';
    do{
        ++count;
        //if(count % 1000000 == 0)
          //  printf("%d\n", count);
        print(b.current());
        b.next();
    }while(!(b.isStart()));
    std::cout << "number of subsets: " << count << '\n';
    std::cout << "checksum: " << globalSum << '\n';
    return 0;
}
