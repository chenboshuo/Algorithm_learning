"""
An appropriate data type in such an environment supports
two operations: remove the maximum and push.
Such a data type is called a priority queue.

Using priority queues is similar to using queues(remove the oldest)
and stacks(remove the newest)
"""
import unittest


class MaxPriorityQueue():
    def __init__(self, *argc):
        """create a priority queue"""
        self.pq = [None]
        self.size = 0
        for i in argc:
            self.push(i)


    def push(self, val):
        """push a key into the priority queue"""
        self.size += 1
        self.pq.append(val)
        self._swim(self.size)

    def max(self):
        """return the largest kay"""
        return self.pq[1]

    def pop(self):
        """return and remove the largest key"""
        self._exchange(1,self.size)
        largest = self.pq.pop()
        self.size -= 1
        self._sink(1) # restore heap property
        return largest
        

    def is_empty(self):
        """is the priority queue empty"""
        return self.size == 0

    def __len__(self):
        """number of keys in the priority queue"""
        return self.size

    def _less(self, i: int, j: int) -> bool:
        """
        compare self.pq[i] and self.pq[j]
        """
        return self.pq[i] < self.pq[j]

    def _exchange(self,i:int,j:int) -> None:
        self.pq[i], self.pq[j] = self.pq[j], self.pq[i]
    
    def _swim(self, k):
        """
        If the heap is violated because a node's key
        becomes larger than that node's parent key,
        then we can make progress toward fixing 
        the violation by exchanging the node with its parent
        @param k the index of the node
                 that violates order
        """
        while k > 1 and self._less(k//2, k):
            self._exchange(k//2, k)
            k //= 2

    def _sink(self, k):
        """
        If the heap order is violate because 
        a node's key become smaller than one or 
        both of that node's child's keys,
        then we can make progress toward fixing the
        violation by exchanging the node with
        the larger of its two children.
        This switch may cause a violation at the child;
        we fix that violation in the same way.
        """
        while 2*k <= self.size:
            j = 2*k
            if j < self.size and self._less(j,j+1):
                j += 1
            if not self._less(k,j):
                break
            self._exchange(k,j)
            k = j

class testMaxPriorityQueue(unittest.TestCase):
    def test_small(self):
        h = MaxPriorityQueue(9, 9, 6)
        self.assertEqual(len(h), 3)
        self.assertEqual(h.max(), 9)
        self.assertEqual(h.pop(), 9)
        self.assertEqual(len(h), 2)
        h.push(8)
        expect = [9, 8, 6]
        for i in expect:
            self.assertEqual(h.pop(), i)

    def test_sort(self):
        h = MaxPriorityQueue()
        for i in [3, 1, 4, 1, 5, 9, 2, 6]:
            h.push(i)
        ans = []
        while not h.is_empty():
            a = h.pop()
            ans.append(a)
        self.assertEqual(ans, [9, 6, 5, 4, 3, 2, 1, 1])


if __name__ == '__main__':
    unittest.main()

    print(line)
