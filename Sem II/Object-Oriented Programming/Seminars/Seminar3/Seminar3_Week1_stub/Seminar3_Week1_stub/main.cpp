#include "UI.h"
#include <Windows.h>
#include "Tests.h"

using namespace std;

int main()
{
	system("color f4");

	Tests::testAll();

	/*Repository repo{};
	Song s1{ "Ed Sheeran", "I see fire", Duration{4, 54}, "https://www.youtube.com/watch?v=2fngvQS_PmQ" };
	Song s2{ "Two Steps From Hell", "Heart of Courage", Duration{8, 12}, "https://www.youtube.com/watch?v=XYKUeZQbMF0" };
	Song s3{ "Pink Martini", "Splendour in the Grass", Duration{3, 47}, "https://www.youtube.com/watch?v=6L-_DiZlrUI" };
	repo.addSong(s1);
	repo.addSong(s2);
	repo.addSong(s3);

	Controller ctrl{ repo };
	UI ui{ ctrl };
	ui.run();*/

	return 0;
}