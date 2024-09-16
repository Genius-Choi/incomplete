devzvol_prunedir(struct sdev_node *ddv)
{
	struct sdev_node *dv;

	ASSERT(RW_READ_HELD(&ddv->sdev_contents));

	sdcmn_err13(("prunedir '%s'", ddv->sdev_name));
	ASSERT(strncmp(ddv->sdev_path, ZVOL_DIR, strlen(ZVOL_DIR)) == 0);
	if (rw_tryupgrade(&ddv->sdev_contents) == 0) {
		rw_exit(&ddv->sdev_contents);
		rw_enter(&ddv->sdev_contents, RW_WRITER);
	}

	dv = SDEV_FIRST_ENTRY(ddv);
	while (dv) {
		sdcmn_err13(("sdev_name '%s'", dv->sdev_name));

		switch (devzvol_validate(dv)) {
		case SDEV_VTOR_VALID:
		case SDEV_VTOR_SKIP:
			dv = SDEV_NEXT_ENTRY(ddv, dv);
			continue;
		case SDEV_VTOR_INVALID:
			sdcmn_err7(("prunedir: destroy invalid "
			    "node: %s\n", dv->sdev_name));
			break;
		}

		if ((SDEVTOV(dv)->v_type == VDIR) &&
		    (sdev_cleandir(dv, NULL, 0) != 0)) {
			dv = SDEV_NEXT_ENTRY(ddv, dv);
			continue;
		}
		SDEV_HOLD(dv);
		/* remove the cache node */
		sdev_cache_update(ddv, &dv, dv->sdev_name,
		    SDEV_CACHE_DELETE);
		SDEV_RELE(dv);
		dv = SDEV_FIRST_ENTRY(ddv);
	}
	rw_downgrade(&ddv->sdev_contents);
}
