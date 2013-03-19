#!/bin/env bash
#

CATALINA_DEBUG="-Xdebug -Xrunjdwp:transport=dt_socket,address=8000,server=y,suspend=n"


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
if [ ! -h binaries/adore-djatoka ]; then 
    echoerr "Download adore-djatoka; create symbolic link at binaries/adore-djatoka to unpacked directory."
    exit 1;
fi

export SERVICE_HOME=`pwd`
export FEDORA_HOME=$SERVICE_HOME/fedora_home
export DRUPAL_HOME=$SERVICE_HOME/drupal
export CATALINA_HOME=$SERVICE_HOME/binaries/tomcat
export CATALINA_OPTS="$CATALINA_DEBUG -XX:MaxPermSize=256m"
export PATH=$FEDORA_HOME/server/bin:$FEDORA_HOME/client/bin:$CATALINA_HOME/bin:$PATH
alias lesscatalinalog="less $CATALINA_HOME/logs/catalina.out"
alias lessfedoralog="less $FEDORA_HOME/server/logs/fedora.log"
alias lessgsearchlog="less $FEDORA_HOME/server/logs/fedoragsearch.daily.log"
alias tomcattunnel="ssh -fNg -L 18080:localhost:8080 islandora.lyrasistechnology.org"

if [ -d $FEDORA_HOME/gsearch -a ! -d $FEDORA_HOME/gsearch/solr ]; then
    echoerr "Directory '$FEDORA_HOME/gsearch/solr' not found; copy $SERVICE_HOME/binaries/solr/examples/solr to $FEDORA_HOME/gsearch"
    exit 1;
fi


###
### BEGIN Copied and Adapted from djatoka distribution
###
# Define DJATOKA_HOME dynamically
export DJATOKA_HOME=$SERVICE_HOME/binaries/adore-djatoka
DJATOKA_LAUNCHDIR=$DJATOKA_HOME/bin
DJATOKA_LIBPATH=$DJATOKA_HOME/lib

if [ `uname` = 'Linux' ] ; then
  if [ `uname -m` = "x86_64" ] ; then
    # Assume Linux AMD 64 has 64-bit Java
    DJATOKA_PLATFORM="Linux-x86-64"
    export DJATOKA_LD_LIBRARY_PATH="$DJATOKA_LIBPATH/$DJATOKA_PLATFORM"
    KAKADU_LIBRARY_PATH="-DLD_LIBRARY_PATH=$DJATOKA_LIBPATH/$DJATOKA_PLATFORM"
  else
    # 32-bit Java
    DJATOKA_PLATFORM="Linux-x86-32"
    export DJATOKA_LD_LIBRARY_PATH="$DJATOKA_LIBPATH/$DJATOKA_PLATFORM"
    KAKADU_LIBRARY_PATH="-DLD_LIBRARY_PATH=$DJATOKA_LIBPATH/$DJATOKA_PLATFORM"
  fi
elif [ `uname` = 'Darwin' ] ; then
  # Mac OS X
  DJATOKA_PLATFORM="Mac-x86"
  export DJATOKA_DYLD_LIBRARY_PATH="$DJATOKA_LIBPATH/$DJATOKA_PLATFORM"
  KAKADU_LIBRARY_PATH="-DDYLD_LIBRARY_PATH=$DJATOKA_LIBPATH/$DJATOKA_PLATFORM"
elif [ `uname` = 'SunOS' ] ; then
  if [ `uname -p` = "i386" ] ; then
    # Assume Solaris x86
    DJATOKA_PLATFORM="Solaris-x86"
    export DJATOKA_LD_LIBRARY_PATH="$DJATOKA_LIBPATH/$DJATOKA_PLATFORM"
  else
    # Sparcv9
    DJATOKA_PLATFORM="Solaris-Sparcv9"
    export DJATOKA_LD_LIBRARY_PATH="$DJATOKA_LIBPATH/$DJATOKA_PLATFORM"
  fi
