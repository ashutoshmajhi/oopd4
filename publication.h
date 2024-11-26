#ifndef PUBLICATION_H
#define PUBLICATION_H

#include <string>
#include <vector>
#include "author.h"

using namespace std;

class Publication {
public:
    string title;
    string venue;
    vector<Author> authors;
    string doi;
    int year;

    Publication(const string& title, const string& venue, const vector<Author>& authors,
                const string& doi, int year);

    bool hasInstituteAffiliation(const string& institute);
};

#endif
