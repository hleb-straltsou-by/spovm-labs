#include <string>
#include "Utils.h"
#include "FileSystem.h"

using namespace std;

int main()
{
	string command;
	FileSystem fs;
	while (true)
	{
		cout << fs.GetCurrentFolder() << ">> ";
		cin >> command;
		if (command == "exit") break;
		else if (command == "help") fs.ShowCommands();
		else if (command == "status") fs.ShowFiles();
		else if (command == "createfolder") fs.CreateEntity(_FOLDER);
		else if (command == "createfile") fs.CreateEntity(_FILE);
		else if (command == "remove") fs.Remove();
		else if (command == "format") fs.Format();
		else if (command == "cd") fs.ChangeFolder();
		else if (command == "cls") system("cls");
		else cout << " Unknown command" << endl;
	}
	return 0;
}