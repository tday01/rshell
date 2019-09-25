#ifndef __MENU_CLASS__
#define __MENU_CLASS__

#include <iostream>
#include "command.h"

using namespace std;

class Menu {
	private:
		int history_index;
		vector<Command*> history;

	public:
		Menu() {
			history_index = -1;
		};
		void execute() {
			if (history.empty()) {
				cout << 0;
			} else {
				cout << history[history_index < 0 ? 0 : history_index]->execute();
			}
			cout << endl;
			//Prints the current commands value (based on history_index), if no commands exist
			//print 0 by default
		};
		bool initialized() {
			return history_index > -1;
			//Return true if the history has been primed with a single op instruciton
			//This is necessary because that is the base of a calculation
		};
		void add_command(Command* cmd) {
			history_index++;
			if (history.size() == history_index) {
				history.push_back(cmd);
			} else {
				history[history_index] = cmd;
			}
			//Adds a command to history in the appropriate posiiton (based on history_index)
		};
		Command* get_command() {
			return history[history_index];
			//Returns the command in history we are currently referring to (based on history_index)
		};
		void undo() {
			if (history_index > -1) {
				history_index--;
			}
			//Moves to the last command in history (if possible)
		};
		void redo() {
			if (history_index + 1 < history.size()) {
				history_index++;
			}
			//Moves to the next command in history (if possible)
		};

		~Menu()
		{
			for (int i = 0; i < history.size(); i++) {
				delete history[i];
			}
		}
};

#endif //__MENU_CLASS__
