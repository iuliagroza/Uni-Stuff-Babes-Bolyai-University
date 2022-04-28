#include "ExtendedTest.h"
#include <assert.h>
#include <exception>
#include <cstdlib>
#include <vector>
#include <iostream>
#include "ListIterator.h"

using namespace std;


//order relation - ascending
bool asc(TComp c1, TComp c2) {
	if (c1 <= c2) {
		return true;
	} else {
		return false;
	}
}

//order relation - descending
bool desc(TComp c1, TComp c2) {
	if (c1 >= c2) {
		return true;
	} else {
		return false;
	}
}

//condition - element smaller or equal to 100
bool cond(TComp c1) {
    return c1 <= 100;
}

void testIteratorSteps(SortedIndexedList& list, Relation r) {
	int count = 0;
	ListIterator li = list.iterator();
	TComp prev = li.getCurrent();
	if (li.valid()) {
		count++;
		li.next();
	}
	while (li.valid()) {
		TComp current = li.getCurrent();
		assert(r(prev, current));
		count++;
		li.next();
		prev = current;
	}
	assert(count == list.size());
}

void testCreate() {
	cout << "Test create" << endl;
	SortedIndexedList list = SortedIndexedList(asc);
	assert(list.size() == 0);
	assert(list.isEmpty());

	ListIterator it = list.iterator();
	assert(!it.valid());
	it.first();

	for (int i = 0; i < 10; i++) {
		assert(!it.valid());
		assert(list.search(i) == -1);
		try {
			assert(list.getElement(i));
			assert(false);
		} catch (exception&) {
			assert(true);
		}
		try {
			assert(list.remove(i));
			assert(false);
		} catch (exception&) {
			assert(true);
		}
		try {
			it.next();
			assert(false);
		}
		catch (exception&) {
			assert(true);
		}
	}
}

//generate a vector with values between cMin and cMax so that
//1) no value that is >=cMin and <=cMax which is a multiple of s is not included
//2) values v, v>=cMin and v<=cMax which are a multiple of m (but not of s) are included c/m + 1 times
//3) values >=cMin and <=cMax are in random order
vector<int> random(int cMin, int cMax, int s, int m) {
	vector<int> v;
	for (int c = cMin; c <= cMax; c++) {
		if (c % s != 0) {
			v.push_back(c);
			if (c % m == 0) {
				for (int j = 0; j < c / m; j++) {
					v.push_back(c);
				}
			}
		}
	}
	int n = v.size();
	for (int i = 0; i < n - 1; i++) {
		int j = i + rand() % (n - i);
		swap(v[i], v[j]);
	}
	return v;
}

//generate a vector containing values >=cMin and <=cMax, each included one time, in random order
vector<int> random(int cMin, int cMax) {
	vector<int> v;
	for (int c = cMin; c <= cMax; c++) {
		v.push_back(c);
	}

	int n = v.size();
	for (int i = 0; i < n - 1; i++) {
		int j = i + rand() % (n - i);
		swap(v[i], v[j]);
	}
	return v;
}

//populate the sorted list with values >=cMin and <=cMax a.i.:
//1) no value that is >=cMin and <=cMax which is a multiple of s is not included
//2) values v, v>=cMin and v<=cMax which are a multiple of m (but not of s) are included c/m + 1 times
//3) values >=cMin and <=cMax are in random order
int populate(SortedIndexedList& list, int cMin, int cMax, int s, int m) {
	vector<int> v = random(cMin, cMax, s, m);
	int n = v.size();
	for (int i = 0; i < n; i++) {
		list.add(v[i]);
	}
	return n;
}

//populate the sorted list with values >=cMin and <=cMax, each included one time, in random order
void populate(SortedIndexedList& list, int cMin, int cMax) {
	vector<int> v = random(cMin, cMax);
	int n = v.size();
	for (int i = 0; i < n; i++) {
		list.add(v[i]);
	}
}

void testAddAndSearch(Relation r) {
	cout << "Test add and search" << endl;
	SortedIndexedList list = SortedIndexedList(r);
	int vMin = 10;
	int vMax = 30;
	int s = 5;
	int m = 3;
	int n = populate(list, vMin, vMax, s, m);
	assert(!list.isEmpty());
	assert(list.size() == n);

    //we can't find values outside the interval or on invalid positions
	int d = 30;
	for (int i = 1; i <= d; i++) {
		assert(list.search(vMin - i) == -1);
		assert(list.search(vMax + i) == -1);
		try{
			list.getElement(n-1+i);
			list.getElement(-d);
			assert(false);
		} catch (exception&) {
			assert(true);
		}
	}

	//check the relation order
	ListIterator it = list.iterator();
	it.first();
	assert(it.valid());
	TComp prev = it.getCurrent();
	it.next();
	while (it.valid()) {
		TComp current = it.getCurrent();
		assert(r(prev, current));
		prev = current;
		it.next();
	}
	testIteratorSteps(list, r);

	//check if added values can be found
		for (int v = vMin; v <= vMax; v++) {
			int p = list.search(v);
			//we can't find values which are a multiple of s
			assert((p != -1) == (v % s != 0));
			//values which are a multiple of m can be found exactly v/m+1 times
            if (p != -1 && v%m == 0){
            	for (int i=0; i<=v/m; i++){
            		try{
            			assert(list.remove(p) == v);
            		} catch (exception&) {
						assert(false);
					}
            	}
            	assert(list.search(v) == -1);
            }
		}
}

