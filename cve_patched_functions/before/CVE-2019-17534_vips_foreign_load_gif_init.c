vips_foreign_load_gif_init( VipsForeignLoadGif *gif )
{
	gif->n = 1;
	gif->transparency = -1;
	gif->delay = 4;
	gif->loop = 0;
	gif->comment = NULL;
	gif->dispose = 0;
}
