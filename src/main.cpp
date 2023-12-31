#include <queue>
#include <iostream>
#include<thread>
#include<string>
#include <codecvt>

using namespace std;


int main(int argc, char** argv) {
    // 请在此行后加入你的程序代码
    string s = u8"我";
    wstring_convert<codecvt_utf8<wchar_t>> conv;
    wstring ws = conv.from_bytes(s);
    wstring nws;
    for (wchar_t ch : ws) {
        //检查是否是标点和空格
        if (!iswpunct(ch) && !iswspace(ch)) {
            nws.push_back(ch);
        }
        //过滤每一行中的标点和空格
        for (wchar_t ch : ws) {
            //检查是否是标点和空格s
            if (!iswpunct(ch) && !iswspace(ch)) {
                nws.push_back(ch);
            }
        }
        //将过滤后的文本重新转换成UTF-8编码的多字节类型
        string ns = conv.to_bytes(ws);
        cout << ns;
    }
    return 0;
}