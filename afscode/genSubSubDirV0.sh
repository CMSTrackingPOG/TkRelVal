#! /bin/bash


printf "<html>\n" > index.html               
#printf "     <body text=\"#000000\" bgcolor=\"#FFFFFF\" link=\"#FFFF00\" vlink=\"#FF00FF\">\n" >> index.html  
printf "  <title>V0 Monitoring Distributions</title>\n" >> index.html
printf "     <body>\n" >> index.html  
printf "        <h3> V0 Monitoring Distributions (Linear) </h3>\n" >> index.html
printf "           <ul>\n   " >> index.html
printf "              <li/><a href=\"Ks_lin\">Ks</a>\n"  >> index.html
printf "              <li/><a href=\"Ks_Lxy16_lin\">Ks Lxy16</a>\n"  >> index.html
printf "              <li/><a href=\"Lambda_lin\">Lambda</a>\n"  >> index.html
printf "              <li/><a href=\"Lambda_Lxy16_lin\">Lambda Lxy16</a>\n"  >> index.html
printf "           </ul>\n" >> index.html
printf "        <h3> V0 Monitoring Distributions (Log) </h3>\n" >> index.html
printf "           <ul>\n   " >> index.html
printf "              <li/><a href=\"Ks_log\">Ks</a>\n"  >> index.html
printf "              <li/><a href=\"Ks_Lxy16_log\">Ks Lxy16</a>\n"  >> index.html
printf "              <li/><a href=\"Lambda_log\">Lambda</a>\n"  >> index.html
printf "              <li/><a href=\"Lambda_Lxy16_log\">Lambda Lxy16</a>\n"  >> index.html
printf "           </ul>\n" >> index.html
printf "     </body>\n" >> index.html
printf "</html>\n" >> index.html
