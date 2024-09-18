static inline int put_sigset_t(compat_sigset_t __user *uset, sigset_t *set)
{
	compat_sigset_t	cset;

	switch (_NSIG_WORDS) {
	case 4: cset.sig[6] = set->sig[3] & 0xffffffffull;
		cset.sig[7] = set->sig[3] >> 32;
	case 3: cset.sig[4] = set->sig[2] & 0xffffffffull;
		cset.sig[5] = set->sig[2] >> 32;
	case 2: cset.sig[2] = set->sig[1] & 0xffffffffull;
		cset.sig[3] = set->sig[1] >> 32;
	case 1: cset.sig[0] = set->sig[0] & 0xffffffffull;
		cset.sig[1] = set->sig[0] >> 32;
	}
	return copy_to_user(uset, &cset, sizeof(*uset));
}
