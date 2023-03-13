TkRelVal
========

----------------------------------------
0. DISCLAIMER: these instructions are obsolete. 
They are stored because they contain valuable informations. Please refer to the tutorial.md in the "collisions" folder for updated framework instructions. Please read validation_instructions.txt for validation instructions.
----------------------------------------

Code for charged particle tracking release validation in CMSSW with data.  This README provides a set of slimmed instructions for performing the validation end-to-end, i.e. the steps in getting the relval samples, running the comparator, analyzing by eye the comparisons, and then writing the relval report. The code is meant to be run on lxplus, although in principle one could hack this to put the images in another file, then copy them over at the end.  

A more verbose set of instructions can be found in: ```validation_instructions.txt```. Please consult this document in case the instructions here are not clear.

----------------------------------------
1. Get the files
----------------------------------------

The first thing (after checking out this repo) is to grab the relevant files from the interwebz: https://cmsweb.cern.ch/dqm/relval/data/browse/ROOT/RelValData/

I have a small script to grab the files: ```getFiles.sh```

To grab files from the same directory do:

```./getFiles.sh [CMSSW_Z_Y_x] [Run #] [ref rel, e.g. Z_Y_x_pre1] [target rel, e.g. Z_Y_x_pre2] [sample, e.g. JetHT]```

e.g. 

```./getFiles.sh CMSSW_7_4_x 256677 8_0_1_pre1 8_0_1_pre2```

Depending on the type of data you grab, it will either be dropped into the collisions subdirectory or the cosmics directory (should be rather obvious, seeing as "Cosmics" is a PD). 

----------------------------------------
2. Ensure subdirectories for viewing plots on the web exist
----------------------------------------

This step is a bit hacky and normally not needed. The comparison plots on the web are placed in directories that mostly match the directories in the relvals. This is done for two reasons: 
1. Some of the subdirectories are superfluous and so the plots are more conviently grouped into at most two subdirectories.   
2. The directory and plots names in the relvals are quite long, so I have shortened them. As will become apparent when using the valDB validation reporting tool, there is a character limit on the link section, and when there are long reports, you may not be able to fit all the relevant plots within the character limit.  

It is not perfect, I must admit, but it gets the job done.  The scripts that will do the subdirectory creation for every campaign are in afscode/. Copy all of these down to: 

```/afs/cern.ch/cms/Physics/tracking/validation/DATA``` 

This only has to be done once, and in principle is already done.  However, if you decide to change the directory structure, obviously you would need to copy down the relevant scripts.

----------------------------------------
3. Run the comparator (collisions)
----------------------------------------

cd to collisions/ first.  The plots are overlaid with a script that calls a ROOT macro (```runValidationComparison.C```), that itself compiles ```ReleaseComparison.cpp/hh```. This will produce a set of pdf's of each plot relevant for tracking validation, with the reference release on top of the target release. Each plot is made in both log and linear y-axis. Each comparison has a ratio plot of Target/Ref. ReleaseComparison.cpp has a number of checks to make sure it can indeed produce the plots, in addition to shortening the strings of plot names, setting the axes, stats, lumi, etc.

Run the plot producer with:

```./makeValidationPlots.sh [Run #] [ref rel] [target rel] [sample] [optional: true/false]```

e.g.

```./makeValidationPlots.sh 256677 8_0_1_pre1 8_0_1_pre2 JetHT false```

The optional bool will produce ALL plots (which is a lot, on the order of ~300 plots). False will just do the "standard" plots, i.e. all that is really needed to the validation. For starters, use "false", as true will also eat into the amount of space where the plots are stored. Occasionally, the DQM files get different strings and this screws things up.  To grab the right files and not crash the macro, check to see all the string matching inside ReleaseComparison.cpp is correct.  Occasionally, you will just have to hack the output directory name/labels in the plots to get the thing to run. All plots are automatically placed in the right directories in:

```/afs/cern.ch/cms/Physics/tracking/validation/DATA```

For the examples above, the output would then be in:

```/afs/cern.ch/cms/Physics/tracking/validation/DATA/CMSSW_8_0_1_pre2_vs_8_0_0_pre1_256677_JetHT/```

