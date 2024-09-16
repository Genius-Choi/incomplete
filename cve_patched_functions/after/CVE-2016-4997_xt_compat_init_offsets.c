void xt_compat_init_offsets(u_int8_t af, unsigned int number)
{
	xt[af].number = number;
	xt[af].cur = 0;
}
