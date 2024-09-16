static inline struct frad_state* state(hdlc_device *hdlc)
{
	return(struct frad_state *)(hdlc->state);
}
