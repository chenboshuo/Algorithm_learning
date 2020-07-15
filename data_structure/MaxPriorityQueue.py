"""
An appropriate data type in such an environment supports
two operations: remove the maximum and insert.
Such a data type is called a priority queue.

Using priority queues is similar to using queues(remove the oldest)
and stacks(remove the newest)
"""
import unittest


class MaxPriorityQueue():
    def __init__(self, *argc):
        """create a priority queue"""
        ...
        self.pq = []

    def insert(self, val):
        """insert a key into the priority queue"""
        ...

    def max(self):
        """return the largest kay"""
        ...

    def pop(self):
        """return and remove the largest key"""
        ...

    def is_empty(self):
        """is the priority queue empty"""
        ...

    def __len__(self):
        """number of keys in the priority queue"""
        ...

    def _less(self, i: int, j: int) -> bool:
        """
        compare self.pq[i] and self.pq[j]
        """
        return self.pq[i] - self.pq[j]

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
        while k > 1 and less(k//2, k):
            self._exchange(k//2, k)
            k //= 2


class testMaxPriorityQueue(unittest.TestCase):
    def text_small(self):
        h = MaxPriorityQueue(9, 9, 6)
        self.assertEqual(len(h), 3)
        self.assertEqual(h.max(), 9)
        self.assertEqual(h.pop(), 9)
        self.assertEqual(len(h), 2)
        h.insert(8)
        expect = [9, 8, 6]
        for i in expect:
            self.assertEqual(h.pop(), i)

    def test_sort():
        h = MaxPriorityQueue()
        for i in [3, 1, 4, 1, 5, 9, 2, 6]:
            pq.insert(i)
        ans = []
        while h.is_empty():
            a = h.pop()
            ans.append(a)
        self.assertEqual(ans, [1, 1, 2, 3, 4, 5, 6, 9])


if __name__ == '__main__':
    unittest.main()

    print(line)
