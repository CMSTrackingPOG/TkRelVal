#! /bin/bash

release=$1
web="https://cmsdoc.cern.ch/Physics/tracking/validation/DATA"

printf "<html>\n" > index.html               
#printf "     <body text=\"#000000\" bgcolor=\"#FFFFFF\" link=\"#FFFF00\" vlink=\"#FF00FF\">\n" >> index.html  
printf "  <title>Packed Candidate Distributions</title>\n" >> index.html
printf "     <body>\n" >> index.html  
printf "        <h3> Packed Candidate Distributions (Linear) </h3>\n" >> index.html
printf "           <ul>\n" >> index.html
printf "              <li/><a href=\"%s/%s/PackCand/MatchedTks_lin\">Matched Tracks</a>\n" ${web} ${release} >> index.html
printf "              <li/><a href=\"%s/%s/PackCand/LostTks_lin\">Lost Tracks</a>\n" ${web} ${release} >> index.html
printf "           </ul>\n" >> index.html
printf "        <h3> Packed Candidate Distributions (Log) </h3>\n" >> index.html
printf "           <ul>\n" >> index.html
printf "              <li/><a href=\"%s/%s/PackCand/MatchedTks_log\">Matched Tracks</a>\n" ${web} ${release} >> index.html
printf "             <li/><a href=\"%s/%s/PackCand/LostTks_log\">Lost Tracks</a>\n" ${web} ${release} >> index.html
printf "           </ul>\n" >> index.html
printf "     </body>\n" >> index.html
printf "</html>\n" >> index.html
