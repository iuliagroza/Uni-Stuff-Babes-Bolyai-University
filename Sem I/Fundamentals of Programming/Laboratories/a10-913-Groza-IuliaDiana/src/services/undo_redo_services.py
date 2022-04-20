from src.validators.errors import UndoError


class UndoElement:
    def __init__(self, undo_function, redo_function, type):
        """
        Element of the undo stack in services.
        :param undo_function: function that calls the undo operation
        :param redo_function: function that calls the redo operation
        :param type: 1, 2 or 3 (depending of the entity it is applied on)
        """
        self.undo_function = undo_function
        self.redo_function = redo_function
        self.type = type


class UndoServices:
    def __init__(self):
        self._undo_stack = []
        self._undo_pointer = 0

    @property
    def undo_stack(self):
        return self._undo_stack

    @property
    def undo_pointer(self):
        return self._undo_pointer

    def _normalise_stack(self):
        """
        When an operation is executed that is not undo or redo, it eliminates everything beyond self._undo_pointer
        from the stack.
        """
        while len(self._undo_stack) != self._undo_pointer:
            self._undo_stack.pop()

    def register_operation(self, operation):
        """
        Registers the operation and pushes it onto the stack.
        :param operation: UndoElement object
        """
        self._normalise_stack()
        self._undo_stack.append(operation)
        self._undo_pointer += 1

    def undo(self):
        """
        Undoes the last performed operation.
        """
        if self._undo_pointer == 0:
            raise UndoError
        self._undo_pointer -= 1
        self._undo_stack[self._undo_pointer].undo_function()

    def redo(self):
        """
        Redoes the last undone operation.
        """
        if self._undo_pointer == len(self._undo_stack):
            raise UndoError
        self._undo_stack[self._undo_pointer].redo_function()
        self._undo_pointer += 1
