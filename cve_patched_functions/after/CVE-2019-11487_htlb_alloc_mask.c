static inline gfp_t htlb_alloc_mask(struct hstate *h)
{
	if (hugepage_movable_supported(h))
		return GFP_HIGHUSER_MOVABLE;
	else
		return GFP_HIGHUSER;
}
