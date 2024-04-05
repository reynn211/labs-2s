#ifndef _STUDENT_H_
#define _STUDENT_H_

#define STR_SIZE 24

typedef enum { EMBEDDED, EXTERNAL, AGP, PCI } VideoControllerType;
typedef enum { SCSI_IDE, ATA_SATA } HDDType;
typedef enum { WINDOWS, LINUX, MACOS, OTHER } OSType;

typedef struct {
    char surname[STR_SIZE];
    int memorySize; // MB
    VideoControllerType videoController;
    int videoMemory; // MB
    HDDType hddType;
    int hddCount;
    int totalHDDCapacity; // GB
    int integratedControllers;
    int externalDevices;
    OSType os;
} Student;

#endif
