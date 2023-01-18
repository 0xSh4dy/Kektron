#ifndef HELPERS_HPP
#define HELPERS_HPP
#include<windows.h>

bool InvalidHandleCheck(HANDLE handle,const char* message){
    if(handle==INVALID_HANDLE_VALUE || handle==NULL){
          MessageBoxA(NULL,message,"Error",MB_OK);
          return true;
    }
    return false;
}
#endif // HELPERS_HPP
