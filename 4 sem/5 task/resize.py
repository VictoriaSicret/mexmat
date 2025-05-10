from PIL import Image

img = Image.open("images/img.jpg")
print(f"Size: {img.size}")
N = input("\nEnter parameter of scaling:\n")
N = float(N)
img1 = img.resize((int(img.width * N), int(img.height * N)))
img1.save("images/img_resize.jpg")
print(f"Size_new: {img1.size}")

