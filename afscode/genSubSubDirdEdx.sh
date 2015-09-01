#! /bin/bash

release=$1
web="https://cmsdoc.cern.ch/Physics/tracking/validation/DATA"

printf "<html>\n" > index.html               
#printf "     <body text=\"#000000\" bgcolor=\"#FFFFFF\" link=\"#FFFF00\" vlink=\"#FF00FF\">\n" >> index.html  
printf "  <title>dEdx Distributions</title>\n" >> index.html
printf "     <body>\n" >> index.html  
printf "        <h3> dEdx Distributions (Linear) </h3>\n" >> index.html
printf "           <ul>\n   " >> index.html
printf "              <li/><a href=\"%s/%s/dEdx/PO_lin\">dEdx DQMHarm2PO</a>\n" ${web} ${release} >> index.html
printf "              <li/><a href=\"%s/%s/dEdx/SO_lin\">dEdx DQMHarm2SO</a>\n" ${web} ${release} >> index.html
printf "              <li/><a href=\"%s/%s/dEdx/SP_lin\">dEdx DQMHarm2SP</a>\n" ${web} ${release} >> index.html
printf "              <li/><a href=\"%s/%s/dEdx/HitInfo_lin\">dEdxHitInfo</a>\n" ${web} ${release} >> index.html
printf "           </ul>\n" >> index.html
printf "        <h3> dEdx Distributions (Log) </h3>\n" >> index.html
printf "           <ul>\n   " >> index.html
printf "              <li/><a href=\"%s/%s/dEdx/PO_log\">dEdx DQMHarm2PO</a>\n" ${web} ${release} >> index.html
printf "              <li/><a href=\"%s/%s/dEdx/SO_log\">dEdx DQMHarm2SO</a>\n" ${web} ${release} >> index.html
printf "              <li/><a href=\"%s/%s/dEdx/SP_log\">dEdx DQMHarm2SP</a>\n" ${web} ${release} >> index.html
printf "              <li/><a href=\"%s/%s/dEdx/HitInfo_log\">dEdxHitInfo</a>\n" ${web} ${release} >> index.html
printf "           </ul>\n" >> index.html
printf "     </body>\n" >> index.html
printf "</html>\n" >> index.html
