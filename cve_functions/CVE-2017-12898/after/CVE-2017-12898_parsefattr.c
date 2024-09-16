parsefattr(netdissect_options *ndo,
           const uint32_t *dp, int verbose, int v3)
{
	const struct nfs_fattr *fap;

	fap = (const struct nfs_fattr *)dp;
	ND_TCHECK(fap->fa_gid);
	if (verbose) {
		ND_PRINT((ndo, " %s %o ids %d/%d",
		    tok2str(type2str, "unk-ft %d ",
		    EXTRACT_32BITS(&fap->fa_type)),
		    EXTRACT_32BITS(&fap->fa_mode),
		    EXTRACT_32BITS(&fap->fa_uid),
		    EXTRACT_32BITS(&fap->fa_gid)));
		if (v3) {
			ND_TCHECK(fap->fa3_size);
			ND_PRINT((ndo, " sz %" PRIu64,
				EXTRACT_64BITS((const uint32_t *)&fap->fa3_size)));
		} else {
			ND_TCHECK(fap->fa2_size);
			ND_PRINT((ndo, " sz %d", EXTRACT_32BITS(&fap->fa2_size)));
		}
	}
	/* print lots more stuff */
	if (verbose > 1) {
		if (v3) {
			ND_TCHECK(fap->fa3_ctime);
			ND_PRINT((ndo, " nlink %d rdev %d/%d",
			       EXTRACT_32BITS(&fap->fa_nlink),
			       EXTRACT_32BITS(&fap->fa3_rdev.specdata1),
			       EXTRACT_32BITS(&fap->fa3_rdev.specdata2)));
			ND_PRINT((ndo, " fsid %" PRIx64,
				EXTRACT_64BITS((const uint32_t *)&fap->fa3_fsid)));
			ND_PRINT((ndo, " fileid %" PRIx64,
				EXTRACT_64BITS((const uint32_t *)&fap->fa3_fileid)));
			ND_PRINT((ndo, " a/m/ctime %u.%06u",
			       EXTRACT_32BITS(&fap->fa3_atime.nfsv3_sec),
			       EXTRACT_32BITS(&fap->fa3_atime.nfsv3_nsec)));
			ND_PRINT((ndo, " %u.%06u",
			       EXTRACT_32BITS(&fap->fa3_mtime.nfsv3_sec),
			       EXTRACT_32BITS(&fap->fa3_mtime.nfsv3_nsec)));
			ND_PRINT((ndo, " %u.%06u",
			       EXTRACT_32BITS(&fap->fa3_ctime.nfsv3_sec),
			       EXTRACT_32BITS(&fap->fa3_ctime.nfsv3_nsec)));
		} else {
			ND_TCHECK(fap->fa2_ctime);
			ND_PRINT((ndo, " nlink %d rdev 0x%x fsid 0x%x nodeid 0x%x a/m/ctime",
			       EXTRACT_32BITS(&fap->fa_nlink),
			       EXTRACT_32BITS(&fap->fa2_rdev),
			       EXTRACT_32BITS(&fap->fa2_fsid),
			       EXTRACT_32BITS(&fap->fa2_fileid)));
			ND_PRINT((ndo, " %u.%06u",
			       EXTRACT_32BITS(&fap->fa2_atime.nfsv2_sec),
			       EXTRACT_32BITS(&fap->fa2_atime.nfsv2_usec)));
			ND_PRINT((ndo, " %u.%06u",
			       EXTRACT_32BITS(&fap->fa2_mtime.nfsv2_sec),
			       EXTRACT_32BITS(&fap->fa2_mtime.nfsv2_usec)));
			ND_PRINT((ndo, " %u.%06u",
			       EXTRACT_32BITS(&fap->fa2_ctime.nfsv2_sec),
			       EXTRACT_32BITS(&fap->fa2_ctime.nfsv2_usec)));
		}
	}
	return ((const uint32_t *)((const unsigned char *)dp +
		(v3 ? NFSX_V3FATTR : NFSX_V2FATTR)));
trunc:
	return (NULL);
}
