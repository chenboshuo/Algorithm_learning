from copy import copy
import unittest
from typing import List
import logging
logging.root.setLevel(level=logging.INFO)


class Permutation():
    """A class generate the permutation of a set"""

    def __init__(self, *elements):
        """
        @param elements the elements to permutation
        """
        self.elements = list(elements)
        self.permutations = list(self.recursive_generation(0, len(elements)-1))
        self.l = []

    def recursive_generation(self, begin: int, end: int) -> List:
        """generate the permutations rescursively
          @param begin the index of the begin element
          @param end the index of the end element
        """
        if begin == end:
            l = copy(self.elements)
            yield l

        else:
            for i in range(begin, end+1):
                # swap i with begin
                self._swap(begin, i)
                # permutation
                yield from self.recursive_generation(begin+1, end)
                # swap i with begin
                self._swap(begin, i)

    def _swap(self, i: int, j: int) -> None:
        """swap self.elements[i] and self.elements[j]"""
        self.elements[j], self.elements[i] \
            = self.elements[i], self.elements[j]


class TestPermutation(unittest.TestCase):
    def test_base0(self):
        p = Permutation()
        self.assertEqual(p.permutations, [])

    def test_base1(self):
        p = Permutation(1)
        self.assertEqual(p.permutations, [[1]])

    def test_base2(self):
        p = Permutation(1, 2)
        self.assertEqual(p.permutations, [[1, 2], [2, 1]])

    def test_case3(self):
        p = Permutation(1, 2, 3)
        self.assertEqual(p.permutations, [[1, 2, 3], [1, 3, 2],
                                          [2, 1, 3], [2, 3, 1],
                                          [3, 2, 1], [3, 1, 2]])


if __name__ == '__main__':
    unittest.main()

    print(line)
