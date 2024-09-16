static CPLXMLNode* FLTGetFirstChildNode(CPLXMLNode* psXMLNode)
{
    if( psXMLNode == NULL )
        return NULL;
    psXMLNode = psXMLNode->psChild;
    while( psXMLNode != NULL )
    {
        if( psXMLNode->eType == CXT_Element )
            return psXMLNode;
        psXMLNode = psXMLNode->psNext;
    }
    return NULL;
}
