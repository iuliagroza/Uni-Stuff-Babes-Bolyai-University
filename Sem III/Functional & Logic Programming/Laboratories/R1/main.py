class Node:
    def __init__(self, elem):
        self.elem = elem
        self.next = None


class List:
    def __init__(self):
        self.first = None

    def get_first_elem(self):
        return self.first.elem

    def is_empty(self):
        return self.first is None

    def add_elem_on_first_pos(self, e):
        new_elem = Node(e)
        new_elem.next = self.first
        self.first = new_elem
        return self

    def sublist(self):
        sublst = List()
        sublst.first = self.first.next
        return sublst


def create_empty_list():
    lst = List()
    return lst


def create_list():
    lst = List()
    lst.first = create_list_rec()
    return lst


def create_list_rec():
    x = int(input("x="))
    if x == 0:
        return None
    else:
        node = Node(x)
        node.next = create_list_rec()
        return node


def print_list(list_to_print):
    print_list_rec(list_to_print.first)


def print_list_rec(nod):
    if nod is not None:
        print(nod.elem, end=" ")
        print_list_rec(nod.next)


def concat_lists(first_list, second_list):
    if first_list.is_empty() and second_list.is_empty():
        return create_empty_list()
    elif first_list.is_empty():
        return concat_lists(first_list, second_list.sublist()).add_elem_on_first_pos(second_list.get_first_elem())
    else:
        return concat_lists(first_list.sublist(), second_list).add_elem_on_first_pos(first_list.get_first_elem())


def replace(lst, e, initial):
    if lst.is_empty():
        return create_empty_list()
    elif lst.get_first_elem() == e:
        return concat_lists(initial, replace(lst.sublist(), e, initial))
    else:
        return replace(lst.sublist(), e, initial).add_elem_on_first_pos(lst.get_first_elem())


def det_k(lst, k):
    if lst.first is None:
        return None
    elif k == 1:
        return lst.first.elem
    else:
        return det_k(lst.sublist(), k - 1)


def main():
    print("""Type the corresponding number of the command:
    1. Substitute all occurrences of an element from a list with another list.
    2. Find the nth element of a list""")

    choice = int(input(">>> "))

    print("Provide initial list:")
    lst = create_list()

    if choice == 1:
        print("Provide placeholder list:")
        rep_lst = create_list()
        print("Provide element to be replace:")
        e = int(input("e = "))
        print("Solution:")
        print("[", end=" ")
        print_list(replace(lst, e, rep_lst))
        print("]")
    else:
        print("Provide a position (the list is 1-indexed):")
        k = int(input("k = "))
        print("Solution:")
        print(det_k(lst, k))


main()
