# include <iostream>
# include <string>
using namespace std;

class Image {
    private:
        int width;
        int height;
        int maxGreyVal;
        int** arrayOfPixels;
    public:
        //functions to be implemented
        void readImage (string);    // reads from file
        void saveImage (string);    // reads into file
        void changeBrightness (int);    //-255 to +255
        void flipImage (string);  // requires direction
        void negate ();
        void medianFilter ();
        void combineImages (Image);  // requires another image
        void applyFilter ();

};

int main()  {

    return 0;
}