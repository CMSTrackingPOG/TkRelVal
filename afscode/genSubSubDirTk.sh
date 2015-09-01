#! /bin/bash

release=$1
tracks=$2
web="https://cmsdoc.cern.ch/Physics/tracking/validation/DATA"

printf "<html>\n" > index.html               
#printf "     <body text=\"#000000\" bgcolor=\"#FFFFFF\" link=\"#FFFF00\" vlink=\"#FF00FF\">\n" >> index.html  
printf "  <title>Track Distributions</title>\n" >> index.html
printf "     <body>\n" >> index.html  
printf "          <a href=\"%s/%s/%s/GenProps_lin\">General Properties (linear)</a>\n" ${web} ${release} ${tracks} >> index.html
printf "          <br />\n" >> index.html    
printf "          <a href=\"%s/%s/%s/HitProps_lin\">Hit Properties (linear)</a>\n" ${web} ${release} ${tracks} >> index.html
if [ "${tracks}" == genTks ] ; then 
printf "          <br />\n" >> index.html    
printf "          <a href=\"%s/%s/%s/TkBuilding_lin\">Track Building (linear)</a>\n" ${web} ${release} ${tracks} >> index.html
fi
printf "          <br />\n" >> index.html    
printf "          <a href=\"%s/%s/%s/GenProps_log\">General Properties (log)</a>\n" ${web} ${release} ${tracks} >> index.html
printf "          <br />\n" >> index.html    
printf "          <a href=\"%s/%s/%s/HitProps_log\">Hit Properties (log)</a>\n" ${web} ${release} ${tracks} >> index.html
if [ "${tracks}" == genTks ] ; then 
printf "          <br />\n" >> index.html    
printf "          <a href=\"%s/%s/%s/TkBuilding_log\">Track Building (log)</a>\n" ${web} ${release} ${tracks} >> index.html
fi
printf "     </body>\n" >> index.html
printf "</html>\n" >> index.html
