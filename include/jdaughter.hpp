#ifndef JDAUGHTER_HPP
#define JDAUGHTER_HPP

#include <string>
#include <sstream>
#include <fstream>
#include <nlohmann/json.hpp>

/**
 * @file jdaughter.hpp
 * @brief Utilities for parsing JSON files with support for C/C++-style comments.
 *
 * This namespace provides functions to parse JSON files or strings that may contain
 * single-line (//) or multi-line (/* ... *​/) comments, which are not supported by the
 * standard JSON specification. Comments are stripped before parsing using nlohmann::json.
 */

namespace jdaughter {

using json = nlohmann::json;

/**
 * @brief Removes C/C++-style comments from a JSON string.
 *
 * This function processes the input string and removes both single-line (//)
 * and multi-line (/* ... *​/) comments, while preserving string literals and escape sequences.
 *
 * @param input The JSON string possibly containing comments.
 * @return A string with all comments removed, suitable for standard JSON parsing.
 */
inline std::string remove_comments(const std::string& input);

/**
 * @brief Parses a JSON string that may contain comments.
 *
 * This function first removes comments from the input string, then parses it using nlohmann::json.
 * An optional parser callback can be provided for custom parsing behavior.
 *
 * @param s The JSON string possibly containing comments.
 * @param cb Optional parser callback for nlohmann::json.
 * @return Parsed JSON object.
 * @throws nlohmann::json::parse_error if parsing fails.
 */
inline json parse(const std::string& s, const json::parser_callback_t& cb = nullptr);

/**
 * @brief Parses a JSON file that may contain comments.
 *
 * This function reads the contents of the specified file, removes comments,
 * and parses the result as JSON.
 *
 * @param filename Path to the JSON file.
 * @return Parsed JSON object.
 * @throws std::runtime_error if the file cannot be opened.
 * @throws nlohmann::json::parse_error if parsing fails.
 */
json parse_file(const std::string& filename);

} // namespace jdaughter

#endif // JDAUGHTER_HPP