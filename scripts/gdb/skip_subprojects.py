import gdb
import os

class SkipSubprojects(gdb.Command):
    def __init__(self):
        super(SkipSubprojects, self).__init__("skip_subprojects", gdb.COMMAND_USER)

    def invoke(self, arg, from_tty): 
        script_dir = os.path.dirname(os.path.realpath(__file__))
        subprojects_dir = os.path.abspath(os.path.join(script_dir, "../../subprojects"))
        print(subprojects_dir)
        for root, dirs, files in os.walk(subprojects_dir):
            for file in files:
                if file.endswith(('.cpp', '.hpp', '.h')):
                    file_path = os.path.join(root, file)
                    gdb.execute(f"skip -file {file_path}")

SkipSubprojects()
gdb.execute("skip_subprojects")
