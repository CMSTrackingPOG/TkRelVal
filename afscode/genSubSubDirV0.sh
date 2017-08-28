#! /bin/bash

release=$1
web="https://cmsdoc.cern.ch/Physics/tracking/validation/DATA"

printf "<html>\n" > index.html               
#printf "     <body text=\"#000000\" bgcolor=\"#FFFFFF\" link=\"#FFFF00\" vlink=\"#FF00FF\">\n" >> index.html  
printf "  <title>V0 Monitoring Distributions</title>\n" >> index.html
printf "     <body>\n" >> index.html  
printf "        <h3> V0 Monitoring Distributions (Linear) </h3>\n" >> index.html
printf "           <ul>\n   " >> index.html
printf "              <li/><a href=\"%s/%s/V0/Ks_lin\">Ks</a>\n" ${web} ${release} >> index.html
printf "              <li/><a href=\"%s/%s/V0/Ks_Lxy16_lin\">Ks Lxy16</a>\n" ${web} ${release} >> index.html
printf "              <li/><a href=\"%s/%s/V0/Lambda_lin\">Lambda</a>\n" ${web} ${release} >> index.html
printf "              <li/><a href=\"%s/%s/V0/Lambda_Lxy16_lin\">Lambda Lxy16</a>\n" ${web} ${release} >> index.html
printf "           </ul>\n" >> index.html
printf "        <h3> V0 Monitoring Distributions (Log) </h3>\n" >> index.html
printf "           <ul>\n   " >> index.html
printf "              <li/><a href=\"%s/%s/V0/Ks_log\">Ks</a>\n" ${web} ${release} >> index.html
printf "              <li/><a href=\"%s/%s/V0/Ks_Lxy16_log\">Ks Lxy16</a>\n" ${web} ${release} >> index.html
printf "              <li/><a href=\"%s/%s/V0/Lambda_log\">Lambda</a>\n" ${web} ${release} >> index.html
printf "              <li/><a href=\"%s/%s/V0/Lambda_Lxy16_log\">Lambda Lxy16</a>\n" ${web} ${release} >> index.html
printf "           </ul>\n" >> index.html
printf "     </body>\n" >> index.html
printf "</html>\n" >> index.html
