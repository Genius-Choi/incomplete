f2flac24_array (const float *src, int32_t *dest, int count, int normalize)
{	float normfact = normalize ? (1.0 * 0x7FFFFF) : 1.0 ;

	while (--count >= 0)
		dest [count] = lrintf (src [count] * normfact) ;
} /* f2flac24_array */
