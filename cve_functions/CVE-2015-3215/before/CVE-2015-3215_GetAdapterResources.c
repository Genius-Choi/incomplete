static BOOLEAN GetAdapterResources(PNDIS_RESOURCE_LIST RList, tAdapterResources *pResources)
{
    UINT i;
    NdisZeroMemory(pResources, sizeof(*pResources));
    for (i = 0; i < RList->Count; ++i)
    {
        ULONG type = RList->PartialDescriptors[i].Type;
        if (type == CmResourceTypePort)
        {
            PHYSICAL_ADDRESS Start = RList->PartialDescriptors[i].u.Port.Start;
            ULONG len = RList->PartialDescriptors[i].u.Port.Length;
            DPrintf(0, ("Found IO ports at %08lX(%d)\n", Start.LowPart, len));
            pResources->ulIOAddress = Start.LowPart;
            pResources->IOLength = len;
        }
        else if (type == CmResourceTypeInterrupt)
        {
            pResources->Vector = RList->PartialDescriptors[i].u.Interrupt.Vector;
            pResources->Level = RList->PartialDescriptors[i].u.Interrupt.Level;
            pResources->Affinity = RList->PartialDescriptors[i].u.Interrupt.Affinity;
            pResources->InterruptFlags = RList->PartialDescriptors[i].Flags;
            DPrintf(0, ("Found Interrupt vector %d, level %d, affinity %X, flags %X\n",
                pResources->Vector, pResources->Level, (ULONG)pResources->Affinity, pResources->InterruptFlags));
        }
    }
    return pResources->ulIOAddress && pResources->Vector;
}
