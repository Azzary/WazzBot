#include "WakfuGameEntity.h"

WakfuGameEntity::WakfuGameEntity(JNIEnv* p_env)
    : p_env(p_env)
{
    Init();
}

LocalPlayerCharacter* WakfuGameEntity::GetLocalPlayerCharacter()
{
    jmethodID method_id = p_env->GetMethodID(class_ptr, "k", "()Lblc;");
    if (method_id == nullptr)
    {
        printf("[-]GetLocalPlayerCharacter Failed to get %s method id\n", name);
        return nullptr;
    }
    jobject local_player_character = p_env->CallObjectMethod(class_instance, method_id);
    if (local_player_character == nullptr)
    {
        printf("[-]GetLocalPlayerCharacter Failed to get %s class instance\n", name);
        return nullptr;
    }
    return new LocalPlayerCharacter(p_env, local_player_character);
}

bool WakfuGameEntity::Init()
{
    class_ptr = p_env->FindClass("aYA");
    if (class_ptr == nullptr)
    {
        printf("[-] Failed to get %s class pointer\n", name);
        return false;
    }
    jfieldID class_instance_field_id = p_env->GetStaticFieldID(class_ptr, "d", "LaYA;");
    if (class_instance_field_id == nullptr)
    {
        printf("[-] Failed to get %s class field id\n", name);
        return false;
    }
    class_instance = p_env->GetStaticObjectField(class_ptr, class_instance_field_id);
    if (class_instance == nullptr)
    {
        printf("[-] Failed to get %s class instance\n", name);
    }
}

jobject WakfuGameEntity::get_class_instance()
{
    return class_instance;
}
