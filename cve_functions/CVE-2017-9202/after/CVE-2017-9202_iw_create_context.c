IW_IMPL(struct iw_context*) iw_create_context(struct iw_init_params *params)
{
	struct iw_context *ctx;

	if(params && params->mallocfn) {
		ctx = (*params->mallocfn)(params->userdata,IW_MALLOCFLAG_ZEROMEM,sizeof(struct iw_context));
	}
	else {
		ctx = iwpvt_default_malloc(NULL,IW_MALLOCFLAG_ZEROMEM,sizeof(struct iw_context));
	}

	if(!ctx) return NULL;

	if(params) {
		ctx->userdata = params->userdata;
		ctx->caller_api_version = params->api_version;
	}

	if(params && params->mallocfn) {
		ctx->mallocfn = params->mallocfn;
		ctx->freefn = params->freefn;
	}
	else {
		ctx->mallocfn = iwpvt_default_malloc;
		ctx->freefn = iwpvt_default_free;
	}

	ctx->max_malloc = IW_DEFAULT_MAX_MALLOC;
	ctx->max_width = ctx->max_height = IW_DEFAULT_MAX_DIMENSION;
	default_resize_settings(&ctx->resize_settings[IW_DIMENSION_H]);
	default_resize_settings(&ctx->resize_settings[IW_DIMENSION_V]);
	ctx->input_w = -1;
	ctx->input_h = -1;
	iw_make_srgb_csdescr_2(&ctx->img1cs);
	iw_make_srgb_csdescr_2(&ctx->img2cs);
	ctx->to_grayscale=0;
	ctx->grayscale_formula = IW_GSF_STANDARD;
	ctx->req.include_screen = 1;
	ctx->opt_grayscale = 1;
	ctx->opt_palette = 1;
	ctx->opt_16_to_8 = 1;
	ctx->opt_strip_alpha = 1;
	ctx->opt_binary_trns = 1;

	return ctx;
}
