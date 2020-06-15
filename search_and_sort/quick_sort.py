from typing import List
import random 

class Array:
    def __init__(self,nums):
        self.nums = nums

    def sort(self):
        random.shuffle(self.nums)
        self._quick_sort(0,len(self.nums)-1)

    def _quick_sort(self,left,right):
        """
        Quicksort is a recursive program that sorts a subarray 
        self.nums[left:right+1] by using _partition() method
        that puts self.nums[i] into the position and arranges
        the rest of the entries such that the recursive calls 
        finish the sort.
        """
        if left >= right:
            return None
        p = self._partition(left,right) # partion
        self._quick_sort(left, p-1) # sort left part
        self._quick_sort(p+1,right) # sort right part
    
    def _partition(self,left, right):
        """ partition into 
        self.nums[left:i] self.nums[i], self.nums[i:right+1]
        """
        i,j = left+1, right
        v = self.nums[left] # partitioning item
        while True:
            while self.nums[i] <= v and i < right:
                i += 1
            while self.nums[j] >= v and j > left:
                j -= 1
            if i >= j:
                break
            self.nums[i],self.nums[j] = self.nums[j],self.nums[i]
        self.nums[left], self.nums[j] = self.nums[j], self.nums[left]
        return j

if __name__ == "__main__":
    test = Array(list('qwertyuiopasdfghjklzxcvbnm'))
    test.sort()
    print("".join(test.nums))