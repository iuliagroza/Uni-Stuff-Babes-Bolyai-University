#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <assert.h>
#include <iostream>
#include <vector>

#include <exception>

using namespace std;

void testIteratorSteps(MultiMap& mm) {
	int count = 0;
	MultiMapIterator mmit = mm.iterator();
	while (mmit.valid()) {
		count++;
		mmit.next();
	}
	assert(count == mm.size());
}

void testCreate() {
	cout << "Test create" << endl;
	MultiMap m;
	assert(m.isEmpty() == true);
	assert(m.size() == 0);

	MultiMapIterator im = m.iterator();
	assert(im.valid() == false);

	for (int i = -10; i < 30; i++) {
		assert(m.remove(i, i) == false);
	}
    vector<TValue> v;
	for (int i = -10; i < 30; i++) {
            v=m.search(i);
            assert(v.size()==0);
	}
}

void testAdd() {
	cout << "Test add" << endl;
	MultiMap m; 
	for (int i = 0; i < 10; i++) {
		m.add(i, i);
	}
	assert(m.isEmpty() == false);
	assert(m.size() == 10);
	for (int i = -10; i < 20; i++) { 
		m.add(i, 2*i);
	}
	testIteratorSteps(m);
	assert(m.isEmpty() == false);
	assert(m.size() == 40);
	for (int i = -100; i < 100; i++) {
		m.add(i, 3*i);
	}
	assert(m.isEmpty() == false);
	assert(m.size() == 240);
	for (int i = -200; i < 200; i++) { 
		vector<TValue> v;
		if (i < -100) {
            v=m.search(i);
			assert(v.size() == 0);
		}
		else if (i < -10) {
            v=m.search(i);
			assert(v.size() == 1);
		}
		else if (i < 0) {
            v=m.search(i);
			assert(v.size() == 2);
		}
		else if (i < 10) {
            v=m.search(i);
			assert(v.size() == 3);
		}
		else if (i < 20) {
            v=m.search(i);
			assert(v.size() == 2);
		}
		else if (i < 100) {
            v=m.search(i);
			assert(v.size() == 1);
		}
		else {
            v=m.search(i);
			assert(v.size() == 0);
		}
	}
	testIteratorSteps(m);
	for (int i = 10000; i > -10000; i--) { 
		m.add(i, 4*i);
	}
	assert(m.size()==20240);
	testIteratorSteps(m);
}

void testRemove() {
	cout << "Test remove" << endl;
	MultiMap m;
	for (int i = -100; i < 100; i++) { 
		assert(m.remove(i, i) == false);
	}
	assert(m.size() == 0);
	for (int i = -100; i < 100; i = i + 2) { 
		m.add(i, i);
	}
	for (int i = -100; i < 100; i++) { 

		if (i % 2 == 0) {
			assert(m.remove(i, i) == true);
			assert(m.remove(i, 2*i) == false);
		}
		else {
			assert(m.remove(i, i) == false);
            assert(m.remove(i, 2*i) == false);
		}
	}
	assert(m.size() == 0);

	for(int i = 0; i <= 100; i++)
        m.add(0, i);    
    m.add(1, 100);
	testIteratorSteps(m);
    for(int i = 0; i <= 100; i++)
        assert(m.remove(0, i) == true);
    
    vector<TValue> v;
	v=m.search(1);
    assert(v.size()==1 && v.at(0)==100);
    v=m.search(0);
    assert(v.size()==0);
    MultiMapIterator it=m.iterator();
    it.next();
    assert(it.valid()==false);
    
    assert(m.remove(1,100)==true);
    
    assert(m.size()==0);
	for (int i = -100; i <= 100; i = i + 2) { 
		m.add(i, 2*i);
	}
	for (int i = 100; i > -100; i--) { 
		if (i % 2 == 0) {
  			assert(m.remove(i, 3*i+1) == false);
			assert(m.remove(i, 2*i) == true);
		}
		else {
			assert(m.remove(i, 3*i+1) == false);
		}
	}

	assert(m.size() == 1);
	bool b = m.remove(-100, -200);
	assert(b==true);
	for (int i = -100; i < 100; i++) { 
	  if(i!=0){
		m.add(i, i+1);
		m.add(i, 2*i+1);
		m.add(i, 3*i+1);
		m.add(i, 4*i+1);
		m.add(i, 5*i+1);
	  }
	}
	assert(m.size() == 995);
	testIteratorSteps(m);
	for (int i = -100; i < 100; i++) {
       if(i!=0){
            v=m.search(i);
			assert(v.size() == 5);
		}
	}
	for (int i = -100; i < 100; i++) { 
	  if (i!=0)
		assert(m.remove(i,i+1) == true);
	}
	testIteratorSteps(m);
	assert(m.size() == 796);
	for (int i = -100; i < 100; i++) {
       if (i!=0){
            v=m.search(i);
			assert(v.size() == 4);
		}
	}
	for (int i = -200; i < 200; i++) { 
		if (i < -100 || i >= 100) {
			assert(m.remove(i, i) == false);
			assert(m.remove(i, i) == false);
			assert(m.remove(i, i) == false);
			assert(m.remove(i, i) == false);
			assert(m.remove(i, i) == false);
		}
		else
          if (i!=0){
			assert(m.remove(i, i+1) == false);
			assert(m.remove(i, 2*i+1) == true);
			assert(m.remove(i, 3*i+1) == true);
			assert(m.remove(i, 4*i+1) == true);
			assert(m.remove(i, 5*i+1) == true);
		}
	}
	assert(m.size() == 0);
	for (int i = -1000; i < 1000; i++) {
            v=m.search(i);
			assert(v.size() == 0);
	}
	int min = -200;
	int max = 200;
	while (min < max) { 
		m.add(min, min);
		m.add(max, max);
		min++;
		max--;
	}
	m.add(0, 100);
	m.add(0, 200);
	assert(m.size() == 402);
	for (int i = -30; i < 30; i++) { 
        v=m.search(i);
		if (i==0) assert(v.size() == 2);
		  else assert(v.size() == 1);
		if (i!=0) assert(m.remove(i, i) == true);
		if (i != 0) {
            v=m.search(i);
			assert(v.size() == 0);
		}
	}
	assert(m.size() == 343);
 }


