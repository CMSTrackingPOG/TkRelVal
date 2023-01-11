#! /bin/bash

printf "<html>\n" > index.html               
#printf "     <body text=\"#000000\" bgcolor=\"#FFFFFF\" link=\"#FFFF00\" vlink=\"#FF00FF\">\n" >> index.html  
printf "  <title>Packed Candidate Distributions</title>\n" >> index.html
printf "     <body>\n" >> index.html  
printf "        <h3> Packed Candidate Distributions (Linear) </h3>\n" >> index.html
printf "           <ul>\n" >> index.html
printf "              <li/><a href=\"MatchedTks_lin\">Matched Tracks</a>\n"  >> index.html
printf "              <li/><a href=\"LostTks_lin\">Lost Tracks</a>\n"  >> index.html
printf "           </ul>\n" >> index.html
printf "        <h3> Packed Candidate Distributions (Log) </h3>\n" >> index.html
printf "           <ul>\n" >> index.html
printf "              <li/><a href=\"MatchedTks_log\">Matched Tracks</a>\n"  >> index.html
printf "             <li/><a href=\"LostTks_log\">Lost Tracks</a>\n"  >> index.html
printf "           </ul>\n" >> index.html
printf "     </body>\n" >> index.html
printf "</html>\n" >> index.html
