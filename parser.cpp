// parser.cpp
#include "parser.h"
#include "publication.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <set>
#include <regex>

using namespace std;

// Function to parse an individual line to extract key-value pairs
pair<string, string> parseLine(const string& line) {
    size_t pos = line.find("=");
    if (pos == string::npos) {
        throw runtime_error("Invalid format, '=' not found.");
    }
    string key = line.substr(0, pos);
    string value = line.substr(pos + 1);

    // Remove leading and trailing whitespaces or quotes from value
    value = regex_replace(value, regex("^\\s+|\\s+$"), "");
    if (value.front() == '"' || value.front() == '{') value = value.substr(1);
    if (value.back() == '"' || value.back() == '}') value = value.substr(0, value.size() - 1);

    return make_pair(key, value);
}

// Function to parse authors from the author string
vector<Author> parseAuthors(const string& value, const string& institute) {
    vector<Author> authors;
    stringstream ss(value);
    string authorName;
    
    // Split authors by 'and'
    while (getline(ss, authorName, 'a')) {
        if (authorName.empty()) continue;
        // Clean up the author string
        authorName = regex_replace(authorName, regex("^\\s+|\\s+$"), "");

        // Assuming the affiliation is the same for all authors in the list
        authors.push_back(Author(authorName, institute));
    }
    return authors;
}

// Function to parse the .bib file and populate the publications vector
void parseBibFile(const string& filename, vector<Publication>& publications, const string& institute) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Could not open the file.");
    }

    string line;
    string title, venue, doi;
    int year;
    vector<Author> authors;
    
    // Read and parse the file line by line
    while (getline(file, line)) {
        if (line.empty() || line[0] == '%' || line[0] == '}') {
            continue;
        }

        if (line.find("@InPROCEEDINGS") != string::npos || line.find("@ARTICLE") != string::npos) {
            title = venue = doi = "";
            year = 0;
            authors.clear();
            continue;
        }

        try {
            auto [key, value] = parseLine(line);  // Parse key-value pairs

            if (key == "title") {
                title = value;
            } else if (key == "venue" || key == "journal") {
                venue = value;
            } else if (key == "year") {
                year = stoi(value);
            } else if (key == "doi") {
                doi = value;
            } else if (key == "author") {
                // Parse authors from the author string
                authors = parseAuthors(value, institute);
            }

        } catch (const runtime_error& e) {
            throw runtime_error("Error while parsing line: " + line);
        }

        // When we encounter the closing brace, we push the publication into the vector
        if (line.find("}") != string::npos) {
            if (authors.empty()) {
                throw runtime_error("No authors found for this publication.");
            }
            publications.push_back(Publication(title, venue, authors, doi, year));
        }
    }
    file.close();
}
