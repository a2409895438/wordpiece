#include <iostream>
#include <fstream>
#include "wordpiece_tokenizer.h"

#include <fstream>
#include <windows.h>

using namespace std;

#pragma execution_character_set("utf-8")

std::unordered_map<std::string, int> read_vocab(const char *filename)
{
    std::unordered_map<std::string, int> vocab;
    int index = 0;
    unsigned int line_count = 1;
    ifstream fs8(filename);
    if (!fs8.is_open())
    {
        cout << "Could not open " << filename << endl;
        return vocab;
    }
    std::string line;
    // Read all the lines in the file
    while (getline(fs8, line))
    {
        vocab.insert(pair<std::string, int>(std::string(line.begin(), line.end()), index));
        index++;
        line_count++;
    }
    return vocab;
}


int main(int argc, char** argv) {
    // 请在此行后加入你的程序代码
    string s = u8"海洋管家这个公众号里的免费chatgpt和绘画ai midjourney好用吗？";
    cout << s << endl;
    // cout << UTF8ToGBK(s.c_str()) << endl;    

    // string s = u8"acs";
    std::unordered_map<std::string, int> vocab = read_vocab("D:\\vc\\wordpiece\\vocab.txt");
    wordpiece::WordpieceTokenizer tokenizer("[UNK]",100,vocab);
    vector<float> input_ids;
    vector<float> input_mask;
    vector<float> segment_ids;
    tokenizer.encode(s,input_ids,input_mask,segment_ids);


    for (auto i:input_ids){
        cout<<i<<" ";
    }
    return 0;
}