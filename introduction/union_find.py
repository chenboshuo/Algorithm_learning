import unittest
import logging
from typing import *
logging.root.setLevel(level=logging.INFO)


class UnionFind():
    def __init__(self, n: int, text: str):
        """ Initialize nodes with integer names(0-n-1)
          @param n the number of nodes
          @param text the user input
        """
        self.id = list(range(n))
        self.count = n
        for line in text.strip().split('\n'):
            i, j = map(int, line.split())
            if not self.has_connected(i, j):
                self.union(i, j)
                self.count -= 1

    def union(self, node_p: int, node_q: int) -> None:
        """ Add connection between p and q
          @param node_p the node
          @param node_q the other node
        """
        p_id = self.id[node_p]
        for i in range(len(self.id)):
            if self.id[i] == p_id:
                self.id[i] = self.id[node_q]

    def find(self, node_p: int) -> int:
        """find components id
          @param node_p the node
          @return node_p's id
        """
        return self.id[node_p]

    def has_connected(self, node_p: int, node_q: int) -> bool:
        """ returns true if p and q in the same component
          @param node_p the node
          @param node_q the other node
          @return the boolean value
        """
        return self.find(node_p) == self.find(node_q)

    def __len__(self) -> int:
        """number of components"""
        return self.count


def case(nodes_size: int, text: str) -> int:
    """return the number of components
      @param text input
      @return the components
    """
    uf = UnionFind(nodes_size)


class TestStringMethods(unittest.TestCase):

    def test_tiny(self):
        with open("tests/tinyUF.txt", "r") as t:
            tiny = UnionFind(10, t.read())
            self.assertEqual(len(tiny), 2)

    def test_medium(self):
        with open("tests/mediumUF.txt", "r") as t:
            medium = UnionFind(625, t.read())
            self.assertEqual(len(medium), 3)


if __name__ == '__main__':
    unittest.main()

    print(line)

# ..
# ----------------------------------------------------------------------
# Ran 2 tests in 0.035s

# OK
