#include "jdaughter.hpp"

namespace jdaughter {

enum class CommentLexerState {
    Normal,
    InString,
    InSingleLineComment,
    InMultiLineComment,
    InStringEscape
};

inline std::string remove_comments(const std::string& input) {
    std::ostringstream out;
    CommentLexerState state = CommentLexerState::Normal;
    size_t len = input.size();
    for (size_t i = 0; i < len; ++i) {
        char c = input[i];
        char next = (i + 1 < len) ? input[i + 1] : '\0';

        switch (state) {
            case CommentLexerState::Normal:
                if (c == '/' && next == '/') {
                    state = CommentLexerState::InSingleLineComment;
                    ++i;
                } else if (c == '/' && next == '*') {
                    state = CommentLexerState::InMultiLineComment;
                    ++i;
                } else if (c == '"') {
                    out << c;
                    state = CommentLexerState::InString;
                } else {
                    out << c;
                }
                break;
            case CommentLexerState::InString:
                out << c;
                if (c == '\\') {
                    state = CommentLexerState::InStringEscape;
                } else if (c == '"') {
                    state = CommentLexerState::Normal;
                }
                break;
            case CommentLexerState::InStringEscape:
                out << c;
                state = CommentLexerState::InString;
                break;
            case CommentLexerState::InSingleLineComment:
                if (c == '\n') {
                    out << c;
                    state = CommentLexerState::Normal;
                }
                break;
            case CommentLexerState::InMultiLineComment:
                if (c == '*' && next == '/') {
                    state = CommentLexerState::Normal;
                    ++i;
                }
                break;
        }
    }
    return out.str();
}

inline nlohmann::json parse(const std::string& s, const nlohmann::json::parser_callback_t& cb) {
    std::string no_comments = remove_comments(s);
    if (cb) {
        return nlohmann::json::parse(no_comments, cb);
    } else {
        return nlohmann::json::parse(no_comments);
    }
}

nlohmann::json parse_file(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) {
        throw std::runtime_error("Could not open file: " + filename);
    }
    std::ostringstream ss;
    ss << in.rdbuf();
    return parse(ss.str());
}

} // namespace jdaughter