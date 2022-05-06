#include "ShortTest.h"
#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <assert.h>
#include <vector>

void testKeySet() {
    cout << "Test keySet\n";
    MultiMap m;
    m.add(1, 100);
    m.add(2, 200);
    m.add(3, 300);
    m.add(1, 500);
    m.add(2, 600);
    m.add(4, 800);
    m.add(5, 100);
    m.add(5, 200);
    m.add(5, 300);
    m.add(16, 500);
    m.add(2, 600);
    m.add(4, 800);

    vector<TKey> keys = m.keySet();
    assert(keys.size() == 6);
    assert(keys[0] == 1);
    assert(keys[1] == 2);
    assert(keys[2] == 3);
    assert(keys[3] == 4);
    assert(keys[4] == 5);
    assert(keys[5] == 16);

    MultiMap m_empty;
    vector<TKey> keys_empty = m_empty.keySet();
    assert(keys_empty.size() == 0);
}

void testAll() {
    testKeySet();

	MultiMap m;
	m.add(1, 100);
	m.add(2, 200);
	m.add(3, 300);
	m.add(1, 500);
	m.add(2, 600);
	m.add(4, 800);

	assert(m.size() == 6);

	assert(m.remove(5, 600) == false);
	assert(m.remove(1, 500) == true);

	assert(m.size() == 5);

    vector<TValue> v;
	v=m.search(6);
	assert(v.size()==0);

	v=m.search(1);
	assert(v.size()==1);

	assert(m.isEmpty() == false);

	MultiMapIterator im = m.iterator();
	assert(im.valid() == true);
	while (im.valid()) {
		im.getCurrent();
		im.next();
	}
	assert(im.valid() == false);
	im.first();
	assert(im.valid() == true);
}
