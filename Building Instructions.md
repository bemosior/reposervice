# Building the LYRASIS Repository Environment

## Git repo setup

The `reposervice` Git repository contains Git submodules of Fedora Commons, Drupal and Islandora.
The `lyr-master` branch is set to be the branch we are running for production services, and corresponds to the latest tagged release of each software comonent.
Remember -- Git submodule directories represent specific commits of the target Git repository.
If the submodule changes -- e.g., has a commit applied to it -- then you will also need to commit the enclosing `reposervice` module so that all users would be at the same submodule point.

## Project Naming Conventions

## Prerequisites for using LYRASIS `reposervice` environment

1. Apache HTTPD
1. MySQL-5.1
1. Maven2 (mvn)
1. Ant
1. PHP-5
	1. Drush
	1. php5-gd
	1. php5-imagick
	1. php5-xdebug (for debugging only)
	1. php-pear
1. ImageMagick
1. Ghostscript

PHP pear is needed to install uploadprogress: `pecl install uploadprogress` and add "extension=uploadprogress.so" to php.ini.

## Setting up the environment from the bare Git repo

1. `git clone reposervice.git` -- use either ssh://islandora.lyrasistechnology.org/var/gitrepo/reposervice or file:///var/gitrepo/reposervice as required (whether the git repo is remote or on the local machine)
1. `cd reposervice`
1. `git submodule init`
1. `git submodule update` -- Use `git submodule status` to make sure all of the submodules are up-to-date.  There should be no plus signs or minus signs in the left-most column.
1. Download and unpack Apache Tomcat and Apache SOLR 3.x into binaries directory.
1. Create symbolic links in binaries directory for `tomcat` and `solr` that point to the unpacked directories of each.


## Setting Up Drupal

1. Create database

	    mysqladmin -u root -p create drupal_islandora
	    mysql -u root -p << EOM
    	    grant all on drupal_islandora.* to drisl@localhost identified by '<password>';
			flush privileges;
			EOM

1. Create symbolic link in Apache's htdocs directory to the drupal directory of the git repo.
1. Delete the `sites/all/settings.php` file
1. Go through the Drupal install web pages
1. `drush enable lyr_base_islandora`

## Setting up Fedora Commons
Be sure `$SERVICE_HOME/bootstrap.sh` has been run to set the environment variables.  You'll see failures for the 'sed' replacements in the `$FEDORA_HOME` directory -- that is okay.  Having the `$FEDORA_HOME` and `$CATALINA_HOME` environment variables set, though, will preconfigure defaults in the repository installer.

You can feed the installer JAR file the properties file created by `bootstrap.sh` to have these choices selected for you: `java -jar fcrepo-installer/target/fcrepo-installer-3.6.2.jar $SERVICE_HOME/sed_substituted_files/fedora-install-properties.txt`

1. Go into the 'fcrepo' directory: `cd fcrepo`

1. Build repository installer:  `mvn clean install -Dintegration.test.skip=true`  (see [Install Fedora from source](https://wiki.duraspace.org/display/FEDORA35/Installation+From+Source)).
Results are in `fcrepo-installer/target/fcrepo-installer-VERSION.jar`
1. Create database

		mysqladmin -u root -p create fcrepo_islandora
		mysql -u root -p << EOM
			GRANT ALL ON fcrepo_islandora.* TO fedoraAdmin@localhost IDENTIFIED BY '<password>';
			FLUSH PRIVILEGES;
			ALTER DATABASE fcrepo_islandora DEFAULT CHARACTER SET utf8;
			ALTER DATABASE fcrepo_islandora DEFAULT COLLATE utf8_bin;

1. Run the installer: `java -jar fcrepo-installer/target/fcrepo-installer-3.6.2.jar` -- If you add `$SERVICE_HOME/sed_substituted_files/fedora-install-properties.txt` to the command line, the following questions will not be asked and the values from the properties file will be used.

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

1. Run `$SERVICE_HOME/bootstrap.sh` to create the configuration files based on the template.

## Set up Islandora module and servlet filter

1. `cd $SERVICE_HOME/islandora_drupal_filter`
1. Build the servlet filter: `mvn install:install-file -Dfile=fcrepo/fcrepo-security/fcrepo-security-http/target/fcrepo-security-http-3.6.2.jar -DgroupId=org.fcrepo -DartifactId=fcrepo-security-http -Dversion=3.6.2 -Dpackaging=jar -DgeneratePom=true`
1. Move `target/fcrepo-drupalauthfilter-3.6.2.jar` to `$CATALINA_HOME/webapps/fedora/WEB-INF/lib`

## Set up GSearch

1. `cd $SERVICE_HOME/gsearch/FedoraGenericSearch`
2. `ant buildfromsource`