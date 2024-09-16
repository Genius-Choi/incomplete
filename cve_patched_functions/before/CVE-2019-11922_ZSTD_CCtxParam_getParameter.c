size_t ZSTD_CCtxParam_getParameter(
        ZSTD_CCtx_params* CCtxParams, ZSTD_cParameter param, unsigned* value)
{
    switch(param)
    {
    case ZSTD_p_format :
        *value = CCtxParams->format;
        break;
    case ZSTD_p_compressionLevel :
        *value = CCtxParams->compressionLevel;
        break;
    case ZSTD_p_windowLog :
        *value = CCtxParams->cParams.windowLog;
        break;
    case ZSTD_p_hashLog :
        *value = CCtxParams->cParams.hashLog;
        break;
    case ZSTD_p_chainLog :
        *value = CCtxParams->cParams.chainLog;
        break;
    case ZSTD_p_searchLog :
        *value = CCtxParams->cParams.searchLog;
        break;
    case ZSTD_p_minMatch :
        *value = CCtxParams->cParams.searchLength;
        break;
    case ZSTD_p_targetLength :
        *value = CCtxParams->cParams.targetLength;
        break;
    case ZSTD_p_compressionStrategy :
        *value = (unsigned)CCtxParams->cParams.strategy;
        break;
    case ZSTD_p_contentSizeFlag :
        *value = CCtxParams->fParams.contentSizeFlag;
        break;
    case ZSTD_p_checksumFlag :
        *value = CCtxParams->fParams.checksumFlag;
        break;
    case ZSTD_p_dictIDFlag :
        *value = !CCtxParams->fParams.noDictIDFlag;
        break;
    case ZSTD_p_forceMaxWindow :
        *value = CCtxParams->forceWindow;
        break;
    case ZSTD_p_forceAttachDict :
        *value = CCtxParams->attachDictPref;
        break;
    case ZSTD_p_nbWorkers :
#ifndef ZSTD_MULTITHREAD
        assert(CCtxParams->nbWorkers == 0);
#endif
        *value = CCtxParams->nbWorkers;
        break;
    case ZSTD_p_jobSize :
#ifndef ZSTD_MULTITHREAD
        return ERROR(parameter_unsupported);
#else
        *value = CCtxParams->jobSize;
        break;
#endif
    case ZSTD_p_overlapSizeLog :
#ifndef ZSTD_MULTITHREAD
        return ERROR(parameter_unsupported);
#else
        *value = CCtxParams->overlapSizeLog;
        break;
#endif
    case ZSTD_p_enableLongDistanceMatching :
        *value = CCtxParams->ldmParams.enableLdm;
        break;
    case ZSTD_p_ldmHashLog :
        *value = CCtxParams->ldmParams.hashLog;
        break;
    case ZSTD_p_ldmMinMatch :
        *value = CCtxParams->ldmParams.minMatchLength;
        break;
    case ZSTD_p_ldmBucketSizeLog :
        *value = CCtxParams->ldmParams.bucketSizeLog;
        break;
    case ZSTD_p_ldmHashEveryLog :
        *value = CCtxParams->ldmParams.hashEveryLog;
        break;
    default: return ERROR(parameter_unsupported);
    }
    return 0;
}
