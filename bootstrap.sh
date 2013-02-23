#!/bin/env bash
#
if [ ! -f config-values.sed ]; then
    echo "File 'config-values.sed' not found; cannot continue."
    exit 1;
fi
if [ ! -h binaries/tomcat ]; then
    echo "Download Apache Tomcat; create symbolic link at binaries/tomcat to unpacked directory."
    exit 1;
fi
if [ ! -h binaries/solr ]; then 
    echo "Download Apache SOLR 3.x; create symbolic link at binaries/solr to unpacked directory."
    exit 1;
fi

export SERVICE_HOME=`pwd`
export FEDORA_HOME=$SERVICE_HOME/fedora_home
export DRUPAL_HOME=$SERVICE_HOME/drupal
export CATALINA_HOME=$SERVICE_HOME/binaries/tomcat
export CATALINA_OPTS=-XX:MaxPermSize=256m
export PATH=$PATH:$FEDORA_HOME/server/bin:$FEDORA_HOME/client/bin:$CATALINA_HOME/bin

if [ -d $FEDORA_HOME/gsearch -a ! -d $FEDORA_HOME/gsearch/solr ]; then
    echo "Directory '$FEDORA_HOME/gsearch/solr' not found; must be copied from SOLR dist examples/solr directory."
    exit 1;
fi

if [ ! -d $SERVICE_HOME/sed_substituted_files ]; then
	mkdir $SERVICE_HOME/sed_substituted_files
fi

SED_TEMPLATES_DIR=sed_templates
EXPANDED_CONFIG_DIR=$SERVICE_HOME/sed_substituted_files
SED_CONFIG_SUBSTITUTES=$(mktemp "$EXPANDED_CONFIG_DIR/temp.XXXXXXX")
cat config-values.sed >> $SED_CONFIG_SUBSTITUTES
printf 's:${SERVICE_HOME}:%s:\n' $SERVICE_HOME >> $SED_CONFIG_SUBSTITUTES
printf 's:${FEDORA_HOME}:%s:\n' $FEDORA_HOME >> $SED_CONFIG_SUBSTITUTES
printf 's:${DRUPAL_HOME}:%s:\n' $DRUPAL_HOME >> $SED_CONFIG_SUBSTITUTES
printf 's:${CATALINA_HOME}:%s:\n' $CATALINA_HOME >> $SED_CONFIG_SUBSTITUTES

CONFIG_FILES=$( cat <<EOF
drupal-settings.txt|$DRUPAL_HOME/sites/default/settings.php
filter-drupal.txt|$FEDORA_HOME/server/config/filter-drupal.xml
fedora-catalina-context.xml|$CATALINA_HOME/conf/Catalina/localhost/fedora.xml
fedora-install-properties.txt|$FEDORA_HOME/install/install.properties
fedora-fcfg.txt|$FEDORA_HOME/server/config/fedora.fcfg
solr.xml|$CATALINA_HOME/conf/Catalina/localhost/solr.xml
solr-schema.xml|$FEDORA_HOME/gsearch/solr/conf/schema.xml
solrconfig.xml|$FEDORA_HOME/gsearch/solr/conf/solrconfig.xml
fedora-users.xml|$FEDORA_HOME/server/config/fedora-users.xml
fgsconfig-islandora-properties.txt|$FEDORA_HOME/gsearch/FgsConfig/fgsconfig-basic-for-islandora.properties
EOF
)

for line in $CONFIG_FILES; do
    SOURCE_FILE=$(echo $line | cut -d"|" -f1)
    DEST_FILE=$(echo $line | cut -d"|" -f2)
	sed -f $SED_CONFIG_SUBSTITUTES $SED_TEMPLATES_DIR/$SOURCE_FILE > $EXPANDED_CONFIG_DIR/$SOURCE_FILE
	if [ -f $DEST_FILE ] && [ "$(openssl md5 $EXPANDED_CONFIG_DIR/$SOURCE_FILE | sed 's/.*(\(.*\))= \(.*\)$/\2/')" != "$(openssl md5 $DEST_FILE | sed 's/.*(\(.*\))= \(.*\)$/\2/')" ]; then
		diff $DEST_FILE $EXPANDED_CONFIG_DIR/$SOURCE_FILE
		read -p "Updated $DEST_FILE -- replace? (y/N) " -n 1 -r
		echo
		if [[ $REPLY =~ ^[Yy]$ ]]
		then
			cp $EXPANDED_CONFIG_DIR/$SOURCE_FILE $DEST_FILE
		fi
	else
		cp $EXPANDED_CONFIG_DIR/$SOURCE_FILE $DEST_FILE
	fi
done

rm -r $SED_CONFIG_SUBSTITUTES

## Files to be copied
## $FEDORA_HOME/install/*war to $CATALINA_HOME/webapps
## $SERVICE_HOME/islandora_drupal_filter/target/fcrepo-drupalauthfilter-3.6.2.jar to $CATALINA_HOME/webapps/fedora/WEB-INF/lib

## Build and install GSearch config files
##
## cd $FEDORA_HOME/gsearch/FgsConfig
## ant -f fgsconfig-basic.xml -Dlocal.FEDORA_HOME=$FEDORA_HOME -propertyfile fgsconfig-basic-for-islandora.properties

## TODO 
## * Save the FgsConfig directory somewhere in version control
