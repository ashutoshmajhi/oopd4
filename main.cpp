#include <iostream>
#include <vector>
#include "publication.h"
#include "parser.h"

using namespace std;

void searchPublicationsByAuthor(const string& authorName, const vector<Publication>& publications) {
    int totalCoAuthors = 0;
    int publicationCount = 0;

    // Loop through publications and check for matching author
    for (const auto& pub : publications) {
        for (const auto& author : pub.authors) {
            if (author.name == authorName) {
                // Output publication details
                cout << "Title: " << pub.title << "\nVenue: " << pub.venue << "\nYear: " << pub.year << "\n";
                if (!pub.doi.empty()) {
                    cout << "DOI: " << pub.doi << "\n";
                }
                cout << "Authors: ";
                for (const auto& coAuthor : pub.authors) {
                    cout << coAuthor.name << " (" << coAuthor.affiliation << "), ";
                }
                cout << "\n\n";

                totalCoAuthors += (pub.authors.size() - 1);  // exclude the author itself
                publicationCount++;
                break;
            }
        }
    }

    // If publications were found, calculate average co-authors
    if (publicationCount > 0) {
        double averageCoAuthors = static_cast<double>(totalCoAuthors) / publicationCount;
        cout << "Average number of co-authors for " << authorName << ": " << averageCoAuthors << "\n";
    } else {
        cout << "No publications found for author: " << authorName << "\n";
    }
}

int main() {
    vector<Publication> publications;
    const string institute = "IIIT-Delhi";

    try {
    // Parse the bib file and construct the publications vector
    parseBibFile("publist.bib", publications, institute);

    string authorName;
    cout << "Enter author name to search: ";
    getline(cin, authorName);

    // Search publications for the specified author
    searchPublicationsByAuthor(authorName, publications);
} catch (const std::exception& e) {
    cerr << "Error: " << e.what() << "\n";
}


    return 0;
}
