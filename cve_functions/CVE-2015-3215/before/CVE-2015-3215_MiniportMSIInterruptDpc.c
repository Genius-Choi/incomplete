static VOID MiniportMSIInterruptDpc(
    IN PVOID  MiniportInterruptContext,
    IN ULONG  MessageId,
    IN PVOID  MiniportDpcContext,
#if NDIS_SUPPORT_NDIS620
    IN PVOID                   ReceiveThrottleParameters,
    IN PVOID                   NdisReserved2
#else
    IN PULONG                  NdisReserved1,
    IN PULONG                  NdisReserved2
#endif
    )
{
    PARANDIS_ADAPTER *pContext = (PARANDIS_ADAPTER *)MiniportInterruptContext;
    bool requireDPCRescheduling;

#if NDIS_SUPPORT_NDIS620
    PNDIS_RECEIVE_THROTTLE_PARAMETERS RxThrottleParameters = (PNDIS_RECEIVE_THROTTLE_PARAMETERS)ReceiveThrottleParameters;

    RxThrottleParameters->MoreNblsPending = 0;
    requireDPCRescheduling = ParaNdis_DPCWorkBody(pContext, RxThrottleParameters->MaxNblsToIndicate);

    if (requireDPCRescheduling)
        {
            GROUP_AFFINITY Affinity;
            GetAffinityForCurrentCpu(&Affinity);

            NdisMQueueDpcEx(pContext->InterruptHandle, MessageId, &Affinity, MiniportDpcContext);
        }
#else
    UNREFERENCED_PARAMETER(NdisReserved1);

    requireDPCRescheduling = ParaNdis_DPCWorkBody(pContext, PARANDIS_UNLIMITED_PACKETS_TO_INDICATE);
    if (requireDPCRescheduling)
    {
        NdisMQueueDpc(pContext->InterruptHandle, MessageId, 1 << KeGetCurrentProcessorNumber(), MiniportDpcContext);
    }
#endif

    UNREFERENCED_PARAMETER(NdisReserved2);
}
