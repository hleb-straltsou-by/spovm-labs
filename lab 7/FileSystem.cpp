#include "FileSystem.h"

FileSystem::FileSystem()
{
	currentFolder = "";
	offsetToMove = 0;
	fsFile.open(_FSFIle, ios::binary | ios::in | ios::out);
	fsFile.read((char*)&mft, sizeof(MFT));
	freeSpaceLeft = FILE_SYSTEM_SIZE + mft.FreeSpace;
}

FileSystem::~FileSystem()
{
	fsFile.close();
}

void FileSystem::ShowFiles()
{
	cout << "Free space left: " << freeSpaceLeft << " bytes" << endl;
	Entity temp;
	if (currentFolder == "")
	{
		_FindNotNULLOffsets
		{
			temp = ReadEntity(mft.FilesOffsets[i]);
			cout << " " << temp.Name;
			if (strcmp(temp.Type, ((string)_FOLDER).c_str()) == 0)
				cout << " <" << temp.Type << ">";
			cout << endl;
			if (strcmp(temp.Type, ((string)_FOLDER).c_str()) == 0)
				ShowFolder(temp);
		}
	}
	else
	{
		temp = FindFolder(currentFolder);
		cout << temp.Name << endl;
		ShowFolder(temp);
	}
	cout << endl;
}

// use tree traversal
void FileSystem::ShowFolder(Entity folder, int lvl)
{
	for (int i = 0; i < _FilesParts; i++)
	{
		if (folder.Blocks[i] != 0)
		{
			Entity temp = ReadEntity(folder.Blocks[i]);
			for (int j = 0; j < lvl; j++)
				cout << "    ";
			cout << "  |---";
			cout << temp.Name;
			if (strcmp(temp.Type, ((string)_FOLDER).c_str()) == 0)
				cout << " <" << temp.Type << ">";
			cout << endl;
			if (strcmp(temp.Type, ((string)_FOLDER).c_str()) == 0)
				ShowFolder(temp, lvl + 1);
		}
	}
}

// creating of new object in file system
void FileSystem::CreateEntity(string type)
{
	string fileName;
	cout << "input file name: " << endl;
	cin >> fileName;
	Entity file;
	strcpy_s(file.Type, type.c_str());
	strcpy_s(file.Name, fileName.c_str());
	if (currentFolder == "")
	{
		if (AddEntityToMFT(file) == 0)
			cout << " Not enough free space" << endl;
	}
	else
		if (AddEntityToFolder(file) == 0)
			cout << " Folder is full" << endl;
}

// removing of object in file system
void FileSystem::Remove()
{
	string fileName;
	cout << "input file name: " << endl;
	cin >> fileName;
	Entity temp;
	if (currentFolder == "")
	{
		_FindNotNULLOffsets
		{
			temp = ReadEntity(mft.FilesOffsets[i]);
			if (strcmp(temp.Name, fileName.c_str()) != 0) continue;
			if (strcmp(temp.Type, ((string)_FOLDER).c_str()) == 0)
				RemoveFolder(temp);
			RemoveEntity(mft.FilesOffsets[i]);
			mft.FilesOffsets[i] = 0;
			SaveMFT();
			return;
		}
	}
	else
	{
		Entity some;
		temp = FindFolder(currentFolder);
		for (int i = 0; i < _FilesParts; i++)
			if (temp.Blocks[i] != 0)
			{
				some = ReadEntity(temp.Blocks[i]);
				if (strcmp(some.Name, fileName.c_str()) != 0) continue;
				if (strcmp(some.Type, ((string)_FOLDER).c_str()) == 0)
					RemoveFolder(some);
				RemoveEntity(temp.Blocks[i]);
				temp.Blocks[i] = 0;
				SaveEntity(FindFolderOffset(currentFolder), temp);
				return;
			}
	}
	cout << "Entity doesn't exist" << endl;
}

void FileSystem::RemoveFolder(Entity folder)
{
	for (int i = 0; i < _FilesParts; i++)
	{
		if (folder.Blocks[i] != 0)
		{
			Entity temp = ReadEntity(folder.Blocks[i]);
			if (strcmp(temp.Type, ((string)_FOLDER).c_str()) == 0)
				RemoveFolder(temp);
			RemoveEntity(folder.Blocks[i]);
		}
	}
}

