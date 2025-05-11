from PIL import Image

img = Image.open("images/image.jpg")
print(f"Size: {img.size}")
N = input("\nEnter parameter of scaling:\n")
N = float(N)
img1 = img.resize((int(img.width * N), int(img.height * N)))
img1.save("images/image.jpg")
print(f"Size_new: {img1.size}")

