#pragma once

#include <jni.h>
#include <cstdio>
#include "LocalPlayerCharacter.h"

class WakfuGameEntity final
{
public:
    WakfuGameEntity(JNIEnv* p_env);
    LocalPlayerCharacter* GetLocalPlayerCharacter();
    bool Init();
    jobject get_class_instance();

private:
    jclass class_ptr;
    jobject class_instance;
    JNIEnv* p_env;
    const char name[16] = { "WakfuGameEntity" };
};
