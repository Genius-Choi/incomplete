static void *cache_alloc_debugcheck_after(struct kmem_cache *cachep,
				gfp_t flags, void *objp, unsigned long caller)
{
	if (!objp)
		return objp;
	if (cachep->flags & SLAB_POISON) {
		check_poison_obj(cachep, objp);
		slab_kernel_map(cachep, objp, 1, 0);
		poison_obj(cachep, objp, POISON_INUSE);
	}
	if (cachep->flags & SLAB_STORE_USER)
		*dbg_userword(cachep, objp) = (void *)caller;

	if (cachep->flags & SLAB_RED_ZONE) {
		if (*dbg_redzone1(cachep, objp) != RED_INACTIVE ||
				*dbg_redzone2(cachep, objp) != RED_INACTIVE) {
			slab_error(cachep, "double free, or memory outside object was overwritten");
			pr_err("%p: redzone 1:0x%llx, redzone 2:0x%llx\n",
			       objp, *dbg_redzone1(cachep, objp),
			       *dbg_redzone2(cachep, objp));
		}
		*dbg_redzone1(cachep, objp) = RED_ACTIVE;
		*dbg_redzone2(cachep, objp) = RED_ACTIVE;
	}

	objp += obj_offset(cachep);
	if (cachep->ctor && cachep->flags & SLAB_POISON)
		cachep->ctor(objp);
	if (ARCH_SLAB_MINALIGN &&
	    ((unsigned long)objp & (ARCH_SLAB_MINALIGN-1))) {
		pr_err("0x%p: not aligned to ARCH_SLAB_MINALIGN=%d\n",
		       objp, (int)ARCH_SLAB_MINALIGN);
	}
	return objp;
}
