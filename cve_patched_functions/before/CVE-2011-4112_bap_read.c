static inline int bap_read(struct airo_info *ai, __le16 *pu16Dst, int bytelen,
			   int whichbap)
{
	return ai->bap_read(ai, pu16Dst, bytelen, whichbap);
}
