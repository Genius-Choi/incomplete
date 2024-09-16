int FLTCheckInvalidOperand(FilterEncodingNode *psFilterNode)
{
    int status = MS_SUCCESS;

    if (psFilterNode->eType ==  FILTER_NODE_TYPE_COMPARISON &&
        psFilterNode->psLeftNode != NULL &&
        psFilterNode->psLeftNode->eType == FILTER_NODE_TYPE_PROPERTYNAME)
    {
        if( strcmp(psFilterNode->psLeftNode->pszValue, "gml:boundedBy") == 0 &&
            strcmp(psFilterNode->pszValue, "PropertyIsNull") != 0 &&
            strcmp(psFilterNode->pszValue, "PropertyIsNil") != 0 )
        {
            msSetError(MS_MISCERR, "Operand '%s' is invalid in comparison.",
                       "FLTCheckInvalidOperand()", psFilterNode->psLeftNode->pszValue);
            return MS_FAILURE;
        }
    }
    if (psFilterNode->psLeftNode)
    {
      status = FLTCheckInvalidOperand(psFilterNode->psLeftNode);
      if( status == MS_SUCCESS )
      {
        if (psFilterNode->psRightNode)
            status = FLTCheckInvalidOperand(psFilterNode->psRightNode);
      }
    }
    return status;
}
