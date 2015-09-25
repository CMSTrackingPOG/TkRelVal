#! /bin/bash

release=$1
web="https://cmsdoc.cern.ch/Physics/tracking/validation/DATA"

printf "<html>\n" > index.html               
#printf "     <body text=\"#000000\" bgcolor=\"#FFFFFF\" link=\"#FFFF00\" vlink=\"#FF00FF\">\n" >> index.html  
printf "  <title>PV Distributions</title>\n" >> index.html
printf "     <body>\n" >> index.html  
printf "        <h3> Primary Vertices Distributions (Linear) </h3>\n" >> index.html
printf "           <ul>\n" >> index.html
printf "              <li/><a href=\"%s/%s/PV/Alignment_lin\">PV Alignment</a>\n" ${web} ${release} >> index.html
printf "              <li/><a href=\"%s/%s/PV/offlineBS_lin\">Offline Beamspot</a>\n" ${web} ${release} >> index.html
printf "              <li/><a href=\"%s/%s/PV/offlinePVs_lin\">Offline Primary Vertices</a>\n" ${web} ${release} >> index.html
printf "           </ul>\n" >> index.html
printf "        <h3> Primary Vertices Distributions (Log) </h3>\n" >> index.html
printf "           <ul>\n" >> index.html
printf "              <li/><a href=\"%s/%s/PV/Alignment_log\">PV Alignment</a>\n" ${web} ${release} >> index.html
printf "              <li/><a href=\"%s/%s/PV/offlineBS_log\">Offline Beamspot</a>\n" ${web} ${release} >> index.html
printf "              <li/><a href=\"%s/%s/PV/offlinePVs_log\">Offline Primary Vertices</a>\n" ${web} ${release} >> index.html
printf "           </ul>\n" >> index.html
printf "     </body>\n" >> index.html
printf "</html>\n" >> index.html
