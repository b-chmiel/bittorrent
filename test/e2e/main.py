import unittest
import subprocess

class Test(unittest.TestCase):
    def test_help(self):
        result = subprocess.run(["../src/main", "--help"], stdout=subprocess.PIPE)
        expected = b"""Allowed options:
  --help                produce help message
  --input arg           input filename
  --client-url arg      client url
  --output arg          output torrent file
"""

        self.assertTrue(expected in result.stdout)


if __name__ == '__main__':
    unittest.main()