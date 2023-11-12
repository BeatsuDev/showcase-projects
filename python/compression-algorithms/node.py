class Node:
    def __init__(self, value, left=None, right=None):
        self.value = value
        self.left = left
        self.right = right

    def __str__(self):
        return f"({self.left} - {self.right})"

    def __repr__(self):
        return self.__str__()

    def __getitem__(self, key):
        if key == 0 and not self.left == None:
            return self.left
        elif key == 1 and not self.right == None:
            return self.right
        else:
            raise IndexError("Index out of bounds")

    def __contains__(self, data: str):
        if data == self.left or data == self.right:
            return True

        if isinstance(self.left, Node):
            if data in self.left:
                return True

        if isinstance(self.right, Node):
            if data in self.right:
                return True

    def serialize_to_binary(self) -> str:
        if self.left is None and self.right is None:
            return '1' + format(self.value, '08b')
        else:
            left_serialized = ""
            if isinstance(self.left, Node):
                left_serialized = self.left.serialize_to_binary()
            else:
                left_serialized = "1" + format(self.left, "08b")

            right_serialized = ""
            if isinstance(self.right, Node):
                right_serialized = self.right.serialize_to_binary()
            else:
                right_serialized = "1" + format(self.right, "08b")

            return "0" + left_serialized + right_serialized

    @classmethod
    def deserialize_binary(cls, node_binary: str):
        def helper(index):
            if index >= len(node_binary):
                return None, index

            if node_binary[index] == '1':
                leaf = int(node_binary[index + 1:index + 9], 2)
                return leaf, index + 9
            else:
                left, index = helper(index + 1)
                right, index = helper(index)
                return Node(None, left, right), index

        root, _ = helper(0)
        return root

    def serialize(self):
        binary = self.serialize_to_binary()
        # add a 1 at the beginning to avoid the int transformation
        # removing leading 0 bits. This must be stripped when deserializing
        return int("1" + binary, 2).to_bytes(len(binary) // 8 + 1, 'big')

    @classmethod
    def deserialize(cls, node_bytes: str):
        # Deserialize from index 3 and out to strip away the first bit
        binary = bin(int.from_bytes(node_bytes, 'big'))[3:]
        return cls.deserialize_binary(binary)

    def get_leaves(self):
        leaves = []

        if not isinstance(self.left, Node):
            leaves.append(self.left)
        else:
            leaves.extend(self.left.get_leaves())
        if not isinstance(self.right, Node):
            leaves.append(self.right)
        else:
            leaves.extend(self.right.get_leaves())

        return leaves
