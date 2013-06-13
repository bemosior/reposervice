<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns:foxml="info:fedora/fedora-system:def/foxml#"
    xmlns:s="http://www.w3.org/2001/sw/DataAccess/rf1/result" exclude-result-prefixes="foxml s"
    version="1.0">
    
    <xsl:template match="/foxml:digitalObject" mode="capture_collection_heirarchy">
        <xsl:variable name="lookupParentUri">
            <xsl:value-of select="concat($PROT, '://', $HOST, ':', $PORT)"/>
            <xsl:text>/fedora/risearch?type=tuples&amp;lang=sparql&amp;format=Sparql&amp;limit=1000&amp;dt=on&amp;query=SELECT%20*%20WHERE%20%7B%20&lt;fedora%3A</xsl:text>
            <xsl:value-of select="$PID"/>
            <xsl:text>&gt;%20&lt;fedora-rels-ext%3AisMemberOfCollection&gt;%2B%20%3Fcollection+.%20%7D</xsl:text>
        </xsl:variable>
        <xsl:message> Querying for parent of <xsl:value-of select="$PID"/> using query:
                <xsl:value-of select="$lookupParentUri"/>
        </xsl:message>
        <xsl:for-each select="document($lookupParentUri)//s:collection">
            <field>
                <xsl:attribute name="name">isl_parent_collection_ms</xsl:attribute>
                <xsl:value-of select="substring-after(@uri,'/')"/>
            </field>
        </xsl:for-each>
    </xsl:template>
    
</xsl:stylesheet>
