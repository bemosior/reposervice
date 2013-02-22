#!/bin/env bash
#
if [ ! -f config-values.sed ];
then
    echo "File 'config-values.sed' not found; cannot continue."
    exit 1;
fi
if [ ! -h binaries/tomcat ];
then
    echo "Download Apache Tomcat; create symbolic link at binaries/tomcat to unpacked directory."
    exit 1;
fi
if [ ! -h binaries/solr ];
then 
    echo "Download Apache SOLR 3.x; create symbolic link at binaries/solr to unpacked directory."
    exit 1;
fi


export SERVICE_HOME=`pwd`
export FEDORA_HOME=$SERVICE_HOME/fedora_home
export DRUPAL_HOME=$SERVICE_HOME/drupal
export CATALINA_HOME=$SERVICE_HOME/binaries/tomcat
export CATALINA_OPTS=-XX:MaxPermSize=256m
export PATH=$PATH:$FEDORA_HOME/server/bin:$FEDORA_HOME/client/bin:$CATALINA_HOME/bin

if [ -d $FEDORA_HOME/gsearch -a ! -d $FEDORA_HOME/gsearch/solr ];
then
    echo "Directory '$FEDORA_HOME/gsearch/solr' not found; must be copied from SOLR dist examples/solr directory."
    exit 1;
fi


SED_CONFIG_SUBSTITUTES=$(mktemp "$SERVICE_HOME/temp.XXXXXXX")
cat config-values.sed >> $SED_CONFIG_SUBSTITUTES
printf 's:${SERVICE_HOME}:%s:\n' $SERVICE_HOME >> $SED_CONFIG_SUBSTITUTES
printf 's:${FEDORA_HOME}:%s:\n' $FEDORA_HOME >> $SED_CONFIG_SUBSTITUTES
printf 's:${DRUPAL_HOME}:%s:\n' $DRUPAL_HOME >> $SED_CONFIG_SUBSTITUTES
printf 's:${CATALINA_HOME}:%s:\n' $CATALINA_HOME >> $SED_CONFIG_SUBSTITUTES

SED_TEMPLATES_DIR=sed_templates
sed -f $SED_CONFIG_SUBSTITUTES $SED_TEMPLATES_DIR/drupal-settings.txt > $DRUPAL_HOME/sites/default/settings.php
sed -f $SED_CONFIG_SUBSTITUTES $SED_TEMPLATES_DIR/filter-drupal.txt > $FEDORA_HOME/server/config/filter-drupal.xml
sed -f $SED_CONFIG_SUBSTITUTES $SED_TEMPLATES_DIR/fedora-catalina-context.xml > $CATALINA_HOME/conf/Catalina/localhost/fedora.xml
sed -f $SED_CONFIG_SUBSTITUTES $SED_TEMPLATES_DIR/fedora-install-properties.txt > $FEDORA_HOME/install/install.properties
sed -f $SED_CONFIG_SUBSTITUTES $SED_TEMPLATES_DIR/fedora-fcfg.txt > $FEDORA_HOME/server/config/fedora.fcfg
sed -f $SED_CONFIG_SUBSTITUTES $SED_TEMPLATES_DIR/solr.xml > $CATALINA_HOME/conf/Catalina/localhost/solr.xml
sed -f $SED_CONFIG_SUBSTITUTES $SED_TEMPLATES_DIR/solr-schema.xml > $FEDORA_HOME/gsearch/solr/conf/schema.xml
sed -f $SED_CONFIG_SUBSTITUTES $SED_TEMPLATES_DIR/solrconfig.xml > $FEDORA_HOME/gsearch/solr/conf/solrconfig.xml
sed -f $SED_CONFIG_SUBSTITUTES $SED_TEMPLATES_DIR/fedora-users.xml > $FEDORA_HOME/server/config/fedora-users.xml
sed -f $SED_CONFIG_SUBSTITUTES $SED_TEMPLATES_DIR/fgsconfig-islandora-properties.txt > $FEDORA_HOME/gsearch/FgsConfig/fgsconfig-basic-for-islandora.properties

rm $SED_CONFIG_SUBSTITUTES

## Files to be copied
## $FEDORA_HOME/install/*war to $CATALINA_HOME/webapps
## $SERVICE_HOME/islandora_drupal_filter/target/fcrepo-drupalauthfilter-3.6.2.jar to $CATALINA_HOME/webapps/fedora/WEB-INF/lib

## Build and install GSearch config files
##
## cd $FEDORA_HOME/gsearch/FgsConfig
## ant -f fgsconfig-basic.xml -Dlocal.FEDORA_HOME=$FEDORA_HOME -propertyfile fgsconfig-basic-for-islandora.properties

## TODO 
## * Save the FgsConfig directory somewhere in version control
