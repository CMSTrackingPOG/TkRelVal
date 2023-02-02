#! /bin/bash

printf "<html>\n" > index.html               
#printf "     <body text=\"#000000\" bgcolor=\"#FFFFFF\" link=\"#FFFF00\" vlink=\"#FF00FF\">\n" >> index.html  
printf "  <title>%s Collisions Validation</title>\n" >> index.html
printf "     <body>\n" >> index.html  
printf "        <h2>%s Collisions Validation </h2>\n" >> index.html
printf "           <ul>\n" >> index.html
printf "              <li/><a href=\"genTks\">General Tracks Plots</a>\n"  >> index.html
printf "              <li/><a href=\"HPTks_dzPV0p1\">High Purity (PV dz < 0.1) Tracks Plots</a>\n"  >> index.html
printf "              <li/><a href=\"HPTks_0to1\">High Purity (0 < pT < 1 GeV) Tracks Plots</a>\n"  >> index.html
printf "              <li/><a href=\"HPTks_gt1\">High Purity (pT > 1 GeV) Tracks Plots</a>\n"  >> index.html
printf "              <li/><a href=\"PackCand\">Packed Candidate Plots</a>\n"  >> index.html
printf "              <li/><a href=\"SiStrip\">SiStrip Plots</a>\n"  >> index.html
printf "              <li/><a href=\"dEdx\">dEdx Plots</a>\n"  >> index.html
printf "              <li/><a href=\"V0\">V0 Monitoring Plots</a>\n"  >> index.html
printf "              <li/><a href=\"OfflinePV\">Offline Primary Vertices Plots</a>\n"  >> index.html
printf "              <li/><a href=\"PV_HPTks\">Tracking High Purity Tracks (0 < pT < 1 GeV) Primary Vertices Plots</a>\n"  >> index.html
printf "           </ul>\n" >> index.html
printf "     </body>\n" >> index.html
printf "</html>\n" >> index.html
