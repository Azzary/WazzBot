#pragma once

#include <jni.h>

class LocalPlayerCharacter final
{
public:
    LocalPlayerCharacter(JNIEnv* p_env, jobject player_instance);
    void move(jint x, jint y, jshort z);
    void UpdatePlayerPosition();

    jint last_x = 0;
    jint last_y = 0;
    jshort last_z = 0;

private:
    JNIEnv* p_env;
    jobject player_instance;
    const char name[21] = { "LocalPlayerCharacter" };
};
