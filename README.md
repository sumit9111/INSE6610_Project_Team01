# README #

## General structure ##

* `doc` is for documentation, report, etc. Create a dir for your team there, e.g., `teamX`, and initialize the report document there.
* `src` is for anything source-related of your project touches that, such as Forensic Lucid specifications, code modifications and patches to external tools, any other scripts, etc. Place your code work under `teamX` subdirectory.
* `data` is any sample data set *legally obtained*, *less than 2GB* (bitbucket limit), *does not contain PII, malware, any other illegal or explicit content*. Otherwise, keep your data set separately locally elsewhere.

## Templates ##

* **LaTeX use is strongly preferred**
* `doc/templates/report-latex-easychair` is the most documented example template in LaTeX, single column, more readable. To be able to compile LaTeX report, install and configure [MiKTeX](http://miktex.org) first (LaTeX backend compiler and styles and packages), then [TeXnicCenter](http://texniccenter.org) (GUI front-end to MikTeX, it will find MikTeX installation when installed after MikTeX). Open `project-report.tcp` project file for TeXnicCenter and compile it using F7 3 times; F5 to preview the PDF.
* `doc/templates/report-latex-ieee` two-column IEEE LaTeX template (the instructions here are pretty much the same as for easychair) 
* `doc/templates/report-word-ieee` two-column IEEE Word template
* `doc/templates/peer-evaluation-form.rtf` to use if there are disputes within teams

## FYI: below is a boilerplate README from BitBucket ##

This README would normally document whatever steps are necessary to get your application up and running.

### What is this repository for? ###

* Quick summary
* Version
* [Learn Markdown](https://bitbucket.org/tutorials/markdowndemo)

### How do I get set up? ###

* Summary of set up
* Configuration
* Dependencies
* Database configuration
* How to run tests
* Deployment instructions

### Contribution guidelines ###

* Writing tests
* Code review
* Other guidelines

### Who do I talk to? ###

* Serguei
* Other community or team contact