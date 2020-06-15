from typing import List
class Array:
    def __init__(self, nums:List):
        self.nums = nums
  
    def _merge(self,left,mid,right):
        """
        Merge self.nums[left:mid+1] with nums[mid+1:right]
        """
        i = left
        j = mid+1
        pre = self.nums[:]

        for k in range(left,right+1):
            if i > mid: # left part has been placed in the array
                self.nums[k] = pre[j]
                j += 1
            elif j > right: # right part has been placed in the array
                self.nums[k] = pre[i]
                i += 1
            # compare and merge
            elif pre[j] < pre[i]:
                self.nums[k] = pre[j]
                j += 1
            else:
                self.nums[k] = pre[i]
                i += 1
    
    def _sort(self,left,right):
        if(left >=right):
            return None
        mid = left + ((right-left) >> 1)
        self._sort(left,mid)
        self._sort(mid+1,right)
        self._merge(left,mid,right)

    def sort(self):
        # recursive implementation 
        # self._sort(0,len(self.nums)-1)

        # bottom-up mergesort
        subarray_size = 1
        length = len(self.nums)
        while subarray_size < length:
            for left in range(0,length,2*subarray_size):
                self._merge(left=left,
                    mid=left+subarray_size-1,
                    right=min(left+2*subarray_size-1,length-1))
                
            subarray_size *= 2
    

if __name__ == "__main__":
    test = Array([9,1,6,4])
    test.sort()
    print(test.nums)