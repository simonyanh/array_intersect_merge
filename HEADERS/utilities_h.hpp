#ifndef __utils_hpp__
#define __utils_hpp__

#include <string>
#include <vector>

#include "../headers/array_h.hpp"

std::vector<std::string> split(const std::string&, const std::string& sep = " ");
size_t insert(const std::string& prompt);
void standard(Array& arr, std::vector<std::string>& chunks);
void intersect(Array& arr);
void merge(Array& arr);

#endif  // __utils_hpp__
