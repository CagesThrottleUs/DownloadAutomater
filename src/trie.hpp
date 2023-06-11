//
// Created by CagesThrottleUs on 11-06-2023.
//

#ifndef DOWNLOADAUTOMATER_TRIE_HPP
#define DOWNLOADAUTOMATER_TRIE_HPP


#include <string>
#include <unordered_map>
#include <vector>

struct TrieNode{
    char32_t data;
    std::unordered_map<char32_t, TrieNode*> m;
    bool isTerm;

    TrieNode();
    explicit TrieNode(char32_t data);
    static void freeTrie(TrieNode* root);
};

class Trie {
    TrieNode* head;
public:
    explicit Trie();
    void fill(const std::string& path, int &retStatus);
    void insert(const std::basic_string<char32_t>& str);
    auto search(const std::u32string& str) -> bool;
    void printTrie(const std::string& src);
    virtual ~Trie();
private:
    static void printer(const std::u32string& str, FILE* fOut);
    auto findStrings() -> std::vector<std::u32string>;
};


#endif //DOWNLOADAUTOMATER_TRIE_HPP
