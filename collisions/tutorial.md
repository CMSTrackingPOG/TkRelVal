# Install a CMSSW release
This framework runs on CMSSW_9_4_8, with root 6.10/09 and python 2.7
The framework has not been tested in other CMSSW release. You are free to do it and let us know the most recent version of CMSSW supported.

    cmsrel CMSSW_9_4_8
    cd CMSSW_9_4_8/src/
    cmsenv

# Download this repo
A github account should be needed to download this repo on lxplus:

    git clone git@github.com:CMSTrackingPOG/TkRelVal.git

# Setup the environment
I strongly suggest to go to the personal (or common, depends if exist) eos and create a folder where to store DQM root files. 
In my case, it shuld be:

    cd /eos/user/a/abulla/

And let's make a directory to store root files:

    mkdir DQM

Now lets do a symbolic link in the repo folder:

    cd 
    cd CMSSW_9_4_8/src/TkRelVal/collisions
    ln -s /eos/user/a/abulla/DQM

# Download brilcalc
Plots make use of brilcalc software to compute the lumonisty of a run.
The calculation is computed in lumiCalc.py, you are free to check it in details. It is based on the LSs (which are not empty) in a given histo.
These LSs are then passed to brilcalc and the ouput is stored. 

To install brilcalc, please follow https://twiki.cern.ch/twiki/bin/view/TOTEM/CMSbril

You need to add this line in you ~/.bashrc file:

    export PATH=$HOME/.local/bin:/afs/cern.ch/cms/lumi/brilconda-X.Y.Z/bin:$PATH
    source ~/.bashrc

and then 

    cd ..
    pip uninstall -y brilws
    pip install --install-option="--prefix=$HOME/.local" brilws
    pip show brilws

# Downlaod some ROOT files
Depending on the release campaign, some DQM root files are needed.
A grid cerificate is needed to download this files.

    ./getFiles.sh CMSSW_12_6_x 357735 pre4 pre5 JetMET

Now automatically in DQM you should find a CMSSW_12_6_x folder, which contains a 357735 folder, a "pre4_vs_pre5" with inside JetMET folder, with 2 (or more) files.

# Prepare the comparison tool:
Before run the tracker comparison tool, make sure to use the correct paths. This is the only modification you need to do in order to run the repo.
You should modify the output directory (where you store the plots) in 'makeValidationPlots.sh': 
https://github.com/CMSTrackingPOG/TkRelVal/blob/master/collisions/makeValidationPlots.sh#L15

Here the common (tracker) eos space is used, but you are free to use your own, I suppose.

# Run the comparison tool:
Run the comparison tool is simple. 
    cd collisions
    python start.py -h 

To check the fundamental parameter you need to pass (as the reference file and the target one).
Some argument are optional. Anyway, I recommend to use them anyway. If not, it is possible that the programm still ask you some information. 

    python start.py --refFile DQM/CMSSW_12_6_x/pre4_vs_pre5/357735/JetMET/DQM_V0001_R000357735__JetMET__CMSSW_12_6_0_pre4-125X_dataRun3_relval_v1_RelVal_2022D-v2__DQMIO.root --targetFile DQM/CMSSW_12_6_x/pre4_vs_pre5/357735/JetMET/DQM_V0001_R000357735__JetMET__CMSSW_12_6_0_pre5-125X_dataRun3_relval_v4_RelVal_2022D-v3__DQMIO.root --refLabel pre4 --targetLabel pre5

Additional --FullPlots option can be used, and as you can see from ReleaseComparison.cpp, it will be responsible for additional plots!

# Enjoy
Wait for the process to end. All the plots are stored in the directory you chose.