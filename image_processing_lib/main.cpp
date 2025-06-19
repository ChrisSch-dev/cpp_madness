#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

struct Image {
    int w, h;
    std::vector<unsigned char> data;
    void load(const std::string& filename) {
        std::ifstream in(filename, std::ios::binary);
        std::string magic; in >> magic; in >> w >> h;
        int maxval; in >> maxval; in.get();
        data.resize(w*h);
        in.read((char*)data.data(), w*h);
    }
    void save(const std::string& filename) {
        std::ofstream out(filename, std::ios::binary);
        out << "P5\n" << w << " " << h << "\n255\n";
        out.write((char*)data.data(), w*h);
    }
    void invert() { for (auto& p : data) p = 255 - p; }
    void blur() {
        std::vector<unsigned char> temp = data;
        for (int y = 1; y < h-1; ++y)
            for (int x = 1; x < w-1; ++x) {
                int sum = 0;
                for (int dy = -1; dy <= 1; ++dy)
                    for (int dx = -1; dx <= 1; ++dx)
                        sum += temp[(y+dy)*w + (x+dx)];
                data[y*w + x] = sum / 9;
            }
    }
    void resize(int neww, int newh) {
        std::vector<unsigned char> newdata(neww*newh);
        for (int y = 0; y < newh; ++y)
            for (int x = 0; x < neww; ++x)
                newdata[y*neww + x] = data[(y*h/newh)*w + (x*w/neww)];
        w = neww; h = newh; data = newdata;
    }
};

int main() {
    Image img;
    std::string file;
    std::cout << "Input .pgm file: "; std::cin >> file;
    img.load(file);
    std::cout << "1. Invert\n2. Blur\n3. Resize\nChoose: ";
    int op; std::cin >> op;
    if (op == 1) img.invert();
    else if (op == 2) img.blur();
    else if (op == 3) {
        int nw, nh;
        std::cout << "New width height: "; std::cin >> nw >> nh;
        img.resize(nw, nh);
    }
    std::string out;
    std::cout << "Output file: "; std::cin >> out;
    img.save(out);
    std::cout << "Done!\n";
}