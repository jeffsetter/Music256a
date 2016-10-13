/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#ifndef BINARYDATA_H_40074662_INCLUDED
#define BINARYDATA_H_40074662_INCLUDED

namespace BinaryData
{
    extern const char*   Blue_qrc;
    const int            Blue_qrcSize = 88;

    extern const char*   Blue_qss;
    const int            Blue_qssSize = 3901;

    extern const char*   Default_qrc;
    const int            Default_qrcSize = 91;

    extern const char*   Default_qss;
    const int            Default_qssSize = 2078;

    extern const char*   Grey_qrc;
    const int            Grey_qrcSize = 88;

    extern const char*   Grey_qss;
    const int            Grey_qssSize = 3895;

    extern const char*   Salmon_qrc;
    const int            Salmon_qrcSize = 90;

    extern const char*   Salmon_qss;
    const int            Salmon_qssSize = 4125;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Number of elements in the namedResourceList array.
    const int namedResourceListSize = 8;

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes) throw();
}

#endif
