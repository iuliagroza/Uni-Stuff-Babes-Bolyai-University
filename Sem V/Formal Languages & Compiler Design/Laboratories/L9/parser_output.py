class Node:
    def __init__(self, symbol, data=None):
        self.symbol = symbol
        self.data = data
        self.parent = None
        self.sibling = None
        self.firstChild = None

class ParserOutput:
    def __init__(self):
        self.root = None
        self.current_node = None

    def add_node(self, symbol, data=None):
        new_node = Node(symbol, data)
        if self.current_node is None:
            self.root = new_node
        else:
            if self.current_node.firstChild is None:
                self.current_node.firstChild = new_node
            else:
                current_child = self.current_node.firstChild
                while current_child.sibling:
                    current_child = current_child.sibling
                current_child.sibling = new_node
            new_node.parent = self.current_node
        self.current_node = new_node

    def ascend_tree(self):
        if self.current_node:
            self.current_node = self.current_node.parent

    def transform_tree(self):
        return self._transform_tree_recursive(self.root)

    def _transform_tree_recursive(self, node):
        if node is None:
            return ""
        result = node.symbol
        child = node.firstChild
        while child:
            result += self._transform_tree_recursive(child)
            child = child.sibling
        return result

    def print_to_screen(self):
        tree_representation = self.transform_tree()
        print(tree_representation)

    def print_to_file(self, file_path):
        tree_representation = self.transform_tree()
        with open(file_path, "w") as file:
            file.write(tree_representation)
