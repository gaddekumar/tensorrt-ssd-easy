#include <iostream>
#include <algorithm>
#include "tensorRTplugin/tensorNet.h"
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include "util/cuda/cudaRGB.h"
#include "util/loadImage.h"

using namespace std;
using namespace nvinfer1;
using namespace nvcaffeparser1;
using namespace cv;

const char* model  = "/home/fares/Desktop/spring18/models/fresh/deploy.prototxt";
const char* weight = "/home/fares/Desktop/spring18/models/fresh/VGG_VOC0712_SSD_300x300_iter_120000.caffemodel";
const char* label  = "/home/fares/Desktop/spring18/models/defaultVOC/labelmap_voc.prototxt";

static const uint32_t BATCH_SIZE = 1;

const char* INPUT_BLOB_NAME = "data";
const char* OUTPUT1 = "mbox_conf_softmax";
const char* OUTPUT2 = "";
const char* OUTPUT3 = "";
const char* OUTPUT_BLOB_NAME = "detection_out";

/* *
 * @TODO: unifiedMemory is used here under -> ( cudaMallocManaged )
 * */
float* allocateMemory(DimsCHW dims, char* info)
{
    float* ptr;
    size_t size;
    std::cout << "Allocate memory: " << info << std::endl;
    size = BATCH_SIZE * dims.c() * dims.h() * dims.w();
    assert(!cudaMallocManaged( &ptr, size*sizeof(float)));
    return ptr;
}

cudaError_t cudaPreImageNetMean( float3* input, size_t inputWidth, size_t inputHeight, float* output, size_t outputWidth, size_t outputHeight, const float3& mean_value);

int main()
{
    std::cout << "Hello, World!" << std::endl;
    VideoCapture cap("/home/fares/Desktop/spring18/videos/outRAW2.avi");

    if(!cap.isOpened())
    {
        cout<<"There is no video in this location"<<endl;
        return -1;
    }

    TensorNet tensorNet;
    tensorNet.caffeToTRTModel( model, weight, std::vector<std::string>{ OUTPUT1 }, BATCH_SIZE);
    tensorNet.createInference();

    DimsCHW dimsData = tensorNet.getTensorDims(INPUT_BLOB_NAME);
    DimsCHW dimsOut  = tensorNet.getTensorDims(OUTPUT_BLOB_NAME);
    DimsCHW dims1    = tensorNet.getTensorDims(OUTPUT1);

    cout << "INPUT Tensor Shape is: C: "  <<dimsData.c()<< "  H: "<<dimsData.h()<<"  W:  "<<dimsData.w()<<endl;
    cout << "OUTPUT1 Tensor Shape is: C: "<<dims1.c()<<"  H: "<<dims1.h()<<"  W: "<<dims1.w()<<endl;

    float* data    = allocateMemory( dimsData , (char*)"input blob");
    float* output  = allocateMemory( dimsOut  , (char*)"output blob");
    float* output1 = allocateMemory( dims1    , (char*)"output1");

    int height = 300;
    int width  = 300;

    Mat frame;
    Mat frame_float;

    frame = cv::imread("/home/fares/Desktop/spring18/inference/testImage.jpg", IMREAD_COLOR);
    resize(frame, frame, Size(300,300));

    /* *
     * @TODO: Replace imgCPU -> h_img ||| imgGPu -> d_img
     * */

    void* imgCPU;
    void* imgCUDA;

    for (int i=0; i<1; i++ )
    {
        const size_t size = width * height * sizeof(float3);

        if( CUDA_FAILED( cudaMalloc( &imgCUDA, size)) )
        {
            cout <<"Cuda Memory allocation error occured."<<endl;
            return false;
        }
        if( !loadImageBGR( frame , (float3**)&imgCPU, (float3**)&imgCUDA, &height, &width))
        {
            printf("failed to load image '%s'\n", "Image");
            return 0;
        }

        if( CUDA_FAILED(cudaPreImageNetMean( (float3*)imgCUDA, width, height, data, dimsData.w(), dimsData.h(), make_float3(123.0f,117.0f,104.0f))))
        {
            cout <<"Cuda pre image net mean failed. " <<endl;
            return 0;
        }

        void* buffers[] = { imgCUDA, output1};

        tensorNet.imageInference( buffers, 2, BATCH_SIZE);
        vector<vector<float> > detections;

        for (int k=0;k<10;k++)
        {
            if ((k)%7==0){
                cout << endl;
            }
            cout<<(output1[k])<<" , ";
        }

        imshow("Objects Detected", frame);
        waitKey(1);
    }

    CUDA(cudaFreeHost(imgCPU));
    tensorNet.destroy();

    return 0;

}
