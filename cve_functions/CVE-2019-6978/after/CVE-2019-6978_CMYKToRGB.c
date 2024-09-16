static int CMYKToRGB(int c, int m, int y, int k, int inverted)
{
	if (inverted) {
		c = 255 - c;
		m = 255 - m;
		y = 255 - y;
		k = 255 - k;
	}
	return gdTrueColor((255 - c) * (255 - k) / 255, (255 - m) * (255 - k) / 255, (255 - y) * (255 - k) / 255);
}
