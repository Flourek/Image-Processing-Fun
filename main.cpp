#include "iostream"
#include "fstream"
#include "vector"

using namespace std;

class Pixel {
public:
    uint8_t R, G, B;
    Pixel() { R = G = B = 0; }

    void setColor(uint8_t x) {
        R = G = B = x;
    }

    float lux() const {
        return (R * 0.3f) + (G * 0.59f) + (B * 0.11f);
    }

    friend ostream& operator<<(ostream& os, const Pixel& p){
        return os << p.R << p.G << p.B;
    }

};


int main(){

    ifstream in;
    ofstream out;
    in.open("testen/e.ppm", fstream::in | fstream::binary);
    out.open("testen/d.ppm", fstream::out | fstream::binary);

    int width;
    int height;
    int rgb_max;
    string type;

    in >> type >> width >> height >> rgb_max;
    out << type << '\n' << width << ' ' << height << '\n' << rgb_max << '\n';
    in.seekg(1, ios_base::cur);

    vector<vector<Pixel>> pixels;



    // Load shit
    for (int y = 0; y < height; ++y) {
        vector<Pixel> row;
        for (int x = 0; x < width; ++x) {
            Pixel p;
            p.R = in.get();
            p.G = in.get();
            p.B = in.get();

            row.push_back(p);
        }
        pixels.push_back(row);
    }

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            Pixel& p = pixels[y][x];

            int e = x % 50;
            int d = y % 50;


            if(abs(x - width) % 10 == abs(y + height) % 10)
                p.setColor(255);

            out << p;

        }
    }


}