# Self-Contained Islandora 7.x Repository Service

This repository contains git submodules, configuration template system, and supplemental scripts for running an [Islandora](http://islandora.ca/) 7.x repository service.  See the `Building Instructions` file for mostly accurate guidance on getting started with this setup.  (In other words, it is a little dated, but will be mostly helpful.)

## Goals of this setup

* Put (most) everything in a self-contained directory using relative paths for most components with a configuration script that generates configuration files for absolute paths.
* Make it easy to track the upstream Islandora work so that you can bring selected commits into your own environment, if desired.
* Put the configuration of Fedora Commons, FedoraGSearch, SOLR, and other associated components under version control.
* Use Drupal Features to store the Drupal configuration and put it under version control.
* Support multi-site setups for separate Islandora/Drupal instances using a common Fedora Commons, SOLR, and djatoka installation.

## What is outside this setup

* Apache HTTPD (with some specific configuration directives specific to Islandora)
* MySQL RDBMS for Drupal and Fedora Commons
* Java JVM
* ImageMagick
* Poppler Utils
* Ghostscript
* Tesseract

## Description of key files, directories, and scripts

### `bootstrap.sh` - Shell environment setup

This bash script in the root directory will set environment variables, command aliases, and other important activities to prepare your shell environment for running the repository service.  It will check the relative modification dates of the configuration files (in `sed_templates/`) versus the generated setup script (`bin/reposervice-env`) and warn if the configuration generator (`bin/reposervice-config`) needs to be run again.

Run this script whenever you start a new shell in order to pick up the repository setup.  **Important**: run this script with the shell `source` command so that it affects the currently running environment:

		cd reposervice
		source ./bootstrap.sh

If you haven't yet run the `bin/reposervice-config` script, you'll be prompted to do so.

### `config-values.sed` - Configuration values

Copy the `config-values.sed-sample` file to the `config-values.sed` name.  This file contains command directives that are fed into `sed` that modify placeholders in  configuration file templates (`sed_templates` directory) with real values.  This file is explicitly not stored in version control (e.g., it is in `.gitignore`) so you can have separate files for development, staging, and production servers.  The names of the placeholders should be self explanatory.

### `sed_templates/` directory - Template files

Files in this directory contain templates of configuration files that are under version control.  Each template file is run through `sed` using the commands in `config-values.sed` (plus others added by `bin/reposervice-config`) to the a file of the same name in the `sed_substituted_files` directory.  Some special files of note:

#### `sed_templates/binaries#tomcat#conf#Catalina#localhost/` files

These files will be processed and copied into the Tomcat `conf/Catalina/localhost/` directory.  It is the tricks in these files that will allow us to:

* put the FedoraGSearch configuration outside of the expanded WAR file
* set the `fedora_home/` path to a location within the `reposervice/` directory
* make Tomcat file WAR files in locations outside of the `webapps/` directory

#### `sed_templates/fedora_home#gsearch#fgsconfigFinal/` directory

These are FedoraGSearch configuration files based on the per-datastream-type transformation model first found in the [Discovery Garden GitHub](https://github.com/discoverygarden/basic-solr-config) repo.

### `reposervice/binaries/` directory

There are several perquisite binaries that are not included in the git repo for reasons of size and/or relatively static nature (e.g., Apache Tomcat, Apache SOLR, djatoka, FITS).  The `bin/reposervice-config` script checks for the existence of these prerequisites and prompts if they are not there.

### `repository_sites/` directory

This directory contains the configuration (e.g., Drupal settings, features and themes, Fedora server setup, and Islandora XML Builder forms) that are specific to a site.  See the `repositesetup` script for more discussion about how this directory is used.  This directory is in the reposervice `.gitignore` file; you probably want to create private Git repo to version control this content outside of reposervice.

### `site_tempate/` directory

This directory is the template of a new Islandora site.  It will be copied to the `repository_sites/` directory and named as the hostname of the new Islandora site as part of the site setup process.

### `bin/reposervice-config` shell script

This shell script has several purposes in setting up the `reposervice/` setup:

* Checks for prerequisites to be downloaded, expanded, and symlinked appropriately in the `reposervices/binaries/` directory.
* Figures out the necessary djakota setup environment.
* Generates the `bin/reposervice-env` shell script, use subsequently by the `bootstrap.sh` script to set up the shell environment.
* Runs the `sed` replacements on the configuration template files, checks to see if they match the current configuration, shows context-sensitive diffs and prompts the user for file replacement.
* Verifies that binary files that have been copied into `reposervice/` tree are at their latest versions (e.g., the compile Fedora Commons WARs, the Islandora Drupal Filter JAR file)

### `bin/repositesetup` script

This Perl script creates and updates an Islandora repository instance under the Drupal multisite setup.  See the "Building Instructions" document for details on using the script.

### `bin/upstreamcheck` script

This script contains a mapping of git submodules to their upstream mainline development branches.  Running this script will fetch upstream commits and show a brief git log between the HEAD and the upstream mainline development.  This is useful on development instances when you are closely tracking upstream development.

### `bin/updaterepoenv` script

This script runs through a series of steps necessary to sync the local environment with reposervice.git.  The environment is somewhat complex, so it is easy to forget some of the steps.
