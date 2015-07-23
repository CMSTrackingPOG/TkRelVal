#! /bin/bash

####
search_dir=$1
####

printf "                    <LI>%s\n" ${search_dir}
printf "                        <UL>\n"

for i in $(ls -dr ${search_dir}*) ;
do

dir=$(echo ${i%%/}) 
printf "                            <LI><A HREF=\"http://cmsdoc.cern.ch/cms/Physics/tracking/validation/DATA/%s/index.html\">%s</A></LI>\n" ${dir} ${dir} #>> ${search_dir}.list

done

printf "                        </UL>\n"
printf "                    </LI>\n"
printf "                    <BR>\n"
printf "                    <BR>\n"

