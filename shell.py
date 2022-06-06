import os
from tkinter import (
    Tk,
    PhotoImage,
    Listbox,
    Scrollbar,
    NONE,
    RIGHT,
    BOTH,
    END,
    Y
)
from pyshell.reval import eval
from pyshell.colour import (
    _RGB_to_TkID,
    paint_llfg,
    paint_llbg,
    fg_colours,
    bg_colours
)


BLACK = _RGB_to_TkID((0, 0, 0))
BACKGROUND_COLOUR = _RGB_to_TkID((220, 220, 220))


class ShellConsole(Tk):
    WIDTH, HEIGHT = 950, 480

    def __init__(self):
        super().__init__()

        icon_file_path = os.path.join('assets', 'paws.ico')
        if os.path.exists(icon_file_path):
            icon = PhotoImage(icon_file_path)
            self.iconbitmap(False, icon)

        self.title("Paws Shell")
        self.resizable(False, False)
        self.geometry("{}x{}".format(self.WIDTH, self.HEIGHT))

        self.terminal = Listbox(
            self,
            bg=BACKGROUND_COLOUR,
            fg=BLACK,
            highlightcolor='black',
            highlightthickness=0,
            selectbackground=BACKGROUND_COLOUR,
            activestyle=NONE
        )
        self.terminal_scrollbar = Scrollbar(self.terminal)
        self.terminal_scrollbar.pack(side=RIGHT, fill=Y)

        self.terminal.pack(expand=True, fill=BOTH)

        self.terminal.insert(END, " Paws Terminal")
        self.terminal.insert(END, " Copyright © 2022 vincent-bell")

        self.shell_usage()

        self.terminal_text = '>>> '

        self.terminal.config(yscrollcommand=self.terminal_scrollbar.set)
        self.terminal_scrollbar.config(command=self.terminal.yview)

        self.terminal.insert(END, '')
        self.terminal.insert(END, '')

        self.append_to_terminal_text('')

        self.terminal.bind(
            '<Return>',
            lambda key: self.press_enter_key()
        )
        self.terminal.bind(
            '<BackSpace>',
            lambda key: self.press_backspace_key()
        )

        self.terminal.bind('a', lambda key: self.append_to_terminal_text('a'))
        self.terminal.bind('b', lambda key: self.append_to_terminal_text('b'))
        self.terminal.bind('c', lambda key: self.append_to_terminal_text('c'))
        self.terminal.bind('d', lambda key: self.append_to_terminal_text('d'))
        self.terminal.bind('e', lambda key: self.append_to_terminal_text('e'))
        self.terminal.bind('f', lambda key: self.append_to_terminal_text('f'))
        self.terminal.bind('g', lambda key: self.append_to_terminal_text('g'))
        self.terminal.bind('h', lambda key: self.append_to_terminal_text('h'))
        self.terminal.bind('i', lambda key: self.append_to_terminal_text('i'))
        self.terminal.bind('j', lambda key: self.append_to_terminal_text('j'))
        self.terminal.bind('k', lambda key: self.append_to_terminal_text('k'))
        self.terminal.bind('l', lambda key: self.append_to_terminal_text('l'))
        self.terminal.bind('m', lambda key: self.append_to_terminal_text('m'))
        self.terminal.bind('n', lambda key: self.append_to_terminal_text('n'))
        self.terminal.bind('o', lambda key: self.append_to_terminal_text('o'))
        self.terminal.bind('p', lambda key: self.append_to_terminal_text('p'))
        self.terminal.bind('q', lambda key: self.append_to_terminal_text('q'))
        self.terminal.bind('r', lambda key: self.append_to_terminal_text('r'))
        self.terminal.bind('s', lambda key: self.append_to_terminal_text('s'))
        self.terminal.bind('t', lambda key: self.append_to_terminal_text('t'))
        self.terminal.bind('u', lambda key: self.append_to_terminal_text('u'))
        self.terminal.bind('v', lambda key: self.append_to_terminal_text('v'))
        self.terminal.bind('w', lambda key: self.append_to_terminal_text('w'))
        self.terminal.bind('x', lambda key: self.append_to_terminal_text('x'))
        self.terminal.bind('y', lambda key: self.append_to_terminal_text('y'))
        self.terminal.bind('z', lambda key: self.append_to_terminal_text('z'))

        self.terminal.bind('A', lambda key: self.append_to_terminal_text('A'))
        self.terminal.bind('B', lambda key: self.append_to_terminal_text('B'))
        self.terminal.bind('C', lambda key: self.append_to_terminal_text('C'))
        self.terminal.bind('D', lambda key: self.append_to_terminal_text('D'))
        self.terminal.bind('E', lambda key: self.append_to_terminal_text('E'))
        self.terminal.bind('F', lambda key: self.append_to_terminal_text('F'))
        self.terminal.bind('G', lambda key: self.append_to_terminal_text('G'))
        self.terminal.bind('H', lambda key: self.append_to_terminal_text('H'))
        self.terminal.bind('I', lambda key: self.append_to_terminal_text('I'))
        self.terminal.bind('J', lambda key: self.append_to_terminal_text('J'))
        self.terminal.bind('K', lambda key: self.append_to_terminal_text('K'))
        self.terminal.bind('L', lambda key: self.append_to_terminal_text('L'))
        self.terminal.bind('M', lambda key: self.append_to_terminal_text('M'))
        self.terminal.bind('N', lambda key: self.append_to_terminal_text('N'))
        self.terminal.bind('O', lambda key: self.append_to_terminal_text('O'))
        self.terminal.bind('P', lambda key: self.append_to_terminal_text('P'))
        self.terminal.bind('Q', lambda key: self.append_to_terminal_text('Q'))
        self.terminal.bind('R', lambda key: self.append_to_terminal_text('R'))
        self.terminal.bind('S', lambda key: self.append_to_terminal_text('S'))
        self.terminal.bind('T', lambda key: self.append_to_terminal_text('T'))
        self.terminal.bind('U', lambda key: self.append_to_terminal_text('U'))
        self.terminal.bind('V', lambda key: self.append_to_terminal_text('V'))
        self.terminal.bind('W', lambda key: self.append_to_terminal_text('W'))
        self.terminal.bind('X', lambda key: self.append_to_terminal_text('X'))
        self.terminal.bind('Y', lambda key: self.append_to_terminal_text('Y'))
        self.terminal.bind('Z', lambda key: self.append_to_terminal_text('Z'))

        self.terminal.bind('1', lambda key: self.append_to_terminal_text('1'))
        self.terminal.bind('2', lambda key: self.append_to_terminal_text('2'))
        self.terminal.bind('3', lambda key: self.append_to_terminal_text('3'))
        self.terminal.bind('4', lambda key: self.append_to_terminal_text('4'))
        self.terminal.bind('5', lambda key: self.append_to_terminal_text('5'))
        self.terminal.bind('6', lambda key: self.append_to_terminal_text('6'))
        self.terminal.bind('7', lambda key: self.append_to_terminal_text('7'))
        self.terminal.bind('8', lambda key: self.append_to_terminal_text('8'))
        self.terminal.bind('9', lambda key: self.append_to_terminal_text('9'))
        self.terminal.bind('0', lambda key: self.append_to_terminal_text('0'))

        self.terminal.bind('.', lambda key: self.append_to_terminal_text('.'))
        self.terminal.bind(':', lambda key: self.append_to_terminal_text(':'))
        self.terminal.bind('!', lambda key: self.append_to_terminal_text('!'))
        self.terminal.bind('-', lambda key: self.append_to_terminal_text('-'))
        self.terminal.bind('_', lambda key: self.append_to_terminal_text('_'))
        self.terminal.bind('?', lambda key: self.append_to_terminal_text('?'))
        self.terminal.bind('=', lambda key: self.append_to_terminal_text('='))

        self.terminal.bind(
            '<slash>',
            lambda key: self.append_to_terminal_text('/')
        )
        self.terminal.bind(
            '<backslash>',
            lambda key: self.append_to_terminal_text('\\')
        )
        self.terminal.bind(
            '<space>',
            lambda key: self.append_to_terminal_text(' ')
        )
        self.terminal.bind(
            '<percent>',
            lambda key: self.append_to_terminal_text(r'%')
        )

        self.protocol("WM_DELETE_WINDOW", lambda: [
            self.destroy()
        ])

        self.mainloop()

    def append_to_terminal_text(self, text: str):
        self.terminal.delete(END)
        self.terminal_text = self.terminal_text + text
        self.terminal.insert(END, self.terminal_text)
        self.terminal.yview_moveto(1)

    def press_enter_key(self):
        eval(self.terminal_text[4:], self)

    def press_backspace_key(self):
        if len(self.terminal_text) > 4:
            self.terminal_text = self.terminal_text[:-1]
            self.append_to_terminal_text("")

    def shell_usage(self, *extras: str):
        WARNING = "[Fatal] Extra text lines passed to shell_usage function must be strings"
        for extra in extras:
            assert type(extra) == str, WARNING
            self.terminal.insert(
                END,
                extra
            )
        RUNT = "        run          <file>"
        SIMT = "        simulate           <file>          (optional debugging mode) -d"
        CMPT = "       compile          <file>          -o          <outfile>"
        MKFT = "       mkf          <file>"
        DELT = "       del           <file>"
        self.terminal.insert(END, "")
        self.terminal.insert(END, " Usage: %paws subcommand <args>")
        self.terminal.insert(END, "")
        self.terminal.insert(END, " Subcommands:")
        self.terminal.insert(END, "       _____________________________________________________________")
        self.terminal.insert(END, "")
        self.terminal.insert(END, RUNT)
        paint_llfg(self, fg_colours['command blue'])
        self.terminal.insert(END, "         ~ Attempt to run a compiled executable.")
        self.terminal.insert(END, "")
        self.terminal.insert(END, SIMT)
        paint_llfg(self, fg_colours['command blue'])
        self.terminal.insert(END, "         ~ Simulate a program.")
        self.terminal.insert(END, "")
        self.terminal.insert(END, CMPT)
        paint_llfg(self, fg_colours['command blue'])
        self.terminal.insert(END, "         ~ Compile a program into an executable.")
        self.terminal.insert(END, "")
        self.terminal.insert(END, MKFT)
        paint_llfg(self, fg_colours['command blue'])
        self.terminal.insert(END, "         ~ Make a new file in the programs folder.")
        self.terminal.insert(END, "")
        self.terminal.insert(END, DELT)
        paint_llfg(self, fg_colours['command blue'])
        self.terminal.insert(END, "         ~ Delete a file in the programs folder.")
        self.terminal.insert(END, "")
        self.terminal.insert(END, "       _____________________________________________________________")


if __name__ == '__main__':
    ShellConsole()
