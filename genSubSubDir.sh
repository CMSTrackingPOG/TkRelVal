#! /bin/bash

release=$1
tracks=$2
web="https://cmsdoc.cern.ch/Physics/tracking/validation/DATA"

printf "<html>\n" > index.html               
#printf "     <body text=\"#000000\" bgcolor=\"#FFFFFF\" link=\"#FFFF00\" vlink=\"#FF00FF\">\n" >> index.html  
printf "  <title>Track Distributions</title>\n" >> index.html
printf "     <body>\n" >> index.html  
printf "          <a href=\"%s/%s/%s/GenProps\">General Properties</a>\n" ${web} ${release} ${tracks} >> index.html
printf "          <br />\n" >> index.html    
printf "          <a href=\"%s/%s/%s/HitProps\">Hit Properties</a>\n" ${web} ${release} ${tracks} >> index.html
printf "     </body>\n" >> index.html
printf "</html>\n" >> index.html
