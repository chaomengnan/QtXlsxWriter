#include <QtGui>
#include "xlsxdocument.h"
#include "xlsxformat.h"

int main(int argc, char** argv)
{
    QGuiApplication(argc, argv);

    QXlsx::Document xlsx;
    xlsx.setColumn(0, 4, 20.0);

    QXlsx::Format *header = xlsx.createFormat();
    header->setFontBold(true);
    header->setFontSize(20);

    //Custom number formats
    QStringList numFormats;
    numFormats<<"Qt #"
             <<"yyyy-mmm-dd"
            <<"$ #,##0.00"
           <<"[red]0.00";
    xlsx.write(0, 0, "Raw data", header);
    xlsx.write(0, 1, "Format", header);
    xlsx.write(0, 2, "Shown value", header);
    for (int i=0; i<numFormats.size(); ++i) {
        int row = i+1;
        xlsx.write(row, 0, 100.0);
        xlsx.write(row, 1, numFormats[i]);
        QXlsx::Format *format = xlsx.createFormat();
        format->setNumberFormat(numFormats[i]);
        xlsx.write(row, 2, 100.0, format);
    }

    //Builtin number formats
    xlsx.addWorksheet();
    xlsx.setColumn(0, 4, 20.0);
    xlsx.write(0, 0, "Raw data", header);
    xlsx.write(0, 1, "Builtin Format", header);
    xlsx.write(0, 2, "Shown value", header);
    for (int i=0; i<50; ++i) {
        int row = i+1;
        int numFmt = i;
        xlsx.write(row, 0, 100.0);
        xlsx.write(row, 1, numFmt);
        QXlsx::Format *format = xlsx.createFormat();
        format->setNumberFormatIndex(numFmt);
        xlsx.write(row, 2, 100.0, format);
    }

    xlsx.save();
    return 0;
}