#include "Header.h"

int Menu() {
	//textcolor(10);
	
	/*char t;
	t = _getch();
	while (int(t) != 13)
	{
		if (t == 1) {
			return 1;
		}
		else if (t == 2) {

			ifstream fin; int numberOfSave = 0; FileSave *File[100];
			fin.open("SaveFile.txt");

			int level; string name;
			GotoXY(17, 15);
			if (fin.peek() == ifstream::traits_type::eof()) cout << "There is no save file!!";
			else {
				cout << "There are those save file: ";
				int line = 17;
				while (!(fin.peek() == ifstream::traits_type::eof())) {
					getline(fin, name);
					fin >> level;
					fin.ignore(100, '\n');
					File[numberOfSave] = new FileSave(level, name);
					GotoXY(17, line); cout << numberOfSave + 1 << ". " << File[numberOfSave]->getName() << " "
						<< File[numberOfSave]->getLevel();
					numberOfSave += 1; line += 1;
				}

				char type; type = _getch();
				if (type != 27) {
					int a = type - '0';
					if (a <= numberOfSave and a > 0) {
						presentLevel = File[a - 1]->getLevel() - 1;
						UpdateLevel();
					}
				}

				Clean();
			}
			fin.close();


			return 2;
		}
		else if (t == 3) {
			return 3;
		}
		else if (t == 4) {
			return 4;
		}
		else return 1;
	}*/
	return 0;
}