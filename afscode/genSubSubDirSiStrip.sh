#! /bin/bash

printf "<html>\n" > index.html               
#printf "     <body text=\"#000000\" bgcolor=\"#FFFFFF\" link=\"#FFFF00\" vlink=\"#FF00FF\">\n" >> index.html  
printf "  <title>SiStrip Distributions</title>\n" >> index.html
printf "     <body>\n" >> index.html  
printf "        <h3> SiStrip Distributions (Linear) </h3>\n" >> index.html
printf "           <ul>\n" >> index.html
printf "              <li/><a href=\"TEC_lin\">TEC ClusterCharge Plots</a>\n" >> index.html
printf "              <li/><a href=\"TIB_lin\">TIB ClusterCharge Plots</a>\n" >> index.html
printf "              <li/><a href=\"TID_lin\">TID ClusterCharge Plots</a>\n" >> index.html
printf "              <li/><a href=\"TOB_lin\">TOB ClusterCharge Plots</a>\n" >> index.html
printf "           </ul>\n" >> index.html
printf "        <h3> SiStrip Distributions (Log) </h3>\n" >> index.html
printf "           <ul>\n" >> index.html
printf "              <li/><a href=\"TEC_log\">TEC ClusterCharge Plots</a>\n" >> index.html
printf "              <li/><a href=\"TIB_log\">TIB ClusterCharge Plots</a>\n" >> index.html
printf "              <li/><a href=\"TID_log\">TID ClusterCharge Plots</a>\n" >> index.html
printf "              <li/><a href=\"TOB_log\">TOB ClusterCharge Plots</a>\n" >> index.html
printf "           </ul>\n" >> index.html
printf "     </body>\n" >> index.html
printf "</html>\n" >> index.html
