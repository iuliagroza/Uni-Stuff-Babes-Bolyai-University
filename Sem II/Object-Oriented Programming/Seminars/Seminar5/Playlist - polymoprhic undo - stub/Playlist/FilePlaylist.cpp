#include "FilePlaylist.h"



FilePlaylist::FilePlaylist() : PlayList{}, filename{""}
{
}

void FilePlaylist::setFilename(const std::string& filename)
{
	this->filename = filename;
}