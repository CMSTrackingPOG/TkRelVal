#! /bin/bash

release=$1
web="https://cmsdoc.cern.ch/Physics/tracking/validation/DATA"

printf "<html>\n" > index.html               
#printf "     <body text=\"#000000\" bgcolor=\"#FFFFFF\" link=\"#FFFF00\" vlink=\"#FF00FF\">\n" >> index.html  
printf "  <title>Tracking High Purity Tracks (0 < pT < 1 GeV) PV Distributions</title>\n" >> index.html
printf "     <body>\n" >> index.html  
printf "        <h3> Primary Vertices Distributions (Linear) </h3>\n" >> index.html
printf "           <ul>\n" >> index.html
printf "              <li/><a href=\"%s/%s/PV_HPTks/offline_lin\">Offline</a>\n" ${web} ${release} >> index.html
#printf "              <li/><a href=\"%s/%s/PV_HPTks/pixel_lin\">Pixel</a>\n" ${web} ${release} >> index.html
printf "           </ul>\n" >> index.html
printf "        <h3> Primary Vertices Distributions (Log) </h3>\n" >> index.html
printf "              <li/><a href=\"%s/%s/PV_HPTks/offline_log\">Offline</a>\n" ${web} ${release} >> index.html
#printf "              <li/><a href=\"%s/%s/PV_HPTks/pixel_log\">Pixel</a>\n" ${web} ${release} >> index.html
printf "           <ul>\n" >> index.html
printf "           </ul>\n" >> index.html
printf "     </body>\n" >> index.html
printf "</html>\n" >> index.html
