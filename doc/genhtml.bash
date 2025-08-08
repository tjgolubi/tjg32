set -x
doc="Manual"
pandoc "$doc.md" -o "$doc.html" --standalone --css=CrcReportStyle.css
