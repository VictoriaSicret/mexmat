double* getGaussian(int r, double sigma) {
    double* filter = new double [2*r+1];

    double sum = 0;
    for (int i = 0; i < 2*r+1; i++) {
        filter[i] = exp(-(i-r) * (i-r) / (2 * sigma * sigma));
        sum += filter[i];
    }

    for (int i = 0; i < 2*r+1; i++) {
            filter[i] /= sum;
    }

    return filter;
}

Image GaussianBlur(Image img, double* filter, int c, int r) {
    Image newimg;
    newimg.cols = img.cols - c + 1;;
    newimg.rows = img.rows - r + 1;;
    newimg.data = new unsigned char * [newimg.rows];
    for (size_t i = 0; i < newimg.rows; ++i) {
        newimg.data[i] = new uchar[newimg.cols];
    }

    for (size_t y = 0; y < newimg.rows; y++) {
        for (size_t x = 0; x < newimg.cols; x++) {
            int sum = 0;
            for (int h = y; h < y + r; h++) {
                for (int w = x; w < x + c; w++) {
                    sum += filter[h - y][w - x] * img.data[h][w];
                }
            }
            newimg.data[y][x] = sum;
        }
    }
    for (size_t y = 0; y < c; ++y) {
        delete[] filter[y];
    }
    delete[] filter;

    return newimg;
}

