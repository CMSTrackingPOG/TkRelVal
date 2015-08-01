#! /bin/bash

release=$1
web="https://cmsdoc.cern.ch/Physics/tracking/validation/DATA"

printf "<html>\n" > index.html               
#printf "     <body text=\"#000000\" bgcolor=\"#FFFFFF\" link=\"#FFFF00\" vlink=\"#FF00FF\">\n" >> index.html  
printf "  <title>%s Validation</title>\n" ${release} >> index.html
printf "     <body>\n" >> index.html  
printf "          <h3>%s Validation</h3>\n" ${release} >> index.html
printf "          <br />\n" >> index.html    
printf "          <a href=\"%s/%s/SiStrip\">SiStrip Plots</a>\n" ${web} ${release} >> index.html
printf "          <br />\n" >> index.html    
printf "          <a href=\"%s/%s/genTks\">generalTracks</a>\n" ${web} ${release} >> index.html
printf "          <br />\n" >> index.html    
printf "          <a href=\"%s/%s/HPTks\">highPurityTracks</a>\n" ${web} ${release} >> index.html
printf "     </body>\n" >> index.html
printf "</html>\n" >> index.html
