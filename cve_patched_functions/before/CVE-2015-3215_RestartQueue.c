bool CParaNdisTX::RestartQueue(bool DoKick)
{
    TSpinLocker LockedContext(m_Lock);
    auto res = ParaNdis_SynchronizeWithInterrupt(m_Context,
                                                 m_messageIndex,
                                                 CParaNdisTX::RestartQueueSynchronously,
                                                 this) ? true : false;

    if(DoKick)
    {
        Kick();
    }

    return res;
}
