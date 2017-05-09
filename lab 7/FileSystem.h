#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "Utils.h"
#include <Windows.h>
#include <conio.h>
#include <iomanip>

class FileSystem
{
	MFT mft;
	string currentFolder;
	fstream fsFile;
	size_t offsetToMove;
	vector<string> SplitFolderName(string Name);
	unsigned long long freeSpaceLeft;
	const unsigned long long FILE_SYSTEM_SIZE = 4294967296;

	void RemoveFolder(Entity folder);
	void RemoveEntity(size_t offset);
	void SaveMFT();
	void SaveEntity(size_t offset, Entity block);
	Entity FindFolder(string folderName);
	size_t FindFolderOffset(string folderName);
	size_t FindSubFolderOffset(vector<string> path, Entity baseFolder, int index);
	Entity ReadEntity(size_t offset);
	Block ReadBlock(size_t offset);
	void SaveBlock(size_t offset, Block block);
	string ReadFromFile(string fileData);
	size_t GetFreeBlockOffset();
	void SaveFile(Entity file, size_t offsetToFile, string str);

public:

	FileSystem();
	~FileSystem();
	void ShowFiles();
	void CreateEntity(string type);
	size_t AddEntityToFolder(Entity entity);
	size_t AddEntityToMFT(Entity entity);
	void ShowFolder(Entity folder, int lvl = 0);
	void Remove();
	void ChangeFolder();
	string GetCurrentFolder();
	void Format();
	void ShowCommands();
};