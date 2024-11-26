#ifndef AUTHOR_H
#define AUTHOR_H

#include <string>

using namespace std;

class Author {
public:
    string name;        // Author's name
    string affiliation; // Author's affiliation

    Author(const string& name, const string& affiliation);
};

#endif
