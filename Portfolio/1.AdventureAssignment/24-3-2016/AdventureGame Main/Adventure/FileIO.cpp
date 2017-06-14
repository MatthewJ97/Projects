#include <iostream>
#include <fstream>
#include <string>

using namespace std;

enum options { SCREEN_WIDTH, SCREEN_HEIGHT, OPTIONS_MAX };
const char *l_readLines[] = {
	"screen width = ",
	"screen height = ",
	""

};

struct binaryData {
	int x;
	int y;
	char ch;
};

int main()
{
	//default values
	int width = 50;
	int height = 100;

	ifstream infile;
	infile.open("InFile.txt", ios_base::in);
	if (infile.is_open()) {
		//success 
		for (int e = SCREEN_WIDTH; e < OPTIONS_MAX; ++e) {


			string line;

			if (getline(infile, line)) {
				cout << line.c_str() << endl;

				//how do we get the width and height from these lines
				char optionsString[_MAX_PATH];
				const char *pdest;
				int pos;
				pdest = strstr(line.c_str(), l_readLines[e]);
				if (!pdest) break;

				pos = pdest - line.c_str() + strlen(l_readLines[e]);
				strcpy_s(optionsString, line.c_str() + pos);
				int num = atoi(optionsString);
				switch (e) {
				case SCREEN_WIDTH:
						width = num;
						break;
				case SCREEN_HEIGHT:
					height = num;
					break;
				}
			}
		}
		infile.close();
	}
	//increase width and height
	width++;
	height++;
	//save the text file
	ofstream outfile;
	outfile.open("InFile.txt", ios_base::out);
	if (outfile.is_open()) {

		outfile << l_readLines[SCREEN_WIDTH] << width <<endl;		
		outfile << l_readLines[SCREEN_HEIGHT] << height << endl;

		outfile.close();
	}
	binaryData bd;
	bd.x = 0;
	bd.y = 100;
	bd.ch = 'a';

	cout << endl;
	ifstream binInFile("InFile.bin", ios::binary);
	if (binInFile.is_open()) {

		binInFile.read((char*)&bd, sizeof(binaryData));

		binInFile.close();
	}
	cout << " x = " << bd.x << " y = " << bd.y << " ch = " << bd.ch << endl;
	bd.x++;
	bd.y++;
	bd.ch++;
	ofstream binOutFile("InFile.bin", ios::binary);
	if (binOutFile.is_open()) {
		binOutFile.write((char*)&bd, sizeof(binaryData));
		binOutFile.close();
	}

	system("pause");
	return EXIT_SUCCESS;

}