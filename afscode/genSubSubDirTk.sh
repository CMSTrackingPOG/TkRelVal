#! /bin/bash

release=$1
tracks=$2

printf "<html>\n" > index.html               
#printf "     <body text=\"#000000\" bgcolor=\"#FFFFFF\" link=\"#FFFF00\" vlink=\"#FF00FF\">\n" >> index.html  
printf "  <title>Track Distributions</title>\n" >> index.html
printf "<head>\n" >> index.html
printf "  <meta charset=\"UTF-8\">\n" >> index.html
printf "  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n" >> index.html
printf "  <title>dEdx Distributions</title>\n" >> index.html
printf "  <link rel="stylesheet" href="style.css">\n" >> index.html
printf "</head>\n" >> index.html
printf "     <body>\n" >> index.html  
printf "        <h3> %s Distributions (Linear) </h3>\n" ${tracks} >> index.html
printf "           <ul>\n" >> index.html
printf "              <li/><a href=\"GenProps_lin\">General Properties</a>\n"  >> index.html
printf "              <li/><a href=\"HitProps_lin\">Hit Properties</a>\n"  >> index.html
if [ "${tracks}" != HPTks_0to1 ] ; then 
printf "              <li/><a href=\"HitEff_lin\">Hit Efficiency from HitPattern</a>\n"  >> index.html
printf "              <li/><a href=\"HitEffAll_lin\">Hit Efficiency from HitPatternAll</a>\n"  >> index.html
if [ "${tracks}" == HPTks_gt1 ] ; then
printf "              <li/><a href=\"HitEffBX_lin\">Hit Efficiency BX from HitPattern</a>\n"  >> index.html
fi
if [ "${tracks}" != genTks ] ; then 
printf "              <li/><a href=\"HitEffSL_lin\">Hit Efficiency SCALLUMI from HitPattern</a>\n"  >> index.html
printf "              <li/><a href=\"HitEffSLAll_lin\">Hit Efficiency SCALLUMI from HitPatternAll</a>\n"  >> index.html
fi
fi
printf "              <li/><a href=\"PU_lin\">Pileup Monitoring</a>\n"  >> index.html
if [ "${tracks}" == genTks ] ; then 
printf "              <li/><a href=\"TkBuilding_lin\">Track Building</a>\n"  >> index.html
fi
printf "              <li/><a href=\"LSan_lin\">Lumi Section Analysis</a>\n"  >> index.html
printf "           </ul>\n" >> index.html
printf "        <h3> %s Distributions (Log) </h3>\n" ${tracks} >> index.html
printf "           <ul>\n" >> index.html
printf "              <li/><a href=\"GenProps_log\">General Properties</a>\n"  >> index.html
printf "              <li/><a href=\"HitProps_log\">Hit Properties</a>\n"  >> index.html
if [ "${tracks}" != HPTks_0to1 ] ; then 
printf "              <li/><a href=\"HitEff_log\">Hit Efficiency from HitPattern</a>\n"  >> index.html
printf "              <li/><a href=\"HitEffAll_log\">Hit Efficiency from HitPatternAll</a>\n"  >> index.html
if [ "${tracks}" == HPTks_gt1 ] ; then
printf "              <li/><a href=\"HitEffBX_log\">Hit Efficiency BX from HitPattern</a>\n"  >> index.html
fi
if [ "${tracks}" != genTks ] ; then 
printf "              <li/><a href=\"HitEffSL_log\">Hit Efficiency SCALLUMI from HitPattern</a>\n"  >> index.html
printf "              <li/><a href=\"HitEffSLAll_log\">Hit Efficiency SCALLUMI from HitPatternAll</a>\n"  >> index.html
fi
fi
printf "              <li/><a href=\"PU_log\">Pileup Monitoring</a>\n"  >> index.html
if [ "${tracks}" == genTks ] ; then 
printf "              <li/><a href=\"TkBuilding_log\">Track Building</a>\n"  >> index.html
fi
printf "              <li/><a href=\"LSan_log\">LumiSection Analysis</a>\n"  >> index.html
printf "           </ul>\n" >> index.html
printf "     </body>\n" >> index.html
printf "</html>\n" >> index.html
