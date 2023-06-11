//
// Created by CagesThrottleUs on 11-06-2023.
//

#include "trie.hpp"
#include "badFileNameException.hpp"
#include "exitCode.hpp"
#include <cstdio>
#include <cstring>
#include <cuchar>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stack>


void Trie::fill(const std::string &srcLocation, int &retStatus) {
    std::cout << "\nChecking if File exists Trie::fill()" << std::endl;
    const std::filesystem::path path(srcLocation);
    if (!std::filesystem::exists(path)) {
        retStatus = BadFileName;
        throw BadFileNameException(path.string() + " NOT FOUND, please enter the correct name");
    }
    std::cout << "FILE FOUND" << std::endl;

    std::basic_ifstream<char32_t> file(srcLocation.c_str());
    std::basic_string<char32_t> str;

    while(std::getline(file,str, U'\n')){
        this->insert(str);
    }

    file.close();
}

Trie::Trie() : head(new TrieNode()) {

}

void Trie::insert(const std::basic_string<char32_t>& str) {
    TrieNode* curr = head;
    for(auto ch: str){
        if(curr->m.contains(ch)){
            curr = curr->m[ch];
        } else{
            curr->m[ch] = new TrieNode(ch);
            curr = curr->m[ch];
        }
    }
    curr->isTerm = true;
}

Trie::~Trie() {
    TrieNode::freeTrie(head);
    delete head;
}

auto Trie::search(const std::u32string &str) -> bool {
    if(head == nullptr){
        return false;
    }

    TrieNode* curr = head;
    for(auto ch: str){
        if(curr->m.contains(ch)){
            curr = curr->m[ch];
        } else{
            return false;
        }
    }

    return curr->isTerm;
}

void Trie::printTrie(const std::string &src) {
    if(head == nullptr){
        return;
    }
    FILE* fout = fopen(src.c_str(),"w");
    std::vector<std::u32string> const allStrings = findStrings();
    for(const auto& str: allStrings){
        printer(str,fout);
    }
    if(fclose(fout) != 0){
        std::cout << "Error Closing File\n" << std::endl;
    }
}

void Trie::printer(const std::u32string &str, FILE *fOut) {
    for(auto ch: str){
        std::setlocale(LC_ALL,"en_US.UTF-8");
        char buf[MB_LEN_MAX + 1] = {0};
        mbstate_t ps;
        memset(&ps,0, sizeof(ps));
        c32rtomb(buf, ch, &ps);
        fprintf(fOut, "%s", buf);
    }
    fprintf(fOut, "\n");
}

struct Stackable{
    TrieNode* ptr{};
    std::u32string str;
};

auto Trie::findStrings() -> std::vector<std::u32string> {
    std::vector<std::u32string> ans;
    std::stack<Stackable> stack;
    TrieNode* curr = head;
    Stackable temp;
    temp.ptr = curr;
    temp.str = U"";
    stack.push(temp);

    while(!stack.empty()){
        temp = stack.top();
        stack.pop();
        temp.str = temp.str + (temp.ptr->data == U'\0' ? U"" : std::basic_string(1,temp.ptr->data));
        if(temp.ptr->isTerm) {
            ans.push_back(temp.str);
        }
        for(auto &[key, value]: temp.ptr->m){
            Stackable temp2;
            temp2.ptr = value;
            temp2.str = temp.str;
            stack.push(temp2);
        }
    }

    return ans;
}

void TrieNode::freeTrie(TrieNode *root) {
    std::stack<TrieNode*> stack;
    stack.push(root);

    while(!stack.empty()){
        TrieNode* curr = stack.top();
        if(curr->isTerm or curr->m.empty()){
            delete curr;
            stack.pop();
        } else{
            for(auto &[key, value]: curr->m){
                stack.push(value);
                curr->m.erase(key);
            }
        }
    }
}

TrieNode::TrieNode(): data(U'\0'), m({}), isTerm(false){};

TrieNode::TrieNode(char32_t data) : data(data), m({}), isTerm(false){

}
