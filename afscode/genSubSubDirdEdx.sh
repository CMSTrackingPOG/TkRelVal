#! /bin/bash

printf "<html>\n" > index.html               
#printf "     <body text=\"#000000\" bgcolor=\"#FFFFFF\" link=\"#FFFF00\" vlink=\"#FF00FF\">\n" >> index.html  
printf "  <title>dEdx Distributions</title>\n" >> index.html
printf "     <body>\n" >> index.html  
printf "        <h3> dEdx Distributions (Linear) </h3>\n" >> index.html
printf "           <ul>\n   " >> index.html
printf "              <li/><a href=\"PO_lin\">dEdx DQMHarm2PO</a>\n" >> index.html
printf "              <li/><a href=\"SO_lin\">dEdx DQMHarm2SO</a>\n" >> index.html
printf "              <li/><a href=\"SP_lin\">dEdx DQMHarm2SP</a>\n" >> index.html
printf "              <li/><a href=\"HitInfo_lin\">dEdxHitInfo</a>\n" >> index.html
printf "           </ul>\n" >> index.html
printf "        <h3> dEdx Distributions (Log) </h3>\n" >> index.html
printf "           <ul>\n   " >> index.html
printf "              <li/><a href=\"PO_log\">dEdx DQMHarm2PO</a>\n" >> index.html
printf "              <li/><a href=\"SO_log\">dEdx DQMHarm2SO</a>\n" >> index.html
printf "              <li/><a href=\"SP_log\">dEdx DQMHarm2SP</a>\n" >> index.html
printf "              <li/><a href=\"HitInfo_log\">dEdxHitInfo</a>\n" >> index.html
printf "           </ul>\n" >> index.html
printf "     </body>\n" >> index.html
printf "</html>\n" >> index.html
