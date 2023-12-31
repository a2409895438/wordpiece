#include<tokenizer_utils.h>

std::vector<std::string> TokenizerUtils::splitStringByUtf8Char(std::string& input) {  
    std::vector<std::string> result;  
    int len = input.length();  
    int start = 0;  
    int end = 0;  
    while (end < len) {  
        // 判断当前字节是否是UTF-8字符的起始字节  
        if ((input[end] & 0x80) == 0) {  
            end++; // 单字节字符  
        } else if ((input[end] & 0xE0) == 0xC0) {  
            end += 2; // 双字节字符  
        } else if ((input[end] & 0xF0) == 0xE0) {  
            end += 3; // 三字节字符  
        } else if ((input[end] & 0xF8) == 0xF0) {  
            end += 4; // 四字节字符  
        } else {  
            // 非法的UTF-8字符  
            end++; // 跳过非法字符  
        }  
        // 将切割出来的字符添加到结果中  
        result.push_back(input.substr(start, end - start));  
        start = end;  
    }  
    return result;  
}  

bool TokenizerUtils::is_chinese_char(std::string& word)
{
     if (str.size() % 3 != 0) {  
        return false; // 非3的倍数，不是UTF-8编码的中文  
    }  
  
    for (char c : str) {  
        uint8_t high = (uint8_t)(c >> 4); // 取高位4位  
        if (high >= 0xE0 && high <= 0xEF) { // 检查是否为中文的UTF-8编码范围  
            return true;  
        }  
    }  
    return false; // 没有找到中文字符
}