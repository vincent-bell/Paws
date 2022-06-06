from tkinter import Tk
from typing import Tuple


def _RGB_to_TkID(RGB: Tuple[int, int, int]) -> str:
    """
    This function converts an RGB tuple (R, G, B) into a colour code 
    which can be used by tkinter.
    :param RGB: Tuple[int, int, int]
    :return: str
    """
    r, g, b = RGB
    return f'#{r:02x}{g:02x}{b:02x}'


def paint_llfg(window: Tk, colour: dict) -> None:
    """
    This function paints the foreground of the most recent inserted line
    in the colour specified by the colour parameter.
    :param window: Tk
    :param colour: dict
    :return: None
    """
    window.terminal.itemconfig(window.terminal.size() - 1, colour)


def paint_llbg(window: Tk, colour: dict) -> None:
    """
    This function paints the background of the most recent inserted line
    in the colour specified by the colour parameter.
    :param window: Tk
    :param colour: dict
    :return: None
    """
    window.terminal.itemconfig(window.terminal.size() - 1, colour)


sea_green = _RGB_to_TkID((124, 223, 172))
bright_orange = _RGB_to_TkID((255, 123, 0))
bright_pink = _RGB_to_TkID((255, 133, 235))
light_goldenrod = _RGB_to_TkID((218, 165, 32))
command_blue = _RGB_to_TkID((0, 0, 205))

fg_colours = {
    'sky blue': { 'fg': "DeepSkyBlue2" },
    'lavender blush': { 'fg': "lavender blush" },
    'sea green': { 'fg': sea_green },
    'bright orange': { 'fg': bright_orange },
    'bright pink': { 'fg': bright_pink },
    'light goldenrod': { 'fg': light_goldenrod },
    'command blue': { 'fg': command_blue }
}

bg_colours = {
    'lavender blush' : {'bg': "lavender blush"}
}
