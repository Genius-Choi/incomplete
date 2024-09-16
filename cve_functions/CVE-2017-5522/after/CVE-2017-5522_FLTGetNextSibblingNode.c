static CPLXMLNode* FLTGetNextSibblingNode(CPLXMLNode* psXMLNode)
{
    if( psXMLNode == NULL )
        return NULL;
    psXMLNode = psXMLNode->psNext;
    while( psXMLNode != NULL )
    {
        if( psXMLNode->eType == CXT_Element )
            return psXMLNode;
        psXMLNode = psXMLNode->psNext;
    }
    return NULL;
}
