#! /bin/bash

release=$1
web="https://cmsdoc.cern.ch/Physics/tracking/validation/DATA"

printf "<html>\n" > index.html               
#printf "     <body text=\"#000000\" bgcolor=\"#FFFFFF\" link=\"#FFFF00\" vlink=\"#FF00FF\">\n" >> index.html  
printf "  <title>%s Validation</title>\n" ${release} >> index.html
printf "     <body>\n" >> index.html  
printf "        <h2> %s Validation </h2>\n" ${release} >> index.html
printf "           <ul>\n" >> index.html
printf "              <li/><a href=\"%s/%s/genTks\">General Tracks Plots</a>\n" ${web} ${release} >> index.html
printf "              <li/><a href=\"%s/%s/HPTks\">High Purity Tracks Plots</a>\n" ${web} ${release} >> index.html
printf "              <li/><a href=\"%s/%s/PackCand\">Packed Candidate Plots</a>\n" ${web} ${release} >> index.html
printf "              <li/><a href=\"%s/%s/SiStrip\">SiStrip Plots</a>\n" ${web} ${release} >> index.html
printf "              <li/><a href=\"%s/%s/dEdx\">dEdx Plots</a>\n" ${web} ${release} >> index.html
printf "              <li/><a href=\"%s/%s/PV\">Primary Vertices Plots</a>\n" ${web} ${release} >> index.html
printf "           </ul>\n" >> index.html
printf "     </body>\n" >> index.html
printf "</html>\n" >> index.html
