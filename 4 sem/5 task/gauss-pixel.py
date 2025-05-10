from PIL import Image
import math

def comp(pixels, i, j, x, y, eps):
    if math.fabs(pixels[i-1, j-1][0] - pixels[x, y][0]) < eps and math.fabs(pixels[i-1, j-1][1] - pixels[x, y][1]) < eps and math.fabs(pixels[i-1, j-1][2] - pixels[x, y][2]) < eps:
        return True
    return False


def getGaussian(r, sigma):
    Gfilter = [0.]*(2*r+1)
    sum = 0.

    for i in range(2*r+1): 
        Gfilter[i] = math.exp((r-i) * (i-r) / (2 * sigma * sigma))
        sum += Gfilter[i]

    for i in range(2*r+1): Gfilter[i] /= sum

    return Gfilter

def GaussianBlur(Gfilter, r, pixels, size, a, b, eps):
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

    lst = []
    for y in range(m):
        for x in range(n):
            if comp(pixels, x, y, a, b, eps):
                lst.append([x, y])

    for y in range(m):
        for x in range(n):
            if [x, y] in lst:
                
                tmp = [pixels[x, j] for j in range(m)]
                buff = GaussBlur1Dim(Gfilter, r, tmp)
                for y in range(m): 
                    img_new.putpixel((x, y), tuple(buff[y]))
                
                tmp = [pixels[i, y] for i in range(n)]
                buff = GaussBlur1Dim(Gfilter, r, tmp)
                for y in range(m): 
                    img_new.putpixel((x, y), tuple(buff[y]))


sigma = 1.5
r = int(math.ceil(3 * sigma))

img = Image.open("images/noise.jpg")
pixels = img.load()

x, y = map(int,input("Enter coordinates of noise: ").split())
eps = int(input("Enter accuracy: "))
img_new = img.copy()

Gfilter = getGaussian(r, sigma)
GaussianBlur(Gfilter, r, pixels, img.size, x, y, eps)

img_new.save("images/clear_gauss.jpg")

