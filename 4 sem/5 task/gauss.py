from PIL import Image
import math


def getGaussian(r, sigma):
    Gfilter = [0.]*(2*r+1)
    sum = 0.

    for i in range(2*r+1): 
        Gfilter[i] = math.exp((r-i) * (i-r) / (2 * sigma * sigma))
        sum += Gfilter[i]

    for i in range(2*r+1): Gfilter[i] /= sum

    return Gfilter

def GaussianBlur(Gfilter, r, pixels, size):
    global img_new
    n = size[0]
    m = size[1]

    def convolution(lst1, lst2):
        sum = [0., 0., 0.]
        for i in range(len(lst1)):
            sum[0] += lst1[i]*lst2[i][0]
            sum[1] += lst1[i]*lst2[i][1]
            sum[2] += lst1[i]*lst2[i][2]
        return sum

    def GaussBlur1Dim(Gfilter, r, values):
        res = [[0, 0, 0]]*len(values)
        
        for x in range(r):
            tmp = Gfilter[:x]
            sum = 0.
            for p in tmp: sum += p
            for p in tmp: p /= sum
            tmp = convolution(tmp, values[:x])
            res[x] = [int(math.floor(tmp[0])), int(math.floor(tmp[1])), int(math.floor(tmp[2]))].copy()
        
        for x in range(r, len(values)-r):
            tmp = convolution(Gfilter, values[x-r:r+x+1])
            res[x] = [int(math.floor(tmp[0])), int(math.floor(tmp[1])), int(math.floor(tmp[2]))].copy()
        
        for x in range(len(values)-r, len(values)):
            tmp = Gfilter[x:]
            sum = 0.
            for p in tmp: sum += p
            for p in tmp: p /= sum
            tmp = convolution(tmp, values[x:])
            res[x] = [int(math.floor(tmp[0])), int(math.floor(tmp[1])), int(math.floor(tmp[2]))].copy()

        return res

    for x in range(n):
        tmp = [pixels[x, j] for j in range(m)]
        buff = GaussBlur1Dim(Gfilter, r, tmp)
        for y in range(m): 
            img_new.putpixel((x, y), tuple(buff[y]))
    
    for y in range(m):
        tmp = [pixels[i, y] for i in range(n)]
        buff = GaussBlur1Dim(Gfilter, r, tmp)
        for x in range(n): img_new.putpixel((x, y), tuple(buff[x]))



sigma = 1.5
r = int(math.ceil(3 * sigma))

img = Image.open("images/image.jpg")
pixels = img.load()

img_new = img.copy()

Gfilter = getGaussian(r, sigma)
GaussianBlur(Gfilter, r, pixels, img.size)

img_new.save("images/image_new.jpg")

