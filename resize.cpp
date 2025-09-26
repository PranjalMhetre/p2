#include <iostream>
#include <cassert>
#include "Image.hpp"
#include <fstream>
#include "processing.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    assert(argc == 4 || argc == 5);

    string file_name = argv[1];
    ifstream fin(file_name);
    if (!fin.is_open()) {
        cout << "Error opening file: " << endl;
        return 1;
    }
    Image img;
    Image_init(&img, fin);
    int img_width = Image_width(&img);
    int img_height = Image_height(&img);

    string output_name = argv[2];

    int output_width = stoi(argv[3]);
    int output_height;
    if (argc == 5) {
        output_height = stoi(argv[4]);
    } else {
        output_height = img_height;
    }
    // check if the literal strings were supposed to be replaced with variables
    if (output_width < 0 || output_width > img_width || output_height < 0 
        || output_height > img_height) {
        cout << "Usage: resize.exe " << file_name << output_name 
        << output_width << output_height << "\n"
        << output_width << " and " << output_height 
        << " must be less than or equal to original" << endl;
        return 1;
    }

    seam_carve(&img, output_width, output_height);
    
    ofstream fout(output_name);
    if (!fout.is_open()) {
        cout << "Error opening file: " << endl;
        return 1;
    }
    Image_print(&img, fout);

    

}