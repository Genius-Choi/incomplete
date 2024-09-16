NO_INLINE void jspeBlock() {
  JSP_MATCH_WITH_RETURN('{',);
  jspeBlockNoBrackets();
  if (!JSP_SHOULDNT_PARSE) JSP_MATCH_WITH_RETURN('}',);
  return;
}
