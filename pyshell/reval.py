import subprocess
import shlex
from tkinter import Tk, END


ENCODING_FORMAT = 'utf-8'


def eval(command: str, window: Tk) -> None:
    """
    This function parses a command and then attempts to execute it.
    :param command: str
    :param window: object
    """
    args = shlex.split(command)
    args.insert(0, "./paws.exe")
    robject = subprocess.run(args, capture_output=True, shell=False)

    if robject.returncode == 0:
        lines = robject.stdout.decode(ENCODING_FORMAT).split('\n')
        lines.pop()
        for i in range(len(lines)):
            window.terminal.insert(END, lines[i])
    else:
        window.terminal.insert(END, robject.stderr.decode(ENCODING_FORMAT))

    window.terminal.insert(END, '')
    window.terminal_text = '>>> '
    window.append_to_terminal_text('')
