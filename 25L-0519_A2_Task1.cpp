    # include <iostream>
    # include <string>
    # include <fstream>
    using namespace std;

    class Image {
        private:
            int width;
            int height;
            int maxGreyVal;
            int** arrayOfPixels;
            string magic;
        public:
            // default constructor --> since data is to be read
            // from file and not gonna be input
            Image ();
            // destructor
            ~Image ();
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

    // constructor
    Image :: Image ()   {
        width = 0;
        height = 0;
        maxGreyVal = 255;
        arrayOfPixels = nullptr;
    }

    // destructor
    Image :: ~Image ()  {
        for (int i = 0; i < height; i++)    {
            delete[] *(arrayOfPixels + i);
        }
        delete[] arrayOfPixels;
    }
    //Save Image Funcion
    void Image :: readImage (string sample)   {
        ifstream fin (sample);
        if (!fin) {
            cout << "File not found" << endl;
            return;
        }
        //string magic; // for P2
        //int width, height, maxGreyVal;

        fin >> magic;
        fin >> width;
        fin >> height;
        fin >> maxGreyVal;

        arrayOfPixels = new int* [height];

        // input pixel data
        for (int i = 0; i < height; i++)    {
            *(arrayOfPixels + i) = new int [width];
            for (int j = 0; j < width; j++)     {
                fin >> *(*(arrayOfPixels + i) + j);
            }
        }
        
        return;
    }

    int main()  {

        return 0;
    }