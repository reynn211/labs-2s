#include <stdio.h>
#include <stdlib.h>

#include "student.h"
#include <string.h>

VideoControllerType getVideoControllerType(const char *type) {
    if (strcmp(type, "EMBEDDED") == 0) return EMBEDDED;
    if (strcmp(type, "EXTERNAL") == 0) return EXTERNAL;
    if (strcmp(type, "AGP") == 0) return AGP;
    if (strcmp(type, "PCI") == 0) return PCI;
    return -1;
}

HDDType getHDDType(const char *type) {
    if (strcmp(type, "SCSI_IDE") == 0) return SCSI_IDE;
    if (strcmp(type, "ATA_SATA") == 0) return ATA_SATA;
    return -1;
}

OSType getOSType(const char *type) {
    if (strcmp(type, "WINDOWS") == 0) return WINDOWS;
    if (strcmp(type, "LINUX") == 0) return LINUX;
    if (strcmp(type, "MACOS") == 0) return MACOS;
    if (strcmp(type, "OTHER") == 0) return OTHER;
    return -1;
}

int student_read_txt(Student *s, FILE *in) {
    char videoControllerStr[STR_SIZE] = {0};
    char hddTypeStr[STR_SIZE] = {0};
    char osStr[STR_SIZE] = {0};

    fscanf(in, "%s", s->surname);
    fscanf(in, "%d", &(s->memorySize));
    fscanf(in, "%s", videoControllerStr);
    fscanf(in, "%d", &(s->videoMemory));
    fscanf(in, "%s", hddTypeStr);
    fscanf(in, "%d", &(s->hddCount));
    fscanf(in, "%d", &(s->totalHDDCapacity));
    fscanf(in, "%d", &(s->integratedControllers));
    fscanf(in, "%d", &(s->externalDevices));
    fscanf(in, "%s", osStr);

    s->videoController = getVideoControllerType(videoControllerStr);
    s->hddType = getHDDType(hddTypeStr);
    s->os = getOSType(osStr);

    return !feof(in);
}

int student_read_bin(Student *s, FILE *in)
{
    fread(s->surname, sizeof(char), STR_SIZE, in);
    fread(&(s->memorySize), sizeof(int), 1, in);
    fread(&(s->videoController), sizeof(VideoControllerType), 1, in);
    fread(&(s->videoMemory), sizeof(int), 1, in);
    fread(&(s->hddType), sizeof(HDDType), 1, in);
    fread(&(s->hddCount), sizeof(int), 1, in);
    fread(&(s->totalHDDCapacity), sizeof(int), 1, in);
    fread(&(s->integratedControllers), sizeof(int), 1, in);
    fread(&(s->externalDevices), sizeof(int), 1, in);
    fread(&(s->os), sizeof(OSType), 1, in);

    return !feof(in);
}

void student_write_bin(Student *s, FILE *out)
{
    fwrite(s->surname, sizeof(char), STR_SIZE, out);
    fwrite(&(s->memorySize), sizeof(int), 1, out);
    fwrite(&(s->videoController), sizeof(VideoControllerType), 1, out);
    fwrite(&(s->videoMemory), sizeof(int), 1, out);
    fwrite(&(s->hddType), sizeof(HDDType), 1, out);
    fwrite(&(s->hddCount), sizeof(int), 1, out);
    fwrite(&(s->totalHDDCapacity), sizeof(int), 1, out);
    fwrite(&(s->integratedControllers), sizeof(int), 1, out);
    fwrite(&(s->externalDevices), sizeof(int), 1, out);
    fwrite(&(s->os), sizeof(OSType), 1, out);
}

void student_print(Student *s)
{
    printf("Surname: %s\n", s->surname);
    printf("Memory Size: %d MB\n", s->memorySize);
    
    switch(s->videoController) {
        case EMBEDDED: printf("Video Controller: EMBEDDED\n"); break;
        case EXTERNAL: printf("Video Controller: EXTERNAL\n"); break;
        case AGP: printf("Video Controller: AGP\n"); break;
        case PCI: printf("Video Controller: PCI\n"); break;
        default: printf("Video Controller: UNKNOWN\n"); break;
    }
    
    printf("Video Memory: %d MB\n", s->videoMemory);
    
    switch(s->hddType) {
        case SCSI_IDE: printf("HDD Type: SCSI_IDE\n"); break;
        case ATA_SATA: printf("HDD Type: ATA_SATA\n"); break;
        default: printf("HDD Type: UNKNOWN\n"); break;
    }
    
    printf("HDD Count: %d\n", s->hddCount);
    printf("Total HDD Capacity: %d GB\n", s->totalHDDCapacity);
    printf("Integrated Controllers: %d\n", s->integratedControllers);
    printf("External Devices: %d\n", s->externalDevices);
    
    switch(s->os) {
        case WINDOWS: printf("OS: WINDOWS\n"); break;
        case LINUX: printf("OS: LINUX\n"); break;
        case MACOS: printf("OS: MACOS\n"); break;
        case OTHER: printf("OS: OTHER\n"); break;
        default: printf("OS: UNKNOWN\n"); break;
    }
    
    printf("\n");
}
