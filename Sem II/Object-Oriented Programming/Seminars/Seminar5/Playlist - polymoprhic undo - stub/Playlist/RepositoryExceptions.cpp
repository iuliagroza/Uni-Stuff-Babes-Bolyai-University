#include "RepositoryExceptions.h"

FileException::FileException(const std::string & msg) : message(msg)
{
}

const char * FileException::what()
{
	return message.c_str();
}

RepositoryException::RepositoryException() : exception{}, message{""}
{
}

RepositoryException::RepositoryException(const std::string & msg): message{msg}
{
}

const char * RepositoryException::what()
{
	return this->message.c_str();
}

const char * DuplicateSongException::what()
{
	return "There is another song with the same artist and title!";
}

const char * InexistenSongException::what()
{
	return "There are no songs with the given artist and title!";
}
