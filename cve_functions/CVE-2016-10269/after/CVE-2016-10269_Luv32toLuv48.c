Luv32toLuv48(LogLuvState* sp, uint8* op, tmsize_t n)
{
	uint32* luv = (uint32*) sp->tbuf;  
	int16* luv3 = (int16*) op;

	while (n-- > 0) {
		double u, v;

		*luv3++ = (int16)(*luv >> 16);
		u = 1./UVSCALE * ((*luv>>8 & 0xff) + .5);
		v = 1./UVSCALE * ((*luv & 0xff) + .5);
		*luv3++ = (int16)(u * (1L<<15));
		*luv3++ = (int16)(v * (1L<<15));
		luv++;
	}
}
