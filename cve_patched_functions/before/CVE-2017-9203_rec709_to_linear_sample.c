static IW_INLINE iw_tmpsample rec709_to_linear_sample(iw_tmpsample v_rec709)
{
	if(v_rec709 < 4.5*0.020) {
		return v_rec709/4.5;
	}
	else {
		return pow( (v_rec709+0.099)/1.099 , 1.0/0.45);
	}
}
