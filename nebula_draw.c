/*
	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

/* 
   The Nebula Centre Project is an active endeavour created by a small group.
   The Nebula Centre Project does not currently have an end goal, 
   but does have a series of primary goals, which are currently being pursued
   and will always be considered in future judgements. To learn more about the
   Nebula Centre Project visit it on the web at https://nebulacentre.net.
   
   We always welcome lain (o.o)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

void refreshColor();
void refreshSymbol();
void refreshSelection();
void refreshHud();
void drawRectangle();
void drawHorizontal();
void drawVertical();
void print();
void about();
void drawProcess();
void erasePoint();
void drawRectangleFill();
void eraseRectangleFill();
void help();

int main(int argc, char *argv[]) {
	int maxx, maxy, key, color = 0, lasty, lastx, symbol_id = 0, selection_type = 0, space_press = 0, i;
	char *symbol, *selection_char, release[6] = "      ";
	initscr();
	noecho();
	clear();
	cbreak();
	curs_set(0);
	keypad(stdscr, TRUE);
	mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
	getmaxyx(stdscr, maxy, maxx);
	if (maxy < 25 || maxx < 105) { 	// Preliminary check for too small a window
		endwin();
		printf("%s", "Your terminal window is too small to run this application.\n");
		return 0;
	}
	printf("\033[?1003h\n");
	box(stdscr, 0, 0);
	start_color();
	refresh();
	MEVENT event;
	// COLORS
	init_pair(0, COLOR_WHITE, COLOR_BLACK);
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(6, COLOR_CYAN, COLOR_BLACK);

	void refreshColor() {
		attrset(COLOR_PAIR(0));
		mvprintw(maxy - 2, maxx - 10, "COLOR ");
		attrset(COLOR_PAIR(color));
		mvprintw(maxy - 2, maxx - 4, "[] ");
		refresh();
	}

	void refreshSymbol() {
		if (symbol_id == 0) {
			symbol = "+  ";
		}
		if (symbol_id == 1) {
			symbol = "@  ";
		}
		if (symbol_id == 2) {
			symbol = "#  ";
		}
		if (symbol_id == 3) {
			symbol = "$  ";
		}
		if (symbol_id == 4) {
			symbol = "^  ";
		}
		if (symbol_id == 5) {
			symbol = "&  ";
		}
		if (symbol_id == 6) {
			symbol = "*  ";
		}
		if (symbol_id == 7) {
			symbol = "/  ";
		}
		if (symbol_id == 8) {
			symbol = "\\  ";
		}
		attrset(COLOR_PAIR(0));
		mvprintw(maxy - 2, maxx - 19, "BRUSH ");
		mvprintw(maxy - 2, maxx - 13, symbol);
		attrset(COLOR_PAIR(color));
		refresh();
	}

	void refreshSelection() {
		if (selection_type == 0) {
			selection_char = "+  ";
		}
		if (selection_type == 1) {
			selection_char = "-  ";
		}
		if (selection_type == 2) {
			selection_char = "|  ";
		}
		if (selection_type == 3) {
			selection_char = "[] ";
		}
		if (selection_type == 4) {
			selection_char = "~ ";
		}
		if (selection_type == 5) {
			selection_char = "[+]";
		}
		if (selection_type == 6) {
			selection_char = "X  ";
		}
		if (selection_type == 7) {
			selection_char = "[X]";
		}
		attrset(COLOR_PAIR(0));
		mvprintw(maxy - 2, maxx - 40, "              ");
		mvprintw(maxy - 2, maxx - 28, "MODE ");
		mvprintw(maxy - 2, maxx - 23, selection_char);
		if (selection_type == 4) {
			mvprintw(maxy - 2, maxx - 40, "MODE ");
			mvprintw(maxy - 2, maxx - 33, "[HOLD SPACE]  ");
			mvprintw(maxy - 2, maxx - 35, selection_char);
		}
		mvprintw(maxy - 2, (maxx / 2) - 19, "                               ");
		mvprintw(maxy - 2, (maxx / 2) + 12, release);
		attrset(COLOR_PAIR(color));
		refresh();
	}

	void refreshHud() {
		refreshColor();
		refreshSymbol();
		refreshSelection();
		attrset(COLOR_PAIR(0));
		box(stdscr, 0, 0);
		mvhline(maxy - 2, 1, ' ', (maxx / 2) - 20);
		mvhline(maxy - 4, 1, ' ', maxx - 2);
		mvhline(maxy - 3, 1, 0, maxx - 2);
		if (selection_type != 4) {
			mvhline(maxy - 2, (maxx / 2) + 18, ' ', (maxx / 2) - 46);
		}
		else; {
			mvhline(maxy - 2, (maxx / 2) + 18, ' ', (maxx / 2) - 58);
		}
		refresh();
	}
	void drawRectangle(int y1, int x1, int y2, int x2) {
		attrset(COLOR_PAIR(color));
		mvhline(y1, x1, *symbol, x2-x1);
		mvhline(y2, x1, *symbol, x2-x1);
		mvvline(y1, x1, *symbol, y2-y1);
		mvvline(y1, x2, *symbol, y2-y1);
		mvaddch(y1, x1, *symbol);
		mvaddch(y2, x1, *symbol);
		mvaddch(y1, x2, *symbol);
		mvaddch(y2, x2, *symbol);
		refreshHud();
	}
	void drawHorizontal(int x1, int x2, int y) {
		attrset(COLOR_PAIR(color));
		mvhline(y, x1, *symbol, x2 - x1);
		refreshHud();
	}
	void drawVertical(int y1, int y2, int x) {
		attrset(COLOR_PAIR(color));
		mvvline(y1, x, *symbol, y2 - y1);
		refreshHud();
	}
	void print() {
		attrset(COLOR_PAIR(color));
		mvaddch(event.y, event.x, *symbol);
		refreshHud();
	}
	void erasePoint() {
		mvaddch(event.y, event.x, ' ');
	}
	void eraseRectangleFill(int y1, int x1, int y2, int x2) {
		attrset(COLOR_PAIR(color));
		mvhline(y1, x1, ' ', x2-x1);
		mvhline(y2, x1, ' ', x2-x1);
		mvvline(y1, x1, ' ', y2-y1);
		mvvline(y1, x2, ' ', y2-y1);
		mvaddch(y1, x1, ' ');
		mvaddch(y2, x1, ' ');
		mvaddch(y1, x2, ' ');
		mvaddch(y2, x2, ' ');
		for (i = 0; i < (y2 - y1); i++) {
			mvhline(y2 - i, x1, ' ', x2-x1);
		}
		refreshHud();
	}
	void drawRectangleFill(int y1, int x1, int y2, int x2) {
		attrset(COLOR_PAIR(color));
		mvhline(y1, x1, *symbol, x2-x1);
		mvhline(y2, x1, *symbol, x2-x1);
		mvvline(y1, x1, *symbol, y2-y1);
		mvvline(y1, x2, *symbol, y2-y1);
		mvaddch(y1, x1, *symbol);
		mvaddch(y2, x1, *symbol);
		mvaddch(y1, x2, *symbol);
		mvaddch(y2, x2, *symbol);
		for (i = 0; i < (y2 - y1); i++) {
			mvhline(y2 - i, x1, *symbol, x2-x1);
		}
		refreshHud();
	}
	void drawProcess() {
		if (selection_type == 0) {
			print();
		}
		if (selection_type == 1) {
			if (lastx - event.x > 0) {
				drawHorizontal(event.x, lastx, lasty);
			}
			if (lastx - event.x < 0) {
				drawHorizontal(lastx, event.x, lasty);
			}
		}
		if (selection_type == 2) {
			if (lasty - event.y > 0) {
				drawVertical(event.y, lasty, lastx);
			}
			if (lasty - event.y < 0) {
				drawVertical(lasty, event.y, lastx);
			}
		}
		if (selection_type == 3) {	
			if (lasty - event.y > 0 && lastx - event.x > 0) {
				drawRectangle(event.y, event.x, lasty, lastx);
			}
			else if (lasty - event.y < 0 && lastx - event.x > 0) {
				drawRectangle(lasty, event.x, event.y, lastx);
			}
			else if (lasty - event.y > 0 && lastx - event.x < 0) {
				drawRectangle(event.y, lastx, lasty, event.x);
			}
			else if (lasty - event.y < 0 && lastx - event.x < 0) {
				drawRectangle(lasty, lastx, event.y, event.x);
			}
		}
		if (selection_type == 5) {
			if (lasty - event.y > 0 && lastx - event.x > 0) {
				drawRectangleFill(event.y, event.x, lasty, lastx);
			}
			else if (lasty - event.y < 0 && lastx - event.x > 0) {
				drawRectangleFill(lasty, event.x, event.y, lastx);
			}
			else if (lasty - event.y > 0 && lastx - event.x < 0) {
				drawRectangleFill(event.y, lastx, lasty, event.x);
			}
			else if (lasty - event.y < 0 && lastx - event.x < 0) {
				drawRectangleFill(lasty, lastx, event.y, event.x);
			}
		}
		if (selection_type == 6) {
			erasePoint();
		}
		if (selection_type == 7) {
			if (lasty - event.y > 0 && lastx - event.x > 0) {
				eraseRectangleFill(event.y, event.x, lasty, lastx);
			}
			else if (lasty - event.y < 0 && lastx - event.x > 0) {
				eraseRectangleFill(lasty, event.x, event.y, lastx);
			}
			else if (lasty - event.y > 0 && lastx - event.x < 0) {
				eraseRectangleFill(event.y, lastx, lasty, event.x);
			}
			else if (lasty - event.y < 0 && lastx - event.x < 0) {
				eraseRectangleFill(lasty, lastx, event.y, event.x);
			}
		}
	}
	void about() {
		//When k is pressed show us the information on this application
		WINDOW * aboutWin = newwin(9, 50, (maxy / 2) - 4.5, (maxx / 2) - 25);
		refresh();
		box(aboutWin, 0, 0);
		wrefresh(aboutWin);
		mvwprintw(aboutWin, 1, 19, "Nebula Draw");
		mvwprintw(aboutWin, 2, 3, "The Nebula Centre Project and Shreda5 @ 2019");
		mvwprintw(aboutWin, 4, 3, "web: https://nebulacentre.net");
		mvwprintw(aboutWin, 5, 3, "irc: https://nebulacentre.net/messaging.html");
		mvwprintw(aboutWin, 7, 11, "Press \"?\" or \"/\" for help");
		wrefresh(aboutWin);
		printf("\033[?1003l\n");
		int k = wgetch(aboutWin);
		for (;;) {
			if (k) {
				wclear(aboutWin);
				wrefresh(aboutWin);
				delwin(aboutWin);
				refreshHud();
				printf("\033[?1003h\n");
				break;
			}
		}
	}
	void help() {
		WINDOW * helpWin = newwin(24, 80, (maxy / 2) - 12, (maxx / 2) - 40);
		refresh();
		box(helpWin, 0, 0);
		wrefresh(helpWin);
		mvwprintw(helpWin, 1, 5, "Controls:");
		mvwprintw(helpWin, 2, 5, "space/ click: Mode action");
		mvwprintw(helpWin, 3, 5, "mouse: Mode position");
		mvwprintw(helpWin, 4, 5, "q, w: Change mode");
		mvwprintw(helpWin, 5, 5, "a, s: Change brush");
		mvwprintw(helpWin, 6, 5, "z, x: Change color");
		mvwprintw(helpWin, 7, 5, "c: Clear the screen");
		mvwprintw(helpWin, 8, 5, "Q, l: Leave");
		mvwprintw(helpWin, 9, 5, "F1: About");
		mvwprintw(helpWin, 10, 5, "/, ?: Help");
		mvwprintw(helpWin, 11, 5, "e: export");
		mvwprintw(helpWin, 13, 5, "Modes:");
		mvwprintw(helpWin, 14, 5, "+ [point] - Press the mode action key to fill the current location of");
		mvwprintw(helpWin, 15, 5, "the pointer with the selected brush and color.");
		mvwprintw(helpWin, 17, 5, "- [horizontal line] - Press the mode action key to select one position");
		mvwprintw(helpWin, 18, 5, "on the screen, then again to select the second position. The space in");
		mvwprintw(helpWin, 19, 5, "between the two points on the x-axis will be filled with the currently");
		mvwprintw(helpWin, 20, 5, "selected brush and color.");
		mvwprintw(helpWin, 22, 11, "Press \"n\" to view the next page, or any other key to exit.");
		wrefresh(helpWin);
		printf("\033[?1003l\n");
		int k = wgetch(helpWin);
		for (;;) {
			if (k != 'n') {
				wclear(helpWin);
				wrefresh(helpWin);
				delwin(helpWin);
				refreshHud();
				printf("\033[?1003h\n");
				break;
			}
			else; {
				wclear(helpWin);
				wrefresh(helpWin);
				delwin(helpWin);
				refreshHud();
				WINDOW * helpWin2 = newwin(24, 80, (maxy / 2) - 12, (maxx / 2) - 40);
				refresh();
				box(helpWin2, 0, 0);
				wrefresh(helpWin2);
				mvwprintw(helpWin2, 3, 5, "Modes (continued):");
				mvwprintw(helpWin2, 5, 5, "| [vertical line] - Press the mode action key to select one position");
				mvwprintw(helpWin2, 6, 5, "on the screen, then again to select the second position. The space in");
				mvwprintw(helpWin2, 7, 5, "between the two points on the y-axis will be filled with the currently");
				mvwprintw(helpWin2, 8, 5, "selected brush and color.");
				mvwprintw(helpWin2, 10, 5, "[] [border] - Press the mode action key to select one position on the");
				mvwprintw(helpWin2, 11, 5, "screen, then again to select the second position. A border will be");
				mvwprintw(helpWin2, 12, 5, "drawn along the edge of the selection with the currently selected");
				mvwprintw(helpWin2, 13, 5, "brush and color.");
				mvwprintw(helpWin2, 15, 5, "~ [free draw] - Hold the primary mode action key (space) to fill the");
				mvwprintw(helpWin2, 16, 5, "current location of the pointer with the selected brush and color.");
				mvwprintw(helpWin2, 17, 5, "Move the cursor while holding down the primary mode action key to");
				mvwprintw(helpWin2, 18, 5, "continue filling each location the pointer hovers over.");
				mvwprintw(helpWin2, 22, 11, "Press \"n\" to view the next page, or any other key to exit.");
				wrefresh(helpWin2);
				printf("\033[?1003l\n");
				k = wgetch(helpWin2);
				for (;;) {
					if (k != 'n') {
						wclear(helpWin2);
						wrefresh(helpWin2);
						delwin(helpWin2);
						refreshHud();
						printf("\033[?1003h\n");
						return;
					}
					else; {
						wclear(helpWin2);
						wrefresh(helpWin2);
						delwin(helpWin2);
						refreshHud();
						WINDOW * helpWin3 = newwin(24, 80, (maxy / 2) - 12, (maxx / 2) - 40);
						refresh();
						box(helpWin3, 0, 0);
						mvwprintw(helpWin3, 2, 5, "Modes (continued):");
						mvwprintw(helpWin3, 4, 5, "[+] [mass fill tool] - Press the mode action key to select one");
						mvwprintw(helpWin3, 5, 5, "position on the screen, then again to select the second position.");
						mvwprintw(helpWin3, 6, 5, "The space in between the two points will be filled with the");
						mvwprintw(helpWin3, 7, 5, "currently selected brush and color.");
						mvwprintw(helpWin3, 9, 5, "X [point erase] - Press the mode action key to erase the position");
						mvwprintw(helpWin3, 10, 5, "under the cursor");
						mvwprintw(helpWin3, 12, 5, "[X] [mass erase tool] - Press the mode action key to select one");
						mvwprintw(helpWin3, 13, 5, "position on the screen, then again to select the second position.");
						mvwprintw(helpWin3, 14, 5, "The space in between the two points will be erased.");
						mvwprintw(helpWin3, 16, 5, "Other:");
						mvwprintw(helpWin3, 17, 5, "Export functionality - Press \"e\", then position the mouse in the");
						mvwprintw(helpWin3, 18, 5, "upper left corner of the screen. While holding down the secondary");
						mvwprintw(helpWin3, 19, 5, "mode action key, move the pointer down to the bottom right of the");
						mvwprintw(helpWin3, 20, 5, "screen. This copies the screen to the clipboard and ready for sharing.");
						mvwprintw(helpWin3, 22, 28, "Press any key to exit.");
						wrefresh(helpWin3);
						printf("\033[?1003l\n");
						k = wgetch(helpWin3);
						for (;;) {
							if (k) {
								wclear(helpWin3);
								wrefresh(helpWin3);
								delwin(helpWin3);
								refreshHud();
								printf("\033[?1003h\n");
								return;
							}
						}
					}
				}
			}
		}
	}
	for (;;) {
		refreshHud();
		key = wgetch(stdscr);
		if (key == ' ' && selection_type == 4) {
			space_press = 0;
			print();
			refreshHud();
		}
		if (key == '?' || key == '/') {
			help();
		}
		if (key == KEY_F(1)) {
			about();
		}
		if (key == 'z') {
			if (color - 1 != -1) {
				color = color - 1;
				refreshHud();
			}
			else if (color -1 == -1) {
				color = 5;
				refreshHud();
			}
		}
		if (key == 'x') {
			if (color + 1 != 6) {
				color = color + 1;
				refreshHud();
			}
			else if (color + 1 == 6) {
				color = 0;
				refreshHud();
			}
		}
		if (key == 's') {
			if (symbol_id + 1 != 9) {
				symbol_id = symbol_id + 1;
				refreshHud();
			}
			else if (symbol_id + 1 == 9) {
				symbol_id = 0;
				refreshHud();
			}
		}	
		if (key == 'a') {
			if (symbol_id - 1 != -1) {
				symbol_id = symbol_id - 1;
				refreshHud();
			}
			else if (symbol_id - 1 == -1) {
				symbol_id = 8;
				refreshHud();
			}
		}
		if (key == 'w') {
			if (selection_type + 1 != 8) {
				selection_type = selection_type + 1;
				refreshHud();
			}
			else if (selection_type + 1 == 8) {
				selection_type = 0;
				refreshHud();
			}
		}
		if (key == 'q') {
			if (selection_type - 1 != -1) {
				selection_type = selection_type - 1;
				refreshHud();
			}
			else if (selection_type - 1 == -1) {
				selection_type = 7;
				refreshHud();
			}
		}
		if (key == 'l' || key == 'Q') {
			printf("\033[?1003l\n");
			endwin();
			return 0;
		}
		if (key == 'c') {
			clear();
			refreshHud();
		}
		// Drawing process init
		if (key == ' ') {
			if (selection_type == 0 || selection_type == 6) {
				drawProcess();
			}
			else if (space_press == 1 && selection_type != 4) {
				drawProcess();
				space_press = 0;
			}
			else if (space_press == 0 && selection_type != 4) {
				lasty = event.y;
				lastx = event.x;
				space_press = 1;
			}
		}
		if (key == 'e') {
			printf("\033[?1003l\n");
			attrset(COLOR_PAIR(color));
			mvhline(0, 0, ' ', maxx);
			mvhline(maxy - 4, 0, ' ', maxx - 1);
			mvhline(maxy - 3, 0, ' ', maxx - 1);
			mvhline(maxy - 2, 0, ' ', maxx - 1);
			mvhline(maxy - 1, 0, ' ', maxx);
			mvvline(0, 0, ' ', maxy);
			mvhline(maxy, 0, ' ', maxx - 1);
			mvvline(0, maxx - 1, ' ', maxy);
			for (;;) {
				key = wgetch(stdscr);
				if (key == 'e') {
					printf("\033[?1003h\n");
					break;
				}
			}
		}
		if (getmouse (&event) == OK) {
			if (event.bstate & BUTTON1_CLICKED) {
				drawProcess();
			}
			else if (event.bstate & BUTTON1_PRESSED) {
				lasty = event.y;
				lastx = event.x;
			}
			else if (event.bstate & BUTTON1_RELEASED) {
				drawProcess();
			}
		}

	}
	endwin();
	printf("'\033[?1003l\n'");
	return 0;
}
