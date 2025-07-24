set -x
doc="LsbTestReport"
#pandoc "$doc.md" -o "$doc.html" --standalone --css=CrcReportStyle.css
pandoc "$doc.md" -o "$doc.html" --standalone
