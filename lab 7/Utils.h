#pragma once
#include <iostream>
#include <stdio.h>
using namespace std;

#define _FSSize 0x110000
#define _BlockSize 0x100
#define _MFTSize 0x10000
#define _AllBlocksCount (_FSSize - _MFTSize) / _BlockSize
#define _FSFIle "../../File.bin"
#define _MaxFileCount 1000
#define _MaxName 100
#define _FOLDER "FOLDER"
#define _FILE "FILE"
#define _FilesParts 25
#define _FindNotNULLOffsets for (int i = 0; i < _MaxFileCount; i++) if (mft.FilesOffsets[i] != 0)
#define _FindFreeBlock for (int j = 0; j < _AllBlocksCount; j++) if (mft.FreeBlocksOffsets[j] != 0)

struct MFT	// Master file table
{
	size_t FreeSpace = _FSSize - _MFTSize;
	size_t FreeBlocksOffsets[_AllBlocksCount];
	size_t FilesOffsets[_MaxFileCount];
	MFT()
	{
		for (int i = 0; i < _AllBlocksCount; i++)
		{
			FreeBlocksOffsets[i] = _BlockSize * i + _MFTSize;
			if (i< _MaxFileCount) FilesOffsets[i] = 0;
		}
	}
};

struct Block	// simple block for storing data
{
	char Data[_BlockSize];
	Block()
	{
		for (int i = 0; i < _BlockSize; i++) Data[i] = 0;
	}
};

struct Entity	// object for file system
{
	char Name[_MaxName];
	char Type[10];
	size_t Blocks[_FilesParts];
	Entity()
	{
		for (int i = 0; i < _MaxName; i++)
		{
			if (i < 10) Type[i] = 0;
			Name[i] = 0;
			if (i < _FilesParts) Blocks[i] = 0;
		}
	}
};