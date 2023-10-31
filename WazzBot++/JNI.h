#pragma once

#include <memory>

#include <Windows.h>
#include <jni.h>

#include "WakfuGameEntity.h"

class JNI final 
{
public:
	JNI()
	{
		{
			jint result = JNI_GetCreatedJavaVMs(&p_jvm, 1, nullptr);

			if (result != 0)
			{
				printf("[-] JNI() failed to initialize p_jvm\n");
				MessageBoxA(0, "ERROR", "Check console", MB_ICONASTERISK);
			}

			p_jvm->AttachCurrentThread((void**)&p_env, nullptr);
		}
		
		{
			p_wakfu_game_entity = std::make_unique<WakfuGameEntity>(p_env);
		}

		is_init = true;
	}

	~JNI()
	{
		p_jvm->DetachCurrentThread();

		is_init = false;
	}

	bool GetInit()
	{
		return is_init;
	}

	JNIEnv* GetEnv()
	{
		return p_env;
	}
public:
	std::unique_ptr<WakfuGameEntity> p_wakfu_game_entity;
private:
	JavaVM* p_jvm;
	JNIEnv* p_env;

	bool is_init{ false };
};

inline std::unique_ptr<JNI> p_jni;
