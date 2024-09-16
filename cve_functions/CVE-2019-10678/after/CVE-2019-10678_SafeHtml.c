std::string SafeHtml(const std::string &txt)
{
    std::string sRet = txt;

    stdreplace(sRet, "\"", "&quot;");
    stdreplace(sRet, "'", "&apos;");
    stdreplace(sRet, "<", "&lt;");
    stdreplace(sRet, ">", "&gt;");
    return sRet;
}
