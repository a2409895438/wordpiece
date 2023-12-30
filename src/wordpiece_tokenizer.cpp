#include <wordpiece_tokenizer.h>
#include <algorithm>

// todo:分割
std::vector<std::string> tokenize(std::string text)
{
    std::vector<std::string> split_tokens;    
    // trim
    text.erase(0, text.find_first_not_of(" \t\r\n"));
    text.erase(text.find_last_not_of(" \t\r\n") + 1);
    if (text == "")
    {
        return split_tokens;
    }

    int len_char_array = text.length();
    int start = 0;

    while(start < len_char_array){
        char letter = char_array[i];
        if (_is_punctuation(letter))
        {
            vector<char> temp = {letter};
            output.push_back(temp);
            start_new_word = true;
        }
        else
        {
            if (start_new_word)
            {
                vector<char> temp_2;
                output.push_back(temp_2);
            }
            start_new_word = false;
            output.back().push_back(letter);
        }
        i += 1;
    }
}


void wordpiece::WordpieceTokenizer::encode(std::string text, std::vector<float> &input_ids, std::vector<float> &input_mask, std::vector<float> &segment_ids,
            int max_seq_length = 512, const char *truncation_strategy = "longest_first")
{

}