#! /bin/bash

release=$1
tracks=$2
web="https://cmsdoc.cern.ch/Physics/tracking/validation/DATA"

printf "<html>\n" > index.html               
#printf "     <body text=\"#000000\" bgcolor=\"#FFFFFF\" link=\"#FFFF00\" vlink=\"#FF00FF\">\n" >> index.html  
printf "  <title>Track Distributions</title>\n" >> index.html
printf "     <body>\n" >> index.html  
printf "        <h3> %s Distributions (Linear) </h3>\n" ${tracks} >> index.html
printf "           <ul>\n" >> index.html
printf "              <li/><a href=\"%s/%s/%s/GenProps_lin\">General Properties</a>\n" ${web} ${release} ${tracks} >> index.html
printf "              <li/><a href=\"%s/%s/%s/HitProps_lin\">Hit Properties</a>\n" ${web} ${release} ${tracks} >> index.html
if [ "${tracks}" == genTks ] ; then 
printf "              <li/><a href=\"%s/%s/%s/TkBuilding_lin\">Track Building</a>\n" ${web} ${release} ${tracks} >> index.html
fi
printf "           </ul>\n" >> index.html
printf "        <h3> %s Distributions (Log) </h3>\n" ${tracks} >> index.html
printf "           <ul>\n" >> index.html
printf "              <li/><a href=\"%s/%s/%s/GenProps_log\">General Properties</a>\n" ${web} ${release} ${tracks} >> index.html
printf "              <li/><a href=\"%s/%s/%s/HitProps_log\">Hit Properties</a>\n" ${web} ${release} ${tracks} >> index.html
if [ "${tracks}" == genTks ] ; then 
printf "              <li/><a href=\"%s/%s/%s/TkBuilding_log\">Track Building</a>\n" ${web} ${release} ${tracks} >> index.html
fi
printf "           </ul>\n" >> index.html
printf "     </body>\n" >> index.html
printf "</html>\n" >> index.html
