#include <unordered_map>
#include <string>
#include <vector>
#include <codecvt>

namespace wordpiece{
    const int WHITESPACE_UNICODE=32;

    class WordpieceTokenizer
    {
    public:
        std::string unk_token_;
        int max_seq_length_;
        std::unordered_map<std::string, int>& vocab_;


        WordpieceTokenizer(std::string unk_token, int max_seq_length, std::unordered_map<std::string, int>& vocab): vocab_(vocab)
        {
            unk_token_ = unk_token;
            max_seq_length_ = max_seq_length;
        }

        std::vector<std::string> read_vocab(std::string path);

        void
        encode(std::string text, std::vector<float> &input_ids, std::vector<float> &input_mask, std::vector<float> &segment_ids);

        std::vector<std::string> tokenize(std::string& text);

        void token_split(std::vector<std::string>& output_tokens,std::wstring_convert<std::codecvt_utf8<wchar_t>>& conv,std::wstring& nws);
    };
}