Now, before we view the plots on the web, we need to unfornately update a small index.html file.

----------------------------------------
3.1 Run the comparator (cosmics)
----------------------------------------

The steps are effectively the same as collisions, just now cd to cosmics/ instead.  The macro + implementation files are more or less copy/pasted.  Ideally, there would be a single executable, but it would take quite some time to get all the strings and such in place.  This again is a bit hacky, but gets the job done.  Note that again here, the full validation == true includes additional plots for cosmics validation.  

----------------------------------------
4. Prepare things for the web viewing
----------------------------------------

Now we need to go down to where the plots are stored:

```cd /afs/cern.ch/cms/Physics/tracking/validation/DATA/```

From here, we will need to use a script that outputs some html code to copy+paste into the index.html file in this directory (getDirHL.sh):

```./getDirHL.sh [CMSSW_Z_Y_x]```

e.g.

```./getDirHL.sh CMSSW_8_0_1_pre1```

from here, copy the output from the terminal into the appropriate heading in index.html.  Obviously, make a new heading if a top category does not exist!  (i.e. CMSSW_8_0_x)

----------------------------------------
5. View plots on the web
----------------------------------------

All campaigns are viewable here: https://cmsdoc.cern.ch/cms/Physics/tracking/validation/DATA/

example:

http://cmsdoc.cern.ch/cms/Physics/tracking/validation/DATA/CMSSW_8_0_1_pre2_vs_8_0_0_pre1_256677_JetHT/index.html

Check the log/linear plots of the most relevant plots produced.  Namely, high purity tracks and general tracks general properties and hit properties is the first place to start.  Make sure to also check the miniAOD validation (PackedCand).  Also check the linear versions of the dxy/dz vs phi/eta in the offlinePV folder (important for alignment checks).  

----------------------------------------
6. Fill out the validation report
----------------------------------------

First, email the tracking conveners and MC/HLT validators in the cms-tracking-validation@cern.ch chain. In the case that changes are expected, check with everyone before writing and submitting your report on valDB.

Once you have the green light, go to valDB: https://cms-conddb-prod.cern.ch/PdmV/valdb/  If there are no changes expected, and all the plots line-up perfectly, just fill out the form in parallel with emailing the conveners.  

Type in the search box the relevant campaign (e.g. 8_0_1_pre2).  On the right hand side, select show all.  Then, click on Reconstruction, and the box for Data tracking will appear.  Click on the box to fill out your report.

This will send an email through the relval HN: https://hypernews.cern.ch/HyperNews/CMS/get/relval.html

Make sure to be subscribed to this HN! That way you will receive the announcements of all the campaigns.  The price of course is that now your inbox will be flooded with emails about relval sample submission as well as every single relval validation report from all the POGs/PAGs/DPGs... so a filter on emails is probably a good idea.

---------------------
Other useful tips
---------------------

Check every few pre-releases campaigns for new plots being added to the relval DQM, and update the tool accordingly.  

Always check in the announcement email for the diffs in the GT's and code on github, to see if any changes are expected. Also check the Tracking POG indico for talks on expected changes as well: https://indico.cern.ch/category/7803/

If you run out of space to write-out plots for the campaigns, there is some EOS disk space with the tracking group.  You will need to get write access from the conveners. I have a number of past campaigns in tarballs for archival purposes, although honestly anything less than 7XY could probably be removed. To view the EOS space, use: eos ls /store/group/phys_tracking/validation/DATA/

Lastly, although not mandatory, check in with the PPD meetings when the present the results from the validation campaigns: https://indico.cern.ch/category/3905/

Other useful links:
* DQM GUI (useful for quick checks): https://cmsweb.cern.ch/dqm/offline/session/ (make sure to select RelVal as the service)
* RelMon (the automatic comparator from central PdmV): http://cms-service-reldqm.web.cern.ch/cms-service-reldqm/cgi-bin/RelMon.py
* Twiki on valDB: https://twiki.cern.ch/twiki/bin/viewauth/CMS/PdmVValDB
