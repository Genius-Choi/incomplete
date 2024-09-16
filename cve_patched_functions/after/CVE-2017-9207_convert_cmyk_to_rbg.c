static void convert_cmyk_to_rbg(struct iw_context *ctx, const JSAMPLE *src,
	JSAMPLE *dst, int npixels)
{
	int i;
	double c, m, y, k, r, g, b;

	for(i=0;i<npixels;i++) {
		c = 1.0 - ((double)src[4*i+0])/255.0;
		m = 1.0 - ((double)src[4*i+1])/255.0;
		y = 1.0 - ((double)src[4*i+2])/255.0;
		k = 1.0 - ((double)src[4*i+3])/255.0;
		r = 1.0 - c*(1.0-k) - k;
		g = 1.0 - m*(1.0-k) - k;
		b = 1.0 - y*(1.0-k) - k;
		if(r<0.0) r=0.0; if(r>1.0) r=1.0;
		if(g<0.0) g=0.0; if(g>1.0) g=1.0;
		if(b<0.0) b=0.0; if(b>1.0) b=1.0;
		dst[3*i+0] = (JSAMPLE)(0.5+255.0*r);
		dst[3*i+1] = (JSAMPLE)(0.5+255.0*g);
		dst[3*i+2] = (JSAMPLE)(0.5+255.0*b);
	}
}
