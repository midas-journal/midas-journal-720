#include "filter.h"

void normalize(std::vector<float> &mask) {
  int len = mask.size();
  float sum = 0;
  for (int i = 1; i < len; i++) {
    sum += fabs(mask[i]);
  }
  sum = 2*sum + fabs(mask[0]);
  for (int i = 0; i < len; i++) {
    mask[i] /= sum;
  }
}


/* convolve image with gaussian filter */
image<float> *smooth(image<float> *src, float sigma) {
  std::vector<float> mask = make_fgauss(sigma);
  normalize(mask);

  image<float> *tmp = new image<float>(src->height(), src->width(), false);
  image<float> *dst = new image<float>(src->width(), src->height(), false);
  convolve_even(src, tmp, mask);
  convolve_even(tmp, dst, mask);

  delete tmp;
  return dst;
}

/* convolve image with gaussian filter */
image<float> *smooth(image<uchar> *src, float sigma) {
  image<float> *tmp = imageUCHARtoFLOAT(src);
  image<float> *dst = smooth(tmp, sigma);
  delete tmp;
  return dst;
}

/* compute laplacian */
image<float> *laplacian(image<float> *src) {
  int width = src->width();
  int height = src->height();
  image<float> *dst = new image<float>(width, height);  

  for (int y = 1; y < height-1; y++) {
    for (int x = 1; x < width-1; x++) {
      float d2x = imRef(src, x-1, y) + imRef(src, x+1, y) -
	2*imRef(src, x, y);
      float d2y = imRef(src, x, y-1) + imRef(src, x, y+1) -
	2*imRef(src, x, y);
      imRef(dst, x, y) = d2x + d2y;
    }
  }
  return dst;
}