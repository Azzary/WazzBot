#include "LocalPlayerCharacter.h"

LocalPlayerCharacter::LocalPlayerCharacter(JNIEnv* p_env, jobject player_instance)
    : p_env(p_env), player_instance(player_instance)
{
}

void LocalPlayerCharacter::move(jint x, jint y, jshort z)
{
    jobject playerInstance = player_instance;
    if (playerInstance == nullptr)
    {
        printf("[-]GetPlayerPosition Failed to get playerInstance\n");
        return;
    }
    jclass playerClass = p_env->GetObjectClass(playerInstance);
    jmethodID method_id = p_env->GetMethodID(playerClass, "a", "(IISZZ)Z");
    if (method_id == nullptr)
    {
        printf("[-]move Failed to get method id\n");
        return;
    }

    printf("call move\n");
    jboolean result = p_env->CallBooleanMethod(playerInstance, method_id, x, y, z, false, true);
    printf("move called with result: %d\n", result);
    printf("move called\n");
}


void LocalPlayerCharacter::UpdatePlayerPosition()
{
    return;
    jobject playerInstance = player_instance;
    jclass playerClass = p_env->GetObjectClass(playerInstance);
    if (playerInstance == nullptr)
    {
        printf("[-]GetPlayerPosition Failed to get playerInstance\n");
        return;
    }
    jmethodID method_id = p_env->GetMethodID(playerClass, "T_", "()LaDE;");
    if (method_id == nullptr)
    {
        printf("[-]move Failed to get method id\n");
        return;
    }
    jobject vector3Postion = p_env->CallObjectMethod(playerInstance, method_id);

    jclass vector3Class = p_env->GetObjectClass(vector3Postion);

    jfieldID xFieldId = p_env->GetFieldID(vector3Class, "c", "I");
    jfieldID yFieldId = p_env->GetFieldID(vector3Class, "d", "I");
    jfieldID zFieldId = p_env->GetFieldID(vector3Class, "e", "S");

    jint x = p_env->GetIntField(vector3Postion, xFieldId);
    jint y = p_env->GetIntField(vector3Postion, yFieldId);
    jshort z = p_env->GetShortField(vector3Postion, zFieldId);
    last_x = x;
    last_y = y;
    last_z = z;
    printf("Player position: %d %d %d\n", x, y, z);
}
