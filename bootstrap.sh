#!/bin/env bash
#
export SERVICE_HOME=`pwd`
export FEDORA_HOME=$SERVICE_HOME/fedora_home
export DRUPAL_HOME=$SERVICE_HOME/drupal
export CATALINA_HOME=/usr/local/opt/tomcat/libexec
export PATH=$PATH:$FEDORA_HOME/server/bin:$FEDORA_HOME/client/bin:$CATALINA_HOME/bin

SED_CONFIG_SUBSTITUTES=$(mktemp "$SERVICE_HOME/temp.XXXXXXX")
cat config-values.sed >> $SED_CONFIG_SUBSTITUTES
printf 's:${SERVICE_HOME}:%s:\n' $SERVICE_HOME >> $SED_CONFIG_SUBSTITUTES
printf 's:${FEDORA_HOME}:%s:\n' $FEDORA_HOME >> $SED_CONFIG_SUBSTITUTES
printf 's:${DRUPAL_HOME}:%s:\n' $DRUPAL_HOME >> $SED_CONFIG_SUBSTITUTES

SED_TEMPLATES_DIR=sed_templates
sed -f $SED_CONFIG_SUBSTITUTES $SED_TEMPLATES_DIR/drupal-settings.txt > $DRUPAL_HOME/sites/default/settings.php
sed -f $SED_CONFIG_SUBSTITUTES $SED_TEMPLATES_DIR/filter-drupal.txt > $FEDORA_HOME/server/config/filter-drupal.xml
sed -f $SED_CONFIG_SUBSTITUTES $SED_TEMPLATES_DIR/fedora-install-properties.txt > $FEDORA_HOME/install/install.properties
sed -f $SED_CONFIG_SUBSTITUTES $SED_TEMPLATES_DIR/fedora-fcfg.txt > $FEDORA_HOME/server/config/fedora.fcfg
sed -f $SED_CONFIG_SUBSTITUTES $SED_TEMPLATES_DIR/solr.xml > $CATALINA_HOME/conf/Catalina/localhost/solr.xml
sed -f $SED_CONFIG_SUBSTITUTES $SED_TEMPLATES_DIR/fedora-users.xml > $FEDORA_HOME/server/config/fedora-users.xml


rm $SED_CONFIG_SUBSTITUTES