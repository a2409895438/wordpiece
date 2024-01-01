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


bool TokenizerUtils::_is_chinese_char(wchar_t cp)
{
    if (
        (cp >= 0x4E00 && cp <= 0x9FFF)
        || (cp >= 0x3400 && cp <= 0x4DBF)
        || (cp >= 0x20000 && cp <= 0x2A6DF)
        || (cp >= 0x2A700 && cp <= 0x2B73F)
        || (cp >= 0x2B740 && cp <= 0x2B81F)
        || (cp >= 0x2B820 && cp <= 0x2CEAF)
        || (cp >= 0xF900 && cp <= 0xFAFF)
        || (cp >= 0x2F800 && cp <= 0x2FA1F) || cp == 0x3002 || cp == 0xFF1F || cp == 0xFF01 || cp == 0xFF0C ||
        cp == 0x3001 || cp == 0xFF1B || cp == 0xFF1A || cp == 0x300C || cp == 0x300D || cp == 0x300E ||
        cp == 0x300F || cp == 0x2018 || cp == 0x2019 || cp == 0x201C || cp == 0x201D || cp == 0xFF08 ||
        cp == 0xFF09 || cp == 0x3014 || cp == 0x3015 || cp == 0x3010 || cp == 0x3011 || cp == 0x2014 ||
        cp == 0x2026 || cp == 0x2013 || cp == 0xFF0E || cp == 0x300A || cp == 0x300B || cp == 0x3008 || cp == 0x3009
        )
        return true;
    else
        return false;
}