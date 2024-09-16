VOID GetAffinityForCurrentCpu(PGROUP_AFFINITY pAffinity)
{
    PROCESSOR_NUMBER ProcNum;
    KeGetCurrentProcessorNumberEx(&ProcNum);

    pAffinity->Group = ProcNum.Group;
    pAffinity->Mask = 1;
    pAffinity->Mask <<= ProcNum.Number;
}
