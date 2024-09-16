static inline int getPixelOverflowTC(gdImagePtr im, const int x, const int y, const int bgColor)
{
	if (gdImageBoundsSafe(im, x, y)) {
		const int c = im->tpixels[y][x];
		if (c == im->transparent) {
			return bgColor == -1 ? gdTrueColorAlpha(0, 0, 0, 127) : bgColor;
		}
		return c;
	} else {
		return bgColor;
	}
}
