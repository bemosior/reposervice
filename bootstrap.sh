#!/bin/env bash
#
function echoerr { echo "$@" >&2; }

if [ ! -f config-values.sed ]; then
    echoerr "File 'config-values.sed' not found; cannot continue. Copy config-values.sed-sample to config-values.sed and edit."
    exit 1;
fi
if [ ! -h binaries/tomcat ]; then
    echoerr "Download Apache Tomcat; create symbolic link at binaries/tomcat to unpacked directory."
    exit 1;
fi
if [ ! -h binaries/solr ]; then 
    echoerr "Download Apache SOLR 3.x; create symbolic link at binaries/solr to unpacked directory."
    exit 1;
fi

export SERVICE_HOME=`pwd`
export FEDORA_HOME=$SERVICE_HOME/fedora_home
export DRUPAL_HOME=$SERVICE_HOME/drupal
export CATALINA_HOME=$SERVICE_HOME/binaries/tomcat
export CATALINA_OPTS=-XX:MaxPermSize=256m
export PATH=$FEDORA_HOME/server/bin:$FEDORA_HOME/client/bin:$CATALINA_HOME/bin:$PATH
alias catalinalog="cat $CATALINA_HOME/logs/catalina.out"
alias fedoralog="cat $FEDORA_HOME/server/logs/fedora.log"
alias fedoragsearchlog="cat $FEDORA_HOME/server/logs/fedoragsearch.daily.log"

if [ -d $FEDORA_HOME/gsearch -a ! -d $FEDORA_HOME/gsearch/solr ]; then
    echoerr "Directory '$FEDORA_HOME/gsearch/solr' not found; copy $SERVICE_HOME/binaries/solr/examples/solr to $FEDORA_HOME/gsearch"
    exit 1;
fi

SED_TEMPLATES_DIR=$SERVICE_HOME/sed_templates
EXPANDED_CONFIG_DIR=$SERVICE_HOME/sed_substituted_files
if [ ! -d $EXPANDED_CONFIG_DIR ]; then
	mkdir $EXPANDED_CONFIG_DIR
fi

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
fgsconfig-islandora-properties.txt|$SERVICE_HOME/gsearch/FgsConfig/fgsconfig-basic-for-islandora.properties
permit-apim-to-authenticated.xml|$FEDORA_HOME/data/fedora-xacml-policies/repository-policies/default
jaas.conf|$FEDORA_HOME/server/config/jaas.conf
logback.xml|$FEDORA_HOME/server/config/logback.xml
lyr_base_islandora.strongarm.inc|$SERVICE_HOME/lyr_base_islandora/lyr_base_islandora.strongarm.inc
tomcat-server.xml|$CATALINA_HOME/conf/server.xml
EOF
)

for line in $CONFIG_FILES; do
    SOURCE_FILE=$(echo $line | cut -d"|" -f1)
    DEST_FILE=$(echo $line | cut -d"|" -f2)
	sed -f $SED_CONFIG_SUBSTITUTES $SED_TEMPLATES_DIR/$SOURCE_FILE > $EXPANDED_CONFIG_DIR/$SOURCE_FILE
	if [ -f $DEST_FILE ]; then
		if [ "$(openssl md5 $EXPANDED_CONFIG_DIR/$SOURCE_FILE | sed 's/.*(\(.*\))= \(.*\)$/\2/')" != "$(openssl md5 $DEST_FILE | sed 's/.*(\(.*\))= \(.*\)$/\2/')" ]; then
			diff $DEST_FILE $EXPANDED_CONFIG_DIR/$SOURCE_FILE
			read -p "Updated $DEST_FILE -- replace? (y/N) " -n 1 -r
			echo
			if [[ $REPLY =~ ^[Yy]$ ]]; then
				cp $EXPANDED_CONFIG_DIR/$SOURCE_FILE $DEST_FILE
			fi
		fi
	else
		cp $EXPANDED_CONFIG_DIR/$SOURCE_FILE $DEST_FILE
	fi
done

rm -r $SED_CONFIG_SUBSTITUTES

BINARY_FILES=$( cat <<EOF
$FEDORA_HOME/install/fedora-demo.war|$CATALINA_HOME/webapps
$FEDORA_HOME/install/fedora.war|$CATALINA_HOME/webapps
$FEDORA_HOME/install/fop.war|$CATALINA_HOME/webapps
$FEDORA_HOME/install/imagemanip.war|$CATALINA_HOME/webapps
$FEDORA_HOME/install/saxon.war|$CATALINA_HOME/webapps
$SERVICE_HOME/islandora_drupal_filter/target/fcrepo-drupalauthfilter-3.6.2.jar|$CATALINA_HOME/webapps/fedora/WEB-INF/lib
$SERVICE_HOME/gsearch/FgsBuild/fromsource/fedoragsearch.war|$CATALINA_HOME/webapps
EOF
)

for line in $BINARY_FILES; do
    SOURCE_FILE=$(echo $line | cut -d"|" -f1)
    DEST_DIR=$(echo $line | cut -d"|" -f2)
    BASE_FILENAME=$(basename $SOURCE_FILE)
    DEST_FILE=$DEST_DIR/$BASE_FILENAME
    if [ ! -f $SOURCE_FILE ]; then 
    	echoerr "Binary source file $SOURCE_FILE doesn't exist, and it probably should."
    else
    	if [ ! -d $DEST_DIR ]; then
    		echoerr "Binary destination directory $DEST_DIR doesn't exist, and it probably should."
    	else
    		if [ -f $DEST_FILE ]; then
    			if [ "$(openssl md5 $SOURCE_FILE | sed 's/.*(\(.*\))= \(.*\)$/\2/')" != "$(openssl md5 $DEST_FILE | sed 's/.*(\(.*\))= \(.*\)$/\2/')" ]; then
    				ls -l $SOURCE_FILE
    				ls -l $DEST_FILE
    				read -p "Update $BASE_FILENAME? (y/N) " -n 1 -r
	    			echo
   		 			if [[ $REPLY =~ ^[Yy]$ ]]; then
    					cp $SOURCE_FILE $DEST_FILE
    				fi
    			fi
    		else
    			cp $SOURCE_FILE $DEST_FILE
    		fi
    	fi
    fi
done

## Build and install GSearch config files
##
## cd $FEDORA_HOME/gsearch/FgsConfig
## ant -f fgsconfig-basic.xml -Dlocal.FEDORA_HOME=$FEDORA_HOME -propertyfile fgsconfig-basic-for-islandora.properties

## TODO 
## * Save the FgsConfig directory somewhere in version control
