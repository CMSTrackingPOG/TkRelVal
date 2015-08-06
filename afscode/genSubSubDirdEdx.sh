#! /bin/bash

release=$1
web="https://cmsdoc.cern.ch/Physics/tracking/validation/DATA"

printf "<html>\n" > index.html               
#printf "     <body text=\"#000000\" bgcolor=\"#FFFFFF\" link=\"#FFFF00\" vlink=\"#FF00FF\">\n" >> index.html  
printf "  <title>dEdx Distributions</title>\n" >> index.html
printf "     <body>\n" >> index.html  
printf "          <a href=\"%s/%s/PO\">dEdx DQMHarm2PO</a>\n" ${web} ${release} >> index.html
printf "          <br />\n" >> index.html    
printf "          <a href=\"%s/%s/SO\">dEdx DQMHarm2SO</a>\n" ${web} ${release} >> index.html
printf "          <br />\n" >> index.html    
printf "          <a href=\"%s/%s/SP\">dEdx DQMHarm2SP</a>\n" ${web} ${release} >> index.html
printf "          <br />\n" >> index.html    
printf "          <a href=\"/%s/%s/HitInfo\">dEdxHitInfo</a>\n" ${web} ${release} >> index.html
printf "     </body>\n" >> index.html
printf "</html>\n" >> index.html
