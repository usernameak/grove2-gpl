import json
import sys
from PIL import Image

img = Image.open(sys.argv[1] + ".png").convert('RGBA')

boundary_pixels = []

chars = """ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789.,;:?!-_~#"'&()[]{}^|`/\\@°+=*%€$£¢<>©®ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖØŒÙÚÛÜÝÞàáâãäåæçèéêëìíîïðñòóôõöøœùúûüýþßÿ¿¡"""
# print(len(chars))

for x in range(img.size[0]):
    is_boundary = True
    for y in range(img.size[1]):
        if img.getpixel((x, y))[3] != 0:
            is_boundary = False
            # print(x, y, img.getpixel((x, y)), "failed")
            break
    if is_boundary:
        for y in range(img.size[1]):
            img.putpixel((x, y), (255, 0, 255, 255))
        boundary_pixels.append(x)

# img.show()
# 
# print(boundary_pixels)
# print(len(boundary_pixels))
assert len(boundary_pixels) == len(chars)


font_size = 12

char_height = 16

font_width = img.size[0]
font_height = img.size[1]

baseline_offset = -4

def find_left_bound(i):
    return 0 if i == 0 else boundary_pixels[i - 1] + 1

def find_right_bound(i):
    return boundary_pixels[i]

root = {
    "atlas": {
        "distanceRange": 1,
        "width": font_width,
        "height": font_height,
        "size": font_size,
        "type": "hardmask",
        "yOrigin": "bottom",
    },
    "glyphs": [
        {
            "advance": 7 / font_size,
            "unicode": ord(' '),
        }
    ],
    "kerning": [],
    "metrics": {
        "ascender": 9 / font_size,
        "descender": -4 / font_size,
        "lineHeight": 16 / font_size,
        "underlineThickness": 1 / font_size,
        "underlineY": -1 / font_size,
    }
}

for i in range(len(chars)):
    root["glyphs"].append({
        "advance": (find_right_bound(i) - find_left_bound(i) + 1) / font_size,
        "unicode": ord(chars[i]),
        "atlasBounds": {
            "top": 16,
            "left": find_left_bound(i),
            "bottom": 0,
            "right": find_right_bound(i),
        },
        "planeBounds": {
            "top": (char_height + baseline_offset) / font_size,
            "left": 0,
            "bottom": baseline_offset / font_size,
            "right": (find_right_bound(i) - find_left_bound(i)) / font_size,
        },
    })

json.dump(root, open(sys.argv[1] + ".json", "w"))
