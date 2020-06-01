"""
The idea is to rearrange the array to give it the property that taking every
h-th entry(starting everywhere) yields a storted subsequence.
Such an array is said to be h-sorted.

An h-sorted sequence is h interleaved sorted subsequence
L E E A M H L E P S O L T S X R
L ------M-------P-------T
  E-------H-------S-------S
    E-------L-------O-------X
      A-------E-------L-------R

Shellsort gains efficiency by making a tradeoff between size and partial order
in the subsequence.
"""

def shell_sort(nums):
    """Sorted nums into increasing order"""
    h = 1
    while h<len(nums)//3:
        h = 3*h + 1
    while h >= 1:
        # h-sort the array
        for i in range(h,len(nums)):
          j = i
          while j>=h and nums[j] < nums[j-h]:
            nums[j],nums[j-h] = nums[j-h],nums[j]
            j -= h
        h //= 3

if __name__ == "__main__":
    s = list("shellsortexample")
    shell_sort(s)
    print("".join(s))