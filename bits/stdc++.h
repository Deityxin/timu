#pragma once

// Local replacement for <bits/stdc++.h> to use with angle brackets
// Aggregates commonly used C and C++ standard headers.

// C headers
#include <cassert>
#include <cctype>
#include <cerrno>
#include <cfenv>
#include <cfloat>
#include <cinttypes>
#include <climits>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

// C++ headers
#include <algorithm>
#include <array>
#include <bitset>
#include <chrono>
#include <complex>
#include <deque>
#include <exception>
#include <forward_list>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <mutex>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <random>
#include <ratio>
#include <regex>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <tuple>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <valarray>
#include <vector>

// Conditionally include C++17 headers when available
#if defined(__has_include)
  #if __has_include(<string_view>)
    #include <string_view>
  #endif
  #if __has_include(<optional>)
    #include <optional>
  #endif
  #if __has_include(<variant>)
    #include <variant>
  #endif
  #if __has_include(<shared_mutex>)
    #include <shared_mutex>
  #endif
  #if __has_include(<filesystem>)
    #include <filesystem>
  #endif
#endif
