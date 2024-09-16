xmlNodePtr FLTGetCapabilities(xmlNsPtr psNsParent, xmlNsPtr psNsOgc, int bTemporal)
{
  xmlNodePtr psRootNode = NULL, psNode = NULL, psSubNode = NULL, psSubSubNode = NULL;

  psRootNode = xmlNewNode(psNsParent, BAD_CAST "Filter_Capabilities");

  psNode = xmlNewChild(psRootNode, psNsOgc, BAD_CAST "Spatial_Capabilities", NULL);

  psSubNode = xmlNewChild(psNode, psNsOgc, BAD_CAST "GeometryOperands", NULL);
  psSubSubNode = xmlNewChild(psSubNode, psNsOgc, BAD_CAST "GeometryOperand", BAD_CAST "gml:Point");
  psSubSubNode = xmlNewChild(psSubNode, psNsOgc, BAD_CAST "GeometryOperand", BAD_CAST "gml:LineString");
  psSubSubNode = xmlNewChild(psSubNode, psNsOgc, BAD_CAST "GeometryOperand", BAD_CAST "gml:Polygon");
  psSubSubNode = xmlNewChild(psSubNode, psNsOgc, BAD_CAST "GeometryOperand", BAD_CAST "gml:Envelope");

  psSubNode = xmlNewChild(psNode, psNsOgc, BAD_CAST "SpatialOperators", NULL);
#ifdef USE_GEOS
  psSubSubNode = xmlNewChild(psSubNode, psNsOgc, BAD_CAST "SpatialOperator", NULL);
  xmlNewProp(psSubSubNode, BAD_CAST "name", BAD_CAST "Equals");
  psSubSubNode = xmlNewChild(psSubNode, psNsOgc, BAD_CAST "SpatialOperator", NULL);
  xmlNewProp(psSubSubNode, BAD_CAST "name", BAD_CAST "Disjoint");
  psSubSubNode = xmlNewChild(psSubNode, psNsOgc, BAD_CAST "SpatialOperator", NULL);
  xmlNewProp(psSubSubNode, BAD_CAST "name", BAD_CAST "Touches");
  psSubSubNode = xmlNewChild(psSubNode, psNsOgc, BAD_CAST "SpatialOperator", NULL);
  xmlNewProp(psSubSubNode, BAD_CAST "name", BAD_CAST "Within");
  psSubSubNode = xmlNewChild(psSubNode, psNsOgc, BAD_CAST "SpatialOperator", NULL);
  xmlNewProp(psSubSubNode, BAD_CAST "name", BAD_CAST "Overlaps");
  psSubSubNode = xmlNewChild(psSubNode, psNsOgc, BAD_CAST "SpatialOperator", NULL);
  xmlNewProp(psSubSubNode, BAD_CAST "name", BAD_CAST "Crosses");
  psSubSubNode = xmlNewChild(psSubNode, psNsOgc, BAD_CAST "SpatialOperator", NULL);
  xmlNewProp(psSubSubNode, BAD_CAST "name", BAD_CAST "Intersects");
  psSubSubNode = xmlNewChild(psSubNode, psNsOgc, BAD_CAST "SpatialOperator", NULL);
  xmlNewProp(psSubSubNode, BAD_CAST "name", BAD_CAST "Contains");
  psSubSubNode = xmlNewChild(psSubNode, psNsOgc, BAD_CAST "SpatialOperator", NULL);
  xmlNewProp(psSubSubNode, BAD_CAST "name", BAD_CAST "DWithin");
  psSubSubNode = xmlNewChild(psSubNode, psNsOgc, BAD_CAST "SpatialOperator", NULL);
  xmlNewProp(psSubSubNode, BAD_CAST "name", BAD_CAST "Beyond");
#endif
  psSubSubNode = xmlNewChild(psSubNode, psNsOgc, BAD_CAST "SpatialOperator", NULL);
  xmlNewProp(psSubSubNode, BAD_CAST "name", BAD_CAST "BBOX");

  if (bTemporal) {
    psNode = xmlNewChild(psRootNode, psNsOgc, BAD_CAST "Temporal_Capabilities", NULL);
    psSubNode = xmlNewChild(psNode, psNsOgc, BAD_CAST "TemporalOperands", NULL);
    psSubSubNode = xmlNewChild(psSubNode, psNsOgc, BAD_CAST "TemporalOperand", BAD_CAST "gml:TimePeriod");
    psSubSubNode = xmlNewChild(psSubNode, psNsOgc, BAD_CAST "TemporalOperand", BAD_CAST "gml:TimeInstant");

    psSubNode = xmlNewChild(psNode, psNsOgc, BAD_CAST "TemporalOperators", NULL);
    psSubSubNode = xmlNewChild(psSubNode, psNsOgc, BAD_CAST "TemporalOperator", NULL);
    xmlNewProp(psSubSubNode, BAD_CAST "name", BAD_CAST "TM_Equals");
  }
  psNode = xmlNewChild(psRootNode, psNsOgc, BAD_CAST "Scalar_Capabilities", NULL);
  xmlNewChild(psNode, psNsOgc, BAD_CAST "LogicalOperators", NULL);
  psNode = xmlNewChild(psNode, psNsOgc, BAD_CAST "ComparisonOperators", NULL);
  psSubNode = xmlNewChild(psNode, psNsOgc, BAD_CAST "ComparisonOperator", BAD_CAST "LessThan");
  psSubNode = xmlNewChild(psNode, psNsOgc, BAD_CAST "ComparisonOperator", BAD_CAST "GreaterThan");
  psSubNode = xmlNewChild(psNode, psNsOgc, BAD_CAST "ComparisonOperator", BAD_CAST "LessThanEqualTo");
  psSubNode = xmlNewChild(psNode, psNsOgc, BAD_CAST "ComparisonOperator", BAD_CAST "GreaterThanEqualTo");
  psSubNode = xmlNewChild(psNode, psNsOgc, BAD_CAST "ComparisonOperator", BAD_CAST "EqualTo");
  psSubNode = xmlNewChild(psNode, psNsOgc, BAD_CAST "ComparisonOperator", BAD_CAST "NotEqualTo");
  psSubNode = xmlNewChild(psNode, psNsOgc, BAD_CAST "ComparisonOperator", BAD_CAST "Like");
  psSubNode = xmlNewChild(psNode, psNsOgc, BAD_CAST "ComparisonOperator", BAD_CAST "Between");

  psNode = xmlNewChild(psRootNode, psNsOgc, BAD_CAST "Id_Capabilities", NULL);
  xmlNewChild(psNode, psNsOgc, BAD_CAST "EID", NULL);
  xmlNewChild(psNode, psNsOgc, BAD_CAST "FID", NULL);
  return psRootNode;
}
