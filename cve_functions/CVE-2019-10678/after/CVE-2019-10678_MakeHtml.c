std::string MakeHtml(const std::string &txt)
{
        std::string sRet = txt;

        stdreplace(sRet, "&", "&amp;");
        stdreplace(sRet, "\"", "&quot;");
        stdreplace(sRet, "'", "&apos;");
        stdreplace(sRet, "<", "&lt;");
        stdreplace(sRet, ">", "&gt;");
        stdreplace(sRet, "\r\n", "<br/>");
        return sRet;
}
