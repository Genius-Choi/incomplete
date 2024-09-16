static int ZSTD_isUpdateAuthorized(ZSTD_cParameter param)
{
    switch(param)
    {
    case ZSTD_p_compressionLevel:
    case ZSTD_p_hashLog:
    case ZSTD_p_chainLog:
    case ZSTD_p_searchLog:
    case ZSTD_p_minMatch:
    case ZSTD_p_targetLength:
    case ZSTD_p_compressionStrategy:
        return 1;

    case ZSTD_p_format:
    case ZSTD_p_windowLog:
    case ZSTD_p_contentSizeFlag:
    case ZSTD_p_checksumFlag:
    case ZSTD_p_dictIDFlag:
    case ZSTD_p_forceMaxWindow :
    case ZSTD_p_nbWorkers:
    case ZSTD_p_jobSize:
    case ZSTD_p_overlapSizeLog:
    case ZSTD_p_enableLongDistanceMatching:
    case ZSTD_p_ldmHashLog:
    case ZSTD_p_ldmMinMatch:
    case ZSTD_p_ldmBucketSizeLog:
    case ZSTD_p_ldmHashEveryLog:
    case ZSTD_p_forceAttachDict:
    default:
        return 0;
    }
}
