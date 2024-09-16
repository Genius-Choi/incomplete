static void clamp_output_samples(struct iw_context *ctx, iw_tmpsample *out_pix, int num_out_pix)
{
	int i;

	for(i=0;i<num_out_pix;i++) {
		if(out_pix[i]<0.0) out_pix[i]=0.0;
		else if(out_pix[i]>1.0) out_pix[i]=1.0;
	}
}
