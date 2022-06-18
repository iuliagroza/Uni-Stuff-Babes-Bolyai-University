#include "Tests.h"
#include <assert.h>
#include "DynamicVector.h"
#include "Repository.h"
#include "PlayList.h"
#include "Controller.h"

void Tests::testSong()
{
	Duration d{ 4, 54 };
	Song s{ "Ed Sheeran", "I see fire", d, "https://www.youtube.com/watch?v=2fngvQS_PmQ" };
	assert(s.getArtist() == "Ed Sheeran");
	assert(s.getTitle() == "I see fire");
	assert(s.getSource() == "https://www.youtube.com/watch?v=2fngvQS_PmQ");
	assert(s.getDuration().getMinutes() == 4);
	assert(s.getDuration().getSeconds() == 54);
}

void Tests::testDynamicVector()
{
	DynamicVector<int> v1{ 2 };
	v1.add(10);
	v1.add(20);
	assert(v1.getSize() == 2);
	assert(v1[1] == 20);
	v1[1] = 25;
	assert(v1[1] == 25);
	v1.add(30);
	assert(v1.getSize() == 3);

	DynamicVector<int> v2{ v1 };
	assert(v2.getSize() == 3);

	DynamicVector<int> v3;
	v3 = v1;
	assert(v3[0] == 10);

	// test iterator
	DynamicVector<int>::iterator it = v1.begin();
	assert(*it == 10);
	assert(it != v1.end());
	it++;
	assert(*it == 25);
}

void Tests::testRepository()
{
	Repository repo{};
	Song s{ "Ed Sheeran", "I see fire", Duration{ 4, 54 }, "https://www.youtube.com/watch?v=2fngvQS_PmQ" };
	repo.addSong(s);
	Song res = repo.findByArtistAndTitle("Ed Sheeran", "I see fire");
	assert(res.getTitle() == s.getTitle() && res.getArtist() == s.getArtist());
	res = repo.findByArtistAndTitle("Ed Sheeran", "");
	assert(res.getArtist() == "");

	DynamicVector<Song> songs = repo.getSongs();
	assert(songs.getSize() == 1);
}

void Tests::testController()
{
	// TODO
}

void Tests::testAll()
{
	testSong();
	testDynamicVector();
	testRepository();
	testController();
}
