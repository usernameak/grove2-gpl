import json

font_size = 12

char_width = 8
char_height = 16

font_width = char_width * 16
font_height = char_height * 16

baseline_offset = -4

root = {
    "atlas": {
        "distanceRange": 1,
        "width": font_width,
        "height": font_height,
        "size": font_size,
        "type": "hardmask",
        "yOrigin": "bottom"
    },
    "glyphs": [
        {
            "advance": char_width / font_size,
            "unicode": i,
            "atlasBounds": {
                "top": font_height - ((i // 16) * char_height),
                "left": (i % 16) * char_width,
                "bottom": font_height - ((i // 16) * char_height + char_height),
                "right": (i % 16) * char_width + char_width
            },
            "planeBounds": {
                "top": (char_height + baseline_offset) / font_size,
                "left": 0,
                "bottom": baseline_offset / font_size,
                "right": char_width / font_size
            }
        } for i in range(32, 127)
    ],
    "kerning": [],
    "metrics": {
        "ascender": 8 / font_size,
        "descender": -4 / font_size,
        "lineHeight": 1,
        "underlineThickness": 1 / font_size,
        "underlineY": -1 / font_size,
    }
}

json.dump(root, open("Default.json", "w"))
