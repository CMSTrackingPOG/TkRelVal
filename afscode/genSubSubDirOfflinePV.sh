#! /bin/bash


printf "<html>\n" > index.html               
#printf "     <body text=\"#000000\" bgcolor=\"#FFFFFF\" link=\"#FFFF00\" vlink=\"#FF00FF\">\n" >> index.html  
printf "  <title>OfflinePV Distributions</title>\n" >> index.html
printf "<head>\n" >> index.html
printf "  <meta charset=\"UTF-8\">\n" >> index.html
printf "  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n" >> index.html
printf "  <title>dEdx Distributions</title>\n" >> index.html
printf "  <link rel="stylesheet" href="style.css">\n" >> index.html
printf "</head>\n" >> index.html
printf "     <body>\n" >> index.html  
printf "        <h3> Primary Vertices Distributions (Linear) </h3>\n" >> index.html
printf "           <ul>\n" >> index.html
printf "              <li/><a href=\"Alignment_lin\">PV Alignment</a>\n"  >> index.html
printf "              <li/><a href=\"ResPV_lin\">PV Resolution</a>\n"  >> index.html
printf "              <li/><a href=\"ResOtherV_lin\">OtherV Resolution</a>\n"  >> index.html
printf "              <li/><a href=\"offlineBS_lin\">Offline Beamspot</a>\n"  >> index.html
printf "              <li/><a href=\"offlinePVs_lin\">Offline Primary Vertices</a>\n"  >> index.html
printf "           </ul>\n" >> index.html
printf "        <h3> Primary Vertices Distributions (Log) </h3>\n" >> index.html
printf "           <ul>\n" >> index.html
printf "              <li/><a href=\"Alignment_log\">PV Alignment</a>\n"  >> index.html
printf "              <li/><a href=\"ResPV_log\">PV Resolution</a>\n"  >> index.html
printf "              <li/><a href=\"ResOtherV_log\">OtherV Resolution</a>\n"  >> index.html
printf "              <li/><a href=\"offlineBS_log\">Offline Beamspot</a>\n"  >> index.html
printf "              <li/><a href=\"offlinePVs_log\">Offline Primary Vertices</a>\n"  >> index.html
printf "           </ul>\n" >> index.html
printf "     </body>\n" >> index.html
printf "</html>\n" >> index.html
