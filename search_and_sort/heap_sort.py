import unittest

def _sink(heap, k, length):
    # length = len(heap)
    child = 2*k + 1
    while child < length:
        if child+1 < length and heap[child] < heap[child+1]:
            child += 1
        if heap[k] >= heap[child]:
            break 
        heap[k], heap[child] = heap[child], heap[k]
        k = child 
        child = 2*k + 1

def heap_sort(l):
    k = (len(l)-2)//2
    while k >= 0:
        _sink(l,k,len(l))
        k -= 1
    disorder = len(l) 
    while disorder:
        l[0], l[disorder-1] = l[disorder-1], l[0]
        disorder -= 1
        _sink(l,0,disorder)
    return l
    
    

class TestHeapsort(unittest.TestCase):
    def test_sink(self):
        l = [0,1,7,9,2,3]
        _sink(l,0,len(l))
        self.assertEqual(l,[7,1,3,9,2,0])

    def test_small(self):
        l = [3,5,1]
        self.assertEqual(heap_sort(l),[1,3,5])

    def test_order(self):
        l = [5,3,1]
        self.assertEqual(heap_sort(l),[1,3,5])
    
    def test_n(self):
        l = [0, 1, 2, 7, 9, 3]
        self.assertEqual(heap_sort(l),[0,1,2,3,7,9])

    def test_large(self):
        l = [1,3,5,7,9,11,10,8,6,4,2,0]
        self.assertEqual([0,1,2,3,4,5,6,7,8,9,10,11],heap_sort(l))


if __name__ == '__main__':
    unittest.main()

    print(line)
