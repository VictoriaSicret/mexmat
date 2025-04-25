from PIL import Image
import math

def PeronMalickBlur(k, t, pixels, size):

    global img_new
    n = size[0]
    m = size[1]

    new_pixels = []
    tmp = []
    for i in range(n+2):
        new_pixels.append(list())
        for j in range(m+2):
            if not(i == 0 or i == n+1 or j == 0 or j == m+1): 
                new_pixels[i].append([*(pixels[i-1, j-1])])
            else:
                new_pixels[i].append([0., 0., 0.])
    
    for i in range(n+2):
        tmp.append(list())
        for j in range(m+2):
            if not(i == 0 or i == n+1 or j == 0 or j == m+1): 
                tmp[i].append([*(pixels[i-1, j-1])])
            else:
                tmp[i].append([0., 0., 0.])
 

    def g(x): 
        return 1./(1.+(math.sqrt(x[0]**2 + x[1]**2 + x[2]**2)/k)**2)

    level = 0.
    delta_t = 0.25
    north = [0., 0., 0.]
    south = [0., 0., 0.]
    east = [0., 0., 0.]
    west = [0., 0., 0.]

    while level < t:
        for i in range(1, n+1):
            for j in range(1, m+1):
                north[0] = new_pixels[i-1][j][0]-new_pixels[i][j][0]                
                north[1] = new_pixels[i-1][j][1]-new_pixels[i][j][1] 
                north[2] = new_pixels[i-1][j][2]-new_pixels[i][j][2]

                south[0] = new_pixels[i+1][j][0]-new_pixels[i][j][0]
                south[1] = new_pixels[i+1][j][1]-new_pixels[i][j][1]
                south[2] = new_pixels[i+1][j][2]-new_pixels[i][j][2]

                east[0] = new_pixels[i][j+1][0]-new_pixels[i][j][0]
                east[1] = new_pixels[i][j+1][1]-new_pixels[i][j][1]
                east[2] = new_pixels[i][j+1][2]-new_pixels[i][j][2]
                
                west[0] = new_pixels[i][j-1][0]-new_pixels[i][j][0]
                west[1] = new_pixels[i][j-1][1]-new_pixels[i][j][1]
                west[2] = new_pixels[i][j-1][2]-new_pixels[i][j][2]
                
                tmp[i][j][0] = new_pixels[i][j][0] + delta_t*(g(north)*north[0]+g(south)*south[0]+g(east)*east[0]+g(west)*west[0])
                tmp[i][j][1] = new_pixels[i][j][1] + delta_t*(g(north)*north[1]+g(south)*south[1]+g(east)*east[1]+g(west)*west[1])
                tmp[i][j][2] = new_pixels[i][j][2] + delta_t*(g(north)*north[2]+g(south)*south[2]+g(east)*east[2]+g(west)*west[2])

        for i in range(1, n+1):
            for j in range(1, m+1):
                new_pixels[i][j] = tmp[i][j].copy()


        level = level + delta_t

    for i in range(1, n+1):
        for j in range(1, m+1):
            new_pixels[i][j][0] = int(math.ceil(new_pixels[i][j][0]))
            new_pixels[i][j][1] = int(math.ceil(new_pixels[i][j][1]))
            new_pixels[i][j][2] = int(math.ceil(new_pixels[i][j][2]))
            img_new.putpixel((i-1, j-1), tuple(new_pixels[i][j]))



img = Image.open("image.jpg")
img_new = img.copy()
pixels = img.load()

PeronMalickBlur(10, 10, pixels, img.size)

img_new.save("image_our_algorithm.jpg")

