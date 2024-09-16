VOID ParaNdis_ProcessorNumberToGroupAffinity(PGROUP_AFFINITY Affinity, const PPROCESSOR_NUMBER Processor)
{
    Affinity->Group = Processor->Group;
    Affinity->Mask = 1;
    Affinity->Mask <<= Processor->Number;
}