void testDeleteSearch(Relation r) {
	cout << "Test delete and search" << endl;
	SortedIndexedList list = SortedIndexedList(r);
	int vMin = 0;
	int vMax = 100;
	populate(list, vMin, vMax);

	int d = 30;
	for (int i = 1; i <= d; i++) {
		try {
			list.remove(list.search(vMax + i));
			assert(false);
		} catch (exception&) {
			assert(true);
		}
	}

	assert(!list.isEmpty());
	assert(list.size() == vMax - vMin + 1);
	ListIterator it1 = list.iterator();
	assert(it1.valid());
	it1.first();
	assert(it1.valid());
	TComp deleted = NULL_TCOMP;
	testIteratorSteps(list, r);
	try {
		deleted = list.remove(list.search(it1.getCurrent()));
		assert(list.size() == vMax - vMin);
		it1.first();
		TComp newFirst = it1.getCurrent();
		assert(newFirst != deleted);
		assert(r(deleted, newFirst));
		it1.first();
		ListIterator it2 = list.iterator();
		assert(it2.valid());
		it2.first();
		assert(it2.valid());
		assert(it1.getCurrent() == newFirst && it2.getCurrent() == newFirst);
	} catch (exception&) {
		assert(false);
	}

	//delete values in random order while checking the relation order
	vector<int> vs = random(vMin, vMax);
	int n = vs.size();
	for (int i = 0; i < n; i++) {
		testIteratorSteps(list, r);
		int v = vs[i];
		try {
			int it1  = list.search(v);
			TComp deletedCurrent = list.remove(it1);
			assert(deletedCurrent != deleted);
			assert(deletedCurrent == v);
			assert(list.search(v)  == -1);

			if (!list.isEmpty()) {
				ListIterator it2 = list.iterator();
				it2.first();
				assert(it2.valid());
				TComp prev = it2.getCurrent();
				while (it2.valid()) {
					TComp current = list.getElement(list.search(it2.getCurrent()));
					assert(r(prev, current));
					assert(!r(deletedCurrent, current) || !r(current, deletedCurrent));
					prev = current;
					it2.next();
				}
			}

		} catch (exception&) {
			assert(v == deleted);
		}
	}

	assert(list.isEmpty());
	assert(list.size() == 0);
}

void testDeleteSearch() {
	testDeleteSearch(asc);
	testDeleteSearch(desc);
}

void testAddAndSearch() {
	testAddAndSearch(asc);
	testAddAndSearch(desc);
}


void testQuantity(){
	cout << "Test quantity" << endl;
	SortedIndexedList list = SortedIndexedList(asc);

	int vMin = 3000;
	int vMax = 6000;
	vector<int> values  = random(vMin, vMax);
	int n = values.size();
    for (int i = 0; i < n; i++){
    	list.add(values[i]);
    }

    assert(list.size() == vMax - vMin + 1);
    for (int v = vMin; v <= vMax; v++){
      	assert(list.search(v)>= 0 && list.search(v) < list.size());
      	assert(list.getElement(list.search(v)) == v);
    }

    ListIterator it  = list.iterator();
    it.first();
    assert(it.valid());
	TComp firstElement = it.getCurrent();
    it.first();
    assert(it.valid());
    assert(it.getCurrent() == firstElement);
    for (int i = 0; i < list.size(); i++) {
    	it.next();
    }

    assert(!it.valid());
    it.first();
    while (it.valid()){
		TComp v  = it.getCurrent();
        assert(vMin <= v && v<=vMax);
        it.next();
    }
    assert(!it.valid());


    int d = 100;
    //consider the interval [vMin-d, vMax+d]
    for (int v = vMin-d; v <= vMax+d; v++){
    	//check that only values from the interval [vMin, vMax] are included in the list
    	 assert((list.search(v) != -1) == (vMin <= v && v <= vMax));
    	 try{
    		 assert(list.remove(list.search(v)));
    		 assert(vMin <= v && v <= vMax);
    	 } catch (exception&) {
			 assert(vMin > v || v > vMax);
		}
    }
    assert(list.size() == 0);
    assert(list.isEmpty());
}

void testFilter() {
    cout << "Test filter" << endl;

    SortedIndexedList list = SortedIndexedList(asc);
    list.add(1);
    list.add(100);
    list.add(101);
    list.add(-5);
    list.add(558);
    list.add(99);
    list.add(-100);
    list.add(229000);

    list.filter(cond);

    assert(list.size() == 5);
    assert(list.search(-100) == 0);
    assert(list.search(-5) == 1);
    assert(list.search(1) == 2);
    assert(list.search(99) == 3);
    assert(list.search(100) == 4);
    assert(list.search(101) == -1);
    assert(list.search(558) == -1);
    assert(list.search(229000) == -1);
}

void testAllExtended() {
	testCreate();
	testAddAndSearch();
	testDeleteSearch();
    testQuantity();
    testFilter();
}



