#include "Tests.h"
#include <assert.h>
#include <iostream>

void Tests::testAdd()
{
    Service s;

    Issue i{ "test", "open", "test", "test" };

    s.addIssue(i);
    assert(s.getIssues()[10].getDescription() == "test");
    assert(s.getIssues()[10].getStatus() == "open");

    Issue ii{ "testnou", "closed", "test", "test" };
    s.addIssue(ii);
    assert(s.getIssues()[11].getDescription() == "testnou");
    assert(s.getIssues()[11].getStatus() == "closed");
}

void Tests::testUpdate()
{
    Service s;

    Issue i{ "test", "open", "test", "test" };

    s.addIssue(i);

    assert(s.getIssues()[10].getDescription() == "test");
    Issue ii{ "testnou", "closed", "test", "test" };
    s.addIssue(ii);
    assert(s.getIssues()[11].getDescription() == "testnou");

    s.updateIssue("testnou", "tu", "ei", "ele");
    assert(s.getIssues()[11].getStatus() == "tu");
    assert(s.getIssues()[11].getSolver() == "ele");
}