void testIterator() { 
	cout << "Test iterator" << endl;
	MultiMap m;
	MultiMapIterator im = m.iterator();
	assert(im.valid() == false);
	try {
		im.getCurrent();
		assert(false);
	}
	catch (exception& ex) {
		assert(true);
	}
	try {
		im.next();
		assert(false);
	}
	catch (exception& ex) {
		assert(true);
	}
	for (int i = 0; i < 100; i++) { 
		m.add(33, 33);
	}
	MultiMapIterator im2 = m.iterator(); 
	assert(im2.valid() == true);
	for (int i = 0; i < 100; i++) {
		TElem elem = im2.getCurrent();
		assert(elem.first == 33 && elem.second==33);
		im2.next();
	}
	assert(im2.valid() == false);
	im2.first(); 
	assert(im2.valid() == true);
	for (int i = 0; i < 100; i++) {
		TElem elem = im2.getCurrent();
		TElem elem2 = im2.getCurrent();
		assert(elem.first == 33 && elem.second==33);
		assert(elem2.first == 33 && elem2.second==33);
		im2.next();
	}
	assert(im2.valid() == false);

	MultiMap m2;
	for (int i = -100; i < 100; i++) { 
		m2.add(i, 2*i);
		m2.add(i, 3*i);
		m2.add(i, 4*i);
	}
	MultiMapIterator im3 = m2.iterator();
	assert(im3.valid() == true); 
	for (int i = 0; i < 600; i++) {
		TElem e1 = im3.getCurrent();
		im3.next();
	}
	assert(im3.valid() == false);
	im3.first();
	assert(im3.valid() == true);
	MultiMap m3;
	for (int i = 0; i < 200; i= i + 4) {
		m3.add(i, 5*i);
	}
	MultiMapIterator im4 = m3.iterator();
	assert(im4.valid() == true);
	int count = 0;
	while (im4.valid()) { 
		TElem e = im4.getCurrent();
		assert(e.first % 4 == 0);
		im4.next();
		count++;
	}
	assert(count == 50);
	MultiMap m4; 
	for (int i = 0; i < 100; i++) {
		m4.add(i, i);
		m4.add(i, i * (-2));
		m4.add(i, i * 2);
		m4.add(i, i / 2);
		m4.add(i, i / (-2));
	}
	
	vector<TElem> elements;
	MultiMapIterator im5 = m4.iterator();
	while (im5.valid()) {
		TElem e = im5.getCurrent();
		elements.push_back(e);
		im5.next();
	}

	assert(elements.size() == m4.size());
	for (unsigned int i = 0; i < elements.size(); i++) {
		TElem lastElem = elements.at(elements.size() - i  - 1);
        vector<TValue> v1;
        v1=m4.search(lastElem.first);
        assert(v1.size() !=0 );
		bool b=m4.remove(lastElem.first, lastElem.second);
		assert(b==true);
	}
}

void testQuantity() {
	cout << "Test quantity" << endl;
	MultiMap m;
	for (int i = 10; i >= 1; i--) {
		for (int j = -30000; j < 30000; j = j + i) {
			m.add(j, j);
		}
	}
	assert(m.size() == 175739);
	vector<TValue> v;
    v=m.search(-30000);
    assert(v.size() == 10);

	MultiMapIterator im = m.iterator();
	assert(im.valid() == true);
	for (int i = 0; i < m.size(); i++) {
		im.next();
	}
	im.first();
	while (im.valid()) { 
		TElem e = im.getCurrent();
        v=m.search(e.first);
        assert(v.size() !=0 );
		im.next();
	}
	assert(im.valid() == false);
}


void testAllExtended() {
	testCreate();
	testAdd();
	testRemove();
    testIterator();
	testQuantity();
}
