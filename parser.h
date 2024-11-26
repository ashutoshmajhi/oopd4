// parser.h
#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>
#include "publication.h"

void parseBibFile(const std::string& filename, std::vector<Publication>& publications, const std::string& institute);

#endif
