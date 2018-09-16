#include <vector>
#include <functional>

/*
 * SUBSET ITERATOR
 * 09/15/2018
 * Iterate on all subsets of a given vector container
 * Uses simple binary coding. 
 * @author: Arnav Kansal <arnav.kansal@nyu.edu>
 *
 */

/* for comparison only, does a lot of unnecessary allocations */

template <typename T>
class SubSets{
public:
    // experimental, enter vector of size < 63 only
    SubSets(const std::vector<T>& container) : container_(container){
        capacity_ = (1L << container.size());
    };
    const std::vector<std::reference_wrapper<T>>& current() const{
        return peek_;
    };
    void next(){
        set_ = (set_ + 1) % capacity_;
        construct();
    }
    bool isStart() const {return set_ == 0;}
private:
    uint64_t set_ = 0;
    uint64_t capacity_;

    // storage for actual set
    std::vector<T> container_;
    // peek vector which offers access to next subset
    std::vector<std::reference_wrapper<T>> peek_;
    
    __attribute__ ((always_inline)) void construct(){
        peek_.clear();
        int ct = 0;
        uint64_t temp = set_;
        while(temp){
            if(temp & 1){
                peek_.push_back(container_[ct]);
            }
            temp = temp >> 1;
            ct++;
        }
    }
};
