ASC_dumpConnectionParameters(T_ASC_Association *association, STD_NAMESPACE ostream& outstream)
{
    OFString str;
    ASC_dumpConnectionParameters(str, association);
    outstream << str << OFendl;
}
