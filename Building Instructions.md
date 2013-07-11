# Building the Repository Environment

## Git repo setup

The `reposervice` Git repository contains Git submodules of Fedora Commons, Drupal and Islandora.
The `lyr-master` branch is set to be the branch we are running for production services, and corresponds to the latest tagged release of each software comonent.
Remember -- Git submodule directories represent specific commits of the target Git repository.
If the submodule changes -- e.g., has a commit applied to it -- then you will also need to commit the enclosing `reposervice` module so that all users would be at the same submodule point.

## Prerequisites for using the `reposervice` environment

These packages must be installed on your system.  The configuration has been tested using Ubuntu and MacOSX 10.8 with Homebrew.

1. (For Ubuntu) The `build-essential` virtual package, because you'll be building some of the prerequisites. (For MacOSX) The XCode package from Apple; same reason.
1. Apache HTTPD
1. MySQL-5.1
1. Java6 JDK
	1. Maven3 (mvn)
	1. Ant
1. PHP-5
	1. Drush
	1. php5-gd
	1. php5-imagick
	1. php5-xdebug (for debugging only)
	1. php-pear
	1. php5-curl
	1. php5-xsl
1. libjasper (install this before ImageMagick so ImageMagick can pick up the library)
1. ImageMagick
1. Ghostscript
1. Poppler or Poppler-utils (for `pdftotext`)
1. Tesseract (needs to be [built from source](http://ubuntuforums.org/showthread.php?t=1647350&p=10248384#post10248384), along with leptonica, and requires these prerequisites)
	1. libpng12-dev
	1. libjpeg62-dev
	1. libtiff4-dev

PHP pear is needed to install uploadprogress: `pecl install uploadprogress` and add "extension=uploadprogress.so" to php.ini.  Apache httpd mod_rewrite is needed for clean URLs; for Ubuntu, move `/etc/apache2/mods-available/rewrite.load` to `/etc/apache2/mods-enabled/`.  Also be sure to allow .htaccess directives to be honored by setting `AllowOverride All` in the httpd configuration file.

## Setting up the environment from the bare Git repo

1. `git clone git@github.com:lyrasis/reposervice.git` 
1. `cd reposervice`
1. `git submodule init`
1. `git submodule update` -- Use `git submodule status` to make sure all of the submodules are up-to-date.  There should be no plus signs or minus signs in the left-most column.
1. Copy `config-values.sed-sample` to `config-values.sed` at the top level of the reposervice setup, then edit it with passwords, executable locations, and other configuration options.
1. Run `bin/reposetup-config` multiple times to be told of all of the dependencies in `binaries/` (or simply read the first part of that file to see what all of the current dependencies are).
1. When `bin/reposetup-config` runs to completion (there will be notices of directories missing in the `fedora_home` directory, and that is okay at this point), run `source ./bootstrap.sh` to set environment variables of the current shell.

When starting subsequent shells, be sure to run `source ./bootstrap.sh` to get these key environment variables:

* `$SERVICE_HOME` -- the top directory of the repository service home
* `$FEDORA_HOME` -- the top directory of the Fedora Commons installation
* `$DRUPAL_HOME` -- the top directory of the Drupal installation

These environment variables can be used in shell commands (e.g. "`cd $SERVICE_HOME`") and are used in the remainder of this document to specify specific file locations.

## Setting up Fedora Commons
Be sure `cd reposervice && source bin/reposervice-config` has been run to set the environment variables.  You'll see failures for the 'sed' replacements in the `$FEDORA_HOME` directory -- that is okay.  Having the `$FEDORA_HOME` and `$CATALINA_HOME` environment variables set, though, will preconfigure defaults in the repository installer.

Create the Fedora Commons database using these commands.  Note that the password in the GRANT ALL ON line must match the password in the `$SERVICE_HOME/config-values.sed` file.

		mysqladmin -u root -p create fcrepo_islandora
		mysql -u root -p << EOM
			GRANT ALL ON fcrepo_islandora.* TO fedoraAdmin@localhost IDENTIFIED BY '<password>';
			FLUSH PRIVILEGES;
			ALTER DATABASE fcrepo_islandora DEFAULT CHARACTER SET utf8;
			ALTER DATABASE fcrepo_islandora DEFAULT COLLATE utf8_bin;

You can install Fedora in one of two ways: from a binary distribution of "fcrepo-installer" or by building the installer from source.

### Using a pre-built Fedora Commons installer

The `reposervice-config` script will generate an `install.properties` file with the settings needed to make Fedora run in the reposervice environment.  Use this file to install Fedora Commons to those specifications: 

		java -jar _location_/fcrepo-installer-3.6.2.jar \
		$SERVICE_HOME/sed_substituted_files/fedora_home/install/install.properties

### Building Fedora Commons from source

1. Go into the 'fcrepo' directory: `cd fcrepo`

1. Build repository installer:  `mvn clean install -Dintegration.test.skip=true`  (see [Install Fedora from source](https://wiki.duraspace.org/display/FEDORA35/Installation+From+Source)).
Results are in `fcrepo-installer/target/fcrepo-installer-VERSION.jar`

1. Run the installer: `java -jar fcrepo-installer/target/fcrepo-installer-3.6.2.jar` -- If you add `$SERVICE_HOME/sed_substituted_files/fedora_home/install/install.properties` to the command line, the following questions will not be asked and the values from the properties file will be used.

	1. Installation type: `custom`
	1. Fedora home directory: *use default response; set by the FEDORA_HOME environment variable*
	1. Fedora administrator password: *set and record*
	1. Fedora server host: *use default `localhost`*
	1. Fedora application server context: *use project naming convention*
	1. Authentication requirement for API-A: *use default `false`*
	1. SSL availability: *use default `true`*
	1. SSL required for API-A: *use default `false`*
	1. SSL required for API-M: *use default `true`*
	1. Servlet engine: `existingTomcat`
	1. Tomcat home directory: *use default response; set by the `CATALINA_HOME` environment variable*
	1. Tomcat HTTP port: *use default `8080`*
	1. Tomcat shutdown port: *use default `8005`*
	1. Tomcat Secure HTTP port: *use default `8443`*
	1. Keystore file: *use default `included` for now. TODO: Fix this*
	1. Database: `mysql`
	1. MySQL JDBC driver: *use default included driver*
	1. Database username: *see above*
	1. Database password: *see above*
	1. JDBC URL: *database name will need to be replaced: `jdbc:mysql://localhost/fcrepo_islandora?useUnicode=true&amp;characterEncoding=UTF-8&amp;autoReconnect=true`*
	1. JDBC DriverClass: *use default*
	1. Use upstream HTTP authentication (Experimental Feature): *use default `false`*
	1. Enable FeSL AuthZ (Experimental Feature): *use default `false`*
	1. Policy enforcement enabled: *use default `true`*
	1. Low Level Storage: *use default `akubra-fs`*
	1. Enable Resource Index: `true`
	1. Enable Messaging: `true`
	1. Messaging Provider URI: *use default*
	1. Deploy local services and demos: *use default `true`*

### After installing Fedora Commons from installer or from source

1. Run `$SERVICE_HOME/reposervice-config` to create the configuration files based on the template.  Some copy errors will happen because not all of the directories are in place yet.
1. Start Tomcat: `catalina.sh start` (note that `$SERVICE_HOME/binaries/tomcat/bin` was put in your path by `reposervice-config`, so you can run this script from the command line).
1. Watch the end of the Tomcat logfile for the end of the startup: `tail -f $SERVICE_HOME/binaries/tomcat/logs/catalina.out` -- You'll see "INFO: Server startup in xxxxx ms"
1. Stop Tomcat: `catalina.sh stop`
2. Run `$SERVICE_HOME/reposervice-config` to create the remaining configuration files.

## Set up Islandora module and servlet filter

1. `cd $SERVICE_HOME/islandora_drupal_filter`
1. Build the servlet filter: `mvn install:install-file -Dfile=fcrepo/fcrepo-security/fcrepo-security-http/target/fcrepo-security-http-3.6.2.jar -DgroupId=org.fcrepo -DartifactId=fcrepo-security-http -Dversion=3.6.2 -Dpackaging=jar -DgeneratePom=true`
1. `$SERVICE_HOME/reposervice-config` will move the jar into the correct location.

## Setting Up Drupal

1. Create database.  Note that the password in the GRANT ALL ON line must match the password in the `$SERVICE_HOME/config-values.sed` file.

	    mysqladmin -u root -p create drupal_islandora
	    mysql -u root -p << EOM
    	    grant all on drupal_islandora.* to drisl@localhost identified by '<password>';
			flush privileges;
			EOM

1. Configure Apache HTTPD to find Drupal in the `$SERVICE_HOME/drupal` directory.  In the simplest case, create symbolic link in Apache's htdocs directory to the `drupal` directory of `$SERVICE_HOME`.
1. Go through the Drupal install web pages
1. `cd $DRUPAL_HOME && drush enable feature_base_islandora` -- This will enable the Fedora modules and create the Islandora objects.

## Adding a new Islandora module as a git submodule

1. Fork module to https://github.org/lyrasis organization account, create `lyr-master` branch, change default branch to `lyr-master` in the GitHub repo settings.
1. `cd $SERVICE_HOME`
1. Add the submodule to the reposervice directory: `git submodule add git@github.com:lyrasis/_reponame_.git`
1. Add an 'upstream' remote to the source of the module: `cd _reponame_ && git remote add upstream https://github.com/islandora/_reponame_.git`
1. Add a relative symbolic link in the Drupal modules directory to the new module: `cd $DRUPAL_HOME/sites/all/modules && ln -s ../../../../_reponame_`
1. To semi-automatically check for updates from the upstream source, add an entry to `$SERVICE_HOME/bin/upstreamcheck`
1. Commit a change to the Drupal submodule with the symbolic link added.
1. Commit a change of .gitmodules, bin/upstreamcheck, the Drupal submodule and the new submodule.

Note that when pulling changes from the Reposervice repo, be sure to run the `bin/updaterepoenv` script, which will (in part) initialize the submodule in other clones.  @@TODO: Add this as a reposervice.git hook?

## Set up GSearch

The GSearch and the SOLR configuration files have diverged from the ones generated by the GSearch configuration generation scripts.  Still, these commands may be useful if the GSearch configuration structure someday changes dramatically.

		cd $SERVICE-HOME/gsearch-config
		ant -f fgsconfig-basic.xml -Dlocal.FEDORA_HOME=$FEDORA_HOME -propertyfile fgsconfig-basic-for-islandora.properties

At the very least fgsconfig-basic-for-islandora.properties will need to be reviewed and or updated.  As of the commit after `aefd016b84657ea60099cf55f3f4f731223e74b1` this file is no longer maintained.

## Install Sun Java JDK
Ubuntu installs OpenJDK by default, but there is a [bug in OpenJDK that Djatoka will trip over](http://sourceforge.net/apps/mediawiki/djatoka/index.php?title=Installation#Ubuntu_-_IncompatibleClassChangeError).
The solution is to [install](http://askubuntu.com/questions/55848/how-do-i-install-oracle-java-jdk-7) the [Sun Java version](http://www.oracle.com/technetwork/java/javase/downloads/index.html).

## Set up Open Seadragon large image viewer
Add these lines to the Apache HTTPD configuration:

		ProxyPass /adore-djatoka http://localhost:8080/adore-djatoka
		ProxyPassReverse /adore-djatoka http://localhost:8080/adore-djatoka
		
## Committing changes to submodules
From the main reposervice.git repository, it is helpful to have the commit summaries of submodules listed; this command will do it.  One may need to run `reset` in the terminal after this. 

		git diff --cached --no-color --submodule [submodule] | git commit -e --file=-

## Creating a new site

The steps of creating a new Islandora site are codified in the `bin/repositesetup` script.  The script takes one parameter -- the hostname of the multisite.  Prior to running this script, copy the `$SERVICE_HOME/site_template` directory into the `$SERVICE_HOME/repository_sites` directory (naming it the hostname of the site being created) and modify the values in the `config-stored.conf` file.  This script generates a `config-local.conf` file, which is not stored in the Git repo, that contains the database parameters for the local machine.  Re-run this script whenever `config-stored.conf` is changed or when anything in the `template_files` is changed; the script prompts you to decide whether running code will be updated.

## Committing changes to submodules
From the main reposervice.git repository, it is helpful to have the commit summaries of submodules listed; this command will do it.  One may need to run `reset` in the terminal after this. 

		git diff --cached --no-color --submodule [submodule] | git commit -e --file=-

## (Other Notes)

### Migrating Content
[emory-libraries/eulfedora · GitHub](https://github.com/emory-libraries/eulfedora)
EULfedora is a Python module that provides utilities, API wrappers, and classes for interacting with the Fedora-Commons Repository (versions 3.4.x and 3.5) in a pythonic, object-oriented way, with optional Django integration.

eulfedora.api provides complete access to the Fedora API, primarily making use of Fedora's REST API. This low-level interface is wrapped by eulfedora.server.Repository and eulfedora.models.DigitalObject, which provide a more abstract, object-oriented, and Pythonic way of interacting with a Fedora Repository or with individual objects and datastreams.

eulfedora.indexdata provides a webservice that returns data for fedora objects in JSON form, which can be used in conjunction with a service for updating an index, such as eulindexer.

When used with Django, eulfedora can pull the Repository connection configuration from Django settings, and provides a custom management command for loading simple content models and fixture objects to the configured repository.

[acoburn/cloche · GitHub](https://github.com/acoburn/cloche)
Python utilities for interacting with a fedora repository

[nigelgbanks/islandora_drush · GitHub](https://github.com/nigelgbanks/islandora_drush)
Batch tasks for maintaining a Fedora Repository, requires the Tuque API.

[manidora/manidora.drush.inc at 7.x · nigelgbanks/manidora · GitHub](https://github.com/nigelgbanks/manidora/blob/7.x/manidora.drush.inc)
Book batch ingest script for University of Manitoba.

[UCLALibrary/ucla_migration · GitHub](https://github.com/UCLALibrary/ucla_migration)
This drush script will migrate an entire collection based on a METS manifest.

### Themes of Other Islandora Sites

[UCLALibrary/UCLA-Theme · GitHub](https://github.com/UCLALibrary/UCLA-Theme)

[jordandukart/UofM-Theme · GitHub](https://github.com/jordandukart/UofM-Theme)

[FLVC/islandoratheme · GitHub](https://github.com/FLVC/islandoratheme)

[rosiel/mona · GitHub](https://github.com/rosiel/mona)

[morganhi/Smith-Theme · GitHub](https://github.com/morganhi/Smith-Theme)

[morganhi/UCLA_Base-Theme · GitHub](https://github.com/morganhi/UCLA_Base-Theme)

## Acknowledgments

The initial version of `reposervice` was created by Peter Murray at LYRASIS.  There is some historic mention of LYRASIS or the 'lyr' prefix in the documentation and implementation.