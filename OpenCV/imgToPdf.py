import img2pdf
from PIL import Image
import os
import datetime
  
img_path = "Resources/ImgForConversion.jpg"
filename = "doc.pdf"
image = Image.open(img_path)
  
# converting
pdf_bytes = img2pdf.convert(image.filename)
  
#creating pdf file
def timeStamped(fname, fmt='%Y-%m-%d-%H-%M-%S_{fname}'):
    return datetime.datetime.now().strftime(fmt).format(fname=fname)

fname = open(timeStamped(filename),'wb')
fname.write(pdf_bytes)
image.close()
fname.close()
  
# output
print("Successfully made pdf file")
