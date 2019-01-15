#include <vector>
#include <functional>

/*
 * SUBSET ITERATOR
 * 09/15/2018
 * Iterate on all subsets of a given vector container
 * Uses GrayCode to minimize allocations. 
 * @author: Arnav Kansal <arnav.kansal@nyu.edu>
 *
 */

/*
 * FUTURE OPTIMIZATIONS
 * keep mapping, inverse mapping encoded in 384Bit (log_2(64)*64)
 * prefereably a 6 8*B register
 */

template <typename T>
class SubSets{
public:
    // experimental, enter vector of size < 63 only
    SubSets(const std::vector<T>& container) : container_(container){
        peek_.reserve(container.size());
        mapping_.reserve(container.size());
        invmapping_.reserve(container.size());
        capacity_ = (1L << container.size());
    };
    const std::vector<std::reference_wrapper<T>>& current() const{
        return peek_;
    };
    void next(){
        uint64_t oldbinary = binTogray(set_);
        set_ = (set_ + 1) & (capacity_ - 1); // a % b = a & (b-1) if b is power of two
        uint64_t newbinary = binTogray(set_);
        // diff is exactly a power of two.
        uint64_t diff = newbinary ^ oldbinary;
        // check addition or deletion and index
        size_t index = setbitpos(diff);
        if(diff & oldbinary)
            remove(index);
        else
            insert(index);
    }
    bool isStart() const {return set_ == 0;}
private:
    uint64_t set_ = 0;
    uint64_t capacity_;

    // storage for actual set
    std::vector<T> container_;
    // peek vector which offers access to next subset
    std::vector<std::reference_wrapper<T>> peek_;
    
    // mapping between bitmap and peek
    std::vector<size_t> mapping_;
    std::vector<size_t> invmapping_;
    
    __attribute__((always_inline)) static uint64_t binTogray(uint64_t n) {
        return n ^ (n>>1);
    }
    // does not work for 64
    __attribute__((always_inline)) static size_t setbitpos(uint64_t n) {
        return __builtin_ctz(n);   
    }
    __attribute__((always_inline)) void insert(size_t pos){
        peek_.push_back(container_[pos]);
        mapping_[pos] = peek_.size()-1;
        invmapping_[peek_.size()-1] = pos;
    }
    __attribute__((always_inline)) void remove(size_t pos){
        size_t last = mapping_[pos];
        std::swap(peek_[last], peek_.back());
        mapping_[invmapping_[peek_.size()-1]] = last;
        invmapping_[last] = invmapping_[peek_.size()-1];
        peek_.pop_back();
    }
};
