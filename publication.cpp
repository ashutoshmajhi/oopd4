#include "publication.h"
#include <algorithm>

Publication::Publication(const string& title, const string& venue, const vector<Author>& authors,
                         const string& doi, int year)
    : title(title), venue(venue), authors(authors), doi(doi), year(year) {}

bool Publication::hasInstituteAffiliation(const string& institute) {
    for (const auto& author : authors) {
        if (author.affiliation == institute) {
            return true;
        }
    }
    return false;
}
