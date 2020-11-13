#pragma once

#define JSON_SINGLE_LINE_PRETTY_ARRAY
/*
    Addition to the nlohmann::json library

    The json.hpp file was edited to make arrays print on one line in pretty print mode,
    in constrast to printing one element per line, which takes up too much space for large arrays.

    To use this custom format: #define JSON_CUSTOM_PRETTY_ARRAY
*/

#include "nlohmann/json.hpp"

#include <string> // for std::string

/*
    Selecting How Json Is Ordered:

    1. nlohmann::ordered_json is ordered in the same order you insert objects
    2. nlohmann::json is ordered alphabetically

    Change the using Json to switch between the two.
*/

namespace accord
{
    using Json = nlohmann::ordered_json;

    extern Json g_json; // for debugging purposes

    std::string JsonToString(const Json& j);

    std::string JsonToPrettyString(const Json& j);
} // namespace accord

