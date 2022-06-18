#include "UI.h"
#include <Windows.h>
#include "CSVPlayList.h"
#include "RepositoryExceptions.h"

using namespace std;

int main()
{
	system("color f4");

	try
	{
		Repository repo("Songs.txt");
		FilePlaylist* p = new CSVPlaylist{};
		Service serv(repo, p, SongValidator{});
		UI ui(serv);
		ui.run();
		delete p;
	}
	catch (FileException&)
	{
		cout << "Repository file could not be opened! The application will terminate." << endl;
		return 1;
	}

	return 0;
}