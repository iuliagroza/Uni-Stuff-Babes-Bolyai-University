from copy import deepcopy


def gnome_sort(lst, function=None, key=None, reverse=False):
    """
    Gnome Sort (Stupid Sort) implementation. The function iterates through the elements of the list and checks each
    element along with the previous and the next element. If they are not in the right order, the elements are swapped.
    If there is no previous element, we step forward. If there is no next element the sorting is finished.

    Time Complexity: O(n^2), where n is the length of lst
    Space Complexity: O(1)

    :param lst: list to be sorted
    :param function: comparing (lambda) function parameter
    :param key: object used in the comparing function
    :param reverse: bool parameter to check if the list should be reversed (in descending order)
    :return: a sorted copy of lst
    """
    def default_key(obj):
        return obj

    def default_compare(obj1, obj2):
        return obj1 < obj2

    new_lst = deepcopy(lst)

    if key is None:
        key = default_key

    if function is None:
        function = default_compare

    pos = 1
    while pos < len(new_lst):
        if pos == 0 or not function(key(new_lst[pos]), key(new_lst[pos - 1])):
            pos += 1
        else:
            new_lst[pos - 1], new_lst[pos] = new_lst[pos], new_lst[pos - 1]
            pos -= 1

    if reverse:
        i = 0
        j = len(new_lst) - 1
        while i < j:
            new_lst[i], new_lst[j] = new_lst[j], new_lst[i]
            i += 1
            j -= 1

    return new_lst


def custom_filter(iterable, accept):
    new_list = type(iterable)()
    for x in iterable:
        if accept(x):
            new_list.append(x)
    return new_list


class Container:
    def __init__(self, new_list=None):
        if new_list is None:
            new_list = []
        self._list = new_list

    def __eq__(self, other):
        return isinstance(other, Container) and self._list == other._list

    def __len__(self):
        return len(self._list)

    def __setitem__(self, key, value):
        self._list[key] = value

    def __getitem__(self, item):
        return self._list[item]

    def __delitem__(self, key):
        del self._list[key]

    def __next__(self):
        self.key += 1

        if self.key >= len(self._list):
            raise StopIteration

        return self._list[self.key]

    def __iter__(self):
        self.key = -1
        return self

    def append(self, item):
        self._list.append(item)

    def remove(self, item):
        self._list.remove(item)
