#include "IntegralImage.h"

// clsII
// constructor
IntegralImage::IntegralImage(){
    // default values
    this->width = 0;  // integral image width
    this->height = 0;  // integral image height
    this->imgChans = 3;  // num. image feature channels (C)
    this->imgWidth = 0;  // image width (Iv)
    this->imgHeight = 0; // image height (Iu)
    this->cellSize = 1;  // cell size
};

// clsII
// constructor
IntegralImage::IntegralImage(int width, int height, int imgChans, int imgWidth, int imgHeight, int cellSize){
    // default values
    this->width = width;  // integral image width
    this->height = height;  // integral image height
    this->imgChans = imgChans;  // num. image feature channels (C)
    this->imgWidth = imgWidth;  // image width (Iv)
    this->imgHeight = imgHeight; // image height (Iu)
    this->cellSize = cellSize;  // cell size
};
// destructor
IntegralImage::~IntegralImage() = default;

// get integral image
cv::Mat IntegralImage::get_image() {
    return this->img;
};

// get integral image
py::array_t<unsigned char> IntegralImage::get_image_py() {
    auto np = new cvMatToNumpy();
    auto result = np->cvMatToNumpyInt(this->img);
    return result;
};
// get image size
int IntegralImage::get_image_width() {
    // inputs:
    // Iu: image size in u (y)
    // Iv: image size in v (x)
    auto Iv = this->imgWidth;
    return Iv;
};

// get image size
int IntegralImage::get_image_height() {
    // inputs:
    // Iu: image size in u (y)
    // Iv: image size in v (x)
    auto Iu = this->imgHeight;
    return Iu;
};
// compute image
void IntegralImage::compute_image(int cell_size){

    // inputs:
    // cellSize: cell size for image pyramid

    // set values
    this->cellSize = cell_size;  // cell size
    this->imgWidth = (int)ceil((float)this->width/this->cellSize);  // image width (Iv)
    this->imgHeight = (int)ceil((float)this->height/this->cellSize);  // image height (Iu)
    // variables
    int W = this->width;  // integral image width
    int H = this->height;  // integral image height
    int C = this->imgChans;  // num. image channels (C)
    int D = this->cellSize;  // cell size
    int Iv = this->imgWidth;  // image width
    int Iu = this->imgHeight;  // image height
    int t,b,l,r;  // top,bottom,left and right values
    double tl,bl,tr,br,val;  // top-left,bottom-left,top-right,bottom-right,value

    // create image
    this->img = cv::Mat(cvSize(Iv,Iu), CV_8UC(C), cv::Scalar::all(0));

    // pointer to image and integral image data
    double* IIPtr = this->II.ptr<double>(0);
    unsigned char *imgPtr = (unsigned char*)(this->img.data);
    // scanning
    for (int u=0; u<Iu-1; u++) {

        // local coordinates
        t = u*D;  // top
        b = t + D;  // bottom

        for (int v=0; v<Iv-1; v++) {

            // local coordinates
            l = v*D;  // left
            r = l + D;  // right

            // check
            if (t<0 || b>=H || l<0 || r>=W)
                std::cout << "Warning: incorrect corner coordinates" << std::endl;

            for (int c=0; c<C; c++){

                // integral image values
                tl = *(IIPtr + t*W*C + l*C + c);  // top-left corner
                bl = *(IIPtr + b*W*C + l*C + c);  // bottom-left corner
                tr = *(IIPtr + t*W*C + r*C + c);  // top-right corner
                br = *(IIPtr + b*W*C + r*C + c);  // bottom-right corner

                // check
                if (tl<0 || bl<0 || tr<0 || br<0)
                    std::cout << "Warning: incorrect corner values" << std::endl;

                // image value
                val = br + tl - tr - bl;
                val = (double)val/(D*D);

                // check (2 -> small error)
                if (val<0 || val>255+2)
                    std::cout << "Warning: incorrect image value" << std::endl;

                // image
                *(img.data + u*Iv*C + v*C + c) = (int) val;

            }
        }
    }
};
// compute integral image
void IntegralImage::integral_image(const cv::Mat& image){
    // inputs:
    // image: input image

    // set integral image size
    this->width = image.cols;  // II width
    this->height = image.rows;  // II height
    this->imgChans = image.channels();  // num. image channels (C)

    // variables
    int W = this->width;  // II width
    int H = this->height;  // II height
    int C = this->imgChans;  // num. image channels
    double imgVal,val;  // image pixel value, value

    // create integral image (II)
    this->II = cv::Mat(H, W, CV_64FC(C), cv::Scalar::all(0));

//  cv::waitKey(1000);
//  cv::imshow("ii1", image);
//  cv::waitKey(0);

    // pointers to image and integral image data
    double* IIPtr = II.ptr<double>(0);
    unsigned char *imgPtr = (unsigned char*)(image.data);

    // construction
    for (int u=0; u<H; u++){
        for (int v=0; v<W; v++){
            for (int c=0; c<C; c++){

                // image pixel value
                imgVal = *(imgPtr + u*W*C + v*C + c);

                // integral image values
                if (v>0){
                    if (u>0){
                        val = *(IIPtr + u*W*C + (v-1)*C + c) + *(IIPtr + (u-1)*W*C + v*C + c) - *(IIPtr + (u-1)*W*C + (v-1)*C + c);
                    }
                    else {
                        val = *(IIPtr + u*W*C + (v-1)*C + c);
                    }
                }
                else {
                    if (u>0){
                        val = *(IIPtr + (u-1)*W*C + v*C + c);
                    }
                    else {
                        val = 0;
                    }
                }

                // compute current pixel value in II
                *(IIPtr + u*W*C + v*C + c) = val + imgVal;

                // check
                if (val + imgVal > (u+1)*(v+1)*255)
                    std::cout << "Warning incorrect integral image value" << std::endl;

            }
        }
    }
}

// compute integral image
void IntegralImage::release_image(){
    // release image
    this->img.release();
}
