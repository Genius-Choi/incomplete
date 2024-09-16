static void rsm_set_desc_flags(struct desc_struct *desc, u32 flags)
{
	desc->g    = (flags >> 23) & 1;
	desc->d    = (flags >> 22) & 1;
	desc->l    = (flags >> 21) & 1;
	desc->avl  = (flags >> 20) & 1;
	desc->p    = (flags >> 15) & 1;
	desc->dpl  = (flags >> 13) & 3;
	desc->s    = (flags >> 12) & 1;
	desc->type = (flags >>  8) & 15;
}
