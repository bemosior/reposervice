#!/bin/env bash
#
export SERVICE_HOME=`pwd`
export FEDORA_HOME=$SERVICE_HOME/fedora_home
export DRUPAL_HOME=$SERVICE_HOME/drupal
export PATH=$PATH:$FEDORA_HOME/server/bin:$FEDORA_HOME/client/bin
export CATALINA_HOME=/usr/local/opt/tomcat/libexec

SED_CONFIG_SUBSTITUTES=config-values.sed
SED_TEMPLATES_DIR=sed_templates
sed -f $SED_CONFIG_SUBSTITUTES $SED_TEMPLATES_DIR/drupal-settings.txt > $DRUPAL_HOME/sites/default/settings.php
sed -f $SED_CONFIG_SUBSTITUTES $SED_TEMPLATES_DIR/filter-drupal.txt > $FEDORA_HOME/server/config/filter-drupal.xml
sed -f $SED_CONFIG_SUBSTITUTES $SED_TEMPLATES_DIR/fedora-install-properties.txt > $FEDORA_HOME/install/install.properties
sed -f $SED_CONFIG_SUBSTITUTES $SED_TEMPLATES_DIR/fedora-fcfg.txt > $FEDORA_HOME/server/config/fedora.fcfg
