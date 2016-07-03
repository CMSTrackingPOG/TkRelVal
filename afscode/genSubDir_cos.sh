#! /bin/bash

release=$1
web="https://cmsdoc.cern.ch/Physics/tracking/validation/DATA"

printf "<html>\n" > index.html               
printf "  <title>%s Cosmics Validation</title>\n" ${release} >> index.html
printf "     <body>\n" >> index.html  
printf "        <h2>%s Cosmics Validation</h2>\n" ${release} >> index.html
printf "        <h3>Tracking/TrackParameters Distributions (Linear) </h3>\n" >> index.html
printf "           <ul>\n" >> index.html
printf "              <li/><a href=\"%s/%s/GenProps_lin\">General Properties</a>\n" ${web} ${release} >> index.html
printf "              <li/><a href=\"%s/%s/HitProps_lin\">Hit Properties</a>\n" ${web} ${release} >> index.html
printf "              <li/><a href=\"%s/%s/PU_lin\">PileUp Monitoring</a>\n" ${web} ${release} >> index.html
printf "              <li/><a href=\"%s/%s/SplitTk_lin\">Split Tracks</a>\n" ${web} ${release} >> index.html
printf "              <li/><a href=\"%s/%s/TkBuilding_lin\">Track Building</a>\n" ${web} ${release} >> index.html
printf "              <li/><a href=\"%s/%s/TkEff_lin\">Tracking Efficiency</a>\n" ${web} ${release} >> index.html
printf "           </ul>\n" >> index.html
printf "        <h3>Tracking/TrackParameters Distributions (Log) </h3>\n" >> index.html
printf "           <ul>\n" >> index.html
printf "              <li/><a href=\"%s/%s/GenProps_log\">General Properties</a>\n" ${web} ${release} >> index.html
printf "              <li/><a href=\"%s/%s/HitProps_log\">Hit Properties</a>\n" ${web} ${release} >> index.html
printf "              <li/><a href=\"%s/%s/PU_log\">PileUp Monitoring</a>\n" ${web} ${release} >> index.html
printf "              <li/><a href=\"%s/%s/SplitTk_log\">Split Tracks</a>\n" ${web} ${release} >> index.html
printf "              <li/><a href=\"%s/%s/TkBuilding_log\">Track Building</a>\n" ${web} ${release} >> index.html
printf "              <li/><a href=\"%s/%s/TkEff_log\">Tracking Efficiency</a>\n" ${web} ${release} >> index.html
printf "           </ul>\n" >> index.html
printf "     </body>\n" >> index.html
printf "</html>\n" >> index.html

