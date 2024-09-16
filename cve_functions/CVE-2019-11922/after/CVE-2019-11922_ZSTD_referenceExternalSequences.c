size_t ZSTD_referenceExternalSequences(ZSTD_CCtx* cctx, rawSeq* seq, size_t nbSeq)
{
    if (cctx->stage != ZSTDcs_init)
        return ERROR(stage_wrong);
    if (cctx->appliedParams.ldmParams.enableLdm)
        return ERROR(parameter_unsupported);
    cctx->externSeqStore.seq = seq;
    cctx->externSeqStore.size = nbSeq;
    cctx->externSeqStore.capacity = nbSeq;
    cctx->externSeqStore.pos = 0;
    return 0;
}
