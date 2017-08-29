#! /bin/bash

release=$1
web="https://cmsdoc.cern.ch/Physics/tracking/validation/DATA"

printf "<html>\n" > index.html               
#printf "     <body text=\"#000000\" bgcolor=\"#FFFFFF\" link=\"#FFFF00\" vlink=\"#FF00FF\">\n" >> index.html  
printf "  <title>%s Collisions Validation</title>\n" ${release} >> index.html
printf "     <body>\n" >> index.html  
printf "        <h2>%s Collisions Validation </h2>\n" ${release} >> index.html
printf "           <ul>\n" >> index.html
printf "              <li/><a href=\"%s/%s/genTks\">General Tracks Plots</a>\n" ${web} ${release} >> index.html
printf "              <li/><a href=\"%s/%s/HPTks_dzPV0p1\">High Purity (dz PV 0 < p < 1) Tracks Plots</a>\n" ${web} ${release} >> index.html
printf "              <li/><a href=\"%s/%s/HPTks_0to1\">High Purity (0 < pT < 1 GeV) Tracks Plots</a>\n" ${web} ${release} >> index.html
printf "              <li/><a href=\"%s/%s/HPTks_gt1\">High Purity (pT > 1 GeV) Tracks Plots</a>\n" ${web} ${release} >> index.html
printf "              <li/><a href=\"%s/%s/PackCand\">Packed Candidate Plots</a>\n" ${web} ${release} >> index.html
printf "              <li/><a href=\"%s/%s/SiStrip\">SiStrip Plots</a>\n" ${web} ${release} >> index.html
printf "              <li/><a href=\"%s/%s/dEdx\">dEdx Plots</a>\n" ${web} ${release} >> index.html
printf "              <li/><a href=\"%s/%s/V0\">V0 Monitoring Plots</a>\n" ${web} ${release} >> index.html
printf "              <li/><a href=\"%s/%s/OfflinePV\">Offline Primary Vertices Plots</a>\n" ${web} ${release} >> index.html
printf "              <li/><a href=\"%s/%s/PV_HPTks\">Tracking High Purity Tracks (0 < pT < 1 GeV) Primary Vertices Plots</a>\n" ${web} ${release} >> index.html
printf "           </ul>\n" >> index.html
printf "     </body>\n" >> index.html
printf "</html>\n" >> index.html
