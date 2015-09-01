#! /bin/bash

release=$1
web="https://cmsdoc.cern.ch/Physics/tracking/validation/DATA"

printf "<html>\n" > index.html               
#printf "     <body text=\"#000000\" bgcolor=\"#FFFFFF\" link=\"#FFFF00\" vlink=\"#FF00FF\">\n" >> index.html  
printf "  <title>dEdx Distributions</title>\n" >> index.html
printf "     <body>\n" >> index.html  
printf "          <a href=\"%s/%s/dEdx/PO_lin\">dEdx DQMHarm2PO (linear)</a>\n" ${web} ${release} >> index.html
printf "          <br />\n" >> index.html    
printf "          <a href=\"%s/%s/dEdx/SO_lin\">dEdx DQMHarm2SO (linear)</a>\n" ${web} ${release} >> index.html
printf "          <br />\n" >> index.html    
printf "          <a href=\"%s/%s/dEdx/SP_lin\">dEdx DQMHarm2SP (linear)</a>\n" ${web} ${release} >> index.html
printf "          <br />\n" >> index.html    
printf "          <a href=\"%s/%s/dEdx/HitInfo_lin\">dEdxHitInfo (linear)</a>\n" ${web} ${release} >> index.html
printf "          <br />\n" >> index.html    
printf "          <a href=\"%s/%s/dEdx/PO_log\">dEdx DQMHarm2PO (log)</a>\n" ${web} ${release} >> index.html
printf "          <br />\n" >> index.html    
printf "          <a href=\"%s/%s/dEdx/SO_log\">dEdx DQMHarm2SO (log)</a>\n" ${web} ${release} >> index.html
printf "          <br />\n" >> index.html    
printf "          <a href=\"%s/%s/dEdx/SP_log\">dEdx DQMHarm2SP (log)</a>\n" ${web} ${release} >> index.html
printf "          <br />\n" >> index.html    
printf "          <a href=\"%s/%s/dEdx/HitInfo_log\">dEdxHitInfo (log)</a>\n" ${web} ${release} >> index.html
printf "     </body>\n" >> index.html
printf "</html>\n" >> index.html
