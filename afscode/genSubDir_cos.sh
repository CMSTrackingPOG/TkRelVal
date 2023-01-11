#! /bin/bash

printf "<html>\n" > index.html               
printf "  <title>%s Cosmics Validation</title>\n"  >> index.html
printf "     <body>\n" >> index.html  
printf "        <h2>%s Cosmics Validation</h2>\n"  >> index.html
printf "        <h3>Tracking/TrackParameters Distributions (Linear) </h3>\n" >> index.html
printf "           <ul>\n" >> index.html
printf "              <li/><a href=\"GenProps_lin\">General Properties</a>\n" >> index.html
printf "              <li/><a href=\"HitProps_lin\">Hit Properties</a>\n" >> index.html
printf "              <li/><a href=\"PU_lin\">PileUp Monitoring</a>\n" >> index.html
printf "              <li/><a href=\"SplitTk_lin\">Split Tracks</a>\n" >> index.html
printf "              <li/><a href=\"TkBuilding_lin\">Track Building</a>\n" >> index.html
printf "              <li/><a href=\"TkEff_lin\">Tracking Efficiency</a>\n" >> index.html
printf "           </ul>\n" >> index.html
printf "        <h3>Tracking/TrackParameters Distributions (Log) </h3>\n" >> index.html
printf "           <ul>\n" >> index.html
printf "              <li/><a href=\"GenProps_log\">General Properties</a>\n" >> index.html
printf "              <li/><a href=\"HitProps_log\">Hit Properties</a>\n" >> index.html
printf "              <li/><a href=\"PU_log\">PileUp Monitoring</a>\n" >> index.html
printf "              <li/><a href=\"SplitTk_log\">Split Tracks</a>\n" >> index.html
printf "              <li/><a href=\"TkBuilding_log\">Track Building</a>\n" >> index.html
printf "              <li/><a href=\"TkEff_log\">Tracking Efficiency</a>\n" >> index.html
printf "           </ul>\n" >> index.html
printf "     </body>\n" >> index.html
printf "</html>\n" >> index.html

