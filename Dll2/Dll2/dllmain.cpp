#include<string.h>
#include<stdio.h>
#pragma warning(disable:4996)
#if defined(WIN32) || defined(_WIN32)
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

#ifdef __cplusplus
extern "C" {
#endif

    EXPORT int foo(int param) {
        int ret = param + 1;
        // do C++ things
        return ret;
    }

    EXPORT int bar() {
        int ret = 0;
        // do C++ things
        return ret;
    }
    EXPORT int testKey(unsigned char* key,int keyLength) {
        FILE* fp = NULL;
        fp = fopen("D:\\C\\test.txt", "w+");
        fprintf(fp, "begin\t\n");
        fprintf(fp, (char*)key);
        fprintf(fp, "\n");
        unsigned char temp[12] = "testKeysada";
        memcpy(key, temp, 12);
        
        

        fprintf(fp, "end\t\n");
        fprintf(fp, (char *)key);
        
        fclose(fp);

        return 0;
    }
    EXPORT int testKey1( char* key, int keyLength) {
        FILE* fp = NULL;
        fp = fopen("D:\\C\\test1.txt", "w+");
        fprintf(fp, "begin\t\n");
        fprintf(fp, (char*)key);
        fprintf(fp, "\n");
        unsigned char temp[12] = "test1Keysad";
        memcpy(key, temp, 12);



        fprintf(fp, "end\t\n");
        fprintf(fp, (char*)key);

        fclose(fp);

        return 0;
    }

#ifdef __cplusplus
}
#endif