else
  echo "djatoka env: Unsupported DJATOKA_PLATFORM: `uname`"
  exit
fi

export KAKADU_HOME=$DJATOKA_HOME/bin/$DJATOKA_PLATFORM
djatoka_classpath=
for line in `ls -1 $DJATOKA_LIBPATH | grep '.jar'`
  do
  djatoka_classpath="$djatoka_classpath:$DJATOKA_LIBPATH/$line"
done

#echo "#!/bin/bash" > $SERVICE_HOME/binaries/tomcat/bin/setenv.sh
#echo "# Generated `date` by $SERVICE_HOME/bootstrap.sh" >> $SERVICE_HOME/binaries/tomcat/bin/setenv.sh
#echo "CLASSPATH=$DJATOKA_LAUNCHDIR:$DJATOKA_HOME/build/:$djatoka_classpath" >> $SERVICE_HOME/binaries/tomcat/bin/setenv.sh

CATALINA_OPTS="$CATALINA_OPTS -Djava.awt.headless=true  -Xmx512M -Xms64M -Dkakadu.home=$KAKADU_HOME -Djava.library.path=$DJATOKA_LIBPATH/$DJATOKA_PLATFORM $KAKADU_LIBRARY_PATH"

###
### END Copied and Adapted from djatoka distribution
###


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
printf 's:${PATH_KAKADU}:%s/kdu_compress:\n' $KAKADU_HOME >> $SED_CONFIG_SUBSTITUTES

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
fgsconfig-islandora-properties.txt|$SERVICE_HOME/gsearch-config/fgsconfig-basic-for-islandora.properties
permit-apim-to-authenticated.xml|$FEDORA_HOME/data/fedora-xacml-policies/repository-policies/default
jaas.conf|$FEDORA_HOME/server/config/jaas.conf
logback.xml|$FEDORA_HOME/server/config/logback.xml
lyr_base_islandora.strongarm.inc|$SERVICE_HOME/lyr_base_islandora/lyr_base_islandora.strongarm.inc
tomcat-server.xml|$CATALINA_HOME/conf/server.xml
djatoka-log4j.properties|$CATALINA_HOME/webapps/adore-djatoka/WEB-INF/classes/log4j.properties
EOF
)

for line in $CONFIG_FILES; do
    SOURCE_FILE=$(echo $line | cut -d"|" -f1)
    DEST_FILE=$(echo $line | cut -d"|" -f2)
	sed -f $SED_CONFIG_SUBSTITUTES $SED_TEMPLATES_DIR/$SOURCE_FILE > $EXPANDED_CONFIG_DIR/$SOURCE_FILE
	
	## For Kakadu to function, we need to inject a LD_LIBRARY_PATH (Linux) or 
	## DYLD_LIBRARY_PATH (MacOSX) environment variable into the Drupal environment. 
	## We're choosing to do this by appending a PHP putenv() at the end of the
	## Drupal settings.php File
	if [ "$SOURCE_FILE" == "drupal-settings.txt" ]; then
		if [ -n "$DJATOKA_LD_LIBRARY_PATH" ]; then
    		echo "putenv(\"LD_LIBRARY_PATH=$DJATOKA_LD_LIBRARY_PATH\");" >> $EXPANDED_CONFIG_DIR/$SOURCE_FILE
		elif [ -n "$DJATOKA_DYLD_LIBRARY_PATH" ]; then
			echo "putenv(\"DYLD_LIBRARY_PATH=$DJATOKA_DYLD_LIBRARY_PATH\");" >> $EXPANDED_CONFIG_DIR/$SOURCE_FILE
		fi
	fi

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
$SERVICE_HOME/binaries/adore-djatoka/dist/adore-djatoka.war|$CATALINA_HOME/webapps
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
## cd $SERVICE-HOME/gsearch-config
## ant -f fgsconfig-basic.xml -Dlocal.FEDORA_HOME=$FEDORA_HOME -propertyfile fgsconfig-basic-for-islandora.properties