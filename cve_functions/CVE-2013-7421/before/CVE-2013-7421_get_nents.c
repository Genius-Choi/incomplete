static int get_nents(struct scatterlist *sg, int nbytes)
{
	int nents = 0;

	while (nbytes > 0) {
		nbytes -= sg->length;
		sg = scatterwalk_sg_next(sg);
		nents++;
	}

	return nents;
}
