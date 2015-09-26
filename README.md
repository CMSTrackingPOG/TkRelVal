TkRelVal
========

Code for data charged particle tracking release validation in CMSSW

----------------------------------------
Get the files
----------------------------------------

To use, first need to grab the relevant files from the interwebz: https://cmsweb.cern.ch/dqm/relval/data/browse/ROOT/RelValData/
I have a small script to grab the files: getFiles.sh
To grab files from the same directory do:

./getFiles.sh [CMSSW_Z_Y_x] [Run #] [ref rel, e.g. Z_Y_x_pre1] [target rel, e.g. Z_Y_x_pre2]
e.g. 
./getFiles.sh CMSSW_7_4_x 191226 7_6_0_pre4 7_6_0_pre5

--> As of now, just grab MinimumBias and Jet... can change the loop to grab ZeroBias, HLTPhysics, etc... Need a grid certificate to get files

----------------------------------------
Rename MinBias
----------------------------------------

Small script renames MinimumBias to MinBias... just do:

./renameMB.sh

----------------------------------------
Make sure afscode matches
----------------------------------------

Not perfect, have some small scripts that handle making plots in right directories for web.  Copy the afsdirectory down to: /afs/cern.ch/cms/Physics/tracking/validation/DATA

if any changes are made to the directory structure (also would change ./makeValidationPlots.sh and ReleaseComparison.cpp)

----------------------------------------
Run the code
----------------------------------------

TO run the plot producer, use the script:

./makeValidationPlots.sh [Run #] [ref rel] [target rel] [sample]
e.g.

./makeValidationPlots.sh 191226 7_6_0_pre4 7_6_0_pre5 Jet

This calls runComparison.C (amongst other small scripts), which compiles ReleaseComparison.cpp (2000 lines...).  produces log and lin plots for all distributions.  Currently at 250+ plots...
This will take about ~3 minutes to run. All plots are automatically placed in the right directories in /afs/cern.ch/cms/Physics/tracking/validation/DATA
For the examples above, the output would then be in:
/afs/cern.ch/cms/Physics/tracking/validation/DATA/CMSSW_7_6_0_pre5_vs_7_6_0_pre4_191226_Jet/

Now, before we view them on the web, need to unfornately update a small index.html file.

----------------------------------------
Prepare things for the web viewing
----------------------------------------

cd /afs/cern.ch/cms/Physics/tracking/validation/DATA/

Now, we will need to use a script that outputs some html code to copy+paste into the index.html file in this directory (getDirHL.sh):

./getDirHL.sh [CMSSW_Z_Y_x]
e.g.
./getDirHL.sh CMSSW_7_6_0_pre5

from here, copy the output from the terminal into the appropriate heading in index.html.   Obviously, make a new heading if a top category does not exist!  (i.e. CMSSW_7_4_x)

----------------------------------------
View on the web
----------------------------------------

All campaigns are viewable here: https://cmsdoc.cern.ch/cms/Physics/tracking/validation/DATA/

example:

http://cmsdoc.cern.ch/cms/Physics/tracking/validation/DATA/CMSSW_7_6_0_pre5_vs_7_6_0_pre4_191226_MinBias/index.html

---> now report to cms-tracking-validation@cern.ch for internal discussion before reporting on valDB.