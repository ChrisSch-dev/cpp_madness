#include <iostream>
#include <fstream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <bitset>
#include <string>
#include <memory>

struct Node {
    char ch;
    int freq;
    std::shared_ptr<Node> left, right;
    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(std::shared_ptr<Node> l, std::shared_ptr<Node> r) {
        return l->freq > r->freq;
    }
};

void build_codes(std::shared_ptr<Node> root, std::string str, std::unordered_map<char,std::string>& codes) {
    if (!root) return;
    if (!root->left && !root->right) codes[root->ch] = str;
    build_codes(root->left, str + "0", codes);
    build_codes(root->right, str + "1", codes);
}

std::shared_ptr<Node> build_tree(const std::string& text, std::unordered_map<char, std::string>& codes) {
    std::unordered_map<char,int> freq;
    for (char c : text) freq[c]++;
    std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, Compare> pq;
    for (auto& f : freq) pq.push(std::make_shared<Node>(f.first, f.second));
    while (pq.size() > 1) {
        auto l = pq.top(); pq.pop();
        auto r = pq.top(); pq.pop();
        auto n = std::make_shared<Node>('\0', l->freq + r->freq);
        n->left = l; n->right = r;
        pq.push(n);
    }
    build_codes(pq.top(), "", codes);
    return pq.top();
}

// Save header for decompression
void save_header(std::ofstream& fo, const std::unordered_map<char, std::string>& codes) {
    fo << codes.size() << "\n";
    for (const auto& p : codes)
        fo << p.first << " " << p.second << "\n";
}

void load_header(std::ifstream& fi, std::unordered_map<std::string, char>& codes) {
    int n; fi >> n;
    for (int i = 0; i < n; ++i) {
        char c; std::string code;
        fi >> std::ws; c = fi.get(); fi >> code;
        codes[code] = c;
    }
    fi.get(); // consume newline
}

void compress(const std::string& in, const std::string& out) {
    std::ifstream fi(in, std::ios::binary);
    std::string text((std::istreambuf_iterator<char>(fi)), std::istreambuf_iterator<char>());
    std::unordered_map<char,std::string> codes;
    build_tree(text, codes);
    std::ofstream fo(out, std::ios::binary);
    save_header(fo, codes);
    std::string bitstr;
    for (char c : text) bitstr += codes[c];
    while (bitstr.size() % 8 != 0) bitstr += '0';
    for (size_t i = 0; i < bitstr.size(); i += 8) {
        std::bitset<8> b(bitstr.substr(i, 8));
        fo.put((unsigned char)b.to_ulong());
    }
    std::cout << "Compression complete.\n";
}

void decompress(const std::string& in, const std::string& out) {
    std::ifstream fi(in, std::ios::binary);
    std::unordered_map<std::string, char> codes;
    load_header(fi, codes);
    std::string bits, outtext;
    char byte;
    while (fi.get(byte)) {
        std::bitset<8> b(byte);
        bits += b.to_string();
    }
    std::string cur;
    for (char bit : bits) {
        cur += bit;
        if (codes.count(cur)) {
            outtext += codes[cur];
            cur.clear();
        }
    }
    std::ofstream fo(out, std::ios::binary);
    fo << outtext;
    std::cout << "Decompression complete.\n";
}

int main() {
    std::cout << "1. Compress\n2. Decompress\nChoose: ";
    int choice; std::cin >> choice;
    std::string in, out;
    std::cout << "Input file: "; std::cin >> in;
    std::cout << "Output file: "; std::cin >> out;
    if (choice == 1) compress(in, out);
    else decompress(in, out);
}