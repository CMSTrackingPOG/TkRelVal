#!/bin/bash

# Assign passed arguments to variables for better readability
refFile=$(basename "${1}")
refLabel="${2}"
newFile=$(basename "${3}")
newLabel="${4}"
refLumi="${5}"
newLumi="${6}"

# Start generating the HTML content
printf "<!DOCTYPE html>\n" > index.html
printf "<html lang=\"en\">\n" >> index.html
printf "<head>\n" >> index.html
printf "  <meta charset=\"UTF-8\">\n" >> index.html
printf "  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n" >> index.html
printf "  <title>Collisions Validation</title>\n" >> index.html
printf "  <link rel=\"stylesheet\" href=\"style.css\">\n" >> index.html
printf "</head>\n" >> index.html
printf "<body>\n" >> index.html
printf "  <h2>Collisions Validation</h2>\n" >> index.html

# Adding the statistics box if arguments are passed and add the statistics box if they are
if [[ -n "${refFile}" && -n "${refLabel}" && -n "${newFile}" && -n "${newLabel}" && -n "${refLumi}" && -n "${newLumi}" ]]; then
  printf "  <div class=\"stats-box\">\n" >> index.html
  printf "    <p>Reference: %s : %s. Lumi: %s fb^-1</p>\n" "${refLabel}" "${refFile}" "${refLumi}" >> index.html
  printf "    <p>Target   : %s : %s. Lumi: %s fb^-1</p>\n" "${newLabel}" "${newFile}" "${newLumi}" >> index.html
  printf "  </div>\n" >> index.html
fi

# Continue with the rest of the HTML content
printf "  <ul>\n" >> index.html
printf "    <li><a href=\"genTks\">General Tracks Plots</a></li>\n" >> index.html
printf "    <li><a href=\"HPTks_dzPV0p1\">High Purity (PV dz < 0.1) Tracks Plots</a></li>\n" >> index.html
printf "    <li><a href=\"HPTks_0to1\">High Purity (0 < pT < 1 GeV) Tracks Plots</a></li>\n" >> index.html
printf "    <li><a href=\"HPTks_gt1\">High Purity (pT > 1 GeV) Tracks Plots</a></li>\n" >> index.html
printf "    <li><a href=\"PackCand\">Packed Candidate Plots</a></li>\n" >> index.html
printf "    <li><a href=\"SiStrip\">SiStrip Plots</a></li>\n" >> index.html
printf "    <li><a href=\"dEdx\">dEdx Plots</a></li>\n" >> index.html
printf "    <li><a href=\"V0\">V0 Monitoring Plots</a></li>\n" >> index.html
printf "    <li><a href=\"OfflinePV\">Offline Primary Vertices Plots</a></li>\n" >> index.html
printf "    <li><a href=\"PV_HPTks\">Tracking High Purity Tracks (0 < pT < 1 GeV) Primary Vertices Plots</a></li>\n" >> index.html
printf "  </ul>\n" >> index.html
printf "</body>\n" >> index.html
printf "</html>\n" >> index.html
