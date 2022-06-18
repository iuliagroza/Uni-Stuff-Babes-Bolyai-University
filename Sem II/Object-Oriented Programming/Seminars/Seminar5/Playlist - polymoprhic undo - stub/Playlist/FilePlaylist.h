#pragma once
#include "PlayList.h"

class FilePlaylist : public PlayList
{
protected:
	std::string filename;

public:
	FilePlaylist();
	virtual ~FilePlaylist() {}

	void setFilename(const std::string& filename);
	virtual void writeToFile() = 0;
	virtual void displayPlaylist() const = 0;
};

