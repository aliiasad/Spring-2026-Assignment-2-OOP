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

    // Read Image Function
    void Image :: saveImage (string sample)  {
        ofstream fout (sample);
        if (!fout) {
            cout << "File not found" << endl;
            return;
        }

        fout << magic << endl;
        fout << width << " " << height << endl;
        fout << maxGreyVal << endl;

        for (int i = 0; i < height; i++)    {
            for (int j = 0; j < width; j++) {
                fout << *(*(arrayOfPixels + i) + j) << " ";
            }
            fout << endl;
        }

        return;
    }

    // Brightness Function
    void Image :: changeBrightness(int pixelChange) {

        for (int i = 0; i < height; i++)    {
            for (int j = 0; j < width; j++) {
                if ((*(*(arrayOfPixels + i) + j) + pixelChange) > 255)  *(*(arrayOfPixels + i) + j) = 255;
                else if ((*(*(arrayOfPixels + i) + j) + pixelChange) < 0)  *(*(arrayOfPixels + i) + j) = 0;
                else *(*(arrayOfPixels + i) + j) += pixelChange;
            }
        }

        return;
    }

    // Flip Image Function
    void Image :: flipImage (string direction)  {

        if (direction == "horizontal" || direction == "Horizontal") {
            // for horizontal, fix rows (height) and reverse cols (width)
            // untill middle col (width / 2) is reached
            for (int i = 0; i < height; i++)    {
                for (int j = 0; j < width / 2; j++) {
                    int temp = *(*(arrayOfPixels + i) + j);
                    *(*(arrayOfPixels + i) + j) = *(*(arrayOfPixels + i) + (width - 1 - j));
                    *(*(arrayOfPixels + i) + (width - 1 - j)) = temp;
                }
            }
        }
        else if (direction == "vertical" || direction == "Vertical")    {
            // for horizontal, fix cols (width) and reverse rows (height)
            // untill middle row (height / 2) is reached
            for (int i = 0; i < height / 2; i++)    {
                for (int j = 0; j < width; j++) {
                    int temp = *(*(arrayOfPixels + i) + j);
                    *(*(arrayOfPixels + i) + j) = *(*(arrayOfPixels + (height - 1 -i)) + j);
                    *(*(arrayOfPixels + (height - 1 - i)) + j) = temp;
                }
            }
        }
        else cout << "Invalid Operation Called. Try first CAPS or all SMALL" << endl;

        return;
    }

    // Negate Function
    void Image :: negate()  {

        // 255 - current pixel = new pixel
        for (int i = 0; i < height; i++)    {
            for (int j = 0; j < width; j++) {
                *(*(arrayOfPixels + i) + j) = 255 - *(*(arrayOfPixels + i) + j);
            }
        }

        return;
    }

    // Combine Images Function
    void Image :: combineImages (Image other)  {
        if (height != other.height) {
            cout << "Heights don't match!" << endl;
            return;
        }
        // calculate new width (here width is this->width)
        int newWidth = width + other.width;

        // new array for larger image
        int** newArray = new int* [height];
        for (int i = 0; i < height; i++)    {
            *(newArray + i) = new int [newWidth];
        }

        // copy first image
        for (int i = 0; i < height; i++)    {
            for (int j = 0; j < width; j++) {
                *(*(newArray + i) + j) = *(*(arrayOfPixels + i) + j);
            }
        }

        // copy second image
        for (int i = 0; i < height; i++)    {
            for (int j = 0; j < other.width; j++)   {
                *(*(newArray + i) + (width + j)) = *(*(other.arrayOfPixels + i) + j);
            }
        }

        // delete old array
        for (int i = 0; i < height; i++)    {
            delete[] *(arrayOfPixels + i);
        }
        delete[] arrayOfPixels;

        // point it to new array
        arrayOfPixels = newArray;
        width = newWidth;

        return;
    }

int main()  {
    Image img1;
    Image img2;
    img1.readImage("sample.pgm");
    img2.readImage("sample2.pgm");
    img1.combineImages(img2);
    img1.saveImage("output.pgm");
    return 0;
}