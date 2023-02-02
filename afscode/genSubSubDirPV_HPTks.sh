#! /bin/bash

printf "<html>\n" > index.html               
#printf "     <body text=\"#000000\" bgcolor=\"#FFFFFF\" link=\"#FFFF00\" vlink=\"#FF00FF\">\n" >> index.html  
printf "  <title>Tracking High Purity Tracks (0 < pT < 1 GeV) PV Distributions</title>\n" >> index.html
printf "     <body>\n" >> index.html  
printf "        <h3> Primary Vertices Distributions (Linear) </h3>\n" >> index.html
printf "           <ul>\n" >> index.html
printf "              <li/><a href=\"offline_lin\">Offline</a>\n"  >> index.html
#printf "              <li/><a href=\"pixel_lin\">Pixel</a>\n"  >> index.html
printf "           </ul>\n" >> index.html
printf "        <h3> Primary Vertices Distributions (Log) </h3>\n" >> index.html
printf "              <li/><a href=\"offline_log\">Offline</a>\n"  >> index.html
#printf "              <li/><a href=\"pixel_log\">Pixel</a>\n"  >> index.html
printf "           <ul>\n" >> index.html
printf "           </ul>\n" >> index.html
printf "     </body>\n" >> index.html
printf "</html>\n" >> index.html
