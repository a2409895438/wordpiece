#include <unordered_map>
#include <string>
#include <vector>

namespace wordpiece{
    class WordpieceTokenizer
    {
    public:
        std::unordered_map<std::string, int> vocab_;
        std::string unk_token_;
        int max_input_chars_per_word_;

        WordpieceTokenizer() {};

        WordpieceTokenizer(const char *vocab_file, std::string unk_token = "[UNK]", int max_input_chars_per_word = 100)
        {
            unk_token_ = unk_token;
            max_input_chars_per_word_ = max_input_chars_per_word;
        }

        std::vector<std::string> read_vocab(std::string path);

        std::string tokenize(std::string text);

        void
        encode(std::string text, std::vector<float> &input_ids, std::vector<float> &input_mask, std::vector<float> &segment_ids,
            int max_seq_length = 512, const char *truncation_strategy = "longest_first");
    };

    std::vector<std::string> tokenize(std::string text);
}

