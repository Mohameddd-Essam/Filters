// File: CS112_A3_Part2B_S25_20231147_20231152_20231016.cpp
// Purpose: This is a Baby Photoshop Program that can apply simple filters
//Section: S25
//Name: Mohamed Essam Abdelhamid
// ID: 20231147 (Took Black and White , Crop, Brightness, Frame, Resize filters & wrote
//the comments)
//Email:mohamedesam157853@gmail.com
//Name: Mahmoud Ibrahim Mahmoud
// ID: 20231152 (Took Greyscale, Blur, Flip, sun, Purple filters)
//Email:askr3556@gmail.com
//Name: Ahmed Yasser EL-Sayed
// ID: 20231016 (Took Invert colors, Rotate, Merge, Detect Image Edges, Infrared filters
//& wrote the menu)
// Email: ahmedyassera7md@gmail.com
#include "Image_Class.h"
using namespace std;
void Again() ;
//Greyscale filter
void Grayscale(Image& image) {
 for (int i = 0; i < image.width; ++i) {
 for (int j = 0; j < image.height; ++j) {
 unsigned int average = 0;
 for (int k = 0; k < 3; ++k) {
 average += image(i, j, k);
 }
 average /= 3;
 for (int k = 0; k < 3; ++k) {
 image(i, j, k) = average;
 }
 }
 }
 image.saveImage("Filtered Image.png");
}
//Black and white filter
void BlackAndWhite(Image& image) {
 for (int i = 0; i < image.width; ++i) {
 for (int j = 0; j < image.height; ++j) {
 unsigned int average = 0;
 for (int k = 0; k < 3; ++k) {
 average += image(i, j, k);
 }
 average /= 3;
 for (int k = 0; k < 3; ++k) {
 if (average > 127.5) {
 image(i, j, k) = 255;
 } else {
 image(i, j, k) = 0;
 }
 }
 }
 }
 image.saveImage("Filtered Image.png");
}
//Invert colors filter
void InvertColors(Image& image) {
 for (int i = 0; i < image.width; ++i) {
 for (int j = 0; j < image.height; ++j) {
 for (int k = 0; k < 3; ++k) {
 unsigned int color = image(i, j, k);
 image(i, j, k) = 255 - color;
 }
 }
 }
 image.saveImage("Filtered Image.png");
}
//Merge filter
void mergeTolarger(Image& larger, Image& smaller){
 Image enlargedImage(larger.width, larger.height);
 float xRatio = static_cast<float>(smaller.width) / larger.width;
 float yRatio = static_cast<float>(smaller.height) / larger.height;
 for (int y = 0; y < larger.height; ++y) {
 for (int x = 0; x < larger.width; ++x) {
 int srcX = static_cast<int>(x * xRatio);
 int srcY = static_cast<int>(y * yRatio);
 for (int c = 0; c < larger.channels; ++c) {
 enlargedImage.setPixel(x, y, c, smaller.getPixel(srcX, srcY, c));
 }
 }
 }
 Image mergedImage(larger.width, larger.height);
 for (int i = 0; i < larger.width; i++) {
 for (int j = 0; j < larger.height; j++) {
 for (int c = 0; c < larger.channels; ++c) {
 unsigned int average = (larger.getPixel(i, j, c) +
enlargedImage.getPixel(i, j, c)) / 2;
 mergedImage.setPixel(i, j, c, average);
 }
 }
 }
 mergedImage.saveImage("Filtered Image.png");
}
void mergeToSmaller(Image& smaller, Image& larger) {
 Image shrinked(larger.width, larger.height);
 float xRatio = static_cast<float>(larger.width) / smaller.width;
 float yRatio = static_cast<float>(larger.height) / smaller.height;
 for (int y = 0; y < larger.height; ++y) {
 for (int x = 0; x < larger.width; ++x) {
 int srcX = static_cast<int>(x / xRatio);
 int srcY = static_cast<int>(y / yRatio);
 for (int c = 0; c < smaller.channels; ++c) {
 shrinked.setPixel(x, y, c, smaller.getPixel(srcX, srcY, c));
 }
 }
 }
 Image mergedImage(larger.width, larger.height);
 for (int i = 0; i < larger.width; i++) {
 for (int j = 0; j < larger.height; j++) {
 for (int c = 0; c < smaller.channels; ++c) {
 unsigned int average = (shrinked.getPixel(i, j, c) + larger.getPixel(i,
j, c)) / 2;
 mergedImage.setPixel(i, j, c, average);
 }
 }
 }
 mergedImage.saveImage("Filtered Image.png");
}
void mergeToSmallestDimensions(Image& image1, Image& image2) {
 int minWidth = min(image1.width, image2.width);
 int minHeight = min(image1.height, image2.height);
 Image merged(minWidth, minHeight);
 float xRatio1 = static_cast<float>(image1.width) / minWidth;
 float yRatio1 = static_cast<float>(image1.height) / minHeight;
 for (int y = 0; y < minHeight; ++y) {
 for (int x = 0; x < minWidth; ++x) {
 int srcX = static_cast<int>(x * xRatio1);
 int srcY = static_cast<int>(y * yRatio1);
 for (int c = 0; c < image1.channels; ++c) {
 merged.setPixel(x, y, c, image1.getPixel(srcX, srcY, c));
 }
 }
 }
 float xRatio2 = static_cast<float>(image2.width) / minWidth;
 float yRatio2 = static_cast<float>(image2.height) / minHeight;
 for (int y = 0; y < minHeight; ++y) {
 for (int x = 0; x < minWidth; ++x) {
 int srcX = static_cast<int>(x * xRatio2);
 int srcY = static_cast<int>(y * yRatio2);
 for (int c = 0; c < image2.channels; ++c) {
 merged.setPixel(x, y, c, (merged.getPixel(x, y, c) +
image2.getPixel(srcX, srcY, c)) / 2);
 }
 }
 }
 // Save the merged image
 merged.saveImage("Filtered Image.png");
}
void mergeToLargestDimensions(Image& image1, Image& image2) {
 // Determine the largest dimensions
 int maxWidth = std::max(image1.width, image2.width);
 int maxHeight = std::max(image1.height, image2.height);
 Image merged(maxWidth, maxHeight);
 float xRatio1 = static_cast<float>(image1.width) / maxWidth;
 float yRatio1 = static_cast<float>(image1.height) / maxHeight;
 for (int y = 0; y < maxHeight; ++y) {
 for (int x = 0; x < maxWidth; ++x) {
 int srcX = static_cast<int>(x * xRatio1);
 int srcY = static_cast<int>(y * yRatio1);
 for (int c = 0; c < image1.channels; ++c) {
 merged.setPixel(x, y, c, image1.getPixel(srcX, srcY, c));
 }
 }
 }
 float xRatio2 = static_cast<float>(image2.width) / maxWidth;
 float yRatio2 = static_cast<float>(image2.height) / maxHeight;
 for (int y = 0; y < maxHeight; ++y) {
 for (int x = 0; x < maxWidth; ++x) {
 int srcX = static_cast<int>(x * xRatio2);
 int srcY = static_cast<int>(y * yRatio2);
 for (int c = 0; c < image2.channels; ++c) {
 merged.setPixel(x, y, c, (merged.getPixel(x, y, c) +
image2.getPixel(srcX, srcY, c)) / 2);
 }
 }
 }
 merged.saveImage("Filtered Image.png");
}
void Merge (Image& image){
 string secimage_name;
 cout<<"Please enter the second image: ";
 getline(cin,secimage_name);
 Image secimage;
 secimage.loadNewImage(secimage_name);
 cout<<"1. Enlarge the smaller image to the larger image then merge\n";
 cout<<"2. Shrink the larger image to the smaller image then merge\n";
 cout<<"3. Take the smallest dimensions from both then merge\n";
 cout<<"4. Take the biggest dimensions from both then merge\n";
 int merge_choice;
 cin>>merge_choice;
 int x = image.width*image.height;
 int y = secimage.width*secimage.height;
 if (merge_choice==1){
 if(x>y){
 mergeTolarger(image,secimage);
 }
 else if(y>x){
 mergeTolarger(secimage,image);
 }
 else{
 mergeTolarger(secimage,image);
 }
 }
 else if (merge_choice==2){
 if(x>y){
 mergeToSmaller(image,secimage);
 }
 else if(y>x){
 mergeToSmaller(secimage,image);
 }
 else{
 mergeToSmaller(secimage,image);
 }
 }
 else if (merge_choice==3){
 mergeToSmallestDimensions(image,secimage);
 }
 else if (merge_choice==4){
 mergeToLargestDimensions(image,secimage);
 }
 else{
 cin.ignore();
 Merge(image);
 }
}
//Flip filter
void Flip(Image& image) {
 int flip_choice;
 cout << "1. Horizontal Flip" << endl;
 cout << "2. Vertical Flip" << endl;
 cin >> flip_choice;
 if (flip_choice == 1){
 for (int i = 0; i < image.height; ++i) {
 for (int j = 0; j < image.width / 2; ++j) {
 for (int c = 0; c < 3; ++c) {
 unsigned char temp = image.getPixel(j, i, c);
image.setPixel(j, i, c, image.getPixel(image.width - j - 1, i, c));
 image.setPixel(image.width - j - 1, i, c, temp);
 }
 }
 }
 }
 else if (flip_choice == 2){
 for (int x = 0; x < image.width; ++x) {
 for (int y = 0; y < image.height / 2; ++y) {
 for (int c = 0; c < image.channels; ++c) {
 unsigned char temp = image.getPixel(x, y, c);
image.setPixel(x, y, c, image.getPixel(x, image.height - y - 1, c));
 image.setPixel(x, image.height - y - 1, c, temp);
 }
 }
 }
 }
 else{
 cout <<"Please try again: \n";
 Flip(image);
 }
 image.saveImage("Filtered Image.png");
}
//Rotate
void Rotate(Image&image){
 cout<<"Do you want to rotate it by (90, 180, 270): \n";
 int degree;
 cin >>degree;
 if (degree==270) {
 Image nwimage(image.height, image.width);
 for (int i = 0; i < nwimage.width; i++) {
 for (int j = 0; j < nwimage.height; j++) {
 for (int k = 0; k < 3; k++) {
 nwimage(i, j, k) = image(j, i, k);
 }
 }
 }
 nwimage.saveImage("Filtered Image.png");
 }
 else if (degree==180) {
 Image nwimage(image.width, image.height);
 for (int i = nwimage.width - 1; i >= 0; i--) {
 for (int j = nwimage.height - 1; j >= 0; j--) {
 for (int k = 0; k < 3; k++) {
 nwimage(nwimage.width - 1 - i, nwimage.height - 1 - j, k) = image(i,
j, k);
 }
 }
 }
 nwimage.saveImage("Filtered Image.png");
 }
 else if (degree==90) {
 Image nwimage(image.height, image.width);
 for (int i = nwimage.width - 1; i >= 0; i--) {
 for (int j = nwimage.height - 1; j >= 0; j--) {
 for (int k = 0; k < 3; k++) {
 nwimage(nwimage.width - 1 - i, nwimage.height - 1 - j, k) = image(j,
i, k);
 }
 }
 }
 nwimage.saveImage("Filtered Image.png");
 }
 else{
 Rotate(image);
 }
}
//Brightness
void Contrast(Image& image){
 cout<<"Please enter the degree of brightness (Preferred from 0 to 2 )";
 float contrast;
 cin>>contrast;
 for (int i = 0; i < image.width; ++i) {
 for (int j = 0; j < image.height; ++j) {
 for (int k = 0; k < 3; ++k) {
 image(i, j, k) = min(255, static_cast<int>(image(i, j, k) * contrast));
 }
 }
 }
 image.saveImage("Filtered Image.png");
}
//Crop
void Crop(Image& image) {
 int width2,height2;
 cout<<"Enter the width and height you want to cut from\n";
 cin>>width2>>height2;
 if (width2 > image.width || height2 > image.height) {
 cout << "Error: Selected dimensions larger than image size. Please try again."
<<endl;
 Crop(image);
 }
 int width, height;
 cout << "Enter dimensions:\n";
 cin >> width >> height;
 if (width > image.width || height > image.height) {
 cout << "Error: Selected dimensions larger than image size. Please try again."
<<endl;
 Crop(image);
 }
 Image nwimage(width, height);
 for (int i = 0; i < nwimage.width; i++) {
 for (int j = 0; j < nwimage.height; j++) {
 for (int k = 0; k < 3; k++) {
 nwimage(i, j, k) = image(i+width2, j+height2, k);
 }
 }
 }
 nwimage.saveImage("Filtered Image.png");
}
//Add frame
void Frame(Image& image) {
 string m, h, y;
 cout << "choose number of frame......1-lined....2-doubled\n";
 cin >> h;
 cout << "choose the number of color of frame....1-blue.....2-orange.....3-
yellow....4-cyan\n";
 cin >> y;
 if (h == "1" && y == "1") {
 for (int i = 0; i < image.width; i++) {
 for (int j = 0; j < 10; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 0;
 image(i, j, 1) = 42;
 image(i, j, 2) = 255;
 }
 }
 }
 for (int i = 0; i < image.width; i++) {
 for (int j = image.height - 10; j < image.height; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 0;
 image(i, j, 1) = 42;
 image(i, j, 2) = 255;
 }
 }
 }
 for (int i = 0; i < 10; i++) {
 for (int j = 0; j < image.height; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 0;
 image(i, j, 1) = 42;
 image(i, j, 2) = 255;
 }
 }
 }
 for (int i = image.width - 10; i < image.width; i++) {
 for (int j = 0; j < image.height; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 0;
 image(i, j, 1) = 42;
 image(i, j, 2) = 255;
 }
 }
 }
 } else if (h == "2" && y == "1") {
 for (int i = 0; i < image.width; i++) {
 for (int j = 0; j < 10; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 0;
 image(i, j, 1) = 42;
 image(i, j, 2) = 255;
 }
 }
 }
 for (int i = 0; i < image.width; i++) {
 for (int j = image.height - 10; j < image.height; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 0;
 image(i, j, 1) = 42;
 image(i, j, 2) = 255;
 }
 }
 }
 for (int i = 0; i < 10; i++) {
 for (int j = 0; j < image.height; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 0;
 image(i, j, 1) = 42;
 image(i, j, 2) = 255;
 }
 }
 }
 for (int i = image.width - 10; i < image.width; i++) {
 for (int j = 0; j < image.height; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 0;
 image(i, j, 1) = 42;
 image(i, j, 2) = 255;
 }
 }
 }
 for (int i = 10; i < image.width - 10; i++) {
 for (int j = 10; j < 13; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 250;
 image(i, j, 1) = 250;
 image(i, j, 2) = 250;
 }
 }
 }
 for (int i = 10; i < image.width - 10; i++) {
 for (int j = image.height - 13; j < image.height - 10; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 250;
 image(i, j, 1) = 250;
 image(i, j, 2) = 250;
 }
 }
 }
 for (int i = 10; i < 13; i++) {
 for (int j = 10; j < image.height - 10; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 250;
 image(i, j, 1) = 250;
 image(i, j, 2) = 250;
 }
 }
 }
 for (int i = image.width - 13; i < image.width - 10; i++) {
 for (int j = 10; j < image.height - 10; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 250;
 image(i, j, 1) = 250;
 image(i, j, 2) = 250;
 }
 }
 }
 for (int i = 14; i < image.width - 14; i++) {
 for (int j = 14; j < 15; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 250;
 image(i, j, 1) = 250;
 image(i, j, 2) = 250;
 }
 }
 }
 for (int i = 12; i < image.width - 12; i++) {
 for (int j = image.height - 17; j < image.height - 16; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 250;
 image(i, j, 1) = 250;
 image(i, j, 2) = 250;
 }
 }
 }
 for (int i = 16; i < 17; i++) {
 for (int j = 13; j < image.height - 13; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 250;
 image(i, j, 1) = 250;
 image(i, j, 2) = 250;
 }
 }
 }
 for (int i = image.width - 17; i < image.width - 16; i++) {
 for (int j = 15; j < image.height - 15; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 250;
 image(i, j, 1) = 250;
 image(i, j, 2) = 250;
 }
 }
 }
 } else if (h == "1" && y == "2") {
 for (int i = 0; i < image.width; i++) {
 for (int j = 0; j < 10; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 255;
 image(i, j, 1) = 165;
 image(i, j, 2) = 0;
 }
 }
 }
 for (int i = 0; i < image.width; i++) {
 for (int j = image.height - 10; j < image.height; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 255;
 image(i, j, 1) = 165;
 image(i, j, 2) = 0;
 }
 }
 }
 for (int i = 0; i < 10; i++) {
 for (int j = 0; j < image.height; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 255;
 image(i, j, 1) = 165;
 image(i, j, 2) = 0;
 }
 }
 }
 for (int i = image.width - 10; i < image.width; i++) {
 for (int j = 0; j < image.height; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 255;
 image(i, j, 1) = 165;
 image(i, j, 2) = 0;
 }
 }
 }
 } else if (h == "1" && y == "3") {
 for (int i = 0; i < image.width; i++) {
 for (int j = 0; j < 10; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 255;
 image(i, j, 1) = 255;
 image(i, j, 2) = 0;
 }
 }
 }
 for (int i = 0; i < image.width; i++) {
 for (int j = image.height - 10; j < image.height; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 255;
 image(i, j, 1) = 255;
 image(i, j, 2) = 0;
 }
 }
 }
 for (int i = 0; i < 10; i++) {
 for (int j = 0; j < image.height; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 255;
 image(i, j, 1) = 255;
 image(i, j, 2) = 0;
 }
 }
 }
 for (int i = image.width - 10; i < image.width; i++) {
 for (int j = 0; j < image.height; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 255;
 image(i, j, 1) = 255;
 image(i, j, 2) = 0;
 }
 }
 }
 } else if (h == "1" && y == "4") {
 for (int i = 0; i < image.width; i++) {
 for (int j = 0; j < 10; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 0;
 image(i, j, 1) = 255;
 image(i, j, 2) = 255;
 }
 }
 }
 for (int i = 0; i < image.width; i++) {
 for (int j = image.height - 10; j < image.height; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 0;
 image(i, j, 1) = 255;
 image(i, j, 2) = 255;
 }
 }
 }
 for (int i = 0; i < 10; i++) {
 for (int j = 0; j < image.height; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 0;
 image(i, j, 1) = 255;
 image(i, j, 2) = 255;
 }
 }
 }
 for (int i = image.width - 10; i < image.width; i++) {
 for (int j = 0; j < image.height; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 0;
 image(i, j, 1) = 255;
 image(i, j, 2) = 255;
 }
 }
 }
 } else if (h == "2" && y == "2") {
 for (int i = 0; i < image.width; i++) {
 for (int j = 0; j < 10; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 255;
 image(i, j, 1) = 165;
 image(i, j, 2) = 0;
 }
 }
 }
 for (int i = 0; i < image.width; i++) {
 for (int j = image.height - 10; j < image.height; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 255;
 image(i, j, 1) = 165;
 image(i, j, 2) = 0;
 }
 }
 }
 for (int i = 0; i < 10; i++) {
 for (int j = 0; j < image.height; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 255;
 image(i, j, 1) = 165;
 image(i, j, 2) = 0;
 }
 }
 }
 for (int i = image.width - 10; i < image.width; i++) {
 for (int j = 0; j < image.height; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 255;
 image(i, j, 1) = 165;
 image(i, j, 2) = 0;
 }
 }
 }
 for (int i = 10; i < image.width - 10; i++) {
 for (int j = 10; j < 13; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 250;
 image(i, j, 1) = 250;
 image(i, j, 2) = 250;
 }
 }
 }
 for (int i = 10; i < image.width - 10; i++) {
 for (int j = image.height - 13; j < image.height - 10; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 250;
 image(i, j, 1) = 250;
 image(i, j, 2) = 250;
 }
 }
 }
 for (int i = 10; i < 13; i++) {
 for (int j = 10; j < image.height - 10; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 250;
 image(i, j, 1) = 250;
 image(i, j, 2) = 250;
 }
 }
 }
 for (int i = image.width - 13; i < image.width - 10; i++) {
 for (int j = 10; j < image.height - 10; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 250;
 image(i, j, 1) = 250;
 image(i, j, 2) = 250;
 }
 }
 }
 for (int i = 14; i < image.width - 14; i++) {
 for (int j = 14; j < 15; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 250;
 image(i, j, 1) = 250;
 image(i, j, 2) = 250;
 }
 }
 }
 for (int i = 12; i < image.width - 12; i++) {
 for (int j = image.height - 17; j < image.height - 16; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 250;
 image(i, j, 1) = 250;
 image(i, j, 2) = 250;
 }
 }
 }
 for (int i = 16; i < 17; i++) {
 for (int j = 13; j < image.height - 13; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 250;
 image(i, j, 1) = 250;
 image(i, j, 2) = 250;
 }
 }
 }
 for (int i = image.width - 17; i < image.width - 16; i++) {
 for (int j = 15; j < image.height - 15; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 250;
 image(i, j, 1) = 250;
 image(i, j, 2) = 250;
 }
 }
 }
 } else if (h == "2" && y == "3") {
 for (int i = 0; i < image.width; i++) {
 for (int j = 0; j < 10; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 255;
 image(i, j, 1) = 255;
 image(i, j, 2) = 0;
 }
 }
 }
 for (int i = 0; i < image.width; i++) {
 for (int j = image.height - 10; j < image.height; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 255;
 image(i, j, 1) = 255;
 image(i, j, 2) = 0;
 }
 }
 }
 for (int i = 0; i < 10; i++) {
 for (int j = 0; j < image.height; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 255;
 image(i, j, 1) = 255;
 image(i, j, 2) = 0;
 }
 }
 }
 for (int i = image.width - 10; i < image.width; i++) {
 for (int j = 0; j < image.height; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 255;
 image(i, j, 1) = 255;
 image(i, j, 2) = 0;
 }
 }
 }
 for (int i = 10; i < image.width - 10; i++) {
 for (int j = 10; j < 13; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 250;
 image(i, j, 1) = 250;
 image(i, j, 2) = 250;
 }
 }
 }
 for (int i = 10; i < image.width - 10; i++) {
 for (int j = image.height - 13; j < image.height - 10; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 250;
 image(i, j, 1) = 250;
 image(i, j, 2) = 250;
 }
 }
 }
 for (int i = 10; i < 13; i++) {
 for (int j = 10; j < image.height - 10; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 250;
 image(i, j, 1) = 250;
 image(i, j, 2) = 250;
 }
 }
 }
 for (int i = image.width - 13; i < image.width - 10; i++) {
 for (int j = 10; j < image.height - 10; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 250;
 image(i, j, 1) = 250;
 image(i, j, 2) = 250;
 }
 }
 }
 for (int i = 14; i < image.width - 14; i++) {
 for (int j = 14; j < 15; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 250;
 image(i, j, 1) = 250;
 image(i, j, 2) = 250;
 }
 }
 }
 for (int i = 12; i < image.width - 12; i++) {
 for (int j = image.height - 17; j < image.height - 16; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 250;
 image(i, j, 1) = 250;
 image(i, j, 2) = 250;
 }
 }
 }
 for (int i = 16; i < 17; i++) {
 for (int j = 13; j < image.height - 13; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 250;
 image(i, j, 1) = 250;
 image(i, j, 2) = 250;
 }
 }
 }
 for (int i = image.width - 17; i < image.width - 16; i++) {
 for (int j = 15; j < image.height - 15; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 250;
 image(i, j, 1) = 250;
 image(i, j, 2) = 250;
 }
 }
 }
 } else if (h == "2" && y == "4") {
 for (int i = 0; i < image.width; i++) {
 for (int j = 0; j < 10; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 0;
 image(i, j, 1) = 255;
 image(i, j, 2) = 255;
 }
 }
 }
 for (int i = 0; i < image.width; i++) {
 for (int j = image.height - 10; j < image.height; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 0;
 image(i, j, 1) = 255;
 image(i, j, 2) = 255;
 }
 }
 }
 for (int i = 0; i < 10; i++) {
 for (int j = 0; j < image.height; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 0;
 image(i, j, 1) = 255;
 image(i, j, 2) = 255;
 }
 }
 }
 for (int i = image.width - 10; i < image.width; i++) {
 for (int j = 0; j < image.height; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 0;
 image(i, j, 1) = 255;
 image(i, j, 2) = 255;
 }
 }
 }
 for (int i = 10; i < image.width - 10; i++) {
 for (int j = 10; j < 13; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 250;
 image(i, j, 1) = 250;
 image(i, j, 2) = 250;
 }
 }
 }
 for (int i = 10; i < image.width - 10; i++) {
 for (int j = image.height - 13; j < image.height - 10; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 250;
 image(i, j, 1) = 250;
 image(i, j, 2) = 250;
 }
 }
 }
 for (int i = 10; i < 13; i++) {
 for (int j = 10; j < image.height - 10; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 250;
 image(i, j, 1) = 250;
 image(i, j, 2) = 250;
 }
 }
 }
 for (int i = image.width - 13; i < image.width - 10; i++) {
 for (int j = 10; j < image.height - 10; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 250;
 image(i, j, 1) = 250;
 image(i, j, 2) = 250;
 }
 }
 }
 for (int i = 14; i < image.width - 14; i++) {
 for (int j = 14; j < 15; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 250;
 image(i, j, 1) = 250;
 image(i, j, 2) = 250;
 }
 }
 }
 for (int i = 12; i < image.width - 12; i++) {
 for (int j = image.height - 17; j < image.height - 16; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 250;
 image(i, j, 1) = 250;
 image(i, j, 2) = 250;
 }
 }
 }
 for (int i = 16; i < 17; i++) {
 for (int j = 13; j < image.height - 13; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 250;
 image(i, j, 1) = 250;
 image(i, j, 2) = 250;
 }
 }
 }
 for (int i = image.width - 17; i < image.width - 16; i++) {
 for (int j = 15; j < image.height - 15; j++) {
 for (int k = 0; k < 3; k++) {
 image(i, j, 0) = 250;
 image(i, j, 1) = 250;
 image(i, j, 2) = 250;
 }
 }
 }
 } else {
 cout << "Error,please try again\n";
 Frame(image);
 }
 image.saveImage("Filtered Image.png");
}
// --------------------------------------------------------------------------------------
--------------------------------
// Detect Edges
void DetectEdges(Image& image){
 for (int i = 0; i < image.width; ++i) {
 for (int j = 0; j < image.height; ++j) {
 unsigned int average = 0;
 for (int k = 0; k < 3; ++k) {
 average += image.getPixel(i, j, k);
 }
 average /= 3;
 for (int k = 0; k < 3; ++k) {
 if (average > 127.5) {
 image.setPixel(i, j, k, 255); // White
 } else {
 image.setPixel(i, j, k, 0); // Black
 }
 }
 }
 }
// Compare each pixel with the neighbour pixel
 for (int j = 0; j < image.height - 1; ++j) {
 for (int i = 0; i < image.width - 1; ++i) {
 for (int k = 0; k < 3; ++k) {
 unsigned int currentPixel = image.getPixel(i, j, k);
 unsigned int nextPixel = image.getPixel(i + 1, j + 1, k);
 if (currentPixel != nextPixel) {
 image.setPixel(i, j, k, 0); // Black
 } else {
 image.setPixel(i, j, k, 255); // White
 }
 }
 }
 }
 image.saveImage("Filtered Image.png");
}
//---------------------------------------------------------------------------------------
-------------------------------
// Resize
void Resize(Image&image){
 cout<<"Please enter the required width";
 float width;
 cin>>width;
 cout<<"Please enter the required height";
 float height;
 cin>>height;
 Image enlargedImage(width, height);
 float xRatio = static_cast<float>(image.width) / width;
 float yRatio = static_cast<float>(image.height) / height;
 for (int y = 0; y < height; ++y) {
 for (int x = 0; x < width; ++x) {
 int srcX = static_cast<int>(x * xRatio);
 int srcY = static_cast<int>(y * yRatio);
 for (int c = 0; c < image.channels; ++c) {
 enlargedImage(x, y, c) = image(srcX, srcY, c);
 }
 }
 }
 enlargedImage.saveImage("Filtered Image.png");
}
//Blur
void Blur(Image& image) {
 int width = image.width;
 int height = image.height;
 int blurRadius = 5;
 for (int y = 0; y < height; ++y) {
 for (int x = 0; x < width; ++x) {
 int totalRed = 0;
 int totalGreen = 0;
 int totalBlue = 0;
 int pixelCount = 0;
 for (int dy = -blurRadius; dy <= blurRadius; ++dy) {
 for (int dx = -blurRadius; dx <= blurRadius; ++dx) {
 int nx = x + dx;
int ny = y + dy;
 if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
 unsigned char red = image.getPixel(nx, ny, 0);
 unsigned char green = image.getPixel(nx, ny, 1);
 unsigned char blue = image.getPixel(nx, ny, 2);
 totalRed += red;
totalGreen += green;
totalBlue += blue;
 pixelCount++;
 }
 }
 }
 unsigned char avgRed = totalRed / pixelCount;
 unsigned char avgGreen = totalGreen / pixelCount;
 unsigned char avgBlue = totalBlue / pixelCount;
 image.setPixel(x, y, 0, avgRed);
 image.setPixel(x, y, 1, avgGreen);
 image.setPixel(x, y, 2, avgBlue);
 }
 }
 image.saveImage("Filtered Image.png");
}
//Sun effect
void Sun(Image& image) {
 for (int i = 0; i < image.width; ++i) {
 for (int j = 0; j < image.height; ++j) {
 image(i, j, 0) = min(255, image(i, j, 0) + 60);
 image(i, j, 1) = min(255, image(i, j, 1) + 60);
 }
 }
 image.saveImage("Filtered Image.png");
}
//Purple effect
void Purple(Image& image) {
 for (int i = 0; i < image.width; ++i) {
 for (int j = 0; j < image.height; ++j) {
 image(i, j, 0) = min(255, image(i, j, 0) + 50);
 // No modification to the green channel
 image(i, j, 2) = min(255, image(i, j, 2) + 80);
 }
 }
 image.saveImage("Filtered Image.png");
}
//Infrared effect
void Infrared(Image& image) {
 for (int i = 0; i < image.width; ++i) {
 for (int j = 0; j < image.height; ++j) {
 unsigned int average = 0;
 for (int k = 0; k < 3; ++k) {
 average += image(i, j, k);
 }
 average /= 3;
 image(i, j, 0) = 255;
 image(i, j, 1) = 255 - average;
 image(i, j, 2) = 255 - average;
 }
 }
 image.saveImage("Filtered Image.png");
}
int main() {
 //Welcome message
 cout<<"Welcome to Baby Photoshop" <<endl;
 string image_name;
 //Take the image from the user as input
 cout<<"Please your image name: ";
 getline(cin,image_name);
 Image image;
 image.loadNewImage(image_name);
 //Show filters list
 int choice;
 cout << "Choose one of the following:" << endl;
 cout << "0. Load new image\n";
 cout << "1. Grayscale Conversion Filter\n";
 cout << "2. Black and White Filter\n";
 cout << "3. Invert Image Filter\n";
 cout << "4. Merge Images Filter\n";
 cout << "5. Flip Image Filter\n";
 cout << "6. Rotate Image Filter\n";
 cout << "7. Contrast Filter\n";
 cout << "8. Crop Images Filter\n";
 cout << "9. Add Frame to Picture Filter\n";
 cout << "10. Detect Image Edges Filter\n";
 cout << "11. Resize Images Filter\n";
 cout << "12. Blur Images Filter\n";
 cout << "13. Sunlight Filter\n";
 cout << "14. Purple Night Filter\n";
 cout << "15. Infrared Filter\n";
 cout << "16. Save the image\n";
 cout << "17. Exit\n";
 cout << "Enter your choice: ";
 cin >> choice;
 if (choice == 1){
 Grayscale(image);
 }
 else if (choice == 2){
 BlackAndWhite(image);
 }
 else if (choice == 3) {
 InvertColors(image);
 }
 else if (choice == 4) {
 cin.ignore();
 Merge(image);
 }
 else if (choice == 5) {
 Flip(image);
 }
 else if (choice == 6) {
 Rotate(image);
 }
 else if (choice == 7) {
 Contrast(image);
 }
 else if (choice == 8) {
 Crop(image);
 }
 else if (choice == 9) {
 Frame(image);
 }
 else if (choice == 10) {
 DetectEdges(image);
 }
 else if (choice == 11) {
 Resize(image);
 }
 else if (choice == 12) {
 Blur(image);
 }
 else if (choice == 13) {
 Sun(image);
 }
 else if (choice == 14) {
 Purple(image);
 }
 else if (choice == 15) {
 Infrared(image);
 }
 else if (choice == 17) {
 cout << "Thank you for using Baby Photoshop\n";
 exit(EXIT_FAILURE);
 }
 else {
 cout <<"Please try again";
 cin.ignore();
 main();
 }
 cout << "Filter applied successfully." << endl;
 Again();
 return 0;
}
//Try again when the program ends
void Again() {
 cout << "Do you want to try again? (1 or 2) " << endl;
 cout << "1. Yes" << endl;
 cout << "2. No" << endl;
 int again;
 cin >> again;
 if (again == 1) {
 // Restart the program
 cin.ignore();
 main();
 } else if(again == 2) {
 cout << "Thank you for using Baby Photoshop";
 exit(EXIT_FAILURE);
 }
 else{
 Again();
 }
}