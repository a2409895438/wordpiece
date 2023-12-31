#include "utils.h"
#include <vector>
#include <queue>
#include <iostream>
#include<thread>
#include<string>
#include <codecvt>
#include <cstdlib>  



#include <fstream>
#include <windows.h>

using namespace std;

static std::string UTF8ToGBK(const char* strUTF8)
{
    int len = MultiByteToWideChar(CP_UTF8, 0, strUTF8, -1, NULL, 0);
    wchar_t* wszGBK = new wchar_t[len + 1];
    memset(wszGBK, 0, len * 2 + 2);
    MultiByteToWideChar(CP_UTF8, 0, strUTF8, -1, wszGBK, len);
    len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
    char* szGBK = new char[len + 1];
    memset(szGBK, 0, len + 1);
    WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, NULL, NULL);
    std::string strTemp(szGBK);

    if (wszGBK) delete[] wszGBK;
    if (szGBK) delete[] szGBK;

    return strTemp;
}

bool _is_chinese_char(wchar_t cp)
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

int main(int argc, char** argv) {
    // 请在此行后加入你的程序代码
    string s = u8"ads我,是谁 ，是";
    wstring_convert<codecvt_utf8<wchar_t>> conv;
    wstring ws = conv.from_bytes(s);
    wstring nws;
    for (wchar_t ch : ws) {
        //检查是否是标点和空格
        if (!iswpunct(ch) && !iswspace(ch)) {
            nws.push_back(ch);
        }
        if (_is_chinese_char(ch)) {
            cout << "中文" << endl;
        }
        else {
            cout << "0中文" << endl;
        }
    }
    //将过滤后的文本重新转换成UTF-8编码的多字节类型
    string ns = conv.to_bytes(nws);
    //cout << UTF8ToGBK(ns.c_str());
    return 0;
}