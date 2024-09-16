set_doc_flag(xmlNode *xml, long flag) 
{

    if(xml && xml->doc && xml->doc->_private){
        /* During calls to xmlDocCopyNode(), xml->doc may be unset */
        xml_private_t *p = xml->doc->_private;

        p->flags |= flag;
        /* crm_trace("Setting flag %x due to %s[@id=%s]", flag, xml->name, ID(xml)); */
    }
}
