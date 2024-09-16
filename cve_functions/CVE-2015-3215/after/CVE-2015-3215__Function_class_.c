BOOLEAN _Function_class_(MINIPORT_SYNCHRONIZE_INTERRUPT) CParaNdisTX::RestartQueueSynchronously(tSynchronizedContext *ctx)
{
    auto TXPath = static_cast<CParaNdisTX *>(ctx->Parameter);
    return !TXPath->m_VirtQueue.Restart();
}