void FileSystem::RemoveEntity(size_t offset)
{
	mft.FreeBlocksOffsets[(offset - _MFTSize) / _BlockSize] = offset;
	mft.FreeSpace += _BlockSize;
	freeSpaceLeft = FILE_SYSTEM_SIZE + mft.FreeSpace;
	fsFile.seekp(offset);
	fsFile.write((char*)&Block(), sizeof(Entity));
	fsFile.flush();
}


size_t FileSystem::AddEntityToMFT(Entity entity)
{
	for (int i = 0; i < _MaxFileCount; i++)
		if (mft.FilesOffsets[i] == 0)
		{
			_FindFreeBlock
			{
				mft.FilesOffsets[i] = mft.FreeBlocksOffsets[j];
				mft.FreeBlocksOffsets[j] = 0;
				mft.FreeSpace -= _BlockSize;
				freeSpaceLeft = FILE_SYSTEM_SIZE + mft.FreeSpace;
				SaveEntity(mft.FilesOffsets[i], entity);
				return mft.FilesOffsets[i];
			}
			break;
		}
	return 0;
}


size_t FileSystem::AddEntityToFolder(Entity entity)
{
	Entity folder = FindFolder(currentFolder);
	for (int i = 0; i < _FilesParts; i++)
		if (folder.Blocks[i] == 0)
		{
			_FindFreeBlock
			{
				folder.Blocks[i] = mft.FreeBlocksOffsets[j];
				mft.FreeBlocksOffsets[j] = 0;
				mft.FreeSpace -= _BlockSize;
				freeSpaceLeft = FILE_SYSTEM_SIZE + mft.FreeSpace;
				SaveEntity(folder.Blocks[i], entity);
				SaveEntity(FindFolderOffset(currentFolder), folder);
				return folder.Blocks[i];
			}
		}
	return 0;
}

void FileSystem::SaveMFT()
{
	fsFile.seekp(0);
	fsFile.write((char*)&mft, sizeof(MFT));
}

void FileSystem::SaveEntity(size_t offset, Entity block)
{
	SaveMFT();
	fsFile.seekp(offset);
	fsFile.write((char*)&block, sizeof(Entity));
	fsFile.flush();
}

void FileSystem::SaveBlock(size_t offset, Block block)
{
	fsFile.seekp(offset);
	fsFile.write((char*)&block, sizeof(Block));
	fsFile.flush();
}

Entity FileSystem::ReadEntity(size_t offset)
{
	Entity file;
	fsFile.seekg(offset);
	fsFile.read((char*)&file, sizeof(Entity));
	return file;
}

Block FileSystem::ReadBlock(size_t offset)
{
	Block block;
	fsFile.seekg(offset);
	fsFile.read((char*)&block, sizeof(Block));
	return block;
}

size_t FileSystem::GetFreeBlockOffset()
{
	for (int i = 0; i < _AllBlocksCount; i++)
		if (mft.FreeBlocksOffsets[i] != 0)
		{
			size_t temp = mft.FreeBlocksOffsets[i];
			mft.FreeBlocksOffsets[i] = 0;
			mft.FreeSpace -= _BlockSize;
			freeSpaceLeft = FILE_SYSTEM_SIZE + mft.FreeSpace;
			return temp;
		}
	return 0;
}

Entity FileSystem::FindFolder(string folderName)
{
	size_t offset = FindFolderOffset(folderName);
	if (offset != 0)
		return ReadEntity(offset);
	return Entity();
}

size_t FileSystem::FindFolderOffset(string folderName)
{
	Entity folder;
	vector<string> folders = SplitFolderName("/" + folderName);
	_FindNotNULLOffsets
	{
		folder = ReadEntity(mft.FilesOffsets[i]);
		if (strcmp(folder.Name, folders[0].c_str()) == 0 &&
			strcmp(folder.Type, ((string)_FOLDER).c_str()) == 0)
			if (folders.size() == 1 || folders[1] == "")
				return mft.FilesOffsets[i];
			else return FindSubFolderOffset(folders, folder, 1);
	}
	return 0;
}

