from typing import List
import random 

class Array:
    def __init__(self,nums):
        self.nums = nums

    def sort(self):
        random.shuffle(self.nums)
        self._quick_sort(0,len(self.nums)-1)
        # self.quick_3_way(0,len(self.nums)-1)

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

    def quick_3_way(self):
        return self._quick_3_way(0,len(self.nums)-1)

    def _quick_3_way(self, left, right):
        if(left >= right):
            return None
        lt,i,gt = left,left+1,right
        while i <= gt:
            if self.nums[i] < self.nums[left]:
                self.nums[lt],self.nums[i] = self.nums[i], self.nums[lt]
                lt += 1
                i += 1
            elif self.nums[i] > self.nums[left]:
                self.nums[gt],self.nums[i] = self.nums[i], self.nums[gt]
                gt -= 1
            else:
                i += 1
            self._quick_3_way(left, lt-1)
            self._quick_3_way(gt+1, right)

    def __str__(self):
        return "".join(test.nums)
if __name__ == "__main__":
    test = Array(list('qwertyuiopasdfghjklzxcvbnm'))
    # test.sort()
    test.quick_3_way()
    print(test)