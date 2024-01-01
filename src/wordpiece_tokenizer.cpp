#include <wordpiece_tokenizer.h>
#include <algorithm>
#include <tokenizer_utils.h>
#include <iostream>
#include <windows.h>


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


void wordpiece::WordpieceTokenizer::token_split(std::vector<std::string>& output_tokens,std::wstring_convert<std::codecvt_utf8<wchar_t>>& conv,std::wstring& nws){
    if (nws.size() == 0) return;
    std::string token = conv.to_bytes(nws);
    int len_char_array = token.length();


    int start = 0;
    bool is_bad = false;
    std::vector<std::string> sub_tokens;
    while(start < len_char_array){
        int end = len_char_array;
        std::string cur_substr = "";
        while (start < end){
            std::string substr = token.substr(start, end - start);
            if(start > 0){
                substr = "##" + substr;
            }
            auto it = vocab_.find(substr);
            if(it != vocab_.end()){
                cur_substr = substr;
                break;
            }
            --end;
        }
        if (cur_substr == ""){
            is_bad = true;
            break;
        }
        sub_tokens.push_back(cur_substr);
        start = end;
    }

    if(is_bad){
        output_tokens.push_back(unk_token_);
    }
    else{
        output_tokens.insert(output_tokens.end(), sub_tokens.begin(), sub_tokens.end());
    }
    nws.clear();
    return;
}

// 传入utf-8编码
std::vector<std::string> wordpiece::WordpieceTokenizer::tokenize(std::string& text)
{
    std::vector<std::string> output_tokens;    
    // trim
    text.erase(0, text.find_first_not_of(" \t\r\n"));
    text.erase(text.find_last_not_of(" \t\r\n") + 1);
    if (text == "")
    {
        return output_tokens;
    }
    std::string text_c;
    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    // 转为unicode的wstring
    std::wstring ws = conv.from_bytes(text);
    std::wstring nws;

    for (wchar_t ch : ws) {
        if(iswspace(ch)){
            token_split(output_tokens, conv, nws);
            continue;
        }
        // 检查是否是标点符号和中文
        if (iswpunct(ch) || TokenizerUtils::_is_chinese_char(ch)) {
            token_split(output_tokens, conv, nws);
            nws.push_back(ch);
            token_split(output_tokens, conv, nws);
        }
        else {
            nws.push_back(ch);
        }
    }
    token_split(output_tokens, conv, nws);

    return output_tokens;
}


void wordpiece::WordpieceTokenizer::encode(std::string text, std::vector<float> &input_ids, std::vector<float> &input_mask, std::vector<float> &segment_ids)
{

    std::vector<std::string> split_tokens = tokenize(text);

    if(split_tokens.size() > max_seq_length_ - 2){
        split_tokens.resize(max_seq_length_ - 2);
    }

    split_tokens.insert(split_tokens.begin(), "[CLS]");
    split_tokens.push_back("[SEP]");


    for (int i = 0; i < split_tokens.size(); ++i){
        std::cout << split_tokens[i] << " ";
        segment_ids.push_back(0.0);
        input_mask.push_back(1.0);

        auto it = vocab_.find(split_tokens[i]);
        if(it != vocab_.end()){
            input_ids.push_back(it->second);
        }else{
            input_ids.push_back(vocab_[unk_token_]);
        }
    }
    std::cout << std::endl;

    while (input_ids.size() < max_seq_length_){
        input_ids.push_back(0.0);
        input_mask.push_back(0.0);
        segment_ids.push_back(0.0);
    }
    return;
}