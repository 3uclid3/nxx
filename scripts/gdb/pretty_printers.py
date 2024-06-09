import gdb.printing
import gdb.types

class Iterator:
    def __iter__(self):
        return self

    if sys.version_info.major == 2:
        def next(self):
            return self.__next__()

    def children(self):
        return self


class ArrayPrinter(Iterator):
    """Print a nxx::array object."""

    def __init__(self, val):
        self.val = val
        t = val.type.template_argument(0).pointer()
        self.begin = val["_buffer"].cast(t)
        self.size = val["_size"]
        self.i = 0

    def __next__(self):
        if self.i == self.size:
            raise StopIteration
        ret = "[{}]".format(self.i), (self.begin + self.i).dereference()
        self.i += 1
        return ret

    def to_string(self):
        return "nxx::array of size {}, capacity {}".format(
            self.size, self.val["_capacity"]
        )

    def display_hint(self):
        return "array"

pp = gdb.printing.RegexpCollectionPrettyPrinter("nxx")

pp.add_printer("nxx::array", "^nxx::(inplace_)?array<.*>$", ArrayPrinter)
pp.add_printer("nxx::details::array_trivial", "^nxx::details::array_trivial<.*>$", ArrayPrinter)
pp.add_printer("nxx::details::array_object", "^nxx::details::array_object<.*>$", ArrayPrinter)

gdb.printing.register_pretty_printer(gdb.current_objfile(), pp)