size_t FileSystem::FindSubFolderOffset(vector<string> folders, Entity baseFolder, int index)
{
	Entity folder;
	for (int i = 0; i < _FilesParts; i++)
	{
		folder = ReadEntity(baseFolder.Blocks[i]);
		if (strcmp(folder.Name, folders[index].c_str()) == 0 &&
			strcmp(folder.Type, ((string)_FOLDER).c_str()) == 0)
			if (folders.size() - 1 == index)
				return baseFolder.Blocks[i];
			else
				return FindSubFolderOffset(folders, folder, index + 1);
	}
	return 0;
}

void FileSystem::ChangeFolder()
{
	string newFolder;
	cout << "Input folder to enter: ";
	cin >> newFolder;
	if (newFolder == "/")
	{
		currentFolder = "";
		return;
	}
	Entity folder = FindFolder(currentFolder + "/" + newFolder);
	if (strcmp(folder.Name, newFolder.c_str()) == 0)
		currentFolder += "/" + newFolder;
	else cout << " Folder doesn't exist" << endl;
}

vector<string> FileSystem::SplitFolderName(string folderName)
{
	int len = folderName.length();
	int i = 0; int k = 0;
	vector<string> words(1);
	do
	{
		char a = folderName[i];
		if (folderName[i] != '/' && folderName[i] != '\0')
			words[k].push_back(folderName[i]);
		else if (words[k] != "")
		{
			string temp;
			words.push_back(temp);
			k++;
		}
	} while (++i < len);
	return words;
}

string FileSystem::GetCurrentFolder()
{
	return currentFolder;
}

void FileSystem::Format()
{
	fsFile.close();
	fstream file(_FSFIle, ios::binary | ios::out | ios::trunc);
	file.write((char*)(new MFT()), sizeof(MFT));
	for (int i = 0; i < _AllBlocksCount; i++)
		file.write((char*)(new Block()), sizeof(Block));
	file.close();
	currentFolder = "";
	offsetToMove = 0;
	fsFile.open(_FSFIle, ios::binary | ios::in | ios::out);
	fsFile.read((char*)&mft, sizeof(MFT));
}

string FileSystem::ReadFromFile(string fileName)
{
	string fileData;
	ifstream infile;
	infile.open(fileName, ios::binary);
	if (!infile.is_open())
	{
		return "0";
	}
	char ch;
	infile.seekg(0, ios::beg);
	for (int i = 0;; i++)
	{
		ch = infile.get();
		if (ch == EOF)
		{
			break;
		}
		fileData += ch;
	}
	infile.close();
	return fileData;
}
void FileSystem::SaveFile(Entity file, size_t offsetToFile, string str)
{
	size_t newOffset;
	Block newBlock;
	int blockNumber = 0, blockIndex = 0, strIndex = 0;
	int size = str.length();
	while (strIndex < size)
	{
		
		newBlock.Data[blockIndex++] = str[strIndex++];
		if (blockIndex == _BlockSize - 1 || strIndex == size)
		{
			newBlock.Data[blockIndex++] = '\0';
			if (blockNumber == 24) break;
			blockIndex = 0;
			newOffset = file.Blocks[blockNumber] == 0 ? GetFreeBlockOffset() : file.Blocks[blockNumber];
			file.Blocks[blockNumber++] = newOffset;
			SaveBlock(newOffset, newBlock);
			newBlock = Block();
		}
	}
	SaveEntity(offsetToFile, file);
}

void FileSystem::ShowCommands()
{
	cout << "Available commands:\n" << endl;
	cout << setw(14) << "help" << "\t- to see available commands;" << endl;
	cout << setw(14) << "exit" << "\t- to exit from file system manager;" << endl;
	cout << setw(14) << "status" << "\t- to check condition of file system;" << endl;
	cout << setw(14) << "remove" << "\t- to remove file or folder from current directory;" << endl;
	cout << setw(14) << "format" << "\t- to format the whole file system;" << endl;
	cout << setw(14) << "cd" << "\t- to enter into inner folder;" << endl;
	cout << setw(14) << "cls" << "\t- to clean up the console;" << endl;
	cout << setw(14) << "createfolder" << "\t- to create new folder in current directory;" << endl;
	cout << setw(14) << "createfile" << "\t- to create new file in current directory;" << endl;
}