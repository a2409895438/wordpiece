#include <vector>
#include <string>

namespace TokenizerUtils {
std::vector<std::string> splitStringByUtf8Char(std::string& input);
bool _is_chinese_char(wchar_t cp);
}