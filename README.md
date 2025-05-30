# jdaughter

A lightweight C++ header-only wrapper around [nlohmann/json](https://github.com/nlohmann/json) that supports JSON files with comments.

## Features

- Supports single-line (`//`) and multi-line (`/* ... */`) comments.
- Strips comments safely without removing string content.
- Easy to use as a drop-in replacement for `nlohmann::json::parse`.

## Usage

```cpp
#include "jdaughter.hpp"
#include <iostream>

int main() {
    std::string json_with_comments = R"(
        {
            // Comment here
            "key": "value" /* another comment */
        }
    )";

    auto j = json_comment::parse(json_with_comments);
    std::cout << j.dump(4) << std::endl;
}