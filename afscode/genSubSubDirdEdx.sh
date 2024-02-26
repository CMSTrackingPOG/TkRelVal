#! /bin/bash

printf "<!DOCTYPE html>\n" > index.html
printf "<html lang=\"en\">\n" >> index.html
printf "<head>\n" >> index.html
printf "  <meta charset=\"UTF-8\">\n" >> index.html
printf "  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n" >> index.html
printf "  <title>dEdx Distributions</title>\n" >> index.html
printf "  <link rel="stylesheet" href="style.css">\n" >> index.html
printf "</head>\n" >> index.html
printf "<body>\n" >> index.html
printf "  <h1>dEdx Distributions</h1>\n" >> index.html
printf "  <h3> dEdx Distributions (Linear) </h3>\n" >> index.html
printf "    <ul>\n" >> index.html
printf "      <li><a href=\"PO_lin\">dEdx DQMHarm2PO</a></li>\n" >> index.html
printf "      <li><a href=\"SO_lin\">dEdx DQMHarm2SO</a></li>\n" >> index.html
printf "      <li><a href=\"SP_lin\">dEdx DQMHarm2SP</a></li>\n" >> index.html
printf "      <li><a href=\"HitInfo_lin\">dEdxHitInfo</a></li>\n" >> index.html
printf "    </ul>\n" >> index.html
printf "  <h3> dEdx Distributions (Log) </h3>\n" >> index.html
printf "    <ul>\n" >> index.html
printf "      <li><a href=\"PO_log\">dEdx DQMHarm2PO</a></li>\n" >> index.html
printf "      <li><a href=\"SO_log\">dEdx DQMHarm2SO</a></li>\n" >> index.html
printf "      <li><a href=\"SP_log\">dEdx DQMHarm2SP</a></li>\n" >> index.html
printf "      <li><a href=\"HitInfo_log\">dEdxHitInfo</a></li>\n" >> index.html
printf "    </ul>\n" >> index.html
printf "</body>\n" >> index.html
printf "</html>\n" >> index.